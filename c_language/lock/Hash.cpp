#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUCKET 10
#define DATARANGE 1000
#define NUMINSERT 100000
#define NUMTHREADS 10

typedef struct node_t { int key; struct node_t* next; pthread_mutex_t lock; } node_t;
typedef struct list_t { node_t* header; pthread_mutex_t lock;}list_t;
typedef struct rand_t { int random[NUMINSERT]; int count; pthread_mutex_t lock; }rand_t;

rand_t random_data;
int finalcounting = 0;

void List_Init(list_t* list){
    list -> header = (node_t*)malloc(sizeof(node_t));
    list -> header -> key = 0;
    list -> header -> next = NULL;
    pthread_mutex_init(&(list->lock), NULL);
}

void List_Insert(node_t* header, int value){
    node_t* curr = (node_t*)malloc(sizeof(node_t));
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    curr = header;
    newnode->key= value;
    while(curr->next != NULL){
        if ((curr->next)->key > value && curr->key < value){
            newnode->next = curr->next;
            curr->next = newnode;
            return;
        }
        else if (curr->next->key == value)
            return;
        curr = curr->next;
    }
    while (curr->next == NULL){
        curr->next = newnode;
        newnode->next = NULL;
        return;
    }
}

void List_scan(node_t* header){
    node_t* curr = (node_t*)malloc(sizeof(node_t));
    curr = header->next;
    while(curr){
        printf("%d ->", curr->key);
        curr = curr->next;
        finalcounting++;
    }
}

void* Insert_Operation(void* arg){
    list_t* list = (list_t*)arg;
    srand(time(NULL));
    for (int i = 0; i < (NUMINSERT/NUMINSERTTHREADS); i++){
        pthread_mutex_lock(&(random_data.lock));
        int key = random_data.random[random_data.count];
        random_data.count++;
        pthread_mutex_unlock(&(random_data.lock));
        pthread_mutex_lock(&(list->lock));
        List_Insert(list->header, key);
        pthread_mutex_unlock(&(list->lock));
    }
    return NULL;
}

int main(){
    clock_t point1, point2;
    double cpu_time;
    list_t list;
    srand(time(NULL));
    pthread_mutex_init(&(random_data.lock), NULL);
    random_data.count = 0;
    for (int i = 0; i < NUMINSERT; i++){
        random_data.random[i] = (rand() % DATARANGE);
    }
    List_Init(&list);
    point1 = clock();
    pthread_t thread[NUMINSERTTHREADS];
    for(int i  = 0; i < NUMINSERTTHREADS; i++){
        pthread_create(&thread[i], NULL, Insert_Operation, &list);
    }
    for(int i = 0; i < NUMINSERTTHREADS; i++){
        pthread_join(thread[i], NULL);
    }
    point2 = clock();

    pthread_mutex_lock(&(list.lock));
    List_scan(list.header);
    pthread_mutex_unlock(&(list.lock));
    cpu_time = ((double)(point2 - point1)) / CLOCKS_PER_SEC;
    printf("final counting is %d\n", finalcounting);
    printf("Total Executing Time is %lf\n", cpu_time);

    return 0;
}