#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
typedef struct node_t
{
	int key;
	struct node_t* next;
}node_t;
typedef struct list_t
{
	node_t* head;
	pthread_mutex_t lock;
}list_t;
void List_Init(list_t* L)
{
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}
int List_Insert(list_t* L, int Key)
{
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	if (newnode == NULL)
	{
		perror("failed the insert the data");
		return -1;
	}
	newnode->key = Key;
	if (L->head == NULL)
	{
		L->head = newnode;
		newnode->next = NULL;
	}
	else
	{
		newnode->next = L->head;
		L->head = newnode;
	}
	return 0;
}
int List_Lookup(list_t* L, int Key)
{
	pthread_mutex_lock(&L->lock);
	node_t* curr = L->head;
	while (curr)
	{
		if (curr->key == Key)
		{
			pthread_mutex_unlock(&L->lock);
			return 0;
		}
		curr = curr->next;
	}
	pthread_mutex_unlock(&L->lock);
	return -1;
}
void List_get(list_t* L)
{
	pthread_mutex_lock(&L->lock);
	node_t* curr = L->head;
	while (curr)
	{
		printf("Data is %d\n", curr->key);
		curr = curr->next;
	}
	pthread_mutex_unlock(&L -> lock);
	return;
}
void* operate(void* L)
{
	list_t* list = (list_t*) L;
	for (int i = 1; i < 10001; i++)
	{
		if (List_Lookup(list, i) == -1)
		{
			pthread_mutex_lock(&(list->lock));
			if (List_Insert(list, i) == -1)
				i--;
			pthread_mutex_unlock(&(list->lock));
		}
	}
	return NULL;
}
int main(void* arg)
{
	clock_t point1, point2;
	double cpu_time;
	list_t list;
	pthread_t thread1, thread2, thread3, thread4;
	point1 = clock();
	List_Init(&list);
	pthread_create(&thread1, NULL, operate, &list);
	pthread_create(&thread2, NULL, operate, &list);
	pthread_create(&thread3, NULL, operate, &list);
	pthread_create(&thread4, NULL, operate, &list);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	point2 = clock();
	List_get(&list);
	cpu_time = ((double)(point2 - point1)) / CLOCKS_PER_SEC;
	printf("Total execution time is %f sec", cpu_time);
    return 0;
}