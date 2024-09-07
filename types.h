#ifndef COLLECTION_TYPES_H
#define COLLECTION_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t _u8;
typedef int8_t _i8;
typedef uint16_t _u16;
typedef uint32_t _u32;
typedef uintptr_t _ptr;
typedef uintptr_t _key;

typedef bool(BooleanPredicate)(const void* expected, const void* actual);
typedef void(VoidIterator)(const void* value);
typedef void(KeyValueIterator)(const _u16 key, const void* value);

#ifdef __cplusplus
}
#endif
#endif  // COLLECTION_TYPES_H
