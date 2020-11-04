	 do{
		printf("\n");
		printf("\t--------------- Menu ----------------\n");
		printf("\n");
		printf("\t1 - Cadastrar musicas\n");
		printf("\t2 - Imprimir todas as musicas\n");
		printf("\t3 - Adicionar musicas na playlist\n");
		printf("\t4 - Imprimir todas as musicas da playlist\n");
	    printf("\n");
		printf("\t\t-- Digite a opcao pretendida: ");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				printf("\n");
				printf("\tDigite a quantidade de musicas a serem adicionadas ao sistema:");
				scanf("%d",&quant);
				for(i = 0;i<quant;i++)
				{
					uma_musica = cadastro_musica();
					insere_musicas(lista_musicas, uma_musica);
				
				}
				printf("\n");
				printf("\t------ Adicionada com sucesso! --------\n");		
				break;
			case 2:
				printf("\tLISTA DE MUSICAS ADICIONADAS AO SISTEMA:\n");
				imprime(lista_musicas);
				break;
			case 3:
				fflush(stdin);
				char string[50];
				printf("\tDigite os ids da musicas a serem adicionados na playlist:");
				playlist = busca_musica_listaDupEncadeada(lista_musicas, string, &tam);	
				break;
			/*case 4:
				printf("\tMusicas da playlist criada por voce!\n");
				imprime_lista_CircularPlaylist(playlist);
				break;*/
			default:
			printf("Erro");
		
		}
	}while(op>0 && op<3);

