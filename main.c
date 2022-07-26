
#include <stdio.h>
#include <stdlib.h>

#include "listas.h"
#include "ListaCodons.h"

#define SUCESSO 0
#define TAM_AMINOACIDO 3

#define ADENINA 'a'
#define CITOSINA 'c'
#define GUANINA 'g'
#define TININA 't'
#define URACILA 'u'

int obtem_codon_inicio (FILE* entrada) {

	entrada = fopen("entrada.txt", "r");

	char base_nitrogenada;

	while (base_nitrogenada != ADENINA) {

		fscanf(entrada, "%c", base_nitrogenada);
	}

	fscanf(entrada, "%c", base_nitrogenada);

	if (base_nitrogenada != URACILA) obtem_codon_inicio;

	else fscanf(entrada, "%c", base_nitrogenada);

	if (base_nitrogenada != GUANINA) obtem_codon_inicio;

	return fseek (entrada, 0, SEEK_CUR);
}

int main (int argc, char** argv) {

	FILE* entrada;
	char n_base; // base nitrogenada
	
	char amostra[TAM_AMINOACIDO];
	
	lista_t* rna_ribossomico;


	entrada = fopen("entrada.txt", "r");

	//Testa se o arquivo foi aberto
	if (entrada == NULL) {


		printf ("ERRO: O arquivo não pode ser encontrado\n");
		return SUCESSO;
	}

	while (!feof(entrada)) {

		int inicio = obtem_codon_inicio;
		fseek(entrada, inicio, SEEK_SET);
	}

	fclose(entrada);
	return SUCESSO;
}
