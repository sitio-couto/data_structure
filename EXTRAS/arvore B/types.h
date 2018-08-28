#ifndef TYPES
#define TYPES

#define ORDER 1

typedef struct node{
	int qnt;
	int key[ORDER*2];
	struct node *child[ORDER*2+1];
}node;

typedef struct insertTools{
	node *newPage;
	int pivot;
}insertTools;

int search( node *r , int target );
void found( int check );
void printing( node *r );
int split( node *r , insertTools *tool );
int insert( node *r , int value , insertTools *tool );
node *initTree( int value );
node *upGrowth( node *root , insertTools *tool );

#endif
