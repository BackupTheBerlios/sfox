#ifndef STARARRAY_H
#define STARARRAY_H

typedef void (*freefunc)(void *object);

typedef struct SArray {
  void **mem;
  unsigned int len;

  /*Private*/
  int clear;
  unsigned int firstfree;
} SArray;

/*if clear is 1, allocate array with zeroed elements*/
extern SArray *s_array_new(int clear, int size);
extern void s_array_push_back(SArray *array, void *data);
extern void *s_array_pop_back(SArray *array);
extern void s_array_resize(SArray *array, unsigned int len);
/*if func!=NULL uses it on every elements of the array */
extern void s_array_free(SArray *array, freefunc func);

/*pointer to a SArray, return item i casted to type t*/
#define s_array_index(a,t,i) ((t)((a)->mem[i]))

#endif
