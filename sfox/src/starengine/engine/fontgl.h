#ifndef FONTGL_H
#define FONTGL_H

typedef struct fontgl *fontgl;

struct fontgl_bbox {
  int width, height;
};

extern int fontgl_init();
extern void fontgl_quit();

extern fontgl fontgl_create(char *fontname, int resX, int resY,
                            unsigned int char_size);

extern inline void fontgl_set_color(fontgl font, float r, float g, float b);

extern void fontgl_DrawTextWithKerning( fontgl font, const unsigned char *str,
                                        float x, float y, 
                                        float pad, int kernOn);

extern void fontgl_printf(fontgl font, float x, float y, float pad, 
                          const char *fmt, ...);

extern void fontgl_get_bbox(fontgl font, unsigned char *str, float pad,
                            int kernOn, struct fontgl_bbox *bbox);

extern void fontgl_get_bbox_printf(fontgl font, struct fontgl_bbox *bbox,
                                   float pad, const char *fmt, ...);

extern inline int fontgl_get_size(fontgl font);

extern void fontgl_delete(fontgl font);

#endif
