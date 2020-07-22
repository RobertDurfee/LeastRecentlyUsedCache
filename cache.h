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
    unsigned int tag;
    unsigned int key;
    bool is_header;
    struct Value value;
    key_value_pointer_t next;
    key_value_pointer_t last;
};

extern struct KeyValue pool[POOL_SIZE + 1];
extern key_value_pointer_t cache[CACHE_SIZE];
extern key_value_pointer_t least_recently_used;
extern key_value_pointer_t most_recently_used;

void put_append(unsigned int tag, unsigned int key, struct Value * value);
void use(key_value_pointer_t key_value);

#endif // CACHE_H
