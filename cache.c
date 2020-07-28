#include <string.h>
#include "cache.h"

node_t node_pool[NODE_POOL_SIZE + 1];
node_ptr_t node_cache[NODE_CACHE_SIZE];
node_ptr_t next_node_ptr = 1;
node_ptr_t lru_node_ptr = 0;
node_ptr_t mru_node_ptr = 0;

// free existing, create a new node, connect it as most recently used
void put_new(key_t key, tag_t tag, value_t * value) {
    // check if there is an existing cache entry
    if (node_cache[key] != 0) {
        // get first and last node pointer from cache
        node_ptr_t first_node_ptr = node_cache[key];
        node_ptr_t last_node_ptr = node_pool[first_node_ptr].last;
        // check if first node is not least recently used (i.e. has previous)
        if (lru_node_ptr != first_node_ptr) {
            node_pool[node_pool[first_node_ptr].previous].next = node_pool[last_node_ptr].next;
            node_pool[first_node_ptr].previous = 0;
        }
        // check if last node is not most recently used (i.e. has next)
        if (mru_node_ptr != last_node_ptr) {
            node_pool[node_pool[last_node_ptr].next].previous = node_pool[first_node_ptr].previous;
        }
        // reconnect last before least recently used
        node_pool[lru_node_ptr].previous = last_node_ptr;
        node_pool[last_node_ptr].next = lru_node_ptr;
        // set first as least recently used
        lru_node_ptr = first_node_ptr;
        // clear node information
        node_pool[first_node_ptr].is_first = false;
    }
    // set new node information
    node_pool[next_node_ptr].previous = mru_node_ptr;
    node_pool[next_node_ptr].is_first = true;
    node_pool[next_node_ptr].key = key;
    node_pool[next_node_ptr].tag = tag;
    memcpy(&node_pool[next_node_ptr].value, value, sizeof(value_t));
    node_pool[next_node_ptr].next = 0;
    node_pool[next_node_ptr].last = next_node_ptr;
    // check if this is the first node
    if (mru_node_ptr) {
        // connect after most recently used
        node_pool[mru_node_ptr].next = next_node_ptr;
        // set new as most recently used
        mru_node_ptr = next_node_ptr;
    } else {
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
    // get first and last node pointer from cache
    node_ptr_t first_node_ptr = node_cache[key];
    node_ptr_t last_node_ptr = node_pool[first_node_ptr].last;
    // check if first node is not least recently used (i.e. has previous)
    if (lru_node_ptr != first_node_ptr) {
        // disconnect first: first_node->previous->next = last_node->next;
        node_pool[node_pool[first_node_ptr].previous].next = node_pool[last_node_ptr].next;
    }
    // check if last node is not most recently used (i.e. has next)
    if (mru_node_ptr != last_node_ptr) {
        // disconnect last: last_node->next->previous = first_node->previous;
        node_pool[node_pool[last_node_ptr].next].previous = node_pool[first_node_ptr].previous;
        node_pool[last_node_ptr].next = 0;
    }
    // reconnect first after most recently used
    node_pool[mru_node_ptr].next = first_node_ptr;
    node_pool[first_node_ptr].previous = mru_node_ptr;
    // set last as most recently used
    mru_node_ptr = last_node_ptr;
    // set new node information
    node_pool[next_node_ptr].previous = mru_node_ptr;
    node_pool[next_node_ptr].is_first = false;
    memcpy(&node_pool[next_node_ptr].value, value, sizeof(value_t));
    node_pool[next_node_ptr].next = 0;
    // connect after most recently used
    node_pool[mru_node_ptr].next = next_node_ptr;
    // set new as most recently used
    mru_node_ptr = next_node_ptr;
    // set new as last
    node_pool[first_node_ptr].last = next_node_ptr;
    // increment next node pointer, if possible, or set to zero
    next_node_ptr = (next_node_ptr + 1) % (NODE_POOL_SIZE + 1);
}

void put(key_t key, tag_t tag, value_t * value) {
    // check if there is an existing cache entry
    if (node_cache[key] != 0) {
        // get first and last node pointer from cache
        node_ptr_t first_node_ptr = node_cache[key];
        node_ptr_t last_node_ptr = node_pool[first_node_ptr].last;
        // check if first node is not least recently used (i.e. has previous)
        if (lru_node_ptr != first_node_ptr) {
            node_pool[node_pool[first_node_ptr].previous].next = node_pool[last_node_ptr].next;
            node_pool[first_node_ptr].previous = 0;
        }
        // check if last node is not most recently used (i.e. has next)
        if (mru_node_ptr != last_node_ptr) {
            node_pool[node_pool[last_node_ptr].next].previous = node_pool[first_node_ptr].previous;
        }
        // reconnect last before least recently used
        node_pool[lru_node_ptr].previous = last_node_ptr;
        node_pool[last_node_ptr].next = lru_node_ptr;
        // set first as least recently used
        lru_node_ptr = first_node_ptr;
        // clear node information
        node_pool[first_node_ptr].is_first = false;
    }
    // get least recently used as current node
    node_ptr_t cur_node_ptr = lru_node_ptr;
    // advance least recently used, if possible
    if (node_pool[cur_node_ptr].next) {
        lru_node_ptr = node_pool[cur_node_ptr].next;
        node_pool[lru_node_ptr].previous = 0;
    }
    // check if about to overwrite existing cache entry
    if (node_pool[cur_node_ptr].is_first) {
        node_cache[node_pool[cur_node_ptr].key] = 0;
    }
    // 
}

void append(key_t key, tag_t tag, value_t * value) {
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
}
