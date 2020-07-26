#ifndef CACHE_H
#define CACHE_H

#define POOL_SIZE 0x0F
#define CACHE_SIZE 0x0F
#define NONE 0

typedef enum { false, true } bool;
typedef unsigned int key_value_pointer_t;

struct Value {
    unsigned int value;
};

struct KeyValue {
    key_value_pointer_t previous;
    bool is_header;
    unsigned int key;
    unsigned int tag;
    struct Value value;
    key_value_pointer_t next;
    key_value_pointer_t last;
};

extern struct KeyValue pool[POOL_SIZE + 1];
extern key_value_pointer_t cache[CACHE_SIZE];
extern key_value_pointer_t next;
extern key_value_pointer_t least_recently_used;
extern key_value_pointer_t most_recently_used;

// these functions are for testing purposes only

void put_new(unsigned int key, unsigned int tag, struct Value * value);
void append_new(unsigned int key, unsigned int tag, struct Value * value);
void put(unsigned int key, unsigned int tag, struct Value * value);
void append(unsigned int key, unsigned int tag, struct Value * value);

// only these functions should be used to mutate the cache

void put_append(unsigned int key, unsigned int tag, struct Value * value);
void use(key_value_pointer_t key_value);

#endif // CACHE_H
