#ifndef _FUNCTIONS
#define _FUNCTIONS

node *createTree( char *currentChar ){
	node *newNode = NULL;

	scanf(" %c", currentChar );
	if( (*currentChar) == '(' ){
		newNode = allocNode( );
		newNode->left = createTree( currentChar );
	}else if( (*currentChar) == ')' ){
		return NULL;
	}	
	
	if( newNode->left != NULL ){
		scanf(" %lf:", &newNode->leftWeight );
	}
	scanf(" %i %c", &newNode->data , currentChar );
	
	if( (*currentChar) == ':' ){
		scanf(" %lf %c", &newNode->rightWeight , currentChar );
	}
	
	newNode->right = createTree( currentChar );
	scanf(" %c", currentChar );

	return newNode;
}

node *allocNode( void ){
	node *newNode = malloc( sizeof( node ) );
	newNode->leftWeight = 0;
	newNode->rightWeight = 0;
	newNode->right = NULL;
	newNode->left = NULL;
	
	return newNode;
}

double pathFinder( node *root ){
	double bigger = 0, auxiliar;
	
	if( root != NULL ){
		bigger = (root->leftWeight) + pathFinder( root->left );
		auxiliar = (root->rightWeight) + pathFinder( root->right );
		if( bigger < auxiliar ){
			bigger = auxiliar;
		}
	}
	
	return bigger;
}

node *cutDownTree( node *root ){
	
	if( root != NULL ){
		root->left = cutDownTree( root->left );
		root->right = cutDownTree( root->right );
		free( root );
	}
	
	return NULL;
}

#endif
