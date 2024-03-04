#include <stdio.h>
#include <stdlib.h>
#include <

typedef struct node_t {
    int key;
    struct node_t *left, *right;
} node_t;