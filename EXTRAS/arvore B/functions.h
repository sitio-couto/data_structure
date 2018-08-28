#ifndef FUNCTIONS
#define FUNCTIONS

void found( int check ){
	if( check ) printf(":)\n");
	else printf(":(\n");
	return;
}

node *upGrowth( node *root , insertTools *tool ){
	node *newRoot = calloc( 1 , sizeof( node ) );
	
	newRoot->qnt = 1;
	newRoot->key[0] = tool->pivot;
	newRoot->child[0] = root;
	newRoot->child[1] = tool->newPage;
	
	return newRoot;
}

int search( node *r , int target ){
	int i;
	if( !r ) return 0;
	
	for( i=0 ; i<r->qnt ; ++i ){
		if( target == r->key[i] ) return 1;
		if( target < r->key[i] ) break;
	}
	
	return search( r->child[i] , target );
}

node* initTree( int value ){
	node *r = calloc( 1 , sizeof( node ) );
	r->key[0] = value;
	++r->qnt;
	return r;
}

void printing( node *r ){
	int i;
	if( !r ) return;
	
	printf("( ");
	for( i=0 ; i<(r->qnt+1) ; ++i ){
		printing( r->child[i] );
		if( i < r->qnt ) printf("%i ", r->key[i] );
	}
	printf(") ");
	
	return;
}

int split( node *r , insertTools *tool ){
	int i, auxKeys[ORDER*2 + 1];
	node *auxChild[ORDER*2 + 2];
	
	for( i=0 ; i<ORDER*2 ; ++i ){
		auxKeys[i] = r->key[i];
		auxChild[i] = r->child[i];
	}
	auxChild[i] = r->child[i];
	
	i = ORDER*2;
	while( ( i > 0 ) && ( tool->pivot < auxKeys[i-1] ) ){
		auxKeys[i] = auxKeys[i-1];
		auxChild[i+1] = auxChild[i];
		--i;
	}
	auxKeys[i] = tool->pivot;
	auxChild[i+1] = tool->newPage;
	
	for( i=0 ; i<ORDER ; ++i ){
		r->key[i] = auxKeys[i];
		r->child[i] = auxChild[i];
		r->key[ORDER*2-1-i] = 0;
		r->child[ORDER*2-i] = NULL;
	}
	r->child[ORDER] = auxChild[ORDER];
	r->qnt = ORDER;
	
	tool->pivot = 	auxKeys[ORDER];
	tool->newPage = calloc( 1 , sizeof( node ) );
	for( i=(ORDER+1) ; i<(ORDER*2+1) ; ++i ){
		tool->newPage->key[i-(ORDER+1)] = auxKeys[i];
		tool->newPage->child[i-(ORDER+1)] = auxChild[i];
	}
	tool->newPage->child[ORDER] = auxChild[ORDER*2+1];
	tool->newPage->qnt = ORDER;
	
	return -1;
}

int insert( node *r , int value , insertTools *tool ){
	int i, j, check;
	if( !r ) return 0;
	
	for( i=0 ; i<r->qnt ; ++i ){
		if( value == r->key[i] ) return 1;
		if( value < r->key[i] ) break;
	}
	
	check = insert( r->child[i] , value , tool );
	if( check == 0 ){
		if( r->qnt < ORDER*2 ){
			for( j=r->qnt ; j>i ; --j ) r->key[j] = r->key[j-1];
			r->key[j] = value;
		}else{
			tool->pivot = value;
			return split( r , tool );
		}
		++r->qnt;
	}else if( check == -1 ){
		if( r->qnt < ORDER*2 ){
			for( i=0 ; i<r->qnt ; ++i ){
				if( tool->pivot < r->key[i] ) break;
			}
			for( j=r->qnt ; j>i ; --j ){
				r->key[j] = r->key[j-1];
				r->child[j+1] = r->child[j];
			}
			r->key[i] = tool->pivot;
			r->child[i+1] = tool->newPage;
			++r->qnt;
		}else{
			return split( r , tool );
		}
	}

	return 1;
}

#endif
