#include <string.h>
#include "cache.h"

struct KeyValue pool[POOL_SIZE + 1];
key_value_pointer_t cache[CACHE_SIZE];
key_value_pointer_t next = 1;
key_value_pointer_t least_recently_used = NONE;
key_value_pointer_t most_recently_used = NONE;

void put_append(unsigned int tag, unsigned int key, struct Value * value) {
}

void use(key_value_pointer_t first) {
}
