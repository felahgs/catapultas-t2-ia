#include "tabuleiro.h"


int avalia(tabuleiro_meu *tabuleiro, char lado_meu, char lado_adv, int tipo)
{
	int Aliados = 0, Inimigos = 0;
	int i,j;
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			if(tabuleiro->tabuleiro[i][j] == lado_meu)
				Aliados++;
			if(tabuleiro->tabuleiro[i][j] == lado_adv)
				Inimigos++;
		}
	}
	if(tipo == 1)
		Aliados += 2;
	return(Aliados-Inimigos);
}


void AlocaTabuleiro(tabuleiro_meu *tabuleiro)
{
	int i;
	tabuleiro->x = 6;
	tabuleiro->y = 6;

	tabuleiro->tabuleiro = (char**)malloc(sizeof(char*)*tabuleiro->x);
	for(i = 0; i < tabuleiro->x; i++)
	{
		tabuleiro->tabuleiro[i] = (char*)malloc(sizeof(char)*tabuleiro->y);
	}

}



void PrintaTabuleiro(tabuleiro_meu *tabuleiro)
{
	int i,j;
	for(i = 0; i < 6; i++)
	{
		printf("\n");
		for(j = 0; j < 6; j++)
		{
			printf("%c",tabuleiro->tabuleiro[i][j]);
		}
	}
	printf("\n");
}


void CopiaTabuleiro(tabuleiro_meu *tabuleiro, tabuleiro_meu *novo)
{
	int i,j;
	novo->x = tabuleiro->x;
	novo->y = tabuleiro->y;
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			novo->tabuleiro[i][j] = tabuleiro->tabuleiro[i][j];
		}
	}

}


void LeInformacao(char *tabuleiro, tabuleiro_meu *tabuleiro_meu)
{
	int aux, i, j;
	aux = 10;
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			tabuleiro_meu->tabuleiro[i][j] = tabuleiro[aux]	;
			aux++;
		}
		aux = aux+3;
	}
	return;
}



//Retorna 1 se possível realizar a jogada e 0 caso contrário
int EhPossivel(tabuleiro_meu *tabuleiro, int PosX_atual, int PosY_atual, int PosX_tentar, int PosY_tentar, int PosX_entre, int PosY_entre, char tipo, char lado_meu)
{
	if(tipo == 'm')
	{
		if(tabuleiro->tabuleiro[PosX_tentar][PosY_tentar] == '-')
			return(1);
		else
			return(0);
	}

	else if(tipo == 's')
	{
		if(tabuleiro->tabuleiro[PosX_tentar][PosY_tentar] == lado_meu)
			return(0);

		else if(tabuleiro->tabuleiro[PosX_entre][PosY_entre] != lado_meu)
			return(0);

		if(tabuleiro->tabuleiro[PosX_tentar][PosY_tentar] == '-')
			return(0);

		else
			return(1);

	}
	else
		printf("\n DEU MERDA \n");
	return(4337);
}


//Executa a jogada em um mapa auxiliar e salva a mesma no grafo
vertice ExecutaJogada(int PosxAtual, int PosyAtual, int PosxNova, int PosyNova, int PosxMeio, int PosyMeio, char tipo, char lado_meu, vertice pai, grafo grafo) 
{
	tabuleiro_meu *tabuleironovo;					//Crio meu novo tabuleiro
	tabuleironovo = malloc(sizeof(tabuleiro_meu));			//Aloco espaço para a estrutura do mesmo
	AlocaTabuleiro(tabuleironovo);					//Aloco espaço para seus componentes
	CopiaTabuleiro(pai->tabuleiro, tabuleironovo);			//Copio o tabuleiro do seu pai

	tabuleironovo->tabuleiro[PosxAtual][PosyAtual] = '-';		//Salvo a jogada executada

	tabuleironovo->tabuleiro[PosxNova][PosyNova]   = lado_meu;
	int *movimentosfilho;
	if(tipo == 's') 						//Se for do tipo salto
	{
		if(pai->pai == NULL)						//Se meu pai for nulo (raiz)
		{
			movimentosfilho = malloc(sizeof(int)*100);
			movimentosfilho[0] = 4;
			movimentosfilho[1] = 1;
			movimentosfilho[2] = PosxAtual;
			movimentosfilho[3] = PosyAtual;
			movimentosfilho[4] = PosxNova;
			movimentosfilho[5] = PosyNova;

			//printf("%d, %d\n",movimentosfilho[2],movimentosfilho[3]);
			//printf("%d, %d\n",movimentosfilho[4],movimentosfilho[5]);
			//printf("copiando\n");
			vertice Filho = constroi_vertice(pai, grafo, tabuleironovo);    //Constroi o vertice com o pai como pai
			copia_array(movimentosfilho,Filho->movimentos);			//Salvo os novos movimentos no vértice
			//printf("%d, %d\n",Filho->movimentos[2],Filho->movimentos[3]);
			//printf("%d, %d\n",Filho->movimentos[4],Filho->movimentos[5]);
			//imprime_array(Filho->movimentos);
			return(Filho); //Se a jogada for salto, utilizarei o novo vertice para testes
		}


		else
		{
			movimentosfilho = malloc(sizeof(int)*100);
			copia_array(pai->movimentos, movimentosfilho);			//Copio o vetor de movimento do pai para a instância atual
			movimentosfilho[movimentosfilho[0]+2] = PosxNova;		//Salvo a nova jogada no vetor conforme seu tamanho expresso em sua posição 0
			movimentosfilho[movimentosfilho[0]+3] = PosyNova;		//Salvo a nova jogada no vetor conforme seu tamanho expresso em sua posição 0
			movimentosfilho[0] = movimentosfilho[0] + 2;			//Incremento o tamanho do vetor
			vertice Filho = constroi_vertice(pai, grafo, tabuleironovo); 	//Constroi o vertice com o pai como pai
			copia_array(movimentosfilho,Filho->movimentos);			//Salvo os novos movimentos no vértice
			return(Filho); //Se a jogada for salto, utilizarei o novo vertice para testes
		}
	}

	else if (tipo == 'm')
	{
		vertice Filho = constroi_vertice(pai, grafo, tabuleironovo);     	//Constroi o vertice com o pai como pai
		movimentosfilho = malloc(sizeof(int)*100);
                movimentosfilho[0] = 4;
                movimentosfilho[1] = 0;
                movimentosfilho[2] = PosxAtual;
                movimentosfilho[3] = PosyAtual;
                movimentosfilho[4] = PosxNova;
                movimentosfilho[5] = PosyNova;
		copia_array(movimentosfilho,Filho->movimentos);
	} 

	//Salvar essa jogada na sequência e salvar o novo mapa.

}

