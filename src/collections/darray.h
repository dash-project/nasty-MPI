#ifndef __DARRAY_H
#define __DARRAY_H

#include <stdlib.h>
#include <stdarg.h>

typedef struct DArray_s
{
  int size;
  int capacity;
  size_t element_size;
  size_t expand_rate;
  void **contents;
} *DArray;


typedef int (DArray_sort_fn) (const void *a, const void *b);

DArray DArray_create(size_t element_size, size_t initial_capacity);

void DArray_destroy(DArray array);

void DArray_clear(DArray array);

int DArray_expand(DArray array);

int DArray_contract(DArray array);


int DArray_push(DArray array, void *el);

void *DArray_pop(DArray array);

void DArray_clear_destroy(DArray array);

void DArray_remove_all(DArray array, DArray to_remove);

int DArray_push_all(DArray dst, DArray src);

int DArray_ensure_capacity(DArray array, int minCapacity);

void DArray_sort(DArray array, DArray_sort_fn *compar);

#define DArray_last(A) ((A)->contents[(A)->size - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->size)
#define DArray_count(A) DArray_end(A)
#define DArray_capacity(A) ((A)->capacity)
#define DArray_free(E) free((E))


#define DARRAY_FOREACH(VAR, TYPE, ARRAY) \
  TYPE _temp; \
  TYPE VAR; \
  size_t _ii; \
  for (_ii = 0, VAR = (ARRAY)->contents[_ii]; _ii < DArray_end(ARRAY); _ii++, VAR = _temp = (ARRAY)->contents[_ii])


#define DEFAULT_EXPAND_RATE 10

static inline void DArray_set(DArray array, int i, void *el)
{
  if (i >= array->capacity) return;

  if (i >= array->size) array->size = i+1;

  array->contents[i] = el;
}

static inline void *DArray_get(DArray array, int i)
{
  if (i >= array->capacity) return NULL;
  return array->contents[i];
}

static inline void *DArray_remove(DArray array, int i)
{
  if (i >= array->capacity) return NULL;

  void *el = array->contents[i];

  array->contents[i] = NULL;

  return el;
}

static inline void *DArray_new(DArray array)
{
  if (array->element_size <= 0) return NULL;

  return calloc(1, array->element_size);
}

static inline int DArray_is_empty(DArray array)
{
  return (!array || DArray_count(array) <= 0);
}


/*
void* DArray_bsearch(const void **key, DArray array,
                         int (*sort_fn)(const void *, const void *));
*/

#endif
