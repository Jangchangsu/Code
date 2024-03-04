#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUCKET 1000
#define DATARANGE 100000
#define NUMINSERT 100000
#define NUMUPDATE 100000
#define NUMINSERTTHREADS 10000
#define NUMUPDATETHREADS 1

typedef struct node_t {
    int key;
    struct node_t* next;
} node_t;

typedef struct header_t{
    node_t header;
    pthread_mutex_t lock;
} header_t;

typedef struct list_t {
    header_t* header[BUCKET];
} list_t;

typedef struct rand_t {
    int random[NUMINSERT+NUMUPDATE];
    int count;
    pthread_mutex_t lock;
} rand_t;

rand_t Create_random;

int finalcounting = 0;
void List_Init(header_t* list, int bucket){
    for (int i = 0; i < bucket; i++) {
        list->header[i] = (header_t*)malloc(sizeof(node_t));
        list->header[i]->key = 0;
        list->header[i]->next = NULL;
        pthread_mutex_init(&(                                                                                                                       list->header[i]->lock), NULL);
    }
}

void List_Insert(node_t* header, int value, pthread_t id) {
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    pthread_mutex_init(&(newnode->lock), NULL);
    newnode->key = value;

    pthread_mutex_lock(&(header->lock));
    newnode->next = header->next;
    header->next = newnode;
    pthread_mutex_unlock(&(header->lock));
}

void List_Scan(node_t* header) {
    node_t* curr = header->next;
    while (curr) {
        printf("%d->", curr->key);
        curr = curr->next;
        finalcounting++;
    }
    printf("NULL\n");
}

void List_Lookup(node_t* header, value){
    node_t* curr = header->next;
    while(curr){
        if (curr->key == value){
            printf("Succeed to search value\n");
            return;
        }
    }
    printf("Failed to search value\n");
    return;
}
void* Insert_Operation(void* arg) {
    list_t* list = (list_t*)arg;
    for (int i = 0; i < NUMINSERT / NUMINSERTTHREADS; i++) {
        pthread_mutex_lock(&(Create_random.lock));
        int key = Create_random.random[Create_random.count];
        Create_random.count++;
        pthread_mutex_unlock(&(Create_random.lock));

        int bucket = key / (DATARANGE / BUCKET);
        node_t *curr = header->next;
        while(curr){
            
        }
        List_Insert(list->header[bucket], key, pthread_self());
    }
    return NULL;
}

void* Update_Operation(void* arg){
    list_t *list = (list_t*)arg;
    for (int i = 0; i < NUMUPDATE / NUMUPDATETHREADS; i++){
        pthread_mutex_lock(&(Create_random.lock));
        int key = Create_random.random[Create_random.count];
        Create_random.count++;
        pthrad_mutex_unlock(&(Create_randomn.lock));

        int bucket = key / (DATARANGE / BUCKET);
    }
}

int main() {
    clock_t point1, point2, point4;
    double cpu_time;
    list_t list;
    srand(time(NULL));
    pthread_mutex_init(&(Create_random.lock), NULL);
    Create_random.count = 0;

    for (int i = 0; i < NUMINSERT + NUMUPDATE; i++)
        Create_random.random[i] = (rand() % DATARANGE);

    List_Init(&list, BUCKET);

    point1 = clock();
    pthread_t thread[NUMINSERTTHREADS];
    for (int i = 0; i < NUMINSERTTHREADS; i++)
        pthread_create(&thread[i], NULL, Insert_Operation, &list);
    for (int i = 0; i < NUMINSERTTHREADS; i++)
        pthread_join(thread[i], NULL);
    point2 = clock();
    /*
    pthread_t thread[NUMUPDATETHREADS];
    for (int i = 0; i < NUMUPDATETHREADS; i++)
        pthread_create(&thread[i], NULL, Update_Operation, &list);
    for (int i = 0; i < NUMUPDATETHREADS; i++)
        pthread_join(&thread[i], NULL);
    point3 = clock();
    */
    for (int i = 0; i < BUCKET; i++) {
        printf("%d BucketList is : \n", i);
        List_Scan(list.header[i]);
    }

    cpu_time = ((double)(point2 - point1)) / CLOCKS_PER_SEC;
    printf("final counting is %d\n", finalcounting);
    printf("Total Execution Time is %lf\n", cpu_time);

    return 0;
}