//A função recebe uma posição de um tabuleiro, ela verifica quais as possíveis jogadas para essa posição, se for possível uma jogada de 'move', a função realiza a movimentação e para por ali.
//Caso uma jogada de salto seja realizada, a função funciona de forma recursiva, chamando outra instância da função AnalisaJogadas até que todos os saltos sejam realizados.
void AnalisaJogadasPossiveis(int Posx, int Posy, char lado_meu, int saltou, vertice atual, grafo grafo)
{
	vertice auxiliar;
	if(atual->tabuleiro->tabuleiro[Posx][Posy] == lado_meu)
	{
		if(saltou == 0)	
		{
			if(Posx < 5)
				if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx+1,Posy,0,0,'m',lado_meu) == 1)
				{
					ExecutaJogada(Posx, Posy, Posx+1, Posy, 0, 0, 'm', lado_meu, atual, grafo);
				}

			if(Posx > 0)
				if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx-1,Posy,0,0,'m',lado_meu) == 1)
				{
					ExecutaJogada(Posx, Posy, Posx-1, Posy, 0, 0, 'm', lado_meu, atual, grafo);
				}

			if(Posy < 5)
				if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx,Posy+1,0,0,'m',lado_meu) == 1)
				{
					ExecutaJogada(Posx, Posy, Posx, Posy+1, 0, 0, 'm', lado_meu, atual, grafo);
				}

			if(Posy > 0)
				if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx,Posy-1,0,0,'m',lado_meu) == 1)
				{
					ExecutaJogada(Posx, Posy, Posx, Posy-1, 0, 0, 'm', lado_meu, atual, grafo);
				}
		}


		//Preciso passar para a função (nessa ordem) tabuleiro, posição x e y atual, posição x e y a onde quero saltar, posição x e y entre minha posição atual e onde quero saltar, tipo da jogada e qua meu lado	

		if(Posx <= 3)
			if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx+2,Posy,Posx+1,Posy,'s',lado_meu) == 1) //Tento Saltar para a baixo
			{
				auxiliar = ExecutaJogada(Posx, Posy, Posx+2, Posy, Posx+1, Posy, 's', lado_meu, atual, grafo);
				AnalisaJogadasPossiveis(Posx+2, Posy, lado_meu, 1, auxiliar, grafo);
			}
		if(Posx >= 2)
			if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx-2,Posy,Posx-1,Posy,'s',lado_meu) == 1) //Tento Saltar para a cima
			{
				auxiliar = ExecutaJogada(Posx, Posy, Posx-2, Posy, Posx-1, Posy, 's', lado_meu, atual, grafo);
				AnalisaJogadasPossiveis(Posx-2, Posy, lado_meu, 1, auxiliar, grafo);
			}
		if(Posy <= 3) 
			if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx,Posy+2,Posx,Posy+1,'s',lado_meu) == 1) //Tento Saltar para a direita
			{
				auxiliar = ExecutaJogada(Posx, Posy, Posx, Posy+2, Posx, Posy+1, 's', lado_meu, atual, grafo);
				AnalisaJogadasPossiveis(Posx, Posy+2, lado_meu, 1, auxiliar, grafo);
			}
		if(Posy >= 2)
			if(EhPossivel(atual->tabuleiro,Posx,Posy,Posx,Posy-2,Posx,Posy-1,'s',lado_meu) == 1) //Tento Saltar para a esquerda
			{
				auxiliar = ExecutaJogada(Posx, Posy, Posx, Posy-2, Posx, Posy-1, 's', lado_meu, atual, grafo);
				AnalisaJogadasPossiveis(Posx, Posy-2, lado_meu, 1, auxiliar, grafo);
			}
	}
	return;
}


