//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	char label;
	struct node *left;
	struct node *right;
}node;

typedef char superString[60];

node* rebuild
(
	char *preOrder,
	char *inOrder,
	int leftLimit,
	int rightLimit,
	int *i
);
void postOrder( node *root );
void levelOrder( node **levelStack , int current , int empty , int end );
void releaseMemory( node *root );

int main(void){
	node **levelStack, *root;
	superString buffer;
	char *inOrder, *preOrder;
	int leftLimit, rightLimit, i = 0;

	while( 1 ){
		scanf(" %s", buffer );
		if( feof( stdin ) ){ break; }
		preOrder = malloc( sizeof(char)*strlen( buffer ) );
		strcpy( preOrder , buffer );
		scanf(" %s", buffer );
		inOrder = malloc( sizeof(char)*strlen( buffer ) );
		strcpy( inOrder , buffer );
		leftLimit = 0; rightLimit = strlen( buffer ) - 1 ;

		root = rebuild( preOrder , inOrder , leftLimit , rightLimit , &i );

		postOrder( root ); i = 0; printf(" ");
		
		levelStack = malloc( sizeof(node *)*strlen(buffer) );
		levelStack[0] = root;
		levelOrder( levelStack , 0 , 1 , (strlen(buffer) - 1) );
		printf("\n");
		
		releaseMemory( root ); root = NULL; strcpy( buffer , "" );
		free( preOrder ); free( inOrder ); free( levelStack );
	}

	return 0;
}

node* rebuild
( 
	char *preOrder, 
	char *inOrder, 
	int leftLimit, 
	int rightLimit,
	int *i 
)
{
	int j = 0;
	node *newNode = malloc( sizeof(node) );
	newNode->label = preOrder[*i];
	while( newNode->label != inOrder[j] ){ ++j; }
	
	if( j - 1 >= leftLimit ){
		++(*i);
		newNode->left = rebuild( preOrder , inOrder , leftLimit , j-1 , i );
	}else{
		newNode->left = NULL;
	}
	
	if( j + 1 <= rightLimit ){
		++(*i);
		newNode->right = rebuild( preOrder , inOrder , j+1 , rightLimit , i );
	}else{
		newNode->right = NULL;
	}
	
	return newNode;
}

void postOrder( node *root ){
	
	if( root->left != NULL ){
		postOrder( root->left );
	}
	if( root->right != NULL ){
		postOrder( root->right );
	}
	printf("%c", root->label );
	
	return;
}

void releaseMemory( node* root ){
	
	if( root->left != NULL ){
		releaseMemory( root->left );
	}
	if( root->right != NULL ){
		releaseMemory( root->right );
	}
	free( root );
	
	return;
}

void levelOrder( node **levelStack , int current , int empty , int end ){
	
	if( levelStack[current]->left != NULL ){
		levelStack[empty] = levelStack[current]->left;
		++empty;
	}
	if( levelStack[current]->right != NULL ){
		levelStack[empty] = levelStack[current]->right;
		++empty;
	}
	printf("%c", levelStack[current]->label );
	
	if( current < end ){
		levelOrder( levelStack , (current+1) , empty , end );
	}
	
	return;
}
















