
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

void* obtem_codon_inicio (FILE* entrada) {

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

	return entrada->_Placeholder;
}

fila_lst* insere_aminoacido(fila_lst* rna_r, char* codon_p, FILE* aminoacidos) {

	char* codon_cmp = (char*) malloc ( sizeof(char) * TAM_AMINOACIDO );

	fseek(aminoacidos, 0, SEEK_SET); // Colocar cursor no inicio do arquivo

	// toupper em toda a string
	for (int i = 0; i < TAM_AMINOACIDO; i++) {
	
		if (codon_p[i] > 90) codon_p[i] -= 32;
	}

	// Procura aminoacido correspondente ao codon lido
	while (!feof(aminoacidos)) {

		fread(codon_cmp, sizeof(char), TAM_AMINOACIDO, aminoacidos);

		if (strcmp(codon_p, codon_cmp) == 0) {

			fseek(aminoacidos, 1, SEEK_CUR); // Pula espaço em branco
			fread(codon_p, sizeof(char), TAM_AMINOACIDO, aminoacidos);
			
			fila_lst_insere(rna_r, codon_p);
			return rna_r;
		}

		if (!feof(aminoacidos)) { // Necessária dupla verificação por estar dentro de um laço
			
			fseek(aminoacidos, 5, SEEK_CUR); // Pula para a prox linha
		}
	}

	// ".*" indica que apenas parte da string será impressa, no caso até a posição 3 (TAM_AMINOACIDO) 
	printf("Codon %.*s n%co %c sintetizante.", TAM_AMINOACIDO, codon_p, 198, 130);

	free(codon_cmp);
	return NULL; // Codon não sintetizante
}

int main (int argc, char** argv) {

	fila_lst* rna_r = fila_lst_cria();
	char* codon = (char*) malloc ( sizeof(char) * TAM_AMINOACIDO );

	FILE* entrada = fopen("entrada.txt", "rb"); 
	FILE* aminoacidos = fopen("aminoacidos.txt", "rb");

	// Testa abertur dos arquivos
	if (entrada == NULL || aminoacidos == NULL) {
		
		printf ("ERRO: O arquivo não pode ser encontrado\n");
		return SUCESSO;
	}

	/*  Com o sucesso da abertura dos arquivos, o cursor do arquivo  *
	 *  será movido para o início da sequência sintetizante        */

	entrada->_Placeholder = obtem_codon_inicio(entrada);

	do {
		
		fread(codon, sizeof(char), TAM_AMINOACIDO, entrada);
		rna_r = insere_aminoacido (rna_r, codon, aminoacidos);
		
		if (rna_r == NULL) return SUCESSO; // Erro ao inserir aminoacido

	} while ( ( !feof(entrada) ) || ( rna_r->fim->info != 'Fim' ) );
		
	free(codon);
	fclose(entrada);
	return SUCESSO;
}
