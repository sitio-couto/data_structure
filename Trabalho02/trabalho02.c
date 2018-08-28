//VINICIUS COUTO ESPINDOLA
//RA: 188115

#include<stdio.h>
#include<stdlib.h>
//O programa executa os metodos de auto-organizacao e reorganizacao 
//e repassa os custos ao vetor resultados na main.

typedef struct node{
	int n;
	int acessos;
	struct node *nodeProx;
}node;

node* alocar( int elementos );
node* rearranjo( node *HEAD , int elementos );
node* freeing( node *HEAD );
node* testeMTF
(
	node *HEAD,
	int *requisicoes,
	int totalRequisicoes,
	int resultados[]
);
node* testeTR
(
	node *HEAD,
	int *requisicoes,
	int totalRequisicoes,
	int resultados[]
);
node* testeC
(
	node *HEAD,
	int *requisicoes,
	int totalRequisicoes,
	int resultados[]
);

int main(void){
	node *HEAD;
	int i;
	int resultados[3] = { 0 , 0 , 0 };
	int elementos, totalRequisicoes;
	scanf(" %i %i", &elementos, &totalRequisicoes );
	int *requisicoes = malloc( sizeof(int)*totalRequisicoes );
	for( i=0 ; i<totalRequisicoes ; ++i ){
		scanf(" %i", &requisicoes[i] );
	}
	
	HEAD = alocar( elementos );
	
	HEAD = testeMTF( HEAD , requisicoes , totalRequisicoes , resultados );
	
	HEAD = rearranjo( HEAD , elementos );
	
	HEAD = testeTR( HEAD , requisicoes , totalRequisicoes , resultados );
	
	HEAD = rearranjo( HEAD , elementos );
	
	HEAD = testeC( HEAD , requisicoes , totalRequisicoes , resultados );
	
	printf("%i %i %i\n", resultados[0], resultados[1], resultados[2] );
	free( requisicoes ); requisicoes = NULL;
	HEAD = freeing( HEAD );
	return 0;
}

//ALOCACAO DE MEMORIA.
node* alocar( int elementos ){
	int i;
	node *HEAD = malloc(sizeof(node));
	(*HEAD).n = 1;
	(*HEAD).acessos = 0;
	node *AUX = HEAD;
	
	for( i=2 ; i<=elementos ; ++i ){
		(*AUX).nodeProx = malloc(sizeof(node));
		AUX = (*AUX).nodeProx;
		(*AUX).n = i;
		(*AUX).acessos = 0;
	}
	(*AUX).nodeProx = NULL;
	
	return HEAD;
}

//RECUPERACAO DA LISTA ORIGINAL.
node* rearranjo( node *HEAD , int elementos ){
	int i;
	node *auxTemporaria, *auxAnterior, *auxAtual;
	
	for( i=elementos ; i>0 ; --i ){
		
		if( (*HEAD).n != i ){
			auxAnterior = HEAD;
			auxAtual = (*HEAD).nodeProx;
			while( 1 ){
				if( (*auxAtual).n == i ){
					auxTemporaria = auxAtual;
					(*auxAnterior).nodeProx = (*auxAtual).nodeProx;
					(*auxAtual).nodeProx = HEAD;
					HEAD = auxTemporaria;
					break;
				}else{
					auxAnterior = (*auxAnterior).nodeProx;
					auxAtual = (*auxAtual).nodeProx;
				}
			}
		}
	}
	
	return HEAD;
}

//CONTAGEM DO METODO MTF.
node* testeMTF
(
	node *HEAD,
	int *requisicoes,
	int totalRequisicoes,
	int resultados[]
)
{
	int i;
	node *auxTemporaria, *auxAnterior, *auxAtual;
	
	for( i=0 ; i<totalRequisicoes ; ++i ){
		auxAnterior = HEAD;
		if( (*HEAD).n == requisicoes[i] ){
			++resultados[0];
		}else{
			++resultados[0];
			auxAtual = (*HEAD).nodeProx;
			while( 1 ){
				++resultados[0];
				if( (*auxAtual).n == requisicoes[i] ){
					auxTemporaria = auxAtual;
					(*auxAnterior).nodeProx = (*auxAtual).nodeProx;
					(*auxAtual).nodeProx = HEAD;
					HEAD = auxTemporaria;
					break;
				}else{
					auxAnterior = (*auxAnterior).nodeProx;
					auxAtual = (*auxAtual).nodeProx;
				}
			}
		}	
	}
	
	return HEAD;
}

