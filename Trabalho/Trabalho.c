#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct musica{
	int id;
	char titulo[200];
	char artista[200];
	char album[200];
	int duracao;
}musica;

typedef struct musica_no{
	musica *musica;
	struct musica_no *ant;
	struct musica_no *prox;
}musica_no;

typedef struct playlist_no{
	musica *musica;
	struct playlist_no *prox;
} playlist_no;

typedef struct lplaylists_no{
	int id;
	char nome[200];
	playlist_no *musicas;
	struct lplaylists_no *prox;
} lplaylists_no;


playlist_no* inicializa_circular()
{
	playlist_no *lista;
	lista = (playlist_no*)malloc(sizeof(playlist_no));
	lista->musica = NULL;
	lista->prox = lista;
	return lista;
}
lplaylists_no* cria_no_simplesmenteEnc()
{
		lplaylists_no *lista;
    	playlist_no *musica;

		lista = (lplaylists_no*)malloc(sizeof(lplaylists_no));
  
    lista->id = 0;
    lista->musicas = NULL;
    lista->prox = NULL;
		return lista;
		
}

lplaylists_no* iniciliza_lista_cabeca()
{
	lplaylists_no *lista;
	lista = malloc(sizeof(lplaylists_no));
	lista->prox = NULL;
	return lista;
}
musica_no*inicializa_lista()
{
	musica_no *lista;
	lista = (musica_no*)malloc(sizeof(musica_no));
	lista->ant = NULL;
	lista->prox = NULL;
	lista->musica = NULL;
	return lista;
}
void insere_musicas(musica_no* lista_musicas, musica* uma_musica)
{
	musica_no* no;
	//alocaco do novo_no
	no =  (musica_no*)malloc(sizeof(musica_no));
	//guardando a musica dentro do no
	no->musica = uma_musica;
	//no-prox recebe prox da lista
	no->prox = lista_musicas->prox;
	//ant da lista recebe o no, ou seja esta inserindo no comeco
	lista_musicas->ant = no;
	//se for diferente o prox da lista de musicas de null ou seja nao esta vazia
	if(lista_musicas->prox)
	{
		//na lista prox e ant recebe o no
		lista_musicas->prox->ant = no;
	}
	lista_musicas->prox = no;     
}

musica* cadastro_musica()
{
	musica *m = (musica*)malloc(sizeof(musica));
	
	char titulo[200],artista[200],album[200];
	int duracao,id;
	
	printf("\n");
	printf("\t---------- Cadastro das Musicas --------------\n");

	printf("\n\tDigite o ID da musica: ");
	scanf("%d",&id);
  
	m->id = id;
	
	fflush(stdin);
	
	printf("\n\tDigite o titulo da musica: ");
	fgets(titulo,199,stdin);
	strcpy(m->titulo,titulo);
	
	fflush(stdin);

	printf("\n\tDigite o nome do artista: ");
	fgets(artista,199,stdin);
	strcpy(m->artista,artista);
	
	fflush(stdin);

	printf("\n\tDigite o nome do album: ");
	fgets(album,199,stdin);
	strcpy(m->album,album);
	
	fflush(stdin);

	printf("\n\tDigite a duracao da musica [em segundos]: ");
	scanf("%d",&duracao);
	m->duracao = duracao;
  	fflush(stdin);
		
	return m;

}
	
int* convert_str(char *string, int *tamanho_final)
{
	int *vet,tam=0,i = 0,j;
	vet = (int*)malloc(15*sizeof(int));
   // Extraindo a primeira str
    char * str = strtok(string, " ");
    //passa pela string para extrair todas as outras strings
      while(str != NULL ) 
	  {
	  	  vet[i] = atoi(str);
	      str = strtok(NULL, " ");
	      tam++;
	      i++;
   	}
  *tamanho_final = tam;
   return vet;
}


