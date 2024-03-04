#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define DATARANGE 1000
#define ELEMENTNUM 100000
#define NUMTHREADS 10

typedef struct node_t {int key; struct node_t *left, *right;} node_t;


node_t* Create_node(int value){
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    if (newnode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newnode->key = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

int main(){
    node_t* root = Create_node(0);
    printf("root address: %p\n", (void*)root);
    printf("root key: %d \n", root->key);
    printf("root left : %p \n", (void*)root->left);
    printf("root right: %p \n", (void*)root->right);
    
    free(root); // 메모리 해제
    return 0;
}
