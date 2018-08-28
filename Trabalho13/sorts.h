#ifndef _SORTS
#define _SORTS

vector scanning( void ){
	int i;
	vector dummy;
	
	scanf(" %i", &dummy.size );
	dummy.vet = malloc( sizeof( int )*dummy.size );
	dummy.auxVet = malloc( sizeof( int )*dummy.size );
	for( i=0 ; i<dummy.size ; ++i ){
		scanf(" %i", &dummy.auxVet[i] );
		dummy.vet[i] = dummy.auxVet[i];
	}
	printf("\n");
	
	return dummy;
}

void resetOrder( vector dummy ){
	int i;
	
	for( i=0 ; i<(dummy.size-1) ; ++i ){
		if( (!flag) && (dummy.vet[i] > dummy.vet[i+1]) ){
			printf("\n\n-->ERROR<--\n\n"); flag = 1;
		}
		dummy.vet[i] = dummy.auxVet[i];
	}
	dummy.vet[dummy.size-1] = dummy.auxVet[dummy.size-1];
	flag = 0;
	
	return;
}

int overtime( void ){
	if( ((clock() - timer)/CLOCKS_PER_SEC) > OVERTIME ){
		flag = 1; return 1;
	}
	
	return 0;
}

void printInfo( long long int timeData[] ){
	int i;
	char name[30];
	scanf(" %s", name );
	FILE *out = fopen( name , "a" );
	
	fprintf( out , "\n" );
	fprintf( out ,"Selection -> %.9lf seg\n", (double)timeData[0]/BI );
	fprintf( out ,"Bubble    -> %.9lf seg\n", (double)timeData[1]/BI );
	fprintf( out ,"Insertion -> %.9lf seg\n", (double)timeData[2]/BI );
	fprintf( out ,"Merge     -> %.9lf seg\n", (double)timeData[3]/BI );
	fprintf( out ,"Quick     -> %.9lf seg\n", (double)timeData[4]/BI );
	fprintf( out ,"Heap      -> %.9lf seg\n", (double)timeData[5]/BI );
	fprintf( out ,"Radix     -> %.9lf seg\n", (double)timeData[6]/BI );
	fprintf( out ,"Shell     -> %.9lf seg\n", (double)timeData[7]/BI );
	fflush( out ); fclose( out );
	
	return;
}

void exeSort( vector dummy , int args , int pos ){
	int i = 0;
	timer = clock( );
	
	do{
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &set );
	
		if( args == 1 ){
			sortType1( dummy );
		}else if( args == 3 ){
			sortType2( dummy , 0 , (dummy.size-1) );
		}
		
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
	
		if( flag ){ 
			printf("\n\n-->OVERTIME<--\n\n");
			timeData[pos] = 0;
			resetOrder( dummy ); 
			return; 
		}else{
			++i; 
			timeData[pos] += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		}
		resetOrder( dummy );
		
	}while( timeData[pos] < BI );
	
	timeData[pos] /= i;
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void selectionSort( vector dummy ){
	int i, min, temp, place = 0;
	
	for( place=0 ; place<(dummy.size-1) ; ++place ){
		min = place;
		for( i=(place+1) ; i<dummy.size ; ++i ){
			if( dummy.vet[i] < dummy.vet[min] ){ min = i ;}							
		} 
		temp = dummy.vet[place];
		dummy.vet[place] = dummy.vet[min];
		dummy.vet[min] = temp;
		if( overtime() ) return;
	}
	
	return;
}

void bubbleSort( vector dummy ){
	int i, temp, check;
	
	do{
		check = 0;
		for( i=0 ; i<(dummy.size - 1) ; ++i ){		
			if( dummy.vet[i] > dummy.vet[i+1] ){							
				check = 1;
				temp = dummy.vet[i+1];
				dummy.vet[i+1] = dummy.vet[i];
				dummy.vet[i] = temp;
			}
		}
		if( overtime() ) return;
	}while(check);
	
	return;
}

