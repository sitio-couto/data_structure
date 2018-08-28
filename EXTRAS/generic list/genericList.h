#ifndef _LISTA_GENERICA_H
#define _LISTA_GENERICA_H
#define TRUE 1
#define FALSE 0


typedef struct node{
	void *data;
	struct node *nodeProx;
}node;

typedef struct list{
	node *head;
	void (*freeData)( void * );
	int (*compareData)( void * , void * );
	void (*printData)( void * );
}list;

list *initList
(
	void (*freeData)( void * ),
	int (*compareData)( void * , void *),
	void (*printData)( void * )
);

void insertList( list *l , void *data );

void removeList( list *l , void *data );

void printList( list *l );

void freeList( list *l );

//CASO-1 (INT)//
int value;

void free_1( void *data );
int compare_1( void *element , void *data );
void print_1( void *data );
//CASO-2 (INT&CHAR)//
typedef struct nameNode{
	int age;
	char name[20];
}nameNode;

void free_2( void *data );
int compare_2( void *element , void *data );
void print_2( void *data );

#endif
