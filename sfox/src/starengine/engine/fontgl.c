#ifdef _WIN32
# include <windows.h>
# include <GL/gl.h>
# include "starglext.h"
#endif /* _WIN32 */

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>

#include "starengine.h"
#include "stargl.h"
#include "starglu.h"

#include "fontgl.h"
#include "utility.h"

#define MAXTEXTURES 1024
#define MAXTEXTURESIZE 256
#define MAXSTRINGLENGTH 256

#define NUM_CHAR 256

#define myassert(x,y) assert((x)&&(y))

/****************************************************************************/

static FT_Library ftLibrary;

struct sLetter {
    float minU,minV;
    float maxU,maxV;
    int advanceX, advanceY;
    int top, left;
    int textureN;
    FT_BBox bbox;
};

struct fontgl {
    float r, g ,b;
    GLuint *tex_name;
    FT_Face Face;
    struct sLetter letter[NUM_CHAR];
    int resx, resy;
    int char_size;
    int maxY, numTextures;
};

/****************************************************************************/

static void fontgl_drawchar( fontgl font, unsigned char c, float x, float y);

/****************************************************************************/

int
fontgl_init()
{
    return FT_Init_FreeType(&ftLibrary);
}

void
fontgl_quit()
{
    FT_Done_FreeType( ftLibrary );
}

static void
fontgl_init_texturesGL(fontgl font, unsigned int char_size)
{
    size_t i;

    font->tex_name = malloc(sizeof(GLuint)*font->numTextures);
    assert(font->tex_name);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    assert(font->numTextures<MAXTEXTURES);
    glGenTextures(font->numTextures, font->tex_name);
    for( i = 0; i < font->numTextures; i++ ) {
	glBindTexture(GL_TEXTURE_2D, font->tex_name[i]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAXTEXTURESIZE, MAXTEXTURESIZE,
		     0, GL_ALPHA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }
}

/*FIXME: invalid value for the last 2 glyphs*/
static void
copyBitmap2Texture( fontgl font, int textureN, FT_Bitmap *bmp,
		    int width, int height, 
		    int posX, int posY )
{
    glBindTexture(GL_TEXTURE_2D, font->tex_name[textureN]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, posX, posY,
		    bmp->width, bmp->rows, 
		    GL_ALPHA, GL_UNSIGNED_BYTE,
		    bmp->buffer);
    PRINTGL_ERROR();
}


/*FIXME: OpenGL invalid value for the last 2 glyphs in Copybitmap2texture*/
fontgl
fontgl_create(char *fontname, int resX, int resY,
	      unsigned int char_size)
{
    fontgl font;
    FT_Face Face;
    FT_BitmapGlyph bmpGlyph;
    FT_Bitmap bmp;
    FT_Glyph glyph;
    FT_GlyphSlot slot;
    int charNumber, x, y, textureN;
    int err, c;
    size_t CharByTexture, CharByLine;

    font = malloc(sizeof(struct fontgl));
    assert(font);
    font->resx = resX;
    font->resy = resY;
    font->r = font->g = font->b = 1.0f;
    font->char_size = char_size;
    err = FT_New_Face(ftLibrary, fontname, 0, &font->Face);
    myassert(!err, "Can't load font");
    err = FT_Set_Pixel_Sizes( font->Face, char_size, char_size);
    myassert(!err, "Can't set size font");

    CharByLine = (int)floor(MAXTEXTURESIZE/char_size);
    CharByTexture = CharByLine*CharByLine;
    CharByTexture = CharByTexture>256?256:CharByTexture;
    font->numTextures = (int)ceil(256.0f/CharByTexture);

    fontgl_init_texturesGL(font, char_size);

    font->maxY = 0;
    Face = font->Face;
    for( c = 0; c < 253; c++ ) {
	unsigned int glyph_index = FT_Get_Char_Index( Face, c);
	err = FT_Load_Glyph( Face, glyph_index, FT_LOAD_NO_HINTING);
	assert(!err && "Can't load glyph.");

	err = FT_Get_Glyph( Face->glyph, &glyph );
	myassert(!err, "Can't get glyph.");

	FT_Glyph_Get_CBox(glyph, ft_glyph_bbox_pixels, &font->letter[c].bbox);

	if( font->maxY < font->letter[c].bbox.yMax && isprint(c) )
	    font->maxY = font->letter[c].bbox.yMax;

	err = FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 0 );
	myassert(!err, "Can't get glyph bitmap.");

	bmpGlyph = (FT_BitmapGlyph)glyph;
	bmp = bmpGlyph->bitmap;
	charNumber = c%CharByTexture;
	x = charNumber%CharByLine;
	y = (int)floor((float)charNumber/CharByLine);
	textureN = (int)floor((float)c/CharByTexture);

	slot = Face->glyph;
	font->letter[c].advanceX = slot->advance.x>>6;
	font->letter[c].advanceY = slot->advance.y>>6;
	font->letter[c].top = bmpGlyph->top;
	font->letter[c].left = bmpGlyph->left;
	font->letter[c].minU = (float)(x*char_size)/MAXTEXTURESIZE;
	font->letter[c].minV = (float)(y*char_size)/MAXTEXTURESIZE;
	font->letter[c].maxU = (float)bmp.width/MAXTEXTURESIZE+
			       font->letter[c].minU;
	font->letter[c].maxV = (float)bmp.rows/MAXTEXTURESIZE+
			       font->letter[c].minV;
	font->letter[c].textureN = textureN;

	copyBitmap2Texture( font, textureN, &bmp, MAXTEXTURESIZE, 
			    MAXTEXTURESIZE, char_size*x, char_size*y );
	FT_Done_Glyph( glyph );
    }
    return font;
}

