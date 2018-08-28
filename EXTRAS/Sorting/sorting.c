#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define OVERTIME 30

typedef struct vector{
	int size;
	int *vet;
	int *auxVet;
}vector;

typedef unsigned long long int llu;

typedef struct data{
	llu op;
	llu rp;
	llu clock;
}data;
data info[8];
int check, count = 0;
char sort[30];
llu timer, lap, operations = 0, repetitions = 0;

void resetOrder( vector dummy );
int overtime( void );
void print( vector dummmy );
void printInfo( data info[] );
void selectionSort( vector dummy );
void bubbleSort( vector dummy );
void insertionSort( vector dummy );
void mergeSort( vector dummy , int start , int endLeft , int endRight );
void quickSort( vector dummy , int start , int end );
void heapSort( vector dummy );
void radixSort( vector dummy );
void shellSort( vector dummy );

int main( void ){
	vector dummy; 
	int i;
	
	scanf(" %i", &dummy.size );
	dummy.vet = malloc( sizeof( int )*dummy.size );
	dummy.auxVet = malloc( sizeof( int )*dummy.size );
	for( i=0 ; i<dummy.size ; ++i ){
		scanf(" %i", &dummy.auxVet[i] );
		dummy.vet[i] = dummy.auxVet[i];
	}
	printf("\n");
	
	timer = clock( ); strcpy( sort , "SELECTION" );
	selectionSort( dummy );
	info[0].clock = (clock() - timer);
	resetOrder( dummy );
	
	timer = clock( );	strcpy( sort , "BUBBLE" );
	bubbleSort( dummy );
	info[1].clock = (clock() - timer);
	resetOrder( dummy );
	
	timer = clock( ); strcpy( sort , "INSERTION" );
	insertionSort( dummy );
	info[2].clock = (clock() - timer);
	resetOrder( dummy );
	
	timer = clock( ); strcpy( sort , "MERGE" ); check = 0;
	mergeSort( dummy , 0 , ((dummy.size-1)/2) , (dummy.size-1) );
	if( !check ){
		printf("--->MERGE<---------------------------------------\n");
		print( dummy );
		info[3].clock = (clock() - timer);
	}else{ resetOrder( dummy ); check = 0; }
	resetOrder( dummy );
	
	timer = clock( ); strcpy( sort , "QUICK" );
	quickSort( dummy , 0 , (dummy.size-1) );
	if( !check ){
		printf("--->QUICK<---------------------------------------\n");
		print( dummy );
		info[4].clock = (clock() - timer);
	}else{ resetOrder( dummy ); check = 0; } 	
	resetOrder( dummy );
	
	timer = clock( ); strcpy( sort , "HEAP" );
	heapSort( dummy );
	info[5].clock = (clock() - timer );	
	resetOrder( dummy );
	
	timer = clock( ); strcpy( sort , "RADIX" );
	radixSort( dummy );
	info[6].clock = (clock() - timer); 	
	resetOrder( dummy );
	
	timer = clock( ); strcpy( sort , "SHELL");
	shellSort( dummy );
	info[7].clock = (clock() - timer); 	
	resetOrder( dummy );
	
	printInfo( info );
	
	free( dummy.vet );
	free( dummy.auxVet );
	return 0;
}

