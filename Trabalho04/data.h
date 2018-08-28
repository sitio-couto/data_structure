//VINICIUS COUTO ESPINDOLA
//RA: 188115
#ifndef _DATA_TYPES
#define _DATA_TYPES

//struct com dados do vetor.
typedef struct dinamicCircularVector{
	double memoryUsed;
	double totalMemory;
	int firstChain;
	int lastChain;
	char **vector;
}dcv;

//buffer para as entradas.
typedef char superString[5000];

//funcoes auxiliares para controle de dados.
dcv* init_dcv( );
void create_vector( dcv *sequence );
void update_dcv_size( dcv *sequence );
void erase_vector( dcv *sequence );
void test_empty( superString buffer );

//funcoes padrao.
void unshift( dcv *sequence );
void shift( dcv *sequence );
void print_first( dcv *sequence );
void push( dcv *sequence );
void pop( dcv *sequence );
void print_last( dcv *sequence );
void is_empty( dcv *sequence );
dcv* end( dcv *sequence );


#endif
