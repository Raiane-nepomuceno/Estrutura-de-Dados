#include<stdio.h>
#include<stdlib.h>

struct Arvore{
	char dado;
	struct Arvore* direita;
	struct Arvore* esquerda;
};

typedef struct Arvore arvore;
 
arvore* cria_vazia()
{
	return NULL;
}
//arvore vazia
int arvore_vazia(arvore* arv)
{
    return arv == NULL;
}
arvore* cria_arvore(char dado,arvore* direita,arvore* esquerda)
{
	arvore* p;
	//alocado o espaço
	p = (arvore*)malloc(sizeof(arvore));
	//adicionando o  dado e linkando com os outros elementos
	p->dado = dado;
	p->direita = direita;
	p->esquerda = esquerda;
	
	return p;
}
void imprime(arvore* a)
{
	//se a diferente de null
	if(a!=NULL)
	{
		printf("%c\n",a->dado);
		imprime(a->direita);
		imprime(a->esquerda);
	}

}
int pertence(arvore *arvore,char c)
{
  if(arvore==NULL)
  {
    return 0;
  }
  else{
  	//feita a comparação do dado e dos elementos da arvore
    return arvore->dado == c||
    pertence(arvore->direita,c) ||
    pertence(arvore->esquerda,c);
    return 1;
  }
  
}
void verificacao(int result)
{
  if(result == 0)
  {
    printf("Dado nao encontrado\n");
  }
  else{
    printf("Dado encontrado com sucesso!\n");
  }
}
arvore* excluir_arvore(arvore *arvore)
{
	//excluindo a arvore inteira
  if(arvore!=NULL)
  {
    excluir_arvore(arvore->direita);
    excluir_arvore(arvore->esquerda);
    free(arvore);
  }
  return NULL;
}
void result_exclusao(arvore *arvore)
{
	//verificando se realmente foi excluida a arvore
    if(arvore == NULL)
    {
      printf("Foi apagado com sucesso!\n");
    }
    else{
      printf("Nao foi possivel apagar.\n");
    }
} 
int main()
{
  int resultado;
  arvore* exclusao;
	arvore* a = cria_arvore('a',
  cria_arvore('b',cria_vazia(),
  cria_arvore('d',cria_vazia(),cria_vazia())
  ),
  cria_arvore('c',
  cria_arvore('e',cria_vazia(),cria_vazia()),
  cria_arvore('f',cria_vazia(),cria_vazia())
  )
  );

  imprime(a);

  resultado = pertence(a,'f');
  verificacao(resultado);

  resultado = pertence(a,'j');
  verificacao(resultado);

 exclusao = excluir_arvore(a);
 result_exclusao(exclusao); 
}
