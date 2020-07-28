#include <assert.h>
#include <stdio.h>
#include "cache.h"
#include "tests.h"

static key_t key_0 = 0;
static key_t key_1 = 1;
static key_t key_2 = 2;
static key_t key_3 = 3;
static key_t key_4 = 4;

static value_t value_0 = { 0 };
static value_t value_1 = { 1 };
static value_t value_2 = { 2 };
static value_t value_3 = { 3 };

static node_ptr_t node_ptr_1 = 1;
static node_ptr_t node_ptr_2 = 2;
static node_ptr_t node_ptr_3 = 3;
static node_ptr_t node_ptr_4 = 4;
static node_ptr_t node_ptr_5 = 5;

void reset(void) {
    next_node_ptr = 1;
    lru_node_ptr = 0;
    mru_node_ptr = 0;

    for (node_ptr_t node_ptr_i = 0; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        node_pool[node_ptr_i].previous = 0;
        node_pool[node_ptr_i].tag = 0;
        node_pool[node_ptr_i].key = 0;
        node_pool[node_ptr_i].is_first = false;
        node_pool[node_ptr_i].value.value = 0;
        node_pool[node_ptr_i].next = 0;
        node_pool[node_ptr_i].last = 0;
    }

    for (key_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        node_cache[key_i] = 0;
    }
}

