#ifndef _FUNCOES
#define _FUNCOES

char **criar_matM( int linhas , int colunas ){
	int i, j;
	char **matM = malloc( sizeof( char * )*linhas );
	
	for( i=0 ; i<linhas ; ++i ){
		matM[i] = malloc( sizeof( char )*colunas );
	}
	
	for( i=0 ; i<linhas ; ++i ){
		for( j=0 ; j<colunas ; ++j ){
			scanf(" %c", &matM[i][j] );
		}
	}

	return matM;
}

int **criar_matR( int linhas , int colunas ){
	int i;
	int **matR = malloc( sizeof( int * )*linhas );
	
	for( i=0 ; i<linhas ; ++i ){
		matR[i] = calloc( sizeof( int ) , colunas );
	}
	
	return matR;
}

void rotular( dados *info , fila *Q ){
	int i, auxi, j, auxj, r = 1;
	
	for( i=0 ; i<(info->linhas) ; ++i ){
		for( j=0 ; j<(info->colunas) ; ++j ){
			if( info->matM[i][j] == 'X' ){
				info->matR[i][j] = -1 ;
			}else if( info->matR[i][j] == 0 ){
				info->matR[i][j] = r;
				inserirNo( Q , i , j );
				while( !filaVazia( Q ) ){
					auxi = Q->comeco->i; 
					auxj = Q->comeco->j;
					removerNo( Q );
					componente( Q , info , auxi , auxj , r );
				}
				
				++r;
			}
		}
	}
	
	return;
}

void componente( fila *Q , dados *info , int i , int j , int r ){
	adjacente( Q , info , i , (j+1) , r );
	adjacente( Q , info , (i+1) , j , r );
	adjacente( Q , info , i , (j-1) , r );
	adjacente( Q , info , (i-1) , j , r );
	return;
}

void adjacente( fila *Q , dados *info , int i , int j , int r ){
	if( dentroDoLimite( info , i , j ) ){
		if( info->matM[i][j] == 'X' ){
			info->matR[i][j] = -1 ;
		}else if( info->matR[i][j] == 0 ){
			info->matR[i][j] = r ;
			inserirNo( Q , i , j );
		}
	}

	return;
}

int dentroDoLimite( dados *info , int i , int  j ){
	return (i>=0)&&(i<info->linhas)&&(j>=0)&&(j<info->colunas) ;
}

void imprimir( dados *info ){
	for( i=0 ; i<(info->linhas) ; ++i ){
		for( j=0 ; j<(info->colunas) ; ++j ){
			if( info->matR[i][j] != -1 ){
				printf("%i ", info->matR[i][j] );
			}else{
				printf("X ");
			}
		}
		printf("\n");
	}
	
	return;
};


#endif
