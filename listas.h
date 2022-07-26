// Junho, 2022
// listas.h - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

#include <stdint.h>

typedef uint8_t bool;

typedef struct lst_s {

	int info;
	struct lst_s* prox;
} lista_t;

lista_t* lst_cria();
bool lst_vazia(lista_t* lista_p);

lista_t* lst_insere(lista_t* lista_p,int info_param);
lista_t* lst_pilha_insere(lista_t* lista_p, int info_param);

void lst_retira(lista_t* lista_p);
lista_t* lst_retira_objetiva (lista_t* lista_p, int rm_info);

void lst_inverte(lista_t* lista_p);
lista_t* lst_busca (lista_t* lista_p, int info_alvo);

void lst_imprime(lista_t* lista_p);

void lst_libera(lista_t* lista_p);