void ProcuraJogadas(tabuleiro_meu *tabuleiro, char lado_meu, grafo grafo)
{
	int i,j;
	vertice verticeinicial = constroi_vertice(NULL,grafo,tabuleiro); 



	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			AnalisaJogadasPossiveis(i,j,lado_meu, 0, verticeinicial, grafo);
		}
	}
}



int main(int argc, char **argv) 
{
	char buf[MAXSTR];
	char tabuleiro[MAXSTR]; 
	char lado_meu;
	char lado_adv;
	char tipo_mov_adv;
	int num_mov_adv;
	int mov_adv_l[MAXINT];
	int mov_adv_c[MAXINT];
	int i, valor = 0;
	int MaiorJogada = 0;
	vertice MelhorVertice;
	grafo grafo;
	tabuleiro_meu *tabuleiro_meu;
	char *final;
	lista l;
	vertice v;
	// conecta com o controlador do campo
	tabuleiro_conecta(argc, argv);
	while(1){

		tabuleiro_meu = NULL;
		tabuleiro_meu = malloc(sizeof(tabuleiro_meu));
		AlocaTabuleiro(tabuleiro_meu);
		// recebe o campo inicial e o movimento do adversario
		tabuleiro_recebe(buf);

		// separa os elementos do string recebido
		sscanf(strtok(buf, " \n"), "%c", &lado_meu);
		sscanf(strtok(NULL, " \n"), "%c", &lado_adv);
		sscanf(strtok(NULL, " \n"), "%c", &tipo_mov_adv);
		if(tipo_mov_adv == 'm') {
			num_mov_adv = 2;
			for(i = 0; i < num_mov_adv; i++) {
				sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_l[i]));
				sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_c[i]));
			}
		}
		else if(tipo_mov_adv == 's') {
			sscanf(strtok(NULL, " \n"), "%d", &num_mov_adv);
			for(i = 0; i < num_mov_adv; i++) {
				sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_l[i]));
				sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_c[i]));
			}
		}
		strncpy(tabuleiro, strtok(NULL, "."), MAXSTR);

		// mostra o que recebeu
		printf("%c\n", lado_meu);
		printf("%c %c", lado_adv, tipo_mov_adv);
		if(tipo_mov_adv != 'n') {
			if(tipo_mov_adv == 's') 
				printf(" %d", num_mov_adv);
			for(i = 0; i < num_mov_adv; i++) {
				printf(" %d", mov_adv_l[i]);
				printf(" %d", mov_adv_c[i]);
			}
		}
		printf("\n");
		printf("%s", tabuleiro);


		//Começa minha parte


		LeInformacao(tabuleiro, tabuleiro_meu);
		PrintaTabuleiro(tabuleiro_meu);
		// prepara um string com o movimento

		grafo = NULL;
		grafo = constroi_grafo(); //Constroi o grafo

		ProcuraJogadas(tabuleiro_meu, lado_meu, grafo);

		///////////////////////////////////////////////////////////////////////////////VERIFICAR PROBLEMA////////////////////////////////////////////////////////////////////////////

		//Verifico todos os vértices do meu Grafo
		l = grafo->vertices;
		MelhorVertice = conteudo(primeiro_no(l)); //Salvo o valor padrão para caso não exista melhor jogada
		for(no n = primeiro_no(l); n; n = proximo_no(n)) 
		{
			v = conteudo(n);
			valor =	 avalia(v->tabuleiro, lado_meu, lado_adv, v->movimentos[1]);
			//printf("Valor da jogada = %d\n", valor);
			if(v->profundidade != 0)
			{
				if(valor > MaiorJogada)
				{
					MelhorVertice = v;
					MaiorJogada = valor;
				}
			}
		}
		valor = 0;
		MaiorJogada = 0;
		i = 0;	
		imprime_array(MelhorVertice->movimentos);
		final = imprime_array_copia(MelhorVertice->movimentos, lado_meu);

		printf("%s\n",final);
		tabuleiro_envia(final);

		//imprime_lista(grafo->vertices);	

		// envia o movimento para o controlador do campo
		//tabuleiro_envia(buf); 
}


}