//CONTAGEM DO METODO TR.
node* testeTR
(
	node *HEAD,
	int *requisicoes,
	int totalRequisicoes,
	int resultados[]
)
{
	int i;
	node *auxTemporaria, *auxDoisAnteriores, *auxAnterior, *auxAtual;
	
	for( i=0 ; i<totalRequisicoes ; ++i ){
		if( (*HEAD).n == requisicoes[i] ){//caso seja a cabeca.
			++resultados[1];
		}else if( (*HEAD).nodeProx->n == requisicoes[i] ){//caso seja o segundo.
			resultados[1] += 2;
			auxAtual = (*HEAD).nodeProx;
			(*HEAD).nodeProx = (*auxAtual).nodeProx;
			(*auxAtual).nodeProx = HEAD;
			HEAD = auxAtual;
		}else{//caso generico.
			resultados[1] += 2;
			auxDoisAnteriores = HEAD;
			auxAnterior = (*HEAD).nodeProx;
			auxAtual = (*HEAD).nodeProx->nodeProx;
			while( 1 ){
				++resultados[1];
				if( (*auxAtual).n == requisicoes[i] ){
					auxTemporaria = auxAtual;
					(*auxAnterior).nodeProx = (*auxAtual).nodeProx;
					(*auxTemporaria).nodeProx = auxAnterior;
					(*auxDoisAnteriores).nodeProx = auxTemporaria;
					break;
				}else{
					auxDoisAnteriores = (*auxDoisAnteriores).nodeProx;
					auxAnterior = (*auxAnterior).nodeProx;
					auxAtual = (*auxAtual).nodeProx;
				}
				
			}
		}	
	}
	
	return HEAD;
}

//CONTAGEM DO METODO C.
node* testeC
(
	node *HEAD,
	int *requisicoes,
	int totalRequisicoes,
	int resultados[]
)
{
	int i, check = 0;
	node *auxAnterior, *auxAtual, *novaPosicao, *auxPosicao;
	
	for( i=0 ; i<totalRequisicoes ; ++i ){
		novaPosicao = HEAD;
		check = 0;
		if( (*HEAD).n == requisicoes[i] ){
			++resultados[2];
			++(*HEAD).acessos;
		}else{
			++resultados[2];
			auxAnterior = HEAD;
			auxAtual = (*HEAD).nodeProx;
			while( 1 ){
				++resultados[2];
				//o IF-ELSE abaixo salva previamente as possiveis posicoes que o
				//no desejado pode vir a ocupar, evitando duas passadas.
				if( (*auxAnterior).acessos == ( 1 + (*auxAtual).acessos ) ){
					if( check == 1 ){
						novaPosicao = auxPosicao;
						check = 0;
					}
					auxPosicao = auxAnterior;
					++check;
				}else if( (*auxAnterior).acessos > (1 + (*auxAtual).acessos) ){
					novaPosicao = auxAnterior;
					check = 0;
				}
				
				if( (*auxAtual).n == requisicoes[i] ){
					++(*auxAtual).acessos;
					(*auxAnterior).nodeProx = (*auxAtual).nodeProx;
					if( (*auxAtual).acessos >= (*HEAD).acessos ){
						HEAD = auxAtual;
						(*auxAtual).nodeProx = novaPosicao;
					}else{
						(*auxAtual).nodeProx = (*novaPosicao).nodeProx;
						(*novaPosicao).nodeProx = auxAtual;
					}
					break;
				}else{
					auxAnterior = (*auxAnterior).nodeProx;
					auxAtual = (*auxAtual).nodeProx;
				}
			}
		}
	}
	
	return HEAD;
}

//LIBERANDO A MEMORIA ALOCADA.
node* freeing( node *HEAD ){
	node *auxApagador = (*HEAD).nodeProx;
	
	while( 1 ){
		free( HEAD );
		HEAD = auxApagador;
		if( HEAD == NULL ){  break; }
		auxApagador = (*auxApagador).nodeProx ;
	}
	
	return HEAD;
}