void insertionSort( vector dummy ){
	int i, j, k, insertion; 
	
	for( i=1 ; i<dummy.size ; ++i ){
		for( j=0 ; j<i ; ++j ){			
			if( dummy.vet[i] < dummy.vet[j] ){
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
	
	return;
}

void mergeSort( vector dummy, int posicaoInicio, int posicaoFim ) 
{
   int i,j,k,metadeTamanho,*vetorTemp;
   if ( posicaoInicio == posicaoFim ) return;
   
   // ordenacao recursiva das duas metades
   metadeTamanho = ( posicaoInicio+posicaoFim )/2;
   mergeSort( dummy, posicaoInicio, metadeTamanho );
   mergeSort( dummy, metadeTamanho+1, posicaoFim );

   // intercalacao no vetor temporario t
   i = posicaoInicio;
   j = metadeTamanho+1;
   k = 0;
   vetorTemp = (int *) malloc(sizeof(int) * (posicaoFim-posicaoInicio+1));
   
   while( i < metadeTamanho+1 || j  < posicaoFim+1 )
   { 
      if ( i == metadeTamanho+1 )
      { // i passou do final da primeira metade, pegar v[j]
         vetorTemp[k] = dummy.vet[j];
         j++;
         k++;
      } 
      else
      {
         if (j==posicaoFim+1) 
         { 
            // j passou do final da segunda metade, pegar v[i]
            vetorTemp[k] = dummy.vet[i];
            i++;
            k++;
         } 
         else 
         {
            if (dummy.vet[i] < dummy.vet[j]) 
            { 
               vetorTemp[k] = dummy.vet[i];
               i++;
               k++;
            } 
            else
            { 
              vetorTemp[k] = dummy.vet[j];
              j++;
              k++;
            }
         }
      }
      
   }
   // copia vetor intercalado para o vetor original
   for( i = posicaoInicio; i <= posicaoFim; i++ )
   {
      dummy.vet[i] = vetorTemp[i-posicaoInicio];
   }
   free(vetorTemp);
}

void quickSort( vector dummy , int start , int end ){
	int i, j, temp, pivot = start;
	
	if( start >= end ) return;											
	
	for( i=(pivot+1) ; i<=end ; ++i ){
		if( dummy.vet[pivot] > dummy.vet[i] ){
			temp = dummy.vet[i];
			for( j=(i-1) ; j >= pivot ; --j ){
				dummy.vet[j+1] = dummy.vet[j];
			}
			dummy.vet[pivot] = temp;
			++pivot;
		}
		if( overtime() ){ return; }
	}
	
	quickSort( dummy , start , (pivot-1) );if( flag ) return;
	quickSort( dummy , (pivot+1) , end );
	
	return;
}

void quickSort2( vector dummy ){
	int i, j, start, end, temp, pivot = 0;								
	limits *aux, *list = malloc( sizeof( limits ) );
	list->start = 0;
	list->end = (dummy.size - 1);
	list->next = NULL;					
										
	while( list != NULL ){
		start = list->start;
		end = list->end;
		aux = list;
		list = list->next;
		free( aux );
		
		pivot = start;
		for( i=(pivot+1) ; i<=end ; ++i ){							
			if( dummy.vet[pivot] > dummy.vet[i] ){
				temp = dummy.vet[i];
				for( j=(i-1) ; j >= pivot ; --j ){
					dummy.vet[j+1] = dummy.vet[j];
					if( overtime() ) return;
				}
				dummy.vet[pivot] = temp;
				++pivot;
				if( overtime() ) return;															
			}
		}
	
		if( start < (pivot-1) ){
			aux = malloc( sizeof( limits ) );
			aux->start = start;
			aux->end = (pivot - 1);
			aux->next = list;
			list = aux;
		}
		if( (pivot + 1) < end ){
			aux = malloc( sizeof( limits ) );
			aux->start = (pivot + 1);
			aux->end = end;
			aux->next = list;
			list = aux;
		}
	}
	
	return;
}

void heapSort( vector dummy ){
	int i, j, temp, aux = 1;
	
	for( i=1 ; i<dummy.size ; ++i ){
		for( j=i ; j>0 ; j=(j-1)/2 ){
			if( dummy.vet[j] > dummy.vet[(j-1)/2] ){
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
		for( j=0 ; (j*2+1)<i ; j=aux ){
			aux = 2*j + 1;
			if( ((2*j + 2) < i) && (dummy.vet[aux] < dummy.vet[2*j+2]) )
				aux = 2*j + 2; 
			if( dummy.vet[j] >= dummy.vet[aux] ) break;
			temp = dummy.vet[j];
			dummy.vet[j] = dummy.vet[aux];
			dummy.vet[aux] = temp;
		}
		if( overtime() ) return;
	}
	
	return;
}

void radixSort( vector dummy ){
	int j, i, biggest = -1, bucket[10];
	int *temp, *newVet = calloc( sizeof( int ) , dummy.size );
	int pos( int i , int j ){
		return (dummy.vet[i]%(j*10) - dummy.vet[i]%j)/j ;
	}
	
	for( i=0 ; i<dummy.size ; ++i ){
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
		
		memcpy( dummy.vet , newVet , (sizeof( int )*dummy.size) );
	}
	free( newVet );

	return;
}

void shellSort( vector dummy ){
	int temp, i, j, aux, gap;
	
	for( gap=(dummy.size/2); gap>=1 ; gap=(gap/2) ){
		for( i=gap ; i<dummy.size ; ++i ){ 
			if( overtime() ) return;
			if( dummy.vet[i] < dummy.vet[i-gap] ){
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
	
	return;
}





#endif
