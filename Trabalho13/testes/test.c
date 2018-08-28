#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define M 10E6


void shuffle( long long int *array , size_t n)
{
	long long t;
	long long j;
	long long i;
	
	srand( (unsigned)time( NULL ) );
   if (n > 1) 
   {
      for (i = 0; i < n - 1; i++ ) 
      {
      	j = i + rand() / (RAND_MAX / (n - i) + 1);
      	t = array[j];
      	array[j] = array[i];
      	array[i] = t;
      }
   }
}


int main( void ){
	long long int i, *vet = malloc( sizeof( long long )*M );
	FILE *doc = fopen( "unique1M.txt" , "w" );

	for( i=0 ; i<M ; ++i ){
		vet[i] = i; 
	}
	
	for( i=0 ; i<10000; ++i ) shuffle( vet , M );
	
	fprintf( doc , "1000000" );
	
	for( i=0 ; i<M ; ++i ){
		if( !(i%5) ) fprintf( doc , "\n" );
		fprintf( doc , "%lli " , vet[i] );
	}fprintf( doc , "\n" );
	
	fclose( doc );

	return 0;
}


