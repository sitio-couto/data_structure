#ifndef _TYPES
#define _TYPES

typedef struct node{
	int row;
	int colunm;
	int value;
}node;

typedef struct data{
	int amount;
	int maxRow;
	node **entry;
}data;

typedef struct csr{
	int amount;
	int maxRow;
	int *values;
	int *colunms;
	int *rows;
}csr;

data *initializeData( void );
data *adjustEntry( void );
int compare( char test , int rs , int i , node **entry );
void mergeSort( node **entry , int start , int endLeft , int endRight , char v );
csr *setCSRMatrix( data *elements );
data *freeElements( data *elements );
void search( int row , int colunm , csr *matrix );
csr *freeCSR( csr *matrix );

#endif

