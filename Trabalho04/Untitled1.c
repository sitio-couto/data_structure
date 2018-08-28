#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ends{
	struct{
		char start;
		char end;
	}firstChain, lastChain;
}ends;

void setValues( ends *firstNlast ){
	firstNlast->firstChain.start = 'a';
	firstNlast->firstChain.end = 'b';
	firstNlast->lastChain.start = 'A';
	firstNlast->lastChain.end = 'B';
}

int main(void){
	ends firstNlast;
	ends *fNl = &firstNlast;
	
	setValues( fNl );
	
	printf("\n%c %c\n%c %c\n",firstNlast.firstChain.start, firstNlast.firstChain.end , firstNlast.lastChain.start , firstNlast.lastChain.end );
	
	return 0;
}
