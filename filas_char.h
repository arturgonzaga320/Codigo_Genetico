// Junho, 2022
// filas_char.h - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

#include <stdint.h>
#define TAMANHO_MAX (2+1)

typedef uint8_t bool;

typedef struct lst_s{
	char info[TAMANHO_MAX];
	struct lst_s* prox;
}lista_t;

typedef struct fila_s {
	lista_t* inicio;
	lista_t* fim;
}fila_lst;

//Implementacao com Listas Encadeadas

fila_lst* fila_lst_cria();
bool fila_lst_vazia(fila_lst* fila_p);

void fila_lst_insere(fila_lst* fila_p,char* info_param);
char* fila_lst_retira(fila_lst* fila_p);

void fila_lst_inverte(fila_lst* fila_p);
lista_t* fila_lst_busca (fila_lst* fila_p, char* info_alvo);

void fila_lst_imprime(fila_lst* fila_p);

void fila_lst_libera(fila_lst* fila_p);