void printInfo( data info[] ){
	int i; 
	double reffExe;
	llu reffClock;
	
	reffExe = ((double)info[0].op/(double)info[0].rp);
	for( i=0 ; i<8 ; ++i ){
		if( i == 6 ){ ++i; }
		if( reffExe < ((double)info[i].op/(double)info[i].rp) ){
			reffExe = (double)info[i].op/(double)info[i].rp;
		}
	}
	
	printf("COMPARATIVE EXECUTION EFFICIENCY:\n");
	if( reffExe == 0 ){
		printf("NULLIFIED-> too few elements\n"); 
	}else{ i = 0;
	printf("Selection -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	printf("Bubble    -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	printf("Insertion -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	printf("Merge     -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	printf("Quick     -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	printf("Heap      -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	printf("Radix     -> 100.00%%\n");++i;
	printf("Shell     -> %.2lf%%\n", 100*((double)info[i].op/(double)info[i].rp)/reffExe );++i;
	}
	
	reffClock = info[0].clock;
	for( i=0 ; i<8 ; ++i ){
		if( reffClock > info[i].clock ){
			reffClock = info[i].clock;
		}
	}
	
	printf("\nCOMPARATIVE TIME EFFICIENCY:\n");
	if( reffClock <= 0 ){ 
		printf("NULLIFIED-> too short time\n"); 
	}else{
	printf("Selection -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[0].clock) );
	printf("Bubble    -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[1].clock) );
	printf("Insertion -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[2].clock) );
	printf("Merge     -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[3].clock) );
	printf("Quick     -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[4].clock) );
	printf("Heap      -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[5].clock) );
	printf("Radix     -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[6].clock) );
	printf("Shell     -> %.2lf%%\n", (double)(100*reffClock)/(double)(info[7].clock) );
	}
	
	return;
}

int overtime( void ){
	if( ((clock() - timer)/CLOCKS_PER_SEC) > OVERTIME ){
		printf("\n-----------------------------------------\n");
		printf(" TIME LIMIT exceded for %s sort", sort );
		printf("\n-----------------------------------------\n");
		check = 1;
		return 1;
	}
	
	return 0;
}

void resetOrder( vector dummy ){
	int i;
	
	for( i=0 ; i<dummy.size ; ++i ){
		dummy.vet[i] = dummy.auxVet[i];
	}
	
	return;
}

void print( vector dummy ){
	int i, start = (dummy.size-5), end1 = 5;
	double efficiency;
	
	info[count].op = operations; info[count].rp = repetitions; ++count;
	
	if( (dummy.size-1) <= end1 ){ end1 = dummy.size; start = (dummy.size+1);}
	else if( (dummy.size-1) < 10 ){ start = 5; }
	
	for( i=0 ; i<end1 ; ++i ){
		printf("| %i ", dummy.vet[i] );
	}
	if( dummy.size > 10 ) printf("| ... ");
	
	
	for( i=start ; i<dummy.size ; ++i ){
		printf("| %i ", dummy.vet[i] );
	}
	
	printf("|\nOPERATIONS: %llu || REPETITIONS: %llu \n", operations, repetitions );
	if( operations == 0 ){
		printf("SPECIFIC EXECUTION EFFICIENCY: <unexecuted> \n\n", efficiency );
	}else{
		efficiency = ((double)operations/(double)repetitions);
		printf("SPECIFIC EXECUTION EFFICIENCY: %.2lf%% \n\n", efficiency*100 );
	}

	repetitions = 0; operations = 0;
	
	return;
}

void selectionSort( vector dummy ){
	int i, min, temp, place = 0;
	
	for( place=0 ; place<(dummy.size-1) ; ++place ){
		min = place;
		for( i=(place+1) ; i<dummy.size ; ++i ){
			if( dummy.vet[i] < dummy.vet[min] ){ min = i ;}							++repetitions;
		}																							if( place != min ) ++operations; 
		temp = dummy.vet[place];
		dummy.vet[place] = dummy.vet[min];
		dummy.vet[min] = temp;
		if( overtime() ) return;
	}
	
	printf("--->SELECTION<-----------------------------------\n");
	print( dummy );
	
	return;
}

void bubbleSort( vector dummy ){
	int i, temp, check;
	
	do{
		check = 0;
		for( i=0 ; i<(dummy.size - 1) ; ++i ){								++repetitions;
			if( dummy.vet[i] > dummy.vet[i+1] ){							++operations;
				check = 1;
				temp = dummy.vet[i+1];
				dummy.vet[i+1] = dummy.vet[i];
				dummy.vet[i] = temp;
			}
		}
		if( overtime() ) return;
	}while(check);
	
	printf("--->BUBBLE<--------------------------------------\n");
	print( dummy );
	
	return;
}

void insertionSort( vector dummy ){
	int i, j, k, insertion; 
	
	for( i=1 ; i<dummy.size ; ++i ){
		for( j=0 ; j<i ; ++j ){													++repetitions;
			if( dummy.vet[i] < dummy.vet[j] ){								++operations;
				insertion = dummy.vet[i]; 										
				for( k=(i-1) ; k>=j ; --k ){									
					dummy.vet[k+1] = dummy.vet[k];
				}
				dummy.vet[j] = insertion;
				break;
			}
		}
		if( overtime() ) return;
	}
	
	printf("--->INSERTION<-----------------------------------\n");
	print( dummy );
	
	return;
}

void mergeSort( vector dummy , int start ,  int endLeft , int endRight ){
	int i, j, temp, rightStart = (endLeft+1);
	
	if( (!check) && (start < endLeft) ){
		mergeSort( dummy , start , ((endLeft-start)/2)+start , endLeft );
	}
	if( (!check) && (rightStart < endRight) ){													
		mergeSort( dummy , rightStart , ((endRight-endLeft)/2)+endLeft , endRight );
	}																						repetitions+=2;
	
	if( check ){ return; }
	while( rightStart <= endRight ){
		
		for( i=start ; i<=endLeft ; ++i ){	
			if( overtime() ){ return; }											++repetitions;
			if( dummy.vet[rightStart] < dummy.vet[i] ){
				temp = dummy.vet[rightStart];
				for( j=endLeft ; j>=i ; --j ){
					dummy.vet[j+1] = dummy.vet[j];
				}
				dummy.vet[i] = temp;
				start = (i+1);
				endLeft = rightStart;												++operations;
				break;
			}
		}
		++rightStart;
	}
	
	return;	
}

void quickSort( vector dummy , int start , int end ){
	int i, j, temp, pivot = start;									++repetitions;
	
	if( start >= end ) return;											
	
	for( i=(pivot+1) ; i<=end ; ++i ){								++repetitions;
		if( dummy.vet[pivot] > dummy.vet[i] ){
			temp = dummy.vet[i];
			for( j=(i-1) ; j >= pivot ; --j ){
				dummy.vet[j+1] = dummy.vet[j];
			}
			dummy.vet[pivot] = temp;
			++pivot;															++operations;
		}
		if( overtime() ){ return; }
	}
	
	quickSort( dummy , start , (pivot-1) );if( check ) return;
	quickSort( dummy , (pivot+1) , end );
	
	return;
}

void heapSort( vector dummy ){
	int i, j, temp, aux = 1;
	
	for( i=1 ; i<dummy.size ; ++i ){
		for( j=i ; j>0 ; j=(j-1)/2 ){														++repetitions;
			if( dummy.vet[j] > dummy.vet[(j-1)/2] ){									++operations;
				temp = dummy.vet[j];
				dummy.vet[j] = dummy.vet[(j-1)/2];
				dummy.vet[(j-1)/2] = temp;
			}
		}
		if( overtime() ) return;
	}

	for( i=(dummy.size-1) ; i>0 ; --i ){
		temp = dummy.vet[0];
		dummy.vet[0] = dummy.vet[i];
		dummy.vet[i] = temp;
		for( j=0 ; (j*2+1)<i ; j=aux ){													repetitions+=3;
			aux = 2*j + 1;
			if( ((2*j + 2) < i) && (dummy.vet[aux] < dummy.vet[2*j+2]) )
				aux = 2*j + 2; 
			if( dummy.vet[j] >= dummy.vet[aux] ) break;								++operations;
			temp = dummy.vet[j];
			dummy.vet[j] = dummy.vet[aux];
			dummy.vet[aux] = temp;
		}
		if( overtime() ) return;
	}
	
	printf("--->HEAP<----------------------------------------\n");
	print( dummy );
	
	return;
}

void radixSort( vector dummy ){
	int j, i, biggest = -1, bucket[10];
	int *temp, *newVet = malloc( sizeof( int )*dummy.size );
	int pos( int i , int j ){
		return (dummy.vet[i]%(j*10) - dummy.vet[i]%j)/j ;
	}
	
	for( i=0 ; i<dummy.size ; ++i ){												++repetitions;
		if( dummy.vet[i] < 0 ){
			printf("\n-----\nERROR: radix denies negative values\n-----\n\n"); 
			return;
		}
		if( dummy.vet[i] > biggest ){ biggest = dummy.vet[i]; }
	}
	
	for( j=1 ; j<=biggest ; j*=10 ){												
		for( i=0 ; i<10 ; ++i ){ bucket[i] = 0; }
		
		for( i=0 ; i<dummy.size ; ++i ){												
			++bucket[pos( i , j )];														
		}
		
		for( i=1 ; i<10 ; ++i ){														
			bucket[i] += bucket[i-1];
		}
		
		for( i=(dummy.size-1) ; i>=0 ; --i ){										
			--bucket[pos( i , j )];														
			newVet[ bucket[pos( i , j )] ] = dummy.vet[i];
		}
		
		temp = dummy.vet;
		dummy.vet = newVet;
		newVet = temp;
		if( overtime() ) return;
	}
	free( newVet );
	
	printf("--->RADIX<---------------------------------------\n");
	print( dummy );
	
	return;
}

void shellSort( vector dummy ){
	int temp, i, j, aux, gap;
	
	for( gap=(dummy.size/2); gap>=1 ; gap=(gap/2) ){
		for( i=gap ; i<dummy.size ; ++i ){ 
			if( overtime() ) return;												++repetitions;
			if( dummy.vet[i] < dummy.vet[i-gap] ){								++operations;
				aux = i;
				do{
					temp = dummy.vet[aux];
					dummy.vet[aux] = dummy.vet[aux-gap];
					dummy.vet[aux-gap] = temp;
					aux = aux - gap;
					if( (aux - gap) < 0 ) break;
				}while( dummy.vet[aux] < dummy.vet[aux-gap] );
			}
		}
	}
	
	printf("--->SHELL<---------------------------------------\n");
	print( dummy );
	
	return;
}

/*
10
9 8 7 6 5 4 3 2 1 0
*/










