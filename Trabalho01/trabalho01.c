//vinicius couto espindola 
//RA:188115

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//pragmas de funcoes
double** jagArray( double tamanho );
void scanning( double tamanho , double **array );
void calculos( double tamanho, double elementos, double **array );
double** freeing( double **array , double tamanho );

int main( void ){
	
	double tamanho, elementos;
	scanf(" %lf", &tamanho );
	
	elementos = ( tamanho*tamanho + tamanho )/2 ; 
	double **array = jagArray( tamanho );
	
	scanning( tamanho , array );
	
	calculos( tamanho, elementos, array );
	
	array = freeing( array , tamanho );
	
	return 0;
}

//alocando o jagged array.
double **jagArray( double tamanho ){
	int i, j;
	double **array;
	
	array = malloc( tamanho*sizeof(double *) );
	
	for( i=0 ; i<tamanho ; ++i ){
		array[i] = malloc( (i+1)*sizeof(double) );
	}
	
	return array;
}

//lendo a entrada.
void scanning( double tamanho , double **array ){
	int i, j;
	
	for( i=0 ; i<tamanho ; ++i ){
		for( j=0 ; j<=i ; ++j ){
			scanf(" %lf", &array[i][j] );
		}
	}
	
}

//calculando a saida.
void calculos( double tamanho, double elementos, double **array ){
	int i, j;
	double desvio, media, somatoria = 0;

	for( i=0 ; i<tamanho ; ++i ){
		for( j=0 ; j<=i ; ++j ){
			somatoria += array[i][j];
		}
	}
	
	media = somatoria/elementos;
	somatoria = 0;
	
	for( i=0 ; i<tamanho ; ++i ){
		for( j=0 ; j<=i ; ++j ){
			somatoria += pow( (array[i][j]-media) , 2 );
		}
	}
	
	desvio = sqrt(somatoria/elementos);
	
	for( i=0 ; i<tamanho ; ++i ){
		for( j=0 ; j<=i ; ++j ){
			printf("%.12lf ", ((array[i][j]-media)/desvio) );
		}
		printf("\n");
	}
	
	printf("\n%.12lf %.12lf \n", media, desvio );
	
}

//liberando memoria.
double** freeing( double **array , double tamanho ){
	int i;
	
	for( i=0 ; i<tamanho ; ++i ){
		free( array[i] );
	}
	free( array );
	
	return NULL;	
}



