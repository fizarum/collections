#include "map.h"

#include <stdlib.h>
#include <string.h>

typedef struct Map_t {
  _u16* keys;
  _ptr* values;
  _u16 size;
  _u16 capacity;
} Map_t;

Map_t* MapCreate(_u16 capacity) {
  Map_t* map = (Map_t*)malloc(sizeof(Map_t));

  if (map == NULL) return NULL;

  map->keys = (_u16*)calloc(capacity, sizeof(_u16));
  map->values = (_ptr*)calloc(capacity, sizeof(_ptr));
  map->size = 0;
  map->capacity = capacity;

  return map;
}

void MapDestroy(Map_t* map) {
  if (map == NULL) {
    return;
  }

  if (map->keys != NULL) {
    free(map->keys);
  }

  if (map->values != NULL) {
    free(map->values);
  }

  free(map);
}

_u16 MapSize(const Map_t* map) { return map->size; }

_u16 MapCapacity(const Map_t* map) { return map->capacity; }

bool MapSet(Map_t* map, const _u16 key, void* value) {
  _u16 keyIndex = MapIndexOfKey(map, key);

  // no existing index for key (new key) and map is full, cancel
  // adding new element
  if (keyIndex == MAP_INDEX_NONE && MapIsFull(map)) {
    return false;
  }

  // key not found, prepare place for new key & value
  if (keyIndex == MAP_INDEX_NONE) {
    keyIndex = map->size;
    map->size++;
  }

  map->keys[keyIndex] = key;
  map->values[keyIndex] = (_ptr)value;

  return true;
}

void* MapGet(const Map_t* map, const _u16 key) {
  _u16 keyIndex = MapIndexOfKey(map, key);

  if (keyIndex != MAP_INDEX_NONE) {
    return (void*)(map->values[keyIndex]);
  }
  return NULL;
}

bool MapRemove(Map_t* map, const _u16 key) {
  if (MapIsEmpty(map) == true) {
    return false;
  }

  _u16 keyIndex = MapIndexOfKey(map, key);

  if (keyIndex == MAP_INDEX_NONE) {
    return false;
  }

  for (_u16 index = keyIndex; index < map->size - 1; index++) {
    map->keys[index] = map->keys[index + 1];
    map->values[index] = map->values[index + 1];
  }

  _u16 lastIndex = map->size - 1;
  map->keys[lastIndex] = 0;
  map->values[lastIndex] = 0;

  map->size--;
  return true;
}

void MapClear(Map_t* map) {
  memset(map->keys, 0, map->size * sizeof(_u16));
  memset(map->values, 0, map->size * sizeof(_ptr));
  map->size = 0;
}

_u16 MapIndexOfKey(const Map_t* map, const _u16 key) {
  for (_u16 index = 0; index < map->size; index++) {
    if (key == map->keys[index]) {
      return index;
    }
  }
  return MAP_INDEX_NONE;
}

bool MapKeyExists(const Map_t* map, const _u16 key) {
  return MapIndexOfKey(map, key) != MAP_INDEX_NONE;
}

bool MapIsFull(const Map_t* map) { return map->size == map->capacity; }

bool MapIsEmpty(const Map_t* map) { return map->size == 0; }

void MapForeach(const Map_t* map, KeyValueIterator iterator) {
  if (iterator == NULL) return;

  for (_u16 index = 0; index < map->size; index++) {
    iterator(map->keys[index], (void*)(map->values[index]));
  }
}