#include<stdio.h>

#include "types.h"
#include "sorts.h"

int main( void ){
	int i;
	vector dummy = scanning( );

	sortType1 = &selectionSort;
	exeSort( dummy , 1 , 0 );
	
	sortType1 = &bubbleSort;
	exeSort( dummy , 1 , 1 );
	
	sortType1 = &insertionSort;
	exeSort( dummy , 1 , 2 );

	sortType2 = &mergeSort;
	exeSort( dummy , 3 , 3 );

	sortType1 = &quickSort2;
	exeSort( dummy , 1 , 4 );

	sortType1 = &heapSort;
	exeSort( dummy , 1 , 5 );

	sortType1 = &radixSort;
	exeSort( dummy , 1 , 6 );

	sortType1 = &shellSort;	
	exeSort( dummy , 1 , 7 );

	printInfo( timeData );
	
	free( dummy.vet );
	free( dummy.auxVet );
	
	return 0;
}
