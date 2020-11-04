#include<stdio.h>
#include<stdlib.h>
//criando a arvore
struct arvore{
	int dado;
	struct arvore* direita;
	struct arvore* esquerda;
};
//preedefinindo a arvore sem precisar ficar declarando sempre
typedef struct arvore arv;

//arvore vazia
arv* arv_vazia()
{
	return NULL;
}
arv* insere(arv* a, int x)
{
	//arvore estando vazia
	if(a == NULL)
	{
		//aloca o espaço e adiciona x em dado
		a = (arv*) malloc(sizeof(arv));
		a->dado = x;
		//direita e esquerda setam para null ou seja não há mais nenhum elemento
		a->direita = a->esquerda = NULL;
	}
	else{
		//se x for menor dado
		if(x < a->dado)
		{
			//ficará a esquerda
			a->esquerda = insere(a->esquerda,x);
		}
		else{
			//se for maior ficara a direita		
			a->direita = insere(a->direita,x);;
		}
		return a;
	}
}
arv* busca(arv* a,int x)
{
	//se a arvore estiver vazia returna null
	if(a == NULL)
	{
		return NULL;
	}
	else{
		//se  o dado que estiver na arvore for maior que x do usuario
		if(a->dado > x)
		{
			return busca(a->esquerda,x);
		}
		if(a->dado < x)
		//se for menor é buscado na direita
		{
			return busca(a->direita,x);
			
		}
		else{
			return a;
			
		}
	}
	
	
}
void mostrando_tela(arv* a)
{
	//se não estiver vazia
	if(a!=NULL)
	{
		//mostra a esquerda 
		mostrando_tela(a->esquerda);
		printf("%d\n",a->dado);
		//mostra a direita
		mostrando_tela(a->direita);
	}
}

arv* removendo(arv* a,int x)
{
	if(a == NULL)
	{
		printf("A lista ja esta vazia!");
		return NULL;
	}
	    else if(x < a->dado)
		{
			a->esquerda = removendo(a->esquerda,x);
		}
		else if(x > a->dado)
		{
			a->direita = removendo(a->direita,x);
		}
		else{
			//removendo o nó sem filhos
			if(a->esquerda == NULL && a->direita == NULL)
			{
				//apagando o no
				free(a);
				//no esta vazio
				a = NULL;
			}
			//no tem um filho na direita
			else if(a->esquerda == NULL)
			{
				//fazendo a copia
				arv* copia = a;
				//setando para o próximo elemento
				a = a->direita;
				//apagando a referencia
				free(copia);
			}
			//no com filho a esquerda
			else if(a->direita == NULL)
			{
				//fazendo a copia
				arv* copia = a;
			    //setando para o próximo elemento
				a = a->esquerda;
				//apagando a referencia
				free(copia);
				
			}
			//nó tem dois filhos
			else{
				//l recebe a copia da esquerda
				arv* l = a->esquerda;
				//enquanto l que seta para direita não estiver vazia
				while(l->direita != NULL)
				{
					//apenas incrementando
					l= l->direita;
				}
				//arvore dado recebe l dado
				a->dado = l->dado;
				//l dado recebe x
				l->dado= x;
				//removendo a esquerda
				a->esquerda = removendo(a->esquerda,x);
			}
		}
		return a;
	}

main()
{
	arv* a = arv_vazia();
	arv* r;
	a = insere(a,6);
	a = insere(a,4);
	a = insere(a,8);
	a = insere(a,2);
	a = insere(a,5);
	a = insere(a,1);
	a = insere(a,3);
	a = insere(a,7);
	a = insere(a,9);
	
	printf("Mostrando antes da exclusao:\n");
	mostrando_tela(a);
	r = busca(a,1);
	r = removendo(a,1);
	printf("Mostrando apos a exclusao do 1:\n");
	mostrando_tela(r);
	
}
