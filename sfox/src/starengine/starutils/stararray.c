#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stararray.h"

SArray *
s_array_new(int clear, int size)
{
  SArray *array = malloc(sizeof(struct SArray));
  array->mem = calloc(size, sizeof(void *));
  array->clear = clear;
  array->len = size;
  array->firstfree = 0;

  return array;
}

void
s_array_push_back(SArray *array, void *data)
{
  if(array->firstfree == array->len)
    s_array_resize(array, (array->len+1)*2);
  array->mem[array->firstfree++] = data;
}

void *
s_array_pop_back(SArray *array)
{
  void *data;

  assert(array->firstfree != 0);
  data = array->mem[array->firstfree--];
  if(array->firstfree < array->len/2)
    s_array_resize(array, array->len/2);

  return data;
}

void
s_array_resize(SArray *array, unsigned int len)
{
  array->mem = realloc(array->mem, len*sizeof(void *));
  if(array->clear)
    memset(array->mem+len, 0, len*sizeof(void *));
  array->len = len;
}

void
s_array_free(SArray *array, freefunc func)
{
  if(func) {
    unsigned int i;
    for(i = 0; i < array->firstfree; i++)
      func(array->mem[i]);
  }
  free(array->mem);
  array->mem = NULL;
  free(array);
}
