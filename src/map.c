
// TODO:

// #include "map.h"
// #include "funcs.h"

// #include <stdio.h>
// #include <stdlib.h>

// map_t map_create(enum datatype key_type, enum datatype value_type) {
//   map_t map;

//   map.keysize = type_map(key_type);
//   map.valuesize = type_map(value_type);
//   map.items = array_create(NULL, 3, PAIR);

//   return map;
// }
// void map_destroy(map_t *map) {
//   ASSERT(map, "NULL passed as parameter...\n");
//   array_destroy(&map->items);
// }

// bool map_set(map_t *map, void *key, void *value) {
//   pair_t keyval = {key, value};
//   if (map_contains(map, key)) {
//     pair_t *pair = map_get(map, key);
//     pair->second = value;
//     return true;
//   }
//   // TODO: make it check this has successfully pushed the item
//   array_pushback(&map->items, &keyval);
//   return true;
// }

// void *map_get(const map_t *map, const void *key);
// bool map_remove(map_t *map, const void *key) {
//   void *ptr = map_get(map, key);
//   if (!ptr) {
//     return false;
//   }
//   map_set(map, key, "");
//   return true;
// }
// bool map_contains(const map_t *map, const void *key) {
//   // optimize this...
//   for (usize i = 0; i < map->items.size; i++) {
//     if (((pair_t *)map->items.data)->first == key) {
//       return true;
//     }
//   }
//   return false;
// }
// void map_clear(map_t *map) {
//   array_destroy(&map->items);
//   map->items = array_create(NULL, 1, PAIR);
// }