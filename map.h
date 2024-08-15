#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define MAP_INDEX_NONE UINT16_MAX

typedef struct Map_t Map_t;

Map_t* MapCreate(_u16 capacity);
void MapDestroy(Map_t* map);

_u16 MapSize(const Map_t* map);
_u16 MapCapacity(const Map_t* map);

bool MapSet(Map_t* map, const _u16 key, void* value);
void* MapGet(const Map_t* map, const _u16 key);
bool MapRemove(Map_t* map, const _u16 key);
void MapClear(Map_t* map);

_u16 MapIndexOfKey(const Map_t* map, const _u16 key);
bool MapKeyExists(const Map_t* map, const _u16 key);

bool MapIsFull(const Map_t* map);
bool MapIsEmpty(const Map_t* map);

void MapForeach(const Map_t* map, KeyValueIterator iterator);

#ifdef __cplusplus
}
#endif

#endif  // MAP_H