static void /*FT_Vector*/
getKerning( fontgl font, FT_UInt prevGlyph, FT_UInt curGlyph, FT_Vector *delta )
{

    FT_Get_Kerning( font->Face, prevGlyph, curGlyph, ft_kerning_unfitted,
		    delta );
    delta->x = delta->x>>6;
    delta->y = delta->y>>6;
}

static void
fontgl_begin(fontgl font)
{
  glPushAttrib(GL_ENABLE_BIT|GL_POLYGON_BIT);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,font->resx,font->resy,0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void
fontgl_end(fontgl font)
{
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
  glPopAttrib();
}

void
fontgl_DrawTextWithKerning(fontgl font, const unsigned char *str,
			   float x, float y, 
			   float pad, int kernOn)
{
    FT_Vector kern;
    FT_UInt prevGlyph, curGlyph;

    if(*str=='\0')
	return;

    fontgl_begin(font);
    if( FT_HAS_KERNING(font->Face) && kernOn ) {
	curGlyph = FT_Get_Char_Index( font->Face, *str );
	getKerning( font, 0, curGlyph, &kern );

	while( *(str+1) != '\0' ) {
	    fontgl_drawchar(font, *str, x+kern.x, y+kern.y);
	    prevGlyph = curGlyph;
	    curGlyph = FT_Get_Char_Index(font->Face, *(str+1));
	    getKerning( font, prevGlyph, curGlyph, &kern );
	    x += font->letter[*str++].advanceX + kern.x + pad;
	}
	fontgl_drawchar(font, *str, x+kern.x, y+kern.y);
    } else {
	while( *str != '\0' ) {
	    fontgl_drawchar(font, *str, x, y);
	    x += font->letter[*str++].advanceX + pad;
	}
    }
    fontgl_end(font);
}

void
fontgl_printf(fontgl font, float x, float y, float pad, const char *fmt, ...)
{
    static char buffer[MAXSTRINGLENGTH];
    va_list liste;

    va_start(liste, fmt);
    vsprintf(buffer, fmt, liste);
    fontgl_DrawTextWithKerning(font, buffer, x, y, pad, 0);
    va_end(liste);
}

static void
fontgl_drawchar(fontgl font, unsigned char c, float x, float y)
{
    float width = (float)(font->letter[c].bbox.xMax-font->letter[c].bbox.xMin);
    float rows  = (float)(font->letter[c].bbox.yMax-font->letter[c].bbox.yMin);

    x += font->letter[c].left;
    y -= font->letter[c].bbox.yMin-font->maxY;

    glBindTexture(GL_TEXTURE_2D, font->tex_name[font->letter[c].textureN]);
    glBegin(GL_QUADS);
    glColor3f(font->r, font->g, font->b);
        
    glTexCoord2f(font->letter[c].minU, font->letter[c].maxV);
    glVertex2f(x,y);

    glTexCoord2f(font->letter[c].maxU, font->letter[c].maxV);
    glVertex2f(x+width,y);

    glTexCoord2f(font->letter[c].maxU, font->letter[c].minV);
    glVertex2f(x+width,y-rows);

    glTexCoord2f(font->letter[c].minU, font->letter[c].minV);
    glVertex2f(x,y-rows);

    glEnd();
    

    /*    glBindTexture(GL_TEXTURE_2D, 2);font->tex_name[0]);*/    
    /*glBegin(GL_QUADS);*/

    /*        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);*/
    /*
     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    
    glTexCoord2f(0, 0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(0+256,0);
    glTexCoord2f(1, 1);
    glVertex2f(0+256,0+256);
    glTexCoord2f(0,1);
    glVertex2f(0,0+256);
    glEnd();
    */
    
}

void
fontgl_get_bbox_printf(fontgl font, struct fontgl_bbox *bbox, float pad,
		       const char *fmt, ...)
{
    static char buffer[MAXSTRINGLENGTH];
    va_list liste;

    va_start(liste, fmt);
    vsprintf(buffer, fmt, liste);
    fontgl_get_bbox(font, buffer, pad, 1, bbox);
    va_end(liste);
}

void
fontgl_get_bbox(fontgl font, unsigned char *str, float pad, int kernOn, 
		struct fontgl_bbox *bbox)
{
  int maxy = 0, height;
  float x=0;
  FT_Vector kern;
  FT_UInt prevGlyph, curGlyph;
	
  if(*str=='\0')
      return;

  if( FT_HAS_KERNING(font->Face) && kernOn ) {
      curGlyph = FT_Get_Char_Index( font->Face, *str );
      getKerning( font, 0, curGlyph, &kern );

      while( *(str+1) != '\0' ) {
        prevGlyph = curGlyph;
        curGlyph = FT_Get_Char_Index( font->Face, *(str+1) );
        getKerning( font, prevGlyph, curGlyph, &kern );
        x += font->letter[*str].advanceX + kern.x + pad;
        height = (font->letter[*str].bbox.yMax-
		  font->letter[*str].bbox.yMin)+kern.y-font->letter[*str].bbox.yMin;
        maxy = (maxy>height)?maxy:height;
	str++;
      }
      x += font->letter[*str].advanceX + kern.x + pad;
      height = (font->letter[*str].bbox.yMax-
		font->letter[*str].bbox.yMin)+kern.y-
	       font->letter[*str].bbox.yMin;
        maxy = (maxy>height)?maxy:height;
    } else {
	while( *str != '\0' ) {
	    x += font->letter[*str].advanceX + pad;
	    height = (font->letter[*str].bbox.yMax-
		      font->letter[*str].bbox.yMin);
	    maxy = (maxy>height)?maxy:height;
      }
    }
  bbox->height = maxy;
  bbox->width = x;
}

inline int
fontgl_get_size(fontgl font)
{
    return font->char_size;
}

inline void
fontgl_set_color(fontgl font, float r, float g, float b)
{
    font->r = r; font->g = g; font->b = b;
}

void
fontgl_delete(fontgl font)
{
    glDeleteTextures(font->numTextures, font->tex_name);
    free(font->tex_name);
    FT_Done_Face(font->Face);
    free(font);
}
