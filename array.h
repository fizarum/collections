#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define ARRAY_INDEX_NONE UINT16_MAX

typedef struct Array_t Array_t;

Array_t* ArrayCreate(_u16 capcity);
void ArrayDestroy(Array_t* array);

_u16 ArraySize(const Array_t* array);
_u16 ArrayCapacity(const Array_t* array);

bool ArrayAdd(Array_t* array, void* value);
bool ArrayRemove(Array_t* array, void* value);
void ArrayClear(Array_t* array);

void* ArrayValueAt(const Array_t* array, const _u16 index);
void* ArrayLastValue(const Array_t* array);
_u16 ArrayIndexOf(const Array_t* array, void* value);
_u16 ArrayLastIndex(const Array_t* array);

bool ArrayIsFull(const Array_t* array);
bool ArrayIsEmpty(const Array_t* array);

void ArrayForeach(const Array_t* array, VoidIterator iterator);

/**
 * @brief finds element in array
 * @param expected - value to compare with
 * @param predicate - function which may return true when value satisfy search
 * request
 */
void* ArrayFind(const Array_t* array, const void* expected,
                BooleanPredicate predicate);

#ifdef __cplusplus
}
#endif

#endif  // ARRAY_H