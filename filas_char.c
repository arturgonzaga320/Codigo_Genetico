// Junho, 2022
// filas.c - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "filas_char.h"

#define TAMANHO_MAX (2+1)
#define VERDADEIRO 0
#define FALSO 1
#define ERRO "  Erro  "

fila_lst* fila_lst_cria(){

	fila_lst* fila_aux;
	fila_aux = (fila_lst*) malloc (sizeof(fila_lst));

	fila_aux->inicio = NULL;
	fila_aux->fim = NULL;

	return fila_aux;
}

bool fila_lst_vazia (fila_lst* fila_p){
	
	if (fila_p->inicio == NULL){
		
		return VERDADEIRO;
	}
	else { return FALSO; }
}

void fila_lst_insere (fila_lst* fila_p, char* info_param){

	lista_t* novo_elem;
	novo_elem = (lista_t*) malloc (sizeof(lista_t));
	
	for (int i = 0; i < TAMANHO_MAX; i++) {
		novo_elem->info[i] = info_param[i];
	}

	novo_elem->prox = NULL;

	if ( fila_lst_vazia(fila_p) == VERDADEIRO ){

		fila_p->inicio = novo_elem;
		fila_p->fim = novo_elem;
	}

	else { 

		lista_t* i_ponteiro;
		
		for (i_ponteiro = fila_p->inicio; i_ponteiro->prox != NULL; i_ponteiro = i_ponteiro->prox);

		i_ponteiro->prox = novo_elem;
		fila_p->fim = novo_elem; 
	}

}

char* fila_lst_retira (fila_lst* fila_p){
	
	if ( fila_lst_vazia(fila_p) == VERDADEIRO ) {

		return NULL;
	}

	char* info_removida = (char*)malloc( sizeof(char) * TAMANHO_MAX);

	for (int i = 0; i < TAMANHO_MAX; i++) {
		info_removida[i] = fila_p->inicio->info[i];
	}

	lista_t* remover_elem;
	remover_elem = (lista_t*) malloc (sizeof(lista_t));
	remover_elem = fila_p->inicio;

	fila_p->inicio = fila_p->inicio->prox;
	
	free (remover_elem);

	if (fila_p->inicio == NULL) {
		
		fila_p->fim = NULL;
	}
	
	return info_removida;
}

void fila_lst_inverte(fila_lst* fila_p){
	
	if (fila_lst_vazia(fila_p) == VERDADEIRO) {

		return;
	}

	int j =0, i = 0, n_elementos = 1;
	char** matriz_valores;
 		
	for (lista_t* i_ponteiro = fila_p->inicio; i_ponteiro->prox != NULL; i_ponteiro = i_ponteiro->prox) { 
		
		n_elementos++;
	}

	// Aloca matriz 
	matriz_valores = (char**)malloc(sizeof(char*) * n_elementos);
	
	if (matriz_valores == NULL) return;

	for (j = 0; j < n_elementos; j++) {

		matriz_valores[j] = (char*)malloc(sizeof(char) * TAMANHO_MAX);
		if (matriz_valores[j] == NULL) return;
	}



	for (lista_t* i_ponteiro = fila_p->inicio; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox) {
		
		strcpy(matriz_valores[i],i_ponteiro->info);
		i++;
	}

	while (fila_lst_vazia(fila_p) == FALSO) {
	
		fila_lst_retira(fila_p);
	}

	for (i = (n_elementos-1); i >= 0; i--) {
		
		fila_lst_insere(fila_p, matriz_valores[i]);
	}


	for (i = 0; i < n_elementos; i++) {
		
		free(matriz_valores[i]);
	}

	free(matriz_valores);
}

lista_t* fila_lst_busca(fila_lst* fila_p, char* info_alvo){
	
	lista_t* i_ponteiro;
	
	for (i_ponteiro = fila_p->inicio; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox){
		
		if (strcmp(i_ponteiro->info, info_alvo) == 0){
			
			return i_ponteiro;
		}
	}

	return NULL;
}

void fila_lst_imprime(fila_lst* fila_p){
	
	lista_t* i_ponteiro;
	
	for (i_ponteiro = fila_p->inicio; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox){
		
		printf("\t\t\t%s\n",i_ponteiro->info);
	}

	free(i_ponteiro);
}

void fila_lst_libera(fila_lst* fila_p) {

	lista_t* i_ponteiro = fila_p->inicio;

	while (i_ponteiro != NULL) {
		
		lista_t* temp = i_ponteiro->prox; 
		free(i_ponteiro);
		i_ponteiro = temp;
	}
	
	free(fila_p);
}
