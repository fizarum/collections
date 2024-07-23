#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

	typedef uint8_t _u8;
	typedef int8_t _i8;
	typedef uint16_t _u16;
	typedef uintptr_t _ptr;
	typedef uintptr_t _key;

#define ARRAY_INDEX_NONE UINT16_MAX

	typedef struct Array_t Array_t;

	Array_t* ArrayCreate(_u16 capcity);
	void ArrayDestroy(Array_t* array);
	void ArrayClear(Array_t* array);

	_u16 ArraySize(const Array_t* array);
	_u16 ArrayCapacity(const Array_t* array);

	bool ArrayAdd(Array_t* array, void* value);
	bool ArrayRemove(Array_t* array, void* value);

	void* ArrayValueAt(const Array_t* array, const _u16 index);
	void* ArrayLastValue(const Array_t* array);
	const _u16 ArrayIndexOf(const Array_t* array, void* value);
	const _u16 ArrayLastIndex(const Array_t* array);

	bool ArrayIsFull(const Array_t* array);
	bool ArrayIsEmpty(const Array_t* array);

	void ArrayForeach(const Array_t* array, void(callback)(void* value));

#ifdef __cplusplus
}
#endif

#endif  // ARRAY_H