void insere_playlist(musica *musica,playlist_no *playlist)
{
	playlist_no *no,*aux;
	no = (playlist_no*) malloc(sizeof(playlist_no));
	no->musica = musica;
	if(playlist == NULL)
	{
		no->prox = no;
	}else{
		no->prox = playlist->prox;
		playlist->prox = no;
	}
	playlist->prox = no;	
	
}
void convertendo(int seg)
{
	int horas,min,segundos;
	horas = seg/3600;
	min = (seg-(horas*3600))/60;
	segundos = seg%60;
	printf("\tDuracao: %d : %d : %d\n",horas,min,segundos);
}
//insere musica na playlist
void insere_musicaPlaylistCircular(playlist_no *playlist,musica *musica)
{

  playlist_no *playlist_usuario;
  playlist_usuario = (playlist_no*)malloc(sizeof(playlist_no));
  playlist_usuario->musica = musica;
  playlist_usuario->prox = playlist->prox;
  playlist->prox = playlist_usuario;
  printf("\tAdicionado com sucesso!");

}
//aqui e passada como parametro a lista inicializada e a musica a ser adicionada
 lplaylists_no* insere_fim_listaEnc(lplaylists_no *lista_playslist,playlist_no*playlist)
{
   char nome[200];
   int id;
   
  printf("\n\tDigite o id da playlist:");
  scanf("%d",&id);


	fflush(stdin);
 
  printf("\n\tDigite o nome da playlist:");
  fgets(nome,200,stdin);
  fflush(stdin);
  
  lplaylists_no *novo_no;
  novo_no = cria_no_simplesmenteEnc();
  novo_no->id = id;
  strcpy(novo_no->nome,nome);
  
  novo_no->musicas = playlist;
  novo_no->prox = lista_playslist;
  lista_playslist->prox = novo_no;
  return lista_playslist;

}
void busca_musica_listaDupEncadeada(musica_no *lista_musicas, char *ids_musicas, int *tam,playlist_no *playlist,lplaylists_no *lista_playlists)
{
	  musica_no *aux;
	  int *vet,i;
      //inicializada a playlist	
	  playlist = inicializa_circular();
	  //vetor com os ids das musicas 
	  vet = convert_str(ids_musicas, tam);
		//percorrendo a lista de musicas
		for(i = 0;i<*tam;i++)
		{
			aux = lista_musicas->prox;
			//enquanto aux diferente de null e o id diferente do id procurado
			while(aux && aux->musica->id != *vet)
			{
				aux = aux->prox;
			}
          vet++;
          //aqui e passado a playlist inicializada e a musica a ser adicionada nela
		  insere_musicaPlaylistCircular(playlist,aux->musica);
		 }
		   
    //lplaylists_no
     insere_fim_listaEnc(lista_playlists,playlist);
}
int tamanho_playlist(playlist_no *lista)
{
    playlist_no *aux = lista->prox;
    int tam = 0;
      while(aux!=lista)
      {  
        tam++;
        aux = aux->prox;
      }
       return tam+1;
}
lplaylists_no *pesquisa_playlist(lplaylists_no *lista, char *nome_playlist)
{
    lplaylists_no *aux;
    lplaylists_no *playlist_selecionada;
	aux = lista->prox;
	//enquanto aux for diferentte de null e aux nome for diferente do nome procurado
    while(aux!=NULL && aux->nome!=nome_playlist)
    {
      aux = aux->prox;
    }
    //se o conteudo da variavel de aux for igual ao nome procurado
    if(aux->nome == nome_playlist)
    {
      playlist_selecionada = aux;
      return aux;
      //retorna a playlist
      }
    else{
      printf("Valor nao encontrado!");
    }
}

void shuffle(lplaylists_no*lista_playlists,char *nome_playlist)
{
	//objetivo:mexer na ordem das musicas
    int i=0,pos;
    //aquilista_playlist->prox seta p/prox para setar a cabeça da lista
    lplaylists_no *aux = lista_playlists->prox;
    playlist_no *aux_copia;
    //percorrendo a lista de playlists e retornando a playlist escolhida
      while(aux && strcmp(aux->nome,nome_playlist)!=0)
      {  
        aux = aux->prox;
      }
      //retornando a playlist com o nome que o usuario digitou
      aux_copia = aux->musicas;

      //criando as variaveis auxiliares ou seja cópias da lista
      //mesma coisa aqui já a copia e feita no primeiro elemento da lista
	  playlist_no *aux2 = aux_copia->prox;
      playlist_no *aux3 = aux_copia->prox;
      musica *musica;
	  playlist_no *musicas;
      //enquanto aux2 != da playlist escolhida
      while(aux2->prox!=aux_copia)
      {
      	//vai sortear a posicao da lista ja que aqui e passado o tamanho da lista
        pos = rand() % tamanho_playlist(aux_copia);
        aux3 = aux_copia->prox;
		//enquanto i for menor que a posicao sorteada 
        while(i<pos)
        {
          i++;
          //percorre lista auxiliar 3 e incrementa o i
          aux3 = aux3->prox;

        }
        //a musica recebe a musica sorteada;
        musica = aux3->musica;
        //indo para a proxima musica
        aux3->musica = aux2->musica;
        aux2->musica = musica;
        aux2 = aux2->prox;
      }
      
}
void imprime_lista_CircularPlaylist(playlist_no *playlist)
{
  playlist_no *aux;
  aux = playlist->prox;
  while(aux != playlist)
  {
  	fflush(stdin);
  	printf("\tId: %d\n",aux->musica->id);
    printf("\tTitulo: %s\n",aux->musica->titulo);
    printf("\tAlbum: %s\n",aux->musica->album);
    printf("\tArtista: %s\n",aux->musica->artista);

    convertendo(aux->musica->duracao);
    aux = aux->prox;
    fflush(stdin);
  }
  printf("\n");
}

