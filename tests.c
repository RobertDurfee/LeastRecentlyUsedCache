#include <assert.h>
#include <stdio.h>
#include "cache.h"
#include "tests.h"

static unsigned int k0 = 0;
static unsigned int k1 = 1;
static unsigned int k2 = 2;
static unsigned int k3 = 3;

static struct Value v0 = { 0 };
static struct Value v1 = { 1 };
static struct Value v2 = { 2 };

static key_value_pointer_t n1 = 1;
static key_value_pointer_t n2 = 2;
static key_value_pointer_t n3 = 3;
static key_value_pointer_t n4 = 4;
static key_value_pointer_t n5 = 5;

void reset(void) {
    for (unsigned int i = 0; i < POOL_SIZE + 1; i++) {
        pool[i].previous = 0;
        pool[i].tag = 0;
        pool[i].key = 0;
        pool[i].is_header = false;
        pool[i].value.value = 0;
        pool[i].next = 0;
        pool[i].last = 0;
    }
    for (unsigned int i = 0; i < CACHE_SIZE; i++) {
        cache[i] = 0;
    }
    next = 1;
    least_recently_used = 0;
    most_recently_used = 0;
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

    assert(next == n1);
    assert(least_recently_used == 0);
    assert(most_recently_used == 0);

    for (unsigned int i = 0; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = 0; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                              0 <- |H1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n2; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                              0 <- |H1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n2; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put_new(k1, k1, &v1);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n1);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n1);
    assert(cache[k1] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append_new(k0, k0, &v1);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == 0);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                              0 <- |H1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n2; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                              0 <- |H1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put(k1, k1, &v1);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k1);
    assert(pool[n1].tag == k1);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k1] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n2; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    assert(cache[k0] == 0);

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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

    append(k0, k0, &v1);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    for (unsigned int i = 0; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k0; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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

    put_new(k0, k0, &v0);
    append(k0, k0, &v1);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    for (unsigned int i = 0; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k0; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                              0 <- |H1 | -> 0                              |\n"
        "|                                   `---'                                   |\n"
        "|                                    `-^                                    |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n2);
    assert(least_recently_used == n1);
    assert(most_recently_used == n1);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n2; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put_new(k0, k0, &v0);
    put_new(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 2 | <=> | 1 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put_new(k1, k1, &v1);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    append_new(k0, k0, &v1);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == false);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);

    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H2 | <=> |H1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(k1, k1, &v1);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n2);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k1);
    assert(pool[n1].tag == k1);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n2);
    assert(cache[k1] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append(k0, k0, &v1);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == false);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);

    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put_new(k0, k0, &v0);
    put_new(k1, k1, &v1);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n1);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n1);
    assert(cache[k1] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k1] == n2);
    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 2 | <=> |H1 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put_new(k1, k1, &v1);

    assert(next == n4);
    assert(least_recently_used == n2);
    assert(most_recently_used == n3);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n3);
    assert(pool[n1].last == n1);

    assert(pool[n3].previous == n1);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n1);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put_new(k2, k2, &v2);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n1);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k2);
    assert(pool[n3].tag == k2);
    assert(pool[n3].value.value == v2.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n1);
    assert(cache[k1] == n2);
    assert(cache[k2] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k3; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H2 | <=> |H1 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append_new(k0, k0, &v1);

    assert(next == n4);
    assert(least_recently_used == n2);
    assert(most_recently_used == n3);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n2);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n3);
    assert(pool[n1].last == n3);

    assert(pool[n3].previous == n1);
    assert(pool[n3].is_header == false);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);

    assert(cache[k1] == n2);
    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H1 | <=> |H2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append_new(k1, k1, &v2);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n1);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == false);
    assert(pool[n3].value.value == v2.value);
    assert(pool[n3].next == 0);

    assert(cache[k0] == n1);
    assert(cache[k1] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H2 | <=> |H1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n2);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k1] == n2);
    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H1 | <=> |H2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(k1, k1, &v1);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n1);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k0] == n1);
    assert(cache[k1] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H2 | <=> |H1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                               `-^       `-^                               |\n"
        "\n"
    );

    put(k2, k2, &v2);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n2);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k2);
    assert(pool[n1].tag == k2);
    assert(pool[n1].value.value == v2.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k1] == n2);
    assert(cache[k2] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    assert(cache[k0] == 0);

    for (unsigned int i = k3; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append(k0, k0, &v1);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == 0);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H2 | <=> | 1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    append(k1, k1, &v2);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k1);
    assert(pool[n2].tag == k1);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == false);
    assert(pool[n1].value.value == v2.value);
    assert(pool[n1].next == 0);

    assert(cache[k1] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    assert(cache[0] == 0);

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- |H1 | <=> | 2 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                `---------^                                |\n"
        "\n"
    );

    put_new(k0, k0, &v0);
    append_new(k0, k0, &v1);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == 0);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );

    put_new(k1, k1, &v1);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n1);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );

    append_new(k0, k0, &v2);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == n2);
    assert(pool[n1].last == n3);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].value.value == v1.value);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == false);
    assert(pool[n3].value.value == v2.value);
    assert(pool[n3].next == 0);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 2 | <=> |H1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 2 | <=> |H1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(k1, k1, &v1);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k1);
    assert(pool[n1].tag == k1);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k1] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    assert(cache[0] == 0);

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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

    append(k0, k0, &v1);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == 0);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k0; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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

    put_new(k0, k0, &v0);
    put_new(k0, k0, &v0);
    append(k0, k0, &v1);
    append(k0, k0, &v2);

    assert(next == n3);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == 0);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k0; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                         0 <- | 2 | <=> |H1 | -> 0                         |\n"
        "|                              `---'     `---'                              |\n"
        "|                                         `-^                               |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n3);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k0);
    assert(pool[n1].tag == k0);
    assert(pool[n1].value.value == v0.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n3; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put_new(k0, k0, &v0);
    append_new(k0, k0, &v1);
    put_new(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 3 | <=> | 1 | <=> | 2 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n5);
    assert(least_recently_used == n3);
    assert(most_recently_used == n4);

    assert(pool[n3].previous == 0);
    assert(pool[n3].is_header == false);
    assert(pool[n3].next == n1);

    assert(pool[n1].previous == n3);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n4);

    assert(pool[n4].previous == n2);
    assert(pool[n4].is_header == true);
    assert(pool[n4].key == k0);
    assert(pool[n4].tag == k0);
    assert(pool[n4].value.value == v0.value);
    assert(pool[n4].next == 0);
    assert(pool[n4].last == n4);

    assert(cache[k0] == n4);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 1 | <=> | 2 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(k1, k1, &v1);

    assert(next == n5);
    assert(least_recently_used == n1);
    assert(most_recently_used == n4);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == n4);
    assert(pool[n3].last == n3);

    assert(pool[n4].previous == n3);
    assert(pool[n4].is_header == true);
    assert(pool[n4].key == k1);
    assert(pool[n4].tag == k1);
    assert(pool[n4].value.value == v1.value);
    assert(pool[n4].next == 0);
    assert(pool[n4].last == n4);

    assert(cache[k0] == n3);
    assert(cache[k1] == n4);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 1 | <=> | 2 | <=> |H3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                          `---------^                      |\n"
        "\n"
    );

    append_new(k0, k0, &v1);

    assert(next == n5);
    assert(least_recently_used == n1);
    assert(most_recently_used == n4);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == n4);
    assert(pool[n3].last == n4);

    assert(pool[n4].previous == n3);
    assert(pool[n4].is_header == false);
    assert(pool[n4].value.value == v1.value);
    assert(pool[n4].next == 0);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 2 | <=> |H3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(k1, k1, &v1);

    assert(next == n4);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == n1);
    assert(pool[n3].last == n3);

    assert(pool[n1].previous == n3);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k1);
    assert(pool[n1].tag == k1);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n3);
    assert(cache[k1] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 2 | <=> |H3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );

    append(k0, k0, &v1);

    assert(next == n4);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n3);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k0);
    assert(pool[n3].tag == k0);
    assert(pool[n3].value.value == v0.value);
    assert(pool[n3].next == n1);
    assert(pool[n3].last == n1);

    assert(pool[n1].previous == n3);
    assert(pool[n1].is_header == false);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);

    assert(cache[k0] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k1; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );
    
    put_new(k0, k0, &v0);
    put_new(k0, k0, &v0);
    put_new(k1, k1, &v1);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 2 | <=> | 1 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(k0, k0, &v0);

    assert(next == n5);
    assert(least_recently_used == n2);
    assert(most_recently_used == n4);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == false);
    assert(pool[n2].next == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n3);

    assert(pool[n3].previous == n1);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n4);
    assert(pool[n3].last == n3);

    assert(pool[n4].previous == n3);
    assert(pool[n4].is_header == true);
    assert(pool[n4].key == k0);
    assert(pool[n4].tag == k0);
    assert(pool[n4].value.value == v0.value);
    assert(pool[n4].next == 0);
    assert(pool[n4].last == n4);

    assert(cache[k1] == n3);
    assert(cache[k0] == n4);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 3 | <=> | 1 | <=> |H2 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );

    put_new(k1, k1, &v1);

    assert(next == n5);
    assert(least_recently_used == n3);
    assert(most_recently_used == n4);

    assert(pool[n3].previous == 0);
    assert(pool[n3].is_header == false);
    assert(pool[n3].next == n1);

    assert(pool[n1].previous == n3);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n4);
    assert(pool[n2].last == n2);

    assert(pool[n4].previous == n2);
    assert(pool[n4].is_header == true);
    assert(pool[n4].key == k1);
    assert(pool[n4].tag == k1);
    assert(pool[n4].value.value == v1.value);
    assert(pool[n4].next == 0);
    assert(pool[n4].last == n4);

    assert(cache[k0] == n2);
    assert(cache[k1] == n4);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 1 | <=> |H2 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );

    put_new(k2, k2, &v2);

    assert(next == n5);
    assert(least_recently_used == n1);
    assert(most_recently_used == n4);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n4);
    assert(pool[n3].last == n3);

    assert(pool[n4].previous == n3);
    assert(pool[n4].is_header == true);
    assert(pool[n4].key == k2);
    assert(pool[n4].tag == k2);
    assert(pool[n4].value.value == v2.value);
    assert(pool[n4].next == 0);
    assert(pool[n4].last == n4);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);
    assert(cache[k2] == n4);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k3; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 1 | <=> |H3 | <=> |H2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^        `---------^                      |\n"
        "\n"
    );

    append_new(k0, k0, &v1);

    assert(next == n5);
    assert(least_recently_used == n1);
    assert(most_recently_used == n4);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n3);

    assert(pool[n3].previous == n1);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n2);
    assert(pool[n3].last == n3);

    assert(pool[n2].previous == n3);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n4);
    assert(pool[n2].last == n4);

    assert(pool[n4].previous == n3);
    assert(pool[n4].is_header == false);
    assert(pool[n4].value.value == v1.value);
    assert(pool[n4].next == 0);

    assert(cache[k1] == n3);
    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|               0 <- | 1 | <=> |H2 | <=> |H3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^        `---------^                      |\n"
        "\n"
    );

    append_new(k1, k1, &v2);

    assert(next == n5);
    assert(least_recently_used == n1);
    assert(most_recently_used == n4);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n4);
    assert(pool[n3].last == n4);

    assert(pool[n4].previous == n3);
    assert(pool[n4].is_header == false);
    assert(pool[n4].value.value == v2.value);
    assert(pool[n4].next == 0);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n5; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H3 | <=> |H2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(k0, k0, &v0);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n2);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n3);

    assert(pool[n3].previous == n1);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n2);
    assert(pool[n3].last == n3);

    assert(pool[n2].previous == n3);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == 0);
    assert(pool[n2].last == n2);

    assert(cache[k1] == n3);
    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );

    put(k1, k1, &v1);

    assert(next == n4);
    assert(least_recently_used == n1);
    assert(most_recently_used == n3);

    assert(pool[n1].previous == 0);
    assert(pool[n1].is_header == false);
    assert(pool[n1].next == n2);

    assert(pool[n2].previous == n1);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == 0);
    assert(pool[n3].last == n3);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H2 | <=> |H3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );

    put(k2, k2, &v2);

    assert(next == n4);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n1);
    assert(pool[n3].last == n3);

    assert(pool[n1].previous == n3);
    assert(pool[n1].is_header == true);
    assert(pool[n1].key == k2);
    assert(pool[n1].tag == k2);
    assert(pool[n1].value.value == v2.value);
    assert(pool[n1].next == 0);
    assert(pool[n1].last == n1);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);
    assert(cache[k2] == n1);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k3; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H3 | <=> |H2 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(k0, k0, &v1);

    assert(next == n4);
    assert(least_recently_used == n3);
    assert(most_recently_used == n1);

    assert(pool[n3].previous == 0);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n2);
    assert(pool[n3].last == n3);

    assert(pool[n2].previous == n3);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n1);
    assert(pool[n2].last == n1);

    assert(pool[n1].previous == n2);
    assert(pool[n1].is_header == false);
    assert(pool[n1].value.value == v1.value);
    assert(pool[n1].next == 0);

    assert(cache[k1] == n3);
    assert(cache[k0] == n2);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- |H2 | <=> |H3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );

    append(k1, k1, &v2);

    assert(next == n4);
    assert(least_recently_used == n2);
    assert(most_recently_used == n1);

    assert(pool[n2].previous == 0);
    assert(pool[n2].is_header == true);
    assert(pool[n2].key == k0);
    assert(pool[n2].tag == k0);
    assert(pool[n2].value.value == v0.value);
    assert(pool[n2].next == n3);
    assert(pool[n2].last == n2);

    assert(pool[n3].previous == n2);
    assert(pool[n3].is_header == true);
    assert(pool[n3].key == k1);
    assert(pool[n3].tag == k1);
    assert(pool[n3].value.value == v1.value);
    assert(pool[n3].next == n1);
    assert(pool[n3].last == n1);

    assert(pool[n1].previous == n3);
    assert(pool[n1].is_header == false);
    assert(pool[n1].value.value == v2.value);
    assert(pool[n1].next == 0);

    assert(cache[k0] == n2);
    assert(cache[k1] == n3);

    assert(pool[0].previous == 0);
    assert(pool[0].is_header == false);
    assert(pool[0].next == 0);

    for (unsigned int i = n4; i < POOL_SIZE + 1; i++) {
        assert(pool[i].previous == 0);
        assert(pool[i].is_header == false);
        assert(pool[i].next == 0);
    }

    for (unsigned int i = k2; i < CACHE_SIZE; i++) {
        assert(cache[i] == 0);
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
        "|                    0 <- | 1 | <=> |H2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );
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
        "|               0 <- | 2 | <=> | 3 | <=> | 1 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> |H2 | <=> | 3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `---------^        `-^                     |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> |H2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `-------------------^                      |\n"
        "\n"
    );
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
        "|                    0 <- | 3 | <=> | 1 | <=> |H2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> | 3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> |H2 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- | 2 | <=> |H1 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- | 3 | <=> |H1 | <=> |H2 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                               `-^       `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> |H2 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^       `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H2 | <=> |H3 | <=> |H1 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^        `---------^                      |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> |H3 | <=> |H2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^        `---------^                      |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> |H2 | <=> |H3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^       `-^        `---------^                      |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> |H3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> |H3 | <=> |H2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> |H2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> |H3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^       `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H3 | <=> |H1 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H3 | <=> |H2 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> |H3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> |H2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                          `-^        `---------^                           |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> |H2 | <=> | 3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `---------^        `-^                     |\n"
        "\n"
    );
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
        "|               0 <- | 2 | <=> | 3 | <=> |H1 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> |H2 | <=> | 3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^        `---------^        `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H2 | <=> | 3 | <=> |H1 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `---------^         `---------^                      |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> |H2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^        `-------------------^                      |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> | 3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- | 3 | <=> |H1 | <=> |H2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> | 3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- | 3 | <=> |H1 | <=> | 2 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H2 | <=> | 3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> | 2 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                         `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- | 3 | <=> |H1 | <=> | 2 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                `---------^        `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> | 2 | <=> |H3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `---------^        `-^       `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H3 | <=> |H1 | <=> | 2 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                     `-^        `-------------------^                      |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> | 2 | <=> |H3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `---------^         `---------^                      |\n"
        "\n"
    );
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
        "|                    0 <- | 2 | <=> |H3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> | 2 | <=> |H3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `---------^        `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- | 2 | <=> |H3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                    `-^       `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );
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
        "|                    0 <- | 2 | <=> |H3 | <=> | 1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                     `---------^                           |\n"
        "\n"
    );
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
        "|                    0 <- |H1 | <=> | 2 | <=> | 3 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                           `-------------------^                           |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> | 2 | <=> | 3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `-------------------^        `-^                     |\n"
        "\n"
    );
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
        "|               0 <- |H1 | <=> | 2 | <=> | 3 | <=> | 4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                      `-----------------------------^                      |\n"
        "\n"
    );
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
        "|                    0 <- | 2 | <=> | 3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );
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
        "|                    0 <- | 2 | <=> | 3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );
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
        "|               0 <- | 1 | <=> | 2 | <=> | 3 | <=> |H4 | -> 0               |\n"
        "|                    `---'     `---'     `---'     `---'                    |\n"
        "|                                                   `-^                     |\n"
        "\n"
    );
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
        "|                    0 <- | 2 | <=> | 3 | <=> |H1 | -> 0                    |\n"
        "|                         `---'     `---'     `---'                         |\n"
        "|                                              `-^                          |\n"
        "\n"
    );
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
