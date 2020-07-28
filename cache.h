#ifndef CACHE_H
#define CACHE_H

#define NODE_POOL_SIZE 0x0F
#define NODE_CACHE_SIZE 0x0F

typedef enum { false, true } bool;
typedef unsigned int node_ptr_t;
typedef unsigned int key_t;
typedef unsigned long tag_t;

typedef struct {
    unsigned int value;
} value_t;

typedef struct {
    node_ptr_t previous;
    bool is_first;
    key_t key;
    tag_t tag;
    value_t value;
    node_ptr_t next;
    node_ptr_t last;
} node_t;

extern node_t node_pool[NODE_POOL_SIZE + 1];
extern node_ptr_t node_cache[NODE_CACHE_SIZE];
extern node_ptr_t next_node_ptr;
extern node_ptr_t lru_node_ptr;
extern node_ptr_t mru_node_ptr;

// these functions are for testing purposes only
void put_new(key_t key, tag_t tag, value_t * value);
void append_new(key_t key, tag_t tag, value_t * value);
void put(key_t key, tag_t tag, value_t * value);
void append(key_t key, tag_t tag, value_t * value);

// only these functions should be used to mutate the cache
void put_append(key_t key, tag_t tag, value_t * value);
void use(node_ptr_t node_ptr);

#endif // CACHE_H
