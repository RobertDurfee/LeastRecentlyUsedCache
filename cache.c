#include <string.h>
#include "cache.h"

node_t node_pool[NODE_POOL_SIZE + 1];
node_ptr_t node_cache[NODE_CACHE_SIZE];
node_ptr_t next_node_ptr = 1;
node_ptr_t lru_node_ptr = 0;
node_ptr_t mru_node_ptr = 0;

void put_new(key_t key, tag_t tag, value_t * value) {
}

void append_new(key_t key, tag_t tag, value_t * value) {
}

void put(key_t key, tag_t tag, value_t * value) {
}

void append(key_t key, tag_t tag, value_t * value) {
}

void put_append(key_t key, tag_t tag, value_t * value) {
}

void use(node_ptr_t node_ptr) {
}
