#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
# include <libgen.h>
#endif /*_WIN32*/
#include <math.h>
#include <png.h>

FILE *rawfile, *pngfile;
unsigned int side_size;

unsigned char *raw_buffer;

void
usage(char *arg0)
{
#ifndef _WIN32
  fprintf(stderr, "usage: %s file.raw file.png\n", basename(arg0));
#else
  fprintf(stderr, "usage: %s file.raw file.png\n", arg0);
#endif /*_WIN32*/
  fprintf(stderr, "file.raw must be a square raw 8bits image\n");
  exit(EXIT_FAILURE);
}

unsigned int
file_get_size(FILE *f)
{
  unsigned int size;

  fseek(rawfile, 0, SEEK_END);
  size = ftell(f);
  fseek(rawfile, 0, SEEK_SET);

  return size;
}

unsigned int
raw_get_side(unsigned int size)
{
  unsigned int s = (unsigned int)sqrt(size);
  
  if( (s*s) == size )
    return s;
  return 0;
}

int
main(int argc, char **argv)
{
  unsigned int i;
  png_byte **row_pointers;
  unsigned int filesize;
  png_infop info_ptr;
  png_structp png_ptr;

  if(argc!=3)
    usage(argv[0]);
  
  rawfile = fopen(argv[1], "rb");
  if(!rawfile)
    usage(argv[0]);

  filesize = file_get_size(rawfile);
  side_size = raw_get_side(filesize);
  if(side_size == 0)
    usage(argv[0]);
  
  raw_buffer = malloc(filesize);
  if( !raw_buffer ) {
    fprintf(stderr, "Not enough memory\n");
    fclose(rawfile);
    exit(EXIT_FAILURE);
  }

  if(fread(raw_buffer, sizeof(char), filesize, rawfile) != filesize) {
    fprintf(stderr, "Raw file reading error\n");
    fclose(rawfile);
    free(raw_buffer);
    exit(EXIT_FAILURE);
  }
  fclose(rawfile);
  

  /*Create png file*/
  pngfile = fopen(argv[2], "wb");
  if(!pngfile) {
    fprintf(stderr, "Can't open %s for writting\n", argv[2]);
    free(raw_buffer);
    exit(EXIT_FAILURE);
  }
  
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fprintf(stderr, "Can't create png file\n");
    free(raw_buffer);
    fclose(pngfile);
    exit(EXIT_FAILURE);
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!png_ptr) {
    png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    fprintf(stderr, "Can't create png file\n");
    free(raw_buffer);
    fclose(pngfile);
    exit(EXIT_FAILURE);
  }
  png_init_io(png_ptr, pngfile);

  png_set_IHDR(png_ptr, info_ptr, side_size, side_size, 8, PNG_COLOR_TYPE_GRAY,
	       PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
	       PNG_FILTER_TYPE_DEFAULT);
  
  row_pointers = malloc(sizeof(png_byte *)*side_size);
  if( !row_pointers ) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fprintf(stderr, "Not enough memory\n");
    free(raw_buffer);
    fclose(pngfile);
    exit(EXIT_FAILURE);
  }

  png_write_info (png_ptr, info_ptr);

  for(i = 0; i < side_size; i++)
    row_pointers[i] = raw_buffer+i*side_size;
  png_write_image(png_ptr, row_pointers);
  png_write_end(png_ptr, NULL);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(pngfile);

  exit(EXIT_SUCCESS);
}
