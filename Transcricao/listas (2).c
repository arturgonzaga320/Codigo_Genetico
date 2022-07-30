#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
Lista * lst_cria()
{
	return NULL;
}

Lista * lst_insere(Lista *l, char i)
{
	Lista * novo=(Lista *)malloc(sizeof(Lista));
	novo->info=i;
	novo->prox=l;
	return novo;
}

void lst_imprime(Lista *l, FILE * saida)
{
	Lista *p;
	for(p = l; p != NULL; p = p->prox)
	{
		fwrite(&p->info,sizeof(char),1,saida);
	}
}