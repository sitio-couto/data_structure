#include<stdio.h>
#include<stdlib.h>
#define T 1
#define MAX_CHAVES 2*T - 1 //Quantidade m?xima de chaves
#define MAX_FILHOS 2*T //Quantidade m?xima de filhos
#define MIN_OCUP T - 1 //Ocupa??o m?nima em cada n?
#define TRUE 1
#define FALSE 0
typedef struct no_arvoreB arvoreB;

struct no_arvoreB {
   int num_chaves; //Quantidades de chaves contida no n?
   int chaves[MAX_CHAVES]; //Chaves armazenadas no n?
   arvoreB *filhos[MAX_FILHOS]; //Ponteiro para os filhos
};

void press( arvoreB *r ){
	int i;
	if( !r ) return;
	printf("( ");
	
	for( i=0 ; i<r->num_chaves ; ++i ){
		press( r->filhos[i] );
		printf("%i ", r->chaves[i] );
	}
	press( r->filhos[i] );
	
	printf(") ");
}

int busca_binaria(arvoreB *no, int info) 
{ 
  int meio, i, f; 
  i = 0;
  f = no->num_chaves-1;

  while (i <= f)
  {
    meio = (i + f)/2;
    if (no->chaves[meio] == info)
       return(meio); //Encontrou. Retorna a pos???o em que a chave est?.
    else if (no->chaves[meio] > info)
            f = meio - 1;
         else i = meio + 1;
  }
  return(i); //N?o encontrou. Retorna a posi??o do ponteiro para o filho.
}

int busca(arvoreB *raiz, int info)
{
  arvoreB *no;
  int pos; //posi??o retornada pelo busca bin?ria.

  no = raiz;
  while (no != NULL)
   {
     pos = busca_binaria(no, info);
     if (pos < no->num_chaves && no->chaves[pos] == info)
         return(TRUE);
     else no = no->filhos[pos];
   }
  return(FALSE);
}


//Insere uma chave e o ponteiro para o filho da direita em um n?
void insere_chave(arvoreB *raiz, int info, arvoreB *filhodir)
{
  int k, pos;

  //busca para obter a posi??o ideal para inserir a nova chave
  pos = busca_binaria(raiz, info);
  k = raiz->num_chaves;

  //realiza o remanejamento para manter as chaves ordenadas
  while (k > pos && info < raiz->chaves[k-1])
  {
    raiz->chaves[k] = raiz->chaves[k-1];
    raiz->filhos[k+1] = raiz->filhos[k];
    k--;
  }
  //insere a chave na posi??o ideal
  raiz->chaves[pos] = info;
  raiz->filhos[pos+1] = filhodir;
  raiz->num_chaves++;
}

//Realiza a busca do n? para inserir a chave e faz as subdivis?es quando necess?rias
arvoreB *insere(arvoreB *raiz, int info, int *h, int *info_retorno)
{
  int i, j, pos,
      info_mediano; //auxiliar para armazenar a chave que ir? subir para o pai
  arvoreB *temp, *filho_dir; //ponteiro para o filho ? direita da chave 

  if (raiz == NULL)
   {
     //O n? anterior ? o ideal para inserir a nova chave (chegou em um n? folha)
     *h = TRUE;
     *info_retorno = info;
     return(NULL);
   }
  else {
         pos = busca_binaria(raiz,info);
         if (raiz->num_chaves > pos && raiz->chaves[pos] == info)
           {
             *h = FALSE;
           }
         else {
                               //desce na ?rvore at? encontrar o n? folha para inserir a chave.
               filho_dir = insere(raiz->filhos[pos],info,h,info_retorno);
               if (*h) //Se TRUE deve inserir a info_retorno no n?.
                 {
                     if (raiz->num_chaves < MAX_CHAVES) //Tem espa?o na p?gina
                     {
                       insere_chave(raiz, *info_retorno, filho_dir);
                       *h = FALSE;
                     }
                   else { //Overflow. Precisa subdividir
                          temp = (arvoreB *) malloc (sizeof(arvoreB));
                          temp->num_chaves = 0;

                         //inicializa filhos com NULL
                         for (i = 0; i < MAX_FILHOS; i++)
                           temp->filhos[i] = NULL;

                         //elemento mediano que vai subir para o pai
                         info_mediano = raiz->chaves[MIN_OCUP];

                         //insere metade do n? raiz no temp (efetua subdivis?o)
                         temp->filhos[0] = raiz->filhos[MIN_OCUP+1];
                         for (i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
                           insere_chave(temp, raiz->chaves[i], raiz->filhos[i+1]);

                         //atualiza n? raiz. 
                         for (i = MIN_OCUP; i<MAX_CHAVES; i++)
                         {
                           raiz->chaves[i] = 0;
                           raiz->filhos[i+1] = NULL;
                         }
                         raiz->num_chaves = MIN_OCUP;

                         //Verifica em qual n? ser? inserida a nova chave
                         if (pos <= MIN_OCUP)
                              insere_chave(raiz, *info_retorno, filho_dir);
                         else insere_chave(temp, *info_retorno, filho_dir);

                         //retorna o mediano para inser?-lo no n? pai e o temp como filho direito do mediano.
                         *info_retorno = info_mediano;
                         return(temp);
                       }
                 }
              }
     }
}

arvoreB *insere_arvoreB(arvoreB *raiz, int info)
{
  int h;
  int info_retorno, i;
  arvoreB *filho_dir, *nova_raiz;

  filho_dir = insere(raiz,info,&h,&info_retorno);
  if (h)
   { //Aumetar? a altura da ?rvore
     nova_raiz = (arvoreB *) malloc (sizeof(arvoreB));
     nova_raiz->num_chaves = 1;
     nova_raiz->chaves[0] = info_retorno;
     nova_raiz->filhos[0] = raiz;
     nova_raiz->filhos[1] = filho_dir;
     for (i = 2; i <= MAX_CHAVES; i++)
       nova_raiz->filhos[i] = NULL;
     return(nova_raiz);
   }
  else return(raiz);
}

int main( void ){	
	char command[15];
	int i, h, linhas, info;
	arvoreB *raiz;
	
	scanf(" %i", &linhas );
	for( i=0 ; i<linhas ; ++i ){
		scanf(" %s", command );
		if( !strcmp( command , "buscar" ) ){
			scanf(" %i", &info );
			if( busca( raiz , info ) ){
				printf(":)\n");
			}else{
				printf(":(\n");
			}
		}else if( !strcmp( command , "inserir" ) ){
			scanf(" %i", &info );
			insere_arvoreB( raiz, info );
		}else if( !strcmp( command , "imprimir" ) ){
			if( !raiz->num_chaves ){
				printf("vazia");	
			}else{
				press( raiz );
			}
			printf("\n");
		}
	}
	
	return 0;
}

















