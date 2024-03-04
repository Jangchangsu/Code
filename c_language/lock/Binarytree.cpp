#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int key;
    struct node_t *left, *right;
} node_t;

void assert_node(node_t* node){
    if (node == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
}

node_t* Create_node(int value){
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    assert_node(newnode);
    newnode->key = value;
    newnode->left = NULL;
    newnode->right = NULL;
    printf("%p, ", (void*)newnode);
    printf("%d\n", newnode->key);
    return newnode;
}

node_t* Search_empty(node_t* node, node_t* parent){
    if (parent == NULL) {
        return NULL;
    }
    
    if (parent->key == node->key){
        return NULL;
    }
    else if (parent->key > node->key){
        if (parent->left != NULL){
            return Search_empty(node, parent->left);
        }
        else{
            return parent;
        }
    }
    else{
        if (parent->right != NULL){
            return Search_empty(node, parent->right);
        }
        else{
            return parent;
        }
    }
}

node_t* Search_key(int value, node_t* parent){
    if(parent == NULL) {
        return NULL;
    }
    
    if(parent->key == value){
        return parent;
    }
    else if (parent->key > value){
        if(parent->left != NULL){
            return Search_key(value, parent->left);
        }
        else{
            return NULL;
        }
    }
    else{
        if(parent->right != NULL){
            return Search_key(value, parent->right);
        }
        else{
            return NULL;
        }
    }
}

void Insert_node(int value, node_t* root){
    node_t* newnode = Create_node(value);
    node_t* parent = NULL;
    parent = Search_empty(newnode, root);
    if (parent != NULL){
        if(parent->key > newnode->key){
            parent->left = newnode;
        }
        else{
            parent->right = newnode;
        }
    }
    else{
        printf("Already allocated\n");
    }
}

node_t* min_value_search(node_t* parent){
    printf("given parent parameter : %p\n", (void*)parent);
    if (parent == NULL){
        return NULL;
    }
    if (parent->left->left == NULL){
        int temp = parent->left->key;
        free(parent->left);
        parent->left = NULL;
        return temp;
    }
    else{
        return min_value_search(parent->left);
    }
}

void Delete_node(int value, node_t* root) {
    node_t* target = Search_key(value, root);
    if (target == NULL) {
        printf("Can not find the target value to delete\n");
        return;
    }
    printf("target key : %d \n", target->key);
    printf("target address : %p \n", (void*)target);
    printf("target left : %p\n", (void*)target->left);
    printf("target right : %p\n", (void*)target->right);

    if (target->right != NULL) {
        target->key = min_value_search(target->right);
        printf("replace key : %d \n", replace->key);
        printf("replace address : %p \n", (void*)replace);
        target->key = replace->key;
        printf("after target key : %d\n", target->key);
        printf("after target address : %p\n", (void*)target);

    } else {
        // 오른쪽 자식이 없는 경우
        // 삭제할 노드가 리프 노드이거나 왼쪽 자식만 가지고 있는 경우
        node_t* temp = target;
        target = target->left;
        free(temp);
        temp = NULL;
        printf("Succeed to release memory1\n");
    }
}


void inorder(node_t* root){
    if(root == NULL) {
        return;
    }
    else{
        printf("root address : %d\n", root->key);
        if(root->left != NULL){
            printf("root->left address : %d\n", (root->left)->key);
        }
        if(root->right != NULL){
            printf("root->right address : %d\n", (root->right)->key);
        }
        inorder(root->left);
        printf("|%d\n", root->key);
        inorder(root->right);
    }
}


int main(){
    node_t* root = Create_node(19);
    Insert_node(4, root);
    Insert_node(17, root);
    Insert_node(25, root);
    Insert_node(20, root);
    Insert_node(15, root);
    Delete_node(4, root);
    inorder(root);
    return 0;
}
