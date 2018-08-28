#include<stdio.h>

int main(void){
	int *HEAD1, *HEAD2 = NULL;
	int i = 3.14;
	HEAD1 = &i;
	
	printf("\nHEAD1 -> %i ||(*HEAD1) -> %i \nHEAD2 -> %i ||(*HEAD2) -> NULL", HEAD1, (*HEAD1), HEAD2 );

	return 0;
}