void imprime(musica_no *lista_musicas)
{
	 musica_no *aux;
	 aux = lista_musicas;
	 printf("\n");
	 printf("\t------------ Musicas -------\n");
	 printf("\n");
	 fflush(stdin);
	 while(aux->prox!=NULL)
	 {
	 	  fflush(stdin);
		 aux = aux->prox;
		 printf("\tId: %d\n",aux->musica->id);
		 printf("\tTitulo: %s\n",aux->musica->titulo);
		 printf("\tAlbum %s\n",aux->musica->album);
		 printf("\tArtista: %s\n",aux->musica->artista);
		 convertendo(aux->musica->duracao);
		 printf("\n");
	     fflush(stdin);

	 }
	 
}
void imprime_lista_simplesEnc(lplaylists_no *lista,char*nome_musica)
{
      lplaylists_no *aux = lista->prox;
      while(aux && strcmp(aux->nome,nome_musica)!=0)
      {  
        aux = aux->prox;
      }
       printf("%d",aux->id);
       
       printf("%s",aux->nome);
       
       imprime_lista_CircularPlaylist(aux->musicas);
	   printf("\n");
}
int main()
{
   	musica *uma_musica;
	musica_no *lista_musicas;
	lplaylists_no *lista_playlists;
	lista_musicas = inicializa_lista();
	lista_playlists = iniciliza_lista_cabeca();
	playlist_no *playlist;
	char string[50],nome_playlist[300],nome_playlist_shuffle[299];

	int i,tam,tam2,num,quant,op,op_exclusao;
	
	 do{
		printf("\n");
		printf("\t--------------- Menu ----------------\n");
		printf("\n");
		printf("\t1 - Cadastrar musicas\n");
		printf("\t2 - Imprimir todas as musicas\n");
		printf("\t3 - Adicionar playlist \n");
	  	printf("\t4 - Imprimir uma playlist\n");
		printf("\t5 - Alterar aleatoriamente a ordem das musicas\n");
    	
		printf("\n");
	    printf("\t\t-- Digite a opcao pretendida: ");
		scanf("%d",&op);
    	fflush(stdin);
		switch(op)
		{	
     		 //cadastro da musica
			case 1:
				printf("\n");
				printf("\tDigite a quantidade de musicas a serem adicionadas ao sistema:");
				scanf("%d",&quant);
        		fflush(stdin);
				for(i = 0;i<quant;i++)
				{
					uma_musica = cadastro_musica();
					insere_musicas(lista_musicas, uma_musica);
				
				}
				printf("\n");
				printf("\t------ Adicionada com sucesso! --------\n");		
				break;
			case 2:
        		//impressao da lista de musicas criadas
				printf("\tLISTA DE MUSICAS ADICIONADAS AO SISTEMA:\n");
				imprime(lista_musicas);
				break;

		    case 3:
			    //buscando a musica
			    //inserindo na playlist   
			      printf("\n");
			      printf("\tDigite as ids das musicas:");
			      fgets(string,49,stdin);
			      fflush(stdin);
			      //insere
			      busca_musica_listaDupEncadeada(lista_musicas,string, &tam2, playlist,lista_playlists);
			      break;
		     case 4:
		        printf("\n\tDigite o nome da playlist:");
		        fgets(nome_playlist,299,stdin);
				printf("\t------ Dados da playlist --------\n");		
		        imprime_lista_simplesEnc(lista_playlists,nome_playlist);
		        break;
		     case 5:
		        //pesquisar a playlist e mexer na ordem 
		        printf("\n\tDigite o nome da playlist:");
		        fgets(nome_playlist_shuffle,299,stdin);
		        shuffle(lista_playlists,nome_playlist_shuffle);
		        break;
          default:
			printf("Erro");
				
				}
	}while(op>0 && op<6);

	}

	


