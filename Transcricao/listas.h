struct lista{
	char info;
	struct lista * prox;
};

typedef struct lista Lista;

/*Funcoes de lista encadeada*/

Lista * lst_cria();

Lista * lst_insere(Lista * l, char i);
