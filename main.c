
// Código Genético
// Artur Gonzaga && Julia Leão 
// 
// Após o estudo de Ácidos Nucleícos, surgiu a ideia de implementar
// os processos estudados em um projeto. 
// 
// - Processo de Transcrição ( DNA -> RNA )
//

#include <stdio.h>
#include <stdlib.h>

#include "listas.h"
#include "aminoacidos.h"


#define SUCESSO 0

#define ADENINA 97
#define CITOSINA 99
#define GUANINA 103
#define TININA 116
#define URACILA 117

#define TAM_AMINOACIDO 3
;

void obtem_codon_inicio (FILE* entrada) {

	char base_nitrogenada;


	do { fscanf(entrada, "%c", base_nitrogenada);

	} while (base_nitrogenada = !ADENINA);

	do { fscanf(entrada, "%c", base_nitrogenada);

	} while (base_nitrogenada = !URACILA);

	do { fscanf(entrada, "%c", base_nitrogenada);

	} while (base_nitrogenada = !GUANINA);
}

int main (int argc, char** argv) {

	FILE* entrada;
	char n_base; // base nitrogenada
	
	char amostra[TAM_AMINOACIDO];

	entrada = fopen("./entrada.txt", "r");

	//Testa se o arquivo foi aberto
	if (entrada == NULL) {


		fputs("ERRO: O arquivo não pode ser encontrado\n", stderr);
		return SUCESSO;
	}

	while (!feof(entrada)) {

		do {

			fscanf(entrada, "%c", &n_base);
			if (n_base =)


		} while (n_base != ADENINA )





	}

	
	return SUCESSO;
}
