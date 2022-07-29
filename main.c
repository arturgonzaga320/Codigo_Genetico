
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filas_char.h"
#include "ListaCodons.h"

#define SUCESSO 0
#define TAM_AMINOACIDO 3

#define ADENINA 'A'
#define CITOSINA 'C'
#define GUANINA 'G'
#define TININA 'T'
#define URACILA 'U'

void obtem_codon_inicio (FILE* entrada) {

	char base_nitrogenada;

	// Nada OK, resta AUG
	do { fread (&base_nitrogenada,sizeof(char),1,entrada);

		if (base_nitrogenada > 90) base_nitrogenada -= 32; // toupper mais legal

	} while (base_nitrogenada != ADENINA && (!feof (entrada)));

	fread (&base_nitrogenada,sizeof(char),1,entrada);
	if (base_nitrogenada > 90) base_nitrogenada -= 32; // toupper mais legal

	// A OK, resta UG;
	if (base_nitrogenada != URACILA) obtem_codon_inicio(entrada);
	
	else {
	
		fread(&base_nitrogenada, sizeof(char), 1, entrada);
		if (base_nitrogenada > 90) base_nitrogenada -= 32; // toupper mais legal
	}

	// AU OK, resta apenas G
	if (base_nitrogenada != GUANINA) obtem_codon_inicio (entrada);

}

fila_lst* insere_aminoacido(fila_lst* rna_r, char* codon_p, FILE* aminoacidos) {

	char* codon_cmp = (char*) malloc ( sizeof(char) * TAM_AMINOACIDO );

	// toupper em toda a string
	for (int i = 0; i < TAM_AMINOACIDO; i++) {
	
		if (codon_p[i] > 90) codon_p[i] -= 32;
	}

	// Procura aminoacido correspondente ao codon lido
	while (!feof(aminoacidos)) {

		fread(codon_cmp, sizeof(char), TAM_AMINOACIDO, aminoacidos);

		if (strcmp(codon_p, codon_cmp) == 0) {

			fseek(aminoacidos, 1, SEEK_CUR); // Pula espa�o em branco
			fread(codon_p, sizeof(char), TAM_AMINOACIDO, aminoacidos);
			
			fila_lst_insere(rna_r, codon_p);
			return rna_r;
		}

		if (!feof(aminoacidos)) { // Necess�ria dupla verifica��o por estar dentro de um la�o
			
			fseek(aminoacidos, 5, SEEK_CUR); // Pula para a prox linha
		}
	}

	// ".*" indica que apenas parte da string ser� impressa, no caso at� a posi��o 3 (TAM_AMINOACIDO) 
	printf("Codon %.*s n%co %c sintetizante.\n", TAM_AMINOACIDO, codon_p, 198, 130);

	free(codon_cmp);
	return NULL; // Codon n�o sintetizante
}

int main (int argc, char** argv) {

	fila_lst* rna_r = fila_lst_cria();
	char* codon = (char*) malloc ( sizeof(char) * TAM_AMINOACIDO );
	char* codon_termino = (char*) malloc ( sizeof(char) * TAM_AMINOACIDO );

	FILE* entrada = fopen("entrada.txt", "rb"); 
	FILE* aminoacidos = fopen("aminoacidos.txt", "rb");

	// Testa abertur dos arquivos
	if (entrada == NULL || aminoacidos == NULL) {
		
		printf ("ERRO: O arquivo n�o pode ser encontrado\n");
		return SUCESSO;
	}

	/*  Com o sucesso da abertura dos arquivos, o cursor do arquivo  *
	 *  ser� movido para o in�cio da sequ�ncia sintetizante        */

	
	obtem_codon_inicio(entrada);

	fseek (aminoacidos, 4, SEEK_SET); // Obtem codon de termino
	fread(codon_termino, sizeof(char), TAM_AMINOACIDO, aminoacidos);

	do {
		
		fseek (aminoacidos, 0, SEEK_SET); // Posiciona cursor no inicio de aminoacidos.txt
		
		fread(codon, sizeof(char), TAM_AMINOACIDO, entrada);
		rna_r = insere_aminoacido (rna_r, codon, aminoacidos);
		
		if (rna_r == NULL) return SUCESSO; // Erro ao inserir aminoacido

	} while ( ( !feof(entrada) ) && ( strcmp (codon, codon_termino) != 0 ) );

	free(codon);
	free(codon_termino);
	fclose(entrada);
	return SUCESSO;
}
