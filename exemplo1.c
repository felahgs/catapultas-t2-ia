#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"

#define MAXSTR 512
#define MAXINT 16

typedef struct {
	char **tabuleiro;
	int x;
	int y;
}tabuleiro_meu;

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
int EhPossivel(tabuleiro_meu *tabuleiro, int PosX_atual, int PosY_atual, PosX_tentar, PosY_tentar, PosX_entre, PosY_entre, char tipo, char lado_meu)
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

		else if(tabuleiro->tabuleiro[PosX_entre][PosY_entre] <> lado_meu)
			return(0);

		else
			return(1);

	}
}


//A função recebe uma posição de um tabuleiro, ela verifica quais as possíveis jogadas para essa posição, se for possível uma jogada de 'move', a função realiza a movimentação e para por ali.
//Caso uma jogada de salto seja realizada, a função funciona de forma recursiva, chamando outra instância da função AnalisaJogadas até que todos os saltos sejam realizados.
void AnalisaJogadasPossiveis(tabuleiro_meu *tabuleiro, int Posx, int Posy, char lado_meu, int saltou)
{

	if(saltou == 0)	
	{
		if(EhPossivel(tabuleiro,Posx,Posy,Posx+1,Posy,0,0,'m',lado_meu) == 1)
			ExecutaJogada(tabuleiro,Posx+1,Posy,'m',lado_meu);

		if(EhPossivel(tabuleiro,Posx,Posy,Posx-1,Posy,0,0,'m',lado_meu) == 1)
			ExecutaJogada(tabuleiro,Posx-1,Posy,'m',lado_meu);

		if(EhPossivel(tabuleiro,Posx,Posy,Posx,Posy+1,0,0,'m',lado_meu) == 1)
			ExecutaJogada(tabuleiro,Posx,Posy+1,'m',lado_meu);

		if(EhPossivel(tabuleiro,Posx,Posy,Posx,Posy-1,0,0,'m',lado_meu) == 1)
			ExecutaJogada(tabuleiro,Posx,Posy-1,'m',lado_meu);
	}

//Preciso passar para a função (nessa ordem) tabuleiro, posição x e y atual, posição x e y a onde quero saltar, posição x e y entre minha posição atual e onde quero saltar, tipo da jogada e qua meu lado	
	if(EhPossivel(tabuleiro,Posx,Posy,Posx+2,Posy,Posx+1,Posy,'s',lado_meu) == 1)
	{
		ExecutaJogada(tabuleiro,Posx+2,Posy,'s',lado_meu);
		AnalisaJogadasPossiveis(,1)
	}
	
	if(EhPossivel(tabuleiro,Posx,Posy,Posx-2,Posy,Posx-1,posy,'s',lado_meu) == 1)
	{
		ExecutaJogada(tabuleiro,Posx-2,Posy,'s',lado_meu);
		AnalisaJogadasPossiveis(,1)
	}

	if(EhPossivel(tabuleiro,Posx,Posy,Posx,Posy+2,Posx,Posy+1,'s',lado_meu) == 1)
	{
		ExcutaJogada(tabuleiro,Posx,Posy+2,'s',lado_meu);
		AnalisaJogadasPossiveis(,1)
	}

	if(EhPossivel(tabuleiro,Posx,Posy,Posx,Posy-2,Posx,Posy-1,'s',lado_meu) == 1)
	{
		ExecutaJogada(tabuleiro,Posx,Posy-2,'s',lado_meu)
		AnalisaJogadasPossiveis(,1)
	}
}


void ProcuraJogadas(tabuleiro_meu *tabuleiro, char lado_meu)
{
	int i,j;
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			AnalisaJogadasPossiveis(tabuleiro,i,j,lado_meu);
		}
	}
}



int main(int argc, char **argv) {
	char buf[MAXSTR];
	char tabuleiro[MAXSTR]; 
	char lado_meu;
	char lado_adv;
	char tipo_mov_adv;
	int num_mov_adv;
	int mov_adv_l[MAXINT];
	int mov_adv_c[MAXINT];
	int i;


	tabuleiro_meu *tabuleiro_meu;
	tabuleiro_meu = malloc(sizeof(tabuleiro_meu));
	AlocaTabuleiro(tabuleiro_meu);



	// conecta com o controlador do campo
	tabuleiro_conecta(argc, argv);

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

	LeInformacao(tabuleiro, tabuleiro_meu);
	PrintaTabuleiro(tabuleiro_meu);
	// prepara um string com o movimento

	ProcuraJogadas(tauleiro_meu, lado_meu,0); 

	// envia o movimento para o controlador do campo
	tabuleiro_envia(buf);  
}
