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

unsigned int i = 0;
typedef char superString[60];

node* rebuild( char *preOrder, char *inOrder, int leftLimit, int rightLimit );
void postOrder( node *root );
void levelOrder(  );
void releaseMemory( node *root );

int main(void){
	node *root;
	superString buffer;
	char *inOrder, *preOrder;
	int leftLimit, rightLimit;
	int currentLevel, levelWanted, totalPrints, endPrint;

	while( 1 ){
		scanf(" %s", buffer );
		if( feof( stdin ) ){ break; }
		preOrder = malloc( sizeof(char)*strlen( buffer ) );
		strcpy( preOrder , buffer );
		scanf(" %s", buffer );
		inOrder = malloc( sizeof(char)*strlen( buffer ) );
		strcpy( inOrder , buffer );
		leftLimit = 0; rightLimit = strlen( buffer ) - 1 ;

		root = rebuild( preOrder , inOrder , leftLimit , rightLimit );

		postOrder( root ); i = 0; printf(" ");
		
		totalPrints = 0 ; levelWanted = 1 ; endPrint = strlen( buffer );
		while( totalPrints<endPrint ){
			levelOrder( root , &currentLevel , levelWanted , &totalPrints );
			++levelWanted;
		}
		printf("\n");
		
		releaseMemory( root ); root = NULL;
		free( preOrder ); free( inOrder ); strcpy( buffer , "" );
	}

	return 0;
}

node* rebuild( char *preOrder, char *inOrder , int leftLimit, int rightLimit ){
	int j = 0;
	node *newNode = malloc( sizeof(node) );
	newNode->label = preOrder[i];
	while( newNode->label != inOrder[j] ){ ++j; }
	
	if( j - 1 >= leftLimit ){
		++i;
		newNode->left = rebuild( preOrder , inOrder , leftLimit , (j-1) );
	}else{
		newNode->left = NULL;
	}
	
	if( j + 1 <= rightLimit ){
		++i;
		newNode->right = rebuild( preOrder , inOrder , (j+1) , rightLimit );
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

void levelOrder
( 
	node *root, 
	int *currentLevel, 
	int levelWanted, 
	int *totalPrints 
)
{
	++(*currentLevel);

	if( (*currentLevel) == levelWanted ){ 
		printf("%c", root->label );
		++(*totalPrints);
	}else{

		if( root->left != NULL ){
			levelOrder( root->left , currentLevel , levelWanted , totalPrints );
		}
		if( root->right != NULL ){
			levelOrder( root->right , currentLevel , levelWanted , totalPrints );
		}
	}
	
	--(*currentLevel);
	return;
}
