// ======================================================================================
//  ZERO NODES
// ======================================================================================

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 1
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_1(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                  LRU MRU                                  |\n"
        "|                                   v   v                                   |\n"
        "|                                   0   0                                   |\n"
        "\n"
    );

    assert(next_node_ptr == node_ptr_1);
    assert(lru_node_ptr == 0);
    assert(mru_node_ptr == 0);

    for (node_ptr_t node_ptr_i = 0; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_1(void) {
    start_1();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                LRU MRU [0]                                |\n"
        "|                                 v   v   v                                 |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_2; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ======================================================================================
//  ONE NODE
// ======================================================================================

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 2
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_2(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                LRU MRU [0]                                |\n"
        "|                                 v   v   v                                 |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_2; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_2(void) {
    start_2();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [0]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_3(void) {
    start_2();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]   MRU [1]                             |\n"
        "|                              v   v     v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_4(void) {
    start_2();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]     MRU                               |\n"
        "|                              v   v       v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_5(void) {
    start_2();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                LRU MRU [0]                                |\n"
        "|                                 v   v   v                                 |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_2; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_6(void) {
    start_2();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                LRU MRU [1]                                |\n"
        "|                                 v   v   v                                 |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_1);
    assert(node_pool[node_ptr_1].tag == key_1);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_2; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_7(void) {
    start_2();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                  LRU MRU                                  |\n"
        "|                                   v   v                                   |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                                                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    for (node_ptr_t node_ptr_i = 0; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (node_ptr_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 3
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_3(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                  LRU MRU                                  |\n"
        "|                                   v   v                                   |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                                                           |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    for (node_ptr_t node_ptr_i = 0; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (node_ptr_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_8(void) {
    start_3();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [0]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_9(void) {
    start_3();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                                LRU MRU [0]                                |\n"
        "|                                 v   v   v                                 |\n"
        "|                                   ,---.                                   |\n"
        "|                              0 <- | 1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_2);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_2; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ======================================================================================
//  TWO NODES
// ======================================================================================

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 4
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_4(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [0]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_10(void) {
    start_4();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 1 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_11(void) {
    start_4();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]     MRU [1]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_12(void) {
    start_4();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]       MRU                          |\n"
        "|                           v         v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_13(void) {
    start_4();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [0]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_14(void) {
    start_4();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]   MRU [1]                             |\n"
        "|                              v   v     v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_1);
    assert(node_pool[node_ptr_1].tag == key_1);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_15(void) {
    start_4();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]     MRU                               |\n"
        "|                              v   v       v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 5
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_5(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]   MRU [1]                             |\n"
        "|                              v   v     v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_16(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [1]     MRU [0]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_17(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]     MRU [1]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 1 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_3);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_18(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]     MRU [2]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put_new(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_19(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]     [0]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 1 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_3);
    assert(node_pool[node_ptr_1].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }

}

void case_20(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append_new(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_21(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [1]   MRU [0]                             |\n"
        "|                              v   v     v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_22(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]   MRU [1]                             |\n"
        "|                              v   v     v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_23(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [1]   MRU [2]                             |\n"
        "|                              v   v     v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_2);
    assert(node_pool[node_ptr_1].tag == key_2);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_24(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]     MRU                               |\n"
        "|                              v   v       v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_25(void) {
    start_5();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [1]     MRU                               |\n"
        "|                              v   v       v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[0] == 0);

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 6
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_6(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                             LRU [0]     MRU                               |\n"
        "|                              v   v       v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_26(void) {
    start_6();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_27(void) {
    start_6();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]             MRU [1]                        |\n"
        "|                         v   v               v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_28(void) {
    start_6();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]               MRU                          |\n"
        "|                         v   v                 v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_29(void) {
    start_6();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [0]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_30(void) {
    start_6();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [1]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_1);
    assert(node_pool[node_ptr_1].tag == key_1);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[0] == 0);

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_31(void) {
    start_6();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU       MRU                               |\n"
        "|                                v         v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                                                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (node_ptr_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 7
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_7(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU       MRU                               |\n"
        "|                                v         v                                |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                                                           |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    put_new(key_0, key_0, &value_0);
    append(key_0, key_0, &value_1);
    append(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == 0);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (node_ptr_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_32(void) {
    start_7();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_33(void) {
    start_7();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                               LRU     MRU [0]                             |\n"
        "|                                v       v   v                              |\n"
        "|                              ,---.     ,---.                              |\n"
        "|                         0 <- | 2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_3);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_3; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ======================================================================================
//  THREE NODES
// ======================================================================================

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 8
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_8(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    append_new(key_0, key_0, &value_1);
    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_34(void) {
    start_8();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                         MRU [0]                   |\n"
        "|                      v                           v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 3 | <=> | 1 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_35(void) {
    start_8();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                 [0]     MRU [1]                   |\n"
        "|                      v                   v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_3);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_36(void) {
    start_8();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                 [0]       MRU                     |\n"
        "|                      v                   v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                          `---------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_37(void) {
    start_8();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_38(void) {
    start_8();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]     MRU [1]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_1);
    assert(node_pool[node_ptr_1].tag == key_1);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_3);
    assert(node_cache[key_1] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_39(void) {
    start_8();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]       MRU                          |\n"
        "|                           v         v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_0);
    assert(node_pool[node_ptr_3].tag == key_0);
    assert(node_pool[node_ptr_3].value.value == value_0.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_0] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 9
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_9(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]     MRU [1]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );
    
    put_new(key_0, key_0, &value_0);
    put_new(key_0, key_0, &value_0);
    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_40(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                 [1]     MRU [0]                   |\n"
        "|                      v                   v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 2 | <=> | 1 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_41(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                 [0]     MRU [1]                   |\n"
        "|                      v                   v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 3 | <=> | 1 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_4);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_42(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]       [1]     MRU [2]                   |\n"
        "|                      v         v         v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_2);
    assert(node_pool[node_ptr_4].tag == key_2);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_2] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_43(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [1]       [0]       MRU                     |\n"
        "|                      v         v         v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 3 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^        `---------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_2);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_3);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_4);
    assert(node_pool[node_ptr_2].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_44(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]       [1]       MRU                     |\n"
        "|                      v         v         v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^        `---------^                      |\n"
        "\n"
    );

    append_new(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_45(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [1]     MRU [0]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 3 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_2);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_3);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_46(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]     MRU [1]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_47(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]     MRU [2]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_2);
    assert(node_pool[node_ptr_1].tag == key_2);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_2] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_48(void) {
    start_9();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]     [0]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 3 | <=> | 2 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_2);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_3);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_49(void) {
    start_9();
    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 10
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_10(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]       MRU                          |\n"
        "|                           v         v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    put_new(key_0, key_0, &value_0);
    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_50(void) {
    start_10();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                         MRU [0]                   |\n"
        "|                      v                           v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 2 | <=> | 3 | <=> | 1 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_1);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_51(void) {
    start_10();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]               MRU [1]                   |\n"
        "|                      v         v                 v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `---------^        `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_52(void) {
    start_10();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]                 MRU                     |\n"
        "|                      v         v                   v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `-------------------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_53(void) {
    start_10();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 3 | <=> | 1 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_54(void) {
    start_10();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]             MRU [1]                        |\n"
        "|                         v   v               v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_1);
    assert(node_pool[node_ptr_1].tag == key_1);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_2);
    assert(node_cache[key_1] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_55(void) {
    start_10();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]               MRU                          |\n"
        "|                         v   v                 v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_0);
    assert(node_pool[node_ptr_2].tag == key_0);
    assert(node_pool[node_ptr_2].value.value == value_0.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_0] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 11
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_11(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]     MRU [2]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    put_new(key_1, key_1, &value_1);
    put_new(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_56(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [1]       [2]     MRU [0]                   |\n"
        "|                      v         v         v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_57(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]       [2]     MRU [1]                   |\n"
        "|                      v         v         v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 2 | <=> | 1 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_3);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_58(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]       [1]     MRU [2]                   |\n"
        "|                      v         v         v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 3 | <=> | 1 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_4);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_2);
    assert(node_pool[node_ptr_4].tag == key_2);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_59(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(3, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]     [1]       [2]     MRU [3]                   |\n"
        "|                    v   v       v         v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^       `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_3, key_3, &value_3);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_3);
    assert(node_pool[node_ptr_4].tag == key_3);
    assert(node_pool[node_ptr_4].value.value == value_3.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_3] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_4; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_60(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [1]     [2]       [0]       MRU                     |\n"
        "|                    v   v       v         v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 2 | <=> | 3 | <=> | 1 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^        `---------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_4);
    assert(node_pool[node_ptr_1].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_1);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_61(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]     [2]       [1]       MRU                     |\n"
        "|                    v   v       v         v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 3 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^        `---------^                      |\n"
        "\n"
    );

    append_new(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_3);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_2);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_3);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_4);
    assert(node_pool[node_ptr_2].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_62(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]     [1]       [2]       MRU                     |\n"
        "|                    v   v       v         v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^        `---------^                      |\n"
        "\n"
    );

    append_new(key_2, key_2, &value_3);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_3.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_63(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]     [2]     MRU [0]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_64(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [2]     MRU [1]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 3 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_3);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == node_ptr_1);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_2);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_3);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_65(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]     MRU [2]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_66(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(3, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]     [2]     MRU [3]                        |\n"
        "|                         v   v       v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put(key_3, key_3, &value_3);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_3);
    assert(node_pool[node_ptr_1].tag == key_3);
    assert(node_pool[node_ptr_1].value.value == value_3.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_3] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_4; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_67(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [2]     [0]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 3 | <=> | 1 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);

    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_1] == 0);

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_68(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [2]     [1]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 3 | <=> | 2 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_2);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_3);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_1);
    assert(node_pool[node_ptr_2].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_2);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_2] == node_ptr_3);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_69(void) {
    start_11();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]     [2]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(key_2, key_2, &value_3);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_2);
    assert(node_pool[node_ptr_3].tag == key_2);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_3.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 12
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_12(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]     [1]       MRU                          |\n"
        "|                         v   v       v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    put_new(key_1, key_1, &value_1);
    append_new(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_70(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [1]               MRU [0]                   |\n"
        "|                      v         v                 v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `---------^        `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_71(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                 [0]     MRU [1]                   |\n"
        "|                      v                   v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 2 | <=> | 3 | <=> | 1 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_4);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_4].previous == node_ptr_1);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_72(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]     [1]               MRU [2]                   |\n"
        "|                    v   v       v                 v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^        `---------^        `-^                     |\n"
        "\n"
    );

    put_new(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_2);
    assert(node_pool[node_ptr_4].tag == key_2);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_73(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [1]               [0]       MRU                     |\n"
        "|                    v   v                 v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 2 | <=> | 3 | <=> | 1 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `---------^         `---------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_4);
    assert(node_pool[node_ptr_1].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_1);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_74(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]     [1]                 MRU                     |\n"
        "|                    v   v       v                   v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^        `-------------------^                      |\n"
        "\n"
    );

    append_new(key_1, key_1, &value_3);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_3.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_75(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]             MRU [0]                        |\n"
        "|                         v   v               v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_76(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]     MRU [1]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 3 | <=> | 1 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);
    assert(node_pool[node_ptr_2].last == node_ptr_2);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_77(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]             MRU [2]                        |\n"
        "|                         v   v               v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_2);
    assert(node_pool[node_ptr_1].tag == key_2);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_2);
    assert(node_cache[key_2] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_78(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [0]       MRU                          |\n"
        "|                           v         v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 3 | <=> | 1 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_2);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_79(void) {
    start_12();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [1]               MRU                          |\n"
        "|                         v   v                 v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );

    append(key_1, key_1, &value_3);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == true);
    assert(node_pool[node_ptr_2].key == key_1);
    assert(node_pool[node_ptr_2].tag == key_1);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);
    assert(node_pool[node_ptr_2].last == node_ptr_1);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_3.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_1] == node_ptr_2);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 13
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_13(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]             MRU [1]                        |\n"
        "|                         v   v               v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    append_new(key_0, key_0, &value_1);
    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_80(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                 [1]     MRU [0]                   |\n"
        "|                      v                   v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_81(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU       [0]               MRU [1]                   |\n"
        "|                      v         v                 v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 3 | <=> | 1 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `---------^        `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_82(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]               [1]     MRU [2]                   |\n"
        "|                    v   v                 v       v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `---------^        `-^       `-^                     |\n"
        "\n"
    );

    put_new(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_2);
    assert(node_pool[node_ptr_4].tag == key_2);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_2] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_83(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [1]     [0]                 MRU                     |\n"
        "|                    v   v       v                   v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 3 | <=> | 1 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^        `-------------------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_3);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_3].previous == 0);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_2);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_84(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]               [1]       MRU                     |\n"
        "|                    v   v                 v         v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `---------^         `---------^                      |\n"
        "\n"
    );

    append_new(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);
    assert(node_pool[node_ptr_3].last == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_2.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_85(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [1]     MRU [0]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_86(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]             MRU [1]                        |\n"
        "|                         v   v               v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == 0);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_87(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(2, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [1]     MRU [2]                        |\n"
        "|                           v         v       v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(key_2, key_2, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_2);
    assert(node_pool[node_ptr_1].tag == key_2);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_3);
    assert(node_cache[key_2] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_3; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_88(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]               MRU                          |\n"
        "|                         v   v                 v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_89(void) {
    start_13();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU       [1]       MRU                          |\n"
        "|                           v         v         v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    append(key_1, key_1, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == true);
    assert(node_pool[node_ptr_3].key == key_1);
    assert(node_pool[node_ptr_3].tag == key_1);
    assert(node_pool[node_ptr_3].value.value == value_1.value);
    assert(node_pool[node_ptr_3].next == node_ptr_1);
    assert(node_pool[node_ptr_3].last == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].value.value == value_2.value);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_cache[key_1] == node_ptr_3);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 14
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_14(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                        LRU [0]               MRU                          |\n"
        "|                         v   v                 v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);
    append_new(key_0, key_0, &value_1);
    append_new(key_0, key_0, &value_2);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_90(void) {
    start_14();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                         MRU [0]                   |\n"
        "|                      v                           v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_91(void) {
    start_14();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]                       MRU [1]                   |\n"
        "|                    v   v                         v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `-------------------^        `-^                     |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_3);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_1);
    assert(node_pool[node_ptr_4].tag == key_1);
    assert(node_pool[node_ptr_4].value.value == value_1.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_1);
    assert(node_cache[key_1] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_92(void) {
    start_14();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                   LRU [0]                         MRU                     |\n"
        "|                    v   v                           v                      |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `-----------------------------^                      |\n"
        "\n"
    );

    append_new(key_0, key_0, &value_3);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == node_ptr_2);
    assert(node_pool[node_ptr_1].last == node_ptr_4);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].value.value == value_1.value);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].value.value == value_2.value);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == false);
    assert(node_pool[node_ptr_4].value.value == value_3.value);
    assert(node_pool[node_ptr_4].next == 0);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_93(void) {
    start_14();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_94(void) {
    start_14();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(1, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [1]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put(key_1, key_1, &value_1);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_1);
    assert(node_pool[node_ptr_1].tag == key_1);
    assert(node_pool[node_ptr_1].value.value == value_1.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_1] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    assert(node_cache[key_0] == 0);

    for (key_t key_i = key_2; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_95(void) {
    start_14();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER append(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU                 MRU                          |\n"
        "|                           v                   v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                                                           |\n"
        "\n"
    );

    append(key_0, key_0, &value_3);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == 0);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (node_ptr_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  START 15
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void start_15(void) {
    reset();

    printf(
        "-----------------------------------------------------------------------------\n"
        " BEFORE:\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU                 MRU                          |\n"
        "|                           v                   v                           |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                                                           |\n"
        "\n"
    );

    put_new(key_1, key_1, &value_1);
    put_new(key_1, key_1, &value_1);
    put_new(key_0, key_0, &value_0);
    append(key_0, key_0, &value_1);
    append(key_0, key_0, &value_2);
    append(key_0, key_0, &value_3);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_3);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == 0);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (node_ptr_t key_i = key_0; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_96(void) {
    start_15();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put_new(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                     LRU                         MRU [0]                   |\n"
        "|                      v                           v   v                    |\n"
        "|                    ,---.     ,---.     ,---.     ,---.                    |\n"
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );

    put_new(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_5);
    assert(lru_node_ptr == node_ptr_1);
    assert(mru_node_ptr == node_ptr_4);

    assert(node_pool[node_ptr_1].previous == 0);
    assert(node_pool[node_ptr_1].is_first == false);
    assert(node_pool[node_ptr_1].next == node_ptr_2);

    assert(node_pool[node_ptr_2].previous == node_ptr_1);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_4);

    assert(node_pool[node_ptr_4].previous == node_ptr_3);
    assert(node_pool[node_ptr_4].is_first == true);
    assert(node_pool[node_ptr_4].key == key_0);
    assert(node_pool[node_ptr_4].tag == key_0);
    assert(node_pool[node_ptr_4].value.value == value_0.value);
    assert(node_pool[node_ptr_4].next == 0);
    assert(node_pool[node_ptr_4].last == node_ptr_4);

    assert(node_cache[key_0] == node_ptr_4);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_5; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void case_97(void) {
    start_15();

    printf(
        "-----------------------------------------------------------------------------\n"
        " AFTER put(0, _):\n"
        "-----------------------------------------------------------------------------\n"
        "\n"
        "|                          LRU               MRU [0]                        |\n"
        "|                           v                 v   v                         |\n"
        "|                         ,---.     ,---.     ,---.                         |\n"
        "|                    0 <- | 2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put(key_0, key_0, &value_0);

    assert(next_node_ptr == node_ptr_4);
    assert(lru_node_ptr == node_ptr_2);
    assert(mru_node_ptr == node_ptr_1);

    assert(node_pool[node_ptr_2].previous == 0);
    assert(node_pool[node_ptr_2].is_first == false);
    assert(node_pool[node_ptr_2].next == node_ptr_3);

    assert(node_pool[node_ptr_3].previous == node_ptr_2);
    assert(node_pool[node_ptr_3].is_first == false);
    assert(node_pool[node_ptr_3].next == node_ptr_1);

    assert(node_pool[node_ptr_1].previous == node_ptr_3);
    assert(node_pool[node_ptr_1].is_first == true);
    assert(node_pool[node_ptr_1].key == key_0);
    assert(node_pool[node_ptr_1].tag == key_0);
    assert(node_pool[node_ptr_1].value.value == value_0.value);
    assert(node_pool[node_ptr_1].next == 0);
    assert(node_pool[node_ptr_1].last == node_ptr_1);

    assert(node_cache[key_0] == node_ptr_1);

    assert(node_pool[0].previous == 0);
    assert(node_pool[0].is_first == false);
    assert(node_pool[0].next == 0);

    for (node_ptr_t node_ptr_i = node_ptr_4; node_ptr_i < NODE_POOL_SIZE + 1; node_ptr_i++) {
        assert(node_pool[node_ptr_i].previous == 0);
        assert(node_pool[node_ptr_i].is_first == false);
        assert(node_pool[node_ptr_i].next == 0);
    }

    for (key_t key_i = key_1; key_i < NODE_CACHE_SIZE; key_i++) {
        assert(node_cache[key_i] == 0);
    }
}

void run_tests(void) {
    case_1();
    case_2();
    case_3();
    case_4();
    case_5();
    case_6();
    case_7();
    case_8();
    case_9();
    case_10();
    case_11();
    case_12();
    case_13();
    case_14();
    case_15();
    case_16();
    case_17();
    case_18();
    case_19();
    case_20();
    case_21();
    case_22();
    case_23();
    case_24();
    case_25();
    case_26();
    case_27();
    case_28();
    case_29();
    case_30();
    case_31();
    case_32();
    case_33();
    case_34();
    case_35();
    case_36();
    case_37();
    case_38();
    case_39();
    case_40();
    case_41();
    case_42();
    case_43();
    case_44();
    case_45();
    case_46();
    case_47();
    case_48();
    case_49();
    case_50();
    case_51();
    case_52();
    case_53();
    case_54();
    case_55();
    case_56();
    case_57();
    case_58();
    case_59();
    case_60();
    case_61();
    case_62();
    case_63();
    case_64();
    case_65();
    case_66();
    case_67();
    case_68();
    case_69();
    case_70();
    case_71();
    case_72();
    case_73();
    case_74();
    case_75();
    case_76();
    case_77();
    case_78();
    case_79();
    case_80();
    case_81();
    case_82();
    case_83();
    case_84();
    case_85();
    case_86();
    case_87();
    case_88();
    case_89();
    case_90();
    case_91();
    case_92();
    case_93();
    case_94();
    case_95();
    case_96();
    case_97();
}
