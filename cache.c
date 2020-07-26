#include <string.h>
#include "cache.h"

struct KeyValue pool[POOL_SIZE + 1];
key_value_pointer_t cache[CACHE_SIZE];
key_value_pointer_t next = 1;
key_value_pointer_t least_recently_used = NONE;
key_value_pointer_t most_recently_used = NONE;

void put_new(unsigned int key, unsigned int tag, struct Value * value) {
}

void append_new(unsigned int key, unsigned int tag, struct Value * value) {
}

void put(unsigned int key, unsigned int tag, struct Value * value) {
}

void append(unsigned int key, unsigned int tag, struct Value * value) {
}

void put_append(unsigned int key, unsigned int tag, struct Value * value) {
}

void use(key_value_pointer_t first) {
}
