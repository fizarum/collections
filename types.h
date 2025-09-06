#ifndef COLLECTION_TYPES_H
#define COLLECTION_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define null ((void*)0);
typedef uint8_t _u8;
typedef int8_t _i8;
typedef uint16_t _u16;
typedef int16_t _i16;
typedef uint32_t _u32;
typedef int32_t _i32;
typedef uintptr_t _ptr;
typedef uintptr_t _key;

typedef bool(BooleanPredicate)(const void* expected, const void* actual);
typedef void(VoidIterator)(void* value);
typedef void(KeyValueIterator)(const _u16 key, const void* value);

#ifdef __cplusplus
}
#endif
#endif  // COLLECTION_TYPES_H
