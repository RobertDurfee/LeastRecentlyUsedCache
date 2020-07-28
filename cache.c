#include <string.h>
#include "cache.h"

node_t node_pool[NODE_POOL_SIZE + 1];
node_ptr_t node_cache[NODE_CACHE_SIZE];
node_ptr_t next_node_ptr = 1;
node_ptr_t lru_node_ptr = 0;
node_ptr_t mru_node_ptr = 0;

void set_lru(node_ptr_t first_node_ptr) {
    // get last node pointer
    node_ptr_t last_node_ptr;
    if (node_pool[first_node_ptr].is_first) {
        last_node_ptr = node_pool[first_node_ptr].last;
    } else {
        last_node_ptr = first_node_ptr;
    }
    // check position in chain
    if (lru_node_ptr == first_node_ptr) {
        // do nothing, already in the correct location
    } else if (mru_node_ptr == last_node_ptr) {
        // disconnect from most recently used end
        node_pool[node_pool[first_node_ptr].previous].next = 0;
        // set most recently used
        mru_node_ptr = node_pool[first_node_ptr].previous;
        // reconnect at least recently used end
        node_pool[lru_node_ptr].previous = last_node_ptr;
        node_pool[first_node_ptr].previous = 0;
        node_pool[last_node_ptr].next = lru_node_ptr;
        // set least recently used
        lru_node_ptr = first_node_ptr;
    } else {
        // disconnect from interior
        node_pool[node_pool[first_node_ptr].previous].next = node_pool[last_node_ptr].next;
        node_pool[node_pool[last_node_ptr].next].previous = node_pool[first_node_ptr].previous;
        // reconnect at least recently used end
        node_pool[lru_node_ptr].previous = last_node_ptr;
        node_pool[first_node_ptr].previous = 0;
        node_pool[last_node_ptr].next = lru_node_ptr;
        // set least recently used
        lru_node_ptr = first_node_ptr;
    }
}

void set_mru(node_ptr_t first_node_ptr) {
    // get last node pointer
    node_ptr_t last_node_ptr;
    if (node_pool[first_node_ptr].is_first) {
        last_node_ptr = node_pool[first_node_ptr].last;
    } else {
        last_node_ptr = first_node_ptr;
    }
    // check position in chain
    if (mru_node_ptr == last_node_ptr) {
        // do nothing, already in the correct location
    } else if (lru_node_ptr == first_node_ptr) {
        // disconnect from least recently used end
        node_pool[node_pool[last_node_ptr].next].previous = 0;
        // set least recently used
        lru_node_ptr = node_pool[last_node_ptr].next;
        // reconnect at most recently used end
        node_pool[mru_node_ptr].next = first_node_ptr;
        node_pool[last_node_ptr].next = 0;
        node_pool[first_node_ptr].previous = mru_node_ptr;
        // set most recently used
        mru_node_ptr = last_node_ptr;
    } else {
        // disconnect from interior
        node_pool[node_pool[first_node_ptr].previous].next = node_pool[last_node_ptr].next;
        node_pool[node_pool[last_node_ptr].next].previous = node_pool[first_node_ptr].previous;
        // reconnect at most recently used end
        node_pool[mru_node_ptr].next = first_node_ptr;
        node_pool[last_node_ptr].next = 0;
        node_pool[first_node_ptr].previous = mru_node_ptr;
        // set most recently used
        mru_node_ptr = last_node_ptr;
    }
}

