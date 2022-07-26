// Junho, 2022
// listas.c - Artur Gonzaga
// Desenvolvimento de Sistemas - COLTEC UFMG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "listas.h"

#define VERDADEIRO 0
#define FALSO 1
#define ERRO 1

lista_t* lst_cria(){

	return NULL;
}

bool lst_vazia (lista_t* lista_p){
	
	if (lista_p == NULL){
		
		return VERDADEIRO;
	}
	else { return FALSO; }
}

lista_t* lst_insere (lista_t* lista_p, int info_param){

	lista_t* novo_elem;
	novo_elem = (lista_t*)malloc(sizeof(lista_t));

	novo_elem->info = info_param;
	novo_elem->prox = lista_p;
	return novo_elem;
}

lista_t* lst_pilha_insere(lista_t* lista_p, int info_param) {

	lista_t* lista_aux = lista_p;

	while (lista_aux->prox != NULL) lista_aux = lista_aux->prox;

	lista_t* novo_elem;
	novo_elem = (lista_t*)malloc(sizeof(lista_t));

	novo_elem->info = info_param;
	novo_elem->prox = NULL;

	lista_aux->prox = novo_elem;

	return lista_p;
}

// lista_t* lst_insere_ordenado (lista_t* lista_p, int info_param){

void lst_retira(lista_t* lista_p) {

	if (lst_vazia(lista_p) == VERDADEIRO) {

		return; // Ao retornar para main, pedir para verificar ERRO
	}

	lista_t* remover_elem;
	remover_elem = (lista_t*)malloc(sizeof(lista_t));
	remover_elem = lista_p;

	lista_p = lista_p->prox;

	free(remover_elem);

}

lista_t* lst_retira_objetiva(lista_t* lista_p, int rm_info) {

	if (lst_vazia(lista_p) == VERDADEIRO){
		
		return NULL;
	}

	lista_t* rm_elem = lista_p;
	lista_t* pre_elem = NULL;

	while ( (rm_elem->info != rm_info) && (rm_elem != NULL) ) {
		pre_elem = rm_elem;
		rm_elem = rm_elem->prox;
	}

	if ( rm_elem == NULL); // Elemento nao encontrado
	
	if ( pre_elem == NULL ) {

		lista_p = rm_elem->prox;
	}
	else {

		pre_elem->prox = rm_elem->prox;
	}

	free(rm_elem);
	return lista_p;
}

void lst_inverte(lista_t* lista_p){
	
	if (lst_vazia(lista_p) == VERDADEIRO) {

		return;
	}

	int i = 0, n_elementos = 1;
	int* vetor_valores;
 		
	for (lista_t* i_ponteiro = lista_p; i_ponteiro->prox != NULL; i_ponteiro = i_ponteiro->prox) { 
		
		n_elementos++;
	}

	vetor_valores = (int*)malloc(sizeof(int) * n_elementos);

	for (lista_t* i_ponteiro = lista_p; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox) {

		vetor_valores[i]=i_ponteiro->info;
		i++;
	}

	while (lst_vazia(lista_p) == FALSO) {
		lst_retira(lista_p);
	}

	for (i = (n_elementos-1); i >= 0; i--) {

		lst_insere(lista_p, vetor_valores[i]);
	}

	free(vetor_valores);
}

lista_t* lst_busca(lista_t* lista_p, int info_alvo){
	
	lista_t* i_ponteiro;
	
	for (i_ponteiro = lista_p; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox){
		
		if (i_ponteiro->info == info_alvo){
			
			return i_ponteiro;
		}
	}

	return NULL;
}

void lst_imprime(lista_t* lista_p){
	
	lista_t* i_ponteiro;
	
	for (i_ponteiro = lista_p; i_ponteiro != NULL; i_ponteiro = i_ponteiro->prox){
		
		printf("\t%d\n",i_ponteiro->info);
	}

	free(i_ponteiro);
}

void lst_libera(lista_t* lista_p) {

	lista_t* i_ponteiro = lista_p;

	while (i_ponteiro != NULL) {
		
		lista_t* temp = i_ponteiro->prox; 
		free(i_ponteiro);
		i_ponteiro = temp;
	}
}
