#ifndef _DATA
#define _DATA

typedef struct node{
	int data;
	struct node *left;
	struct node *right;
	double leftWeight;
	double rightWeight;
}node;

node *createTree( char *currentChar );
node *allocNode( void );
double pathFinder( node *root );
node *cutDownTree( node *root );

#endif
