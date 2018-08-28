#ifndef _TYPES
#define _TYPES

#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#define BI 1000000000
#define OVERTIME 300

typedef struct vector{
	int size;
	int *vet;
	int *auxVet;
}vector;

typedef struct limits{
	unsigned start;
	unsigned end;
	struct limits *next; 
}limits;

int timer, flag = 0;
struct timespec set, lap;
long long int timeData[8] = {0,0,0,0,0,0,0,0};

void (*sortType1)( vector );
void (*sortType2)( vector , int , int );

void resetOrder( vector dummy );
int overtime( void );
void printInfo( long long int timeData[] );
void selectionSort( vector dummy );
void bubbleSort( vector dummy );
void insertionSort( vector dummy );
void mergeSort( vector dummy , int posicaoInicio, int posicaoFim );
void quickSort( vector dummy , int start , int end );
void heapSort( vector dummy );
void radixSort( vector dummy );
void shellSort( vector dummy );

void exeSort( vector dummy , int args , int pos );

#endif
