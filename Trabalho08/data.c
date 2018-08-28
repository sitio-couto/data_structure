#ifndef _DATA
#define _DATA

typedef char string[20];

typedef struct node{
	int value;
	struct node *increase;
	struct node *decrease;
}node;

void preOrder( node *root );
void inOrder( node *root );
void postOrder( node *root );

void insertNode( node **root , int value );
int empty( node *root );
int memory( node *root );

#endif
