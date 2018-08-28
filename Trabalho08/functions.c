#ifndef _FUNCTIONS
#define _FUNCTIONS

void minimum( node *root ){
	
	if( root->decrease != NULL ){
		minimum( root->decrease );
	}else{
		printf("%i\n", root->value );
	}
	
	return;
}

void maximum( node *root ){
	
	if( root->increase != NULL ){
		maximum( root->increase );
	}else{
		printf("%i\n", root->value );
	}
	
	return;
}

void preOrder( node *root ){
	
	if( root != NULL ){
		printf("%i " , root->value );
		preOrder( root->decrease );
		preOrder( root->increase );	
	}
	
	return;
}

void inOrder( node *root ){
	
	if( root != NULL ){
		inOrder( root->decrease );
		printf("%i " , root->value );
		inOrder( root->increase );	
	}
	
	return;
}

void postOrder( node *root ){
	
	if( root != NULL ){
		postOrder( root->decrease );
		postOrder( root->increase );
		printf("%i " , root->value );	
	}
	
	return;
}

void levelOrder( node **stack , int current , int empty ){
	
	if( stack[current]->decrease != NULL ){
		stack[empty] = stack[current]->decrease;
		++empty;
	}
	if( stack[current]->increase != NULL ){
		stack[empty] = stack[current]->increase;
		++empty;
	}
	printf("%i ", stack[current]->value );
	
	if( current != (empty - 1) ){
		levelOrder( stack , (current + 1) , empty );
	}
	
	return;
}

int empty( node *root ){
	
	if( root == NULL ){
		printf("vazia\n");
		return TRUE;
	}
	
	return FALSE;
}

int totalNodes( node *root ){
	int i = 0;
	
	if( root != NULL ){
		++i;
		i += totalNodes( root->decrease );
		i += totalNodes( root->increase );
	}
	
	return i;
}

void insertNode( node **root , int value ){
	
	if( (*root) == NULL ){
		(*root) = malloc( sizeof( node ) );
		if( memory( *root ) ){
			(*root)->value = value;
			(*root)->decrease = NULL;
			(*root)->increase = NULL;  
		}
	}else if( value < (*root)->value ){
		insertNode( &(*root)->decrease , value );
	}else if( value > (*root)->value ){
		insertNode( &(*root)->increase , value );
	}
	
	return;
}

int memory( node *root ){
	
	if( root == NULL ){
		printf("memoria insuficiente\n");
		return FALSE;
	}
	
	return TRUE;
}

void removeNode( node **parent , int value ){
	node *temp, *mendSpot;

	if( (*parent) != NULL ){
		if( value == (*parent)->value ){
			if( checkChildren( (*parent) ) == TRUE ){
				mendSpot = (*parent)->decrease;
				temp = (*parent)->increase;
				free( (*parent) ); (*parent) = mendSpot;
				while( mendSpot->increase != NULL){
					mendSpot = mendSpot->increase;
				}
				
				mendSpot->increase = temp;
			}else if( checkChildren( (*parent) ) == FALSE ){
				free( (*parent) );
				(*parent) = NULL;
			}else if( (*parent)->decrease != NULL ){
				temp = (*parent)->decrease;
				free( (*parent) );
				(*parent) = temp;
			}else if( (*parent)->increase != NULL ){
				temp = (*parent)->increase;
				free( (*parent) );
				(*parent) = temp;
			}
			
		}else if( value < (*parent)->value ){
			removeNode( &(*parent)->decrease , value );
		}else{
			removeNode( &(*parent)->increase , value );
		}
	}
	
	return;
}

int checkChildren( node *root ){
	if( (root->decrease == NULL) && (root->increase == NULL) ){
		return FALSE;
	}else if( (root->decrease != NULL)&&(root->increase != NULL) ){
		return TRUE;
	}

	return -1;	
}
void search( node *root , int value ){
	
	if( root != NULL ){
		if( root->value == value ){
			printf("pertence\n");
		}else if( value < root->value ){
			search( root->decrease , value );
		}else{
			search( root->increase , value );
		}
	}else{
		printf("nao pertence\n");
	}
	
	return;
}

void freeTree( node *root ){
	
	if( root != NULL ){
		freeTree( root->decrease );
		freeTree( root->increase );
		free( root );
	}
	
	return;
}
 
#endif
