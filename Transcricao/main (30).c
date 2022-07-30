#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listas.h"

#define SUCESSO 0
#define ERRO (!SUCESSO)

#define ADENINA 'a'
#define CITOSINA 'c'
#define GUANINA 'g'
#define TININA 't'
#define URACILA 'u'

/*  * afazeres da juiajuia:
    * salvar tudo em um arquivo binario
    * estudar iniciador do dna e implementar
    * estudar splicing e implementar */
    
int main (int argc, char** argv) 
{
    //Variaveis
	char basenitrogenada; //base lida

    /*  Arquivos Necessarios - 
    - arquivo entrada: cod. da fita molde de dna
    - arquivo de saida: cod. do rna mensageiro      */
	FILE * entrada = fopen("fitamoldedna.txt", "r");
    FILE * saida = fopen("rnamensgeiro.txt", "w");
    
	// Caso o arquivo nao tenha sido aberto
	if (entrada == NULL) 
	{
		printf ("ERRO: O arquivo não pode ser encontrado\n");
		return ERRO;
	}
	if (saida == NULL) 
	{
		printf ("ERRO: O arquivo não pode ser encontrado\n");
		return ERRO;
	}
    //se o arquivo foi aberto
	do
	{   
	    //le um char do arquivo
	    basenitrogenada = fgetc(entrada);
	    /*  caso seja uma das bases nitrogenadas
	    sera escrito o char equivalente a aquela
	    base no arquivo                         */
		if(basenitrogenada == GUANINA)
		{ fputc(CITOSINA,saida); }
		if(basenitrogenada == CITOSINA)
		{ fputc(GUANINA,saida); }
		if(basenitrogenada == TININA)
		{ fputc(ADENINA,saida); }
		if(basenitrogenada == ADENINA)
		{ fputc(URACILA,saida); }
		
    } while (!feof(entrada));
	
	fclose(entrada);
	fclose(saida);
	return SUCESSO;
}