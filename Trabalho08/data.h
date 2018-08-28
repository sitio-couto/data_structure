//VINICIUS COUTO ESPINDOLA
//RA: 188115
#ifndef _DATA
#define _DATA
#define TRUE 1
#define FALSE 0
#define UNKNOWN -1

typedef char string[20];

typedef struct node{
	int value;
	struct node *increase;
	struct node *decrease;
}node;

void preOrder( node *root );
void inOrder( node *root );
void postOrder( node *root );
void levelOrder( node **stack , int current , int empty );
void minimum( node *root );
void maximum( node *root );

void insertNode( node **root , int value );
void removeNode( node **parent , int value );
void search( node *root , int value );
int empty( node *root );
int memory( node *root );
int totalNodes( node *root );
void freeTree( node *root );

#endif
