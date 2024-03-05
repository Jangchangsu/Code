#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BUCKETRANGE 10
#define DATARANGE 1000
#define BUCKET (DATARANGE/BUCKETRANGE)
#define NUMINSERT 10000
#define NUMSEARCH 10000
#define NUMINSERTTHREADS 100
#define NUMSEARCHTHREADS 1

#define EMPTY -1

typedef struct node{
    int key;
    struct node *next;
}node;

typedef struct header{
    int num;
    node *next;
    pthread_mutex_t lock;
}header;

typedef struct headerlist{
    header *headers[BUCKET];
}headerlist;

typedef struct listType1{
    int random[NUMINSERT];
    int count;
    pthread_mutex_t lock;
}listType1;

typedef struct listType2{
    int random[NUMSEARCH];
    int count;
    pthread_mutex_t lock;
}listType2;

listType1 insertList;
listType2 searchList;

int scanCount = 0;
int insertCount = 0;
int searchCount = 0;
int searchHistory[NUMSEARCH];

header* createHeader(){
    header* newheader = (header*)malloc(sizeof(header));
    newheader->num = EMPTY;
    newheader->next = NULL;
    pthread_mutex_init(&(newheader->lock), NULL);
    return newheader;
}

node* createNode(int value){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->key = value;
    newnode->next = NULL;
    return newnode;
}

void initHeaderlist(headerlist* headerslist){
    for (int i = 0 ; i < BUCKET; i++){
        headerslist->headers[i] = createHeader();
    }
}

void initiListType1(){
    srand(time(NULL));
    for (int i = 0; i < NUMINSERT; i++){
        insertList.random[i] = (rand() % DATARANGE);
    }
    insertList.count = 0;
    pthread_mutex_init(&(insertList.lock), NULL);
}

void initiListType2(){
    srand(time(NULL));
    for (int i = 0; i < NUMINSERT; i++){
        searchList.random[i] = (rand() % DATARANGE);
    }
    searchList.count = 0;
    pthread_mutex_init(&(searchList.lock), NULL);
}

node* searchNode(header *header, int target){
    node* curr = header->next;
    while(target == EMPTY){
        if(curr->next == NULL){
            return curr;
        }
        curr = curr->next;
    }
    while(target != EMPTY){
        if(curr->next != NULL){
            if(curr->next != NULL && curr->key == target){
                return curr;
            }
            curr = curr->next;
        }
        else{
            return NULL;
        }
    }
    return NULL;
}

void insertNode(header *header, int value){
    if(header->num == EMPTY){
        header->next = createNode(value);
    }
    else{
        node* temp = searchNode(header, EMPTY);
        temp->next = createNode(value);
    }
    header->num++;
}

void scanBucket(header *header){
    node *curr = header->next;
    while(curr){
        printf("%d->", curr->key);
        curr = curr->next;
        scanCount++;
    }
    printf("NULL\n");
}

void* insertOper(void* arg){
    headerlist *headerslist = (headerlist*)arg;
    for (int i = 0; i < NUMINSERT/NUMINSERTTHREADS; i++){
        pthread_mutex_lock(&(insertList.lock));
        int selectBucket = insertList.random[insertList.count] / BUCKETRANGE;
        pthread_mutex_lock(&(headerslist->headers[selectBucket]->lock));
        int temp = insertList.random[insertList.count];
        insertList.count++;
        pthread_mutex_unlock(&(insertList.lock));
        insertNode(headerslist->headers[selectBucket],temp);
        pthread_mutex_unlock(&(headerslist->headers[selectBucket]->lock));
        insertCount++;
    }
    return NULL;
}

void* searchOper(void* arg){
    headerlist *headerslist = (headerlist*)arg;
    for(int i = 0; i < NUMSEARCH/NUMSEARCHTHREADS; i++){
        pthread_mutex_lock(&(searchList.lock));
        int selectBucket = searchList.random[insertList.count] / BUCKETRANGE;
        pthread_mutex_lock(&(headerslist->headers[selectBucket]->lock));
        int temp = searchList.random[searchList.count];
        searchList.count++;
        pthread_mutex_unlock(&(searchList.lock));
        searchCount++;
        if (NULL != searchNode(headerslist->headers[selectBucket],temp)){
            searchHistory[searchCount] = 1;
        }
        else{
            searchHistory[searchCount] = 0;
        }
        pthread_mutex_unlock(&(headerslist->headers[selectBucket]->lock));
    }
    return NULL;
}


int main(){
    clock_t point1, point2, point3;
    double cpu_time;
    headerlist headerslist;

    initiListType1();
    initiListType2();
    point1 = clock();

    initHeaderlist(&headerslist);
    pthread_t insertThreads[NUMINSERTTHREADS];
    pthread_t searchThreads[NUMSEARCHTHREADS];
    for (int i = 0; i < NUMINSERTTHREADS; i++){
        pthread_create(&insertThreads[i], NULL, insertOper, &headerslist);
    }
    for (int i = 0; i < NUMSEARCHTHREADS; i++){
        pthread_create(&searchThreads[i], NULL, searchOper, &headerslist);
    }
    for (int i = 0; i < NUMINSERTTHREADS; i++){
        pthread_join(insertThreads[i], NULL);
    }
    for (int i = 0; i < NUMSEARCHTHREADS; i++){
        pthread_join(searchThreads[i], NULL);
    }
    point2 = clock();

    for (int i = 0; i < BUCKET; i++){
        printf("BUCKET NUM : %d\n", i);
        scanBucket(headerslist.headers[i]);
    }
    cpu_time = ((double)(point2 - point1)) / CLOCKS_PER_SEC;

    printf("--------------Search Histroy--------------\n");
    for (int i = 0; i < searchCount; i++){
        printf("%d->", searchHistory[i]);
    } 
    printf("Finish\n");
    printf("--------------print Count List--------------\n");
    printf("Scan count%d\n", scanCount);
    printf("Insert count%d\n", insertCount);
    printf("Search count%d\n", searchCount);
    printf("--------------print Running Time List--------------\n");
    printf("Total Execution Time is %lf\n", cpu_time);
    return 0;
}