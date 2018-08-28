#include<stdio.h>
#include<stdlib.h>

#include "tiposED.h"
#include "filaED.h"
#include "funcoesED.h"

int main( void ){
	dados info;
	fila Q;
	
	scanf(" %i %i", &info.linhas, &info.colunas );
	
	inicializarFila( &Q );
	info.matM = criar_matM( info.linhas , info.colunas );
	info.matR = criar_matR( info.linhas , info.colunas );
	
	rotular( &info , &Q );
	
	imprimir( &info );
	
	return 0;
}
