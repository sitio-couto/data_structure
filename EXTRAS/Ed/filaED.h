#ifndef _FILA
#define _FILA

void inicializarFila( fila *Q ){
	Q->comeco = NULL;
	Q->fim = NULL;
	return;
}

int filaVazia( fila *Q ){
	return ( Q->comeco == NULL );
}

void inserirNo( fila *Q , int i , int j ){
	no *novo = malloc( sizeof( no ) );
	novo->prox = NULL;
	novo->i = i;
	novo->j = j;
	
	if( filaVazia( Q ) ){
		Q->comeco = novo;
	}else{
		Q->fim->prox = novo;
	}
	Q->fim = novo;
	
	return;
}

void removerNo( fila *Q ){
	no *temp;
	
	if( !filaVazia( Q ) ){
		temp = Q->comeco->prox;
		free( Q->comeco );
		Q->comeco = temp;
		if( Q->comeco == NULL ){
			Q->fim = NULL;
		}
	}
	
	return;
}

#endif
