#ifndef COLLECTION_TYPES_H
#define COLLECTION_TYPES_H

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

	typedef const bool (BooleanPredicate)(const void* expected, const void* actual);
	typedef void (VoidIterator)(const void* value);

#ifdef __cplusplus
}
#endif
#endif // COLLECTION_TYPES_H