void put_new(key_t key, tag_t tag, value_t * value) {
    // check if there is an existing cache entry
    if (node_cache[key] != 0) {
        // set as least recently used
        set_lru(node_cache[key]);
        // clear node information
        node_pool[node_cache[key]].is_first = false;
    }
    // set new node information
    node_pool[next_node_ptr].is_first = true;
    node_pool[next_node_ptr].key = key;
    node_pool[next_node_ptr].tag = tag;
    memcpy(&node_pool[next_node_ptr].value, value, sizeof(value_t));
    node_pool[next_node_ptr].last = next_node_ptr;
    // check if this is the first node
    if (mru_node_ptr) {
        // connect after most recently used
        node_pool[mru_node_ptr].next = next_node_ptr;
        node_pool[next_node_ptr].previous = mru_node_ptr;
        node_pool[next_node_ptr].next = 0;
        // set new as most recently used
        mru_node_ptr = next_node_ptr;
    } else {
        // connect to nothing
        node_pool[next_node_ptr].previous = 0;
        node_pool[next_node_ptr].next = 0;
        // set new as both most and least recently used
        lru_node_ptr = next_node_ptr;
        mru_node_ptr = next_node_ptr;
    }
    // set cache entry
    node_cache[key] = next_node_ptr;
    // increment next node pointer, if possible, or set to zero
    next_node_ptr = (next_node_ptr + 1) % (NODE_POOL_SIZE + 1);
}

// set existing as most recently used, create new node, connect it as last
void append_new(key_t key, tag_t tag, value_t * value) {
    // set as most recently used
    set_mru(node_cache[key]);
    // set new node information
    node_pool[next_node_ptr].is_first = false;
    memcpy(&node_pool[next_node_ptr].value, value, sizeof(value_t));
    // connect after most recently used
    node_pool[mru_node_ptr].next = next_node_ptr;
    node_pool[next_node_ptr].previous = mru_node_ptr;
    node_pool[next_node_ptr].next = 0;
    // set new as most recently used
    mru_node_ptr = next_node_ptr;
    // set new as last
    node_pool[node_cache[key]].last = next_node_ptr;
    // increment next node pointer, if possible, or set to zero
    next_node_ptr = (next_node_ptr + 1) % (NODE_POOL_SIZE + 1);
}

void put(key_t key, tag_t tag, value_t * value) {
    // check if there is an existing cache entry
    if (node_cache[key] != 0) {
        // set as least recently used
        set_lru(node_cache[key]);
        // clear node information
        node_pool[node_cache[key]].is_first = false;
    }
    // get current node as least recently used
    node_ptr_t cur_node_ptr = lru_node_ptr;
    // check if about to overwrite existing cache entry
    if (node_pool[cur_node_ptr].is_first) {
        node_cache[node_pool[cur_node_ptr].key] = 0;
        node_pool[cur_node_ptr].is_first = false;
    }
    // set as most recently used
    set_mru(cur_node_ptr);
    // set node information
    node_pool[cur_node_ptr].is_first = true;
    node_pool[cur_node_ptr].key = key;
    node_pool[cur_node_ptr].tag = tag;
    memcpy(&node_pool[cur_node_ptr].value, value, sizeof(value_t));
    node_pool[cur_node_ptr].last = cur_node_ptr;
    // set cache entry
    node_cache[key] = cur_node_ptr;
}

void append(key_t key, tag_t tag, value_t * value) {
    // set as most recently used
    set_mru(node_cache[key]);
    // get current node as least recently used
    node_ptr_t cur_node_ptr = lru_node_ptr;
    // check if about to overwrite existing cache entry
    if (node_pool[cur_node_ptr].is_first) {
        node_cache[node_pool[cur_node_ptr].key] = 0;
        node_pool[cur_node_ptr].is_first = false;
    }
    // set as most recently used
    set_mru(cur_node_ptr);
    // set node information
    node_pool[cur_node_ptr].is_first = false;
    memcpy(&node_pool[cur_node_ptr].value, value, sizeof(value_t));
    // set as last
    node_pool[node_cache[key]].last = cur_node_ptr;
}

void put_append(key_t key, tag_t tag, value_t * value) {
    // check if there is a new node available
    if (next_node_ptr) {
        // check if cache contains a node with the same tag
        if (node_pool[node_cache[key]].tag == tag) {
            append_new(key, tag, value);
        } else {
            put_new(key, tag, value);
        }
    } else {
        // check if cache contains a node with the same tag
        if (node_pool[node_cache[key]].tag == tag) {
            append(key, tag, value);
        } else {
            put(key, tag, value);
        }
    }
}

void use(node_ptr_t node_ptr) {
    // set as most recently used
    set_mru(node_ptr);
}
