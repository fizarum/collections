#include "array.h"

#include <stdlib.h>
#include <string.h>

typedef struct Array_t {
  // pointer on pointers of data
  _ptr* values;
  // count of added items in array
  _u16 size;
  // total capacity
  _u16 capacity;
} Array_t;

Array_t* ArrayCreate(_u16 capcity) {
  Array_t* array = (Array_t*)malloc(sizeof(Array_t));

  if (array == NULL) return NULL;

  array->capacity = capcity;
  array->size = 0;
  array->values = (_ptr*)calloc(capcity, sizeof(_ptr));
  return array;
}

void ArrayDestroy(Array_t* array) {
  if (array == NULL) return;

  free(array->values);
  free(array);
}

_u16 ArraySize(const Array_t* array) { return array != NULL ? array->size : 0; }

_u16 ArrayCapacity(const Array_t* array) {
  return array != NULL ? array->capacity : 0;
}

bool ArrayAdd(Array_t* array, void* value) {
  if (ArrayIsFull(array) == true) return false;
  array->values[array->size] = (_ptr)value;
  array->size++;
  return true;
}

bool ArrayRemove(Array_t* array, void* value) {
  _u16 indexToRemove = ArrayIndexOf(array, value);
  if (indexToRemove == ARRAY_INDEX_NONE) return false;

  array->values[indexToRemove] = 0;
  array->size--;
  for (_u16 index = indexToRemove; index < array->capacity; index++) {
    array->values[index] = array->values[index + 1];
  }
  return true;
}

bool ArrayRemoveIndex(Array_t* array, _u16 index) {
  if (index == ARRAY_INDEX_NONE) return false;
  if (index > ArrayLastIndex(array)) return false;

  array->values[index] = 0;
  array->size--;
  for (_u16 indexToUpdate = index; indexToUpdate < array->capacity;
       indexToUpdate++) {
    array->values[indexToUpdate] = array->values[indexToUpdate + 1];
  }
  return true;
}

void ArrayClear(Array_t* array) {
  memset(array->values, 0, sizeof(_ptr) * (array->capacity));
  array->size = 0;
}

void* ArrayValueAt(const Array_t* array, const _u16 index) {
  if (index != ARRAY_INDEX_NONE) {
    return (void*)array->values[index];
  }
  return NULL;
}

void* ArrayLastValue(const Array_t* array) {
  _u16 index = ArrayLastIndex(array);

  return (void*)ArrayValueAt(array, index);
}

_u16 ArrayIndexOf(const Array_t* array, void* value) {
  for (_u16 index = 0; index < array->size; index++) {
    if (array->values[index] == (_ptr)value) {
      return index;
    }
  }
  return ARRAY_INDEX_NONE;
}

_u16 ArrayLastIndex(const Array_t* array) {
  if (array->size == 0) return ARRAY_INDEX_NONE;
  return array->size - 1;
}

bool ArrayIsFull(const Array_t* array) {
  return array->size == array->capacity;
}

bool ArrayIsEmpty(const Array_t* array) { return array->size == 0; }

void ArrayForeach(const Array_t* array, VoidIterator iterator) {
  for (_u16 index = 0; index < array->size; index++) {
    void* value = (void*)(array->values[index]);
    iterator(value);
  }
}

void* ArrayFind(const Array_t* array, const void* expected,
                BooleanPredicate predicate) {
  for (_u16 index = 0; index < array->size; index++) {
    void* value = (void*)(array->values[index]);
    if (predicate(expected, value) == true) {
      return value;
    }
  }
  return NULL;
}