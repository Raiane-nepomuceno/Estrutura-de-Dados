#include<stdio.h>
#include<stdlib.h>
struct no{
	int dado;
	struct no *prox,*ant;
};
typedef struct no No;

No* cria_lista()
{
	//se dentro da lista não estiver nada dentro de lista entao aponta para null
	No* lista = (No *) malloc(sizeof(No));
	if(lista != NULL)
	{
		*lista = NULL;
	}
	return lista;
}
No* busca(No* lista,int num)
{
	No *p = ini;
	while(p && p->dado!=k)
	{
		p = p->prox;
	}
	return p;
}
void remove(No* d)
{
	No* p =d->ant;
	p->prox = d->prox;
	if(d->prox)
	{
		d->prox->ant = p;
	}
}
//falta fazer inserção no inicio,fim,ordenação,(?excluir);
main()
{
	No *lista;
	//primeiro nó da lista
	lista = cria_lista();
}
