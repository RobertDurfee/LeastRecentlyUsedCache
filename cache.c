#include <string.h>
#include "cache.h"

struct KeyValue pool[POOL_SIZE + 1];
key_value_pointer_t cache[CACHE_SIZE];
key_value_pointer_t least_recently_used = 1;
key_value_pointer_t most_recently_used = POOL_SIZE;

void put_append(unsigned int tag, unsigned int key, struct Value * value) {

    // if the cache has this key with a matched tag (append)
    if (cache[key] != NONE && pool[cache[key]].tag == tag) {

        // get least recently used key value from pool
        key_value_pointer_t current = least_recently_used;

        // if key value from pool about to be overwritten is a header ...
        if (pool[current].is_header) {

            // ... and in the cache, clear the cache entry
            if (pool[cache[pool[current].key]].tag == pool[current].tag) {
                cache[pool[current].key] = NONE;
            }

            // unset as header either way
            pool[current].is_header = false;
        }

        // remove least recently used
        least_recently_used = pool[current].next;
        pool[least_recently_used].previous = NONE;

        // copy the value
        memcpy(&pool[current].value, value, sizeof(struct Value));

        // get last from cache entry
        key_value_pointer_t first = cache[key];
        key_value_pointer_t last = pool[first].last;

        // reinsert after last from cache entry
        pool[pool[last].next].previous = current;
        pool[current].next = pool[last].next;
        pool[last].next = current;
        pool[current].previous = last;

    // otherwise this corresponds to an empty cache entry (put)
    } else {

        // get the least recently used key value from the pool
        key_value_pointer_t current = least_recently_used;

        // if key value from pool about to be overwritten is a header and in the cache, clear the cache entry
        if (pool[current].is_header && pool[cache[pool[current].key]].tag == pool[current].tag) {
            cache[pool[current].key] = NONE;
        }

        // remove least recently used
        least_recently_used = pool[current].next;
        pool[least_recently_used].previous = NONE;

        // set key value header information
        pool[current].tag = tag;
        pool[current].key = key;
        pool[current].is_header = true;
        memcpy(&pool[current].value, value, sizeof(struct Value));
        pool[current].last = current;

        // reinsert as most recently used
        pool[most_recently_used].next = current;
        pool[current].previous = most_recently_used;
        most_recently_used = current;
        pool[most_recently_used].next = NONE;

        // if cache entry currently holds a different value about to be overwritten
        if (cache[key] != NONE) {

            // get first and last from overwritten entry
            key_value_pointer_t free_first = cache[key];
            key_value_pointer_t free_last = pool[free_first].last;

            // remove overwritten entry
            pool[pool[free_first].previous].next = pool[free_last].next;
            pool[pool[free_last].next].previous = pool[free_first].previous;

            // reinsert as least recently used
            pool[least_recently_used].previous = free_last;
            pool[free_last].next = least_recently_used;
            least_recently_used = free_first;
            pool[least_recently_used].previous = NONE;

        }

        // insert into cache, overwritten has been set as least recently used
        cache[key] = current;
    }
}

void use(key_value_pointer_t first) {
    if (first == most_recently_used) {
        // Do nothing, already in the correct place.
    } else if (first == least_recently_used) {
        key_value_pointer_t last = pool[first].last;
    } else {
    }
}
