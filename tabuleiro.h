#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 512
#define MAXINT 16

typedef struct grafo *grafo; 
typedef struct vertice *vertice;


typedef struct {
	char **tabuleiro;
	int x;
	int y;

}tabuleiro_meu;


struct vertice {
  int id, profundidade;
  tabuleiro_meu *tabuleiro;
  int movimentos[100]; //A posição 0 indica o tamanho do vetor e a posição 1 indica qual o tipo de jogada realiza. Se a pos 1 for igual a 0 então 'Move' Se a pos 1 for igual a 1 então 'Salta'

  vertice pai;
  lista filhos; // lista de vizinhos de saida 
};

struct grafo {
    unsigned int numVertice;
    vertice raiz;
    lista vertices;
};

grafo constroi_grafo();
vertice constroi_vertice (vertice pai, grafo g, tabuleiro_meu * tabuleiro);
lista vertices(grafo g);
void imprime_filhos(vertice ver);
void imprime_lista(lista l);
void tabuleiro_conecta(int, char**);
void tabuleiro_envia(char*);
void tabuleiro_recebe(char*);
void AlocaTabuleiro(tabuleiro_meu *tabuleiro);
void PrintaTabuleiro(tabuleiro_meu *tabuleiro);
void CopiaTabuleiro(tabuleiro_meu *tabuleiro, tabuleiro_meu *novo);
void LeInformacao(char *tabuleiro, tabuleiro_meu *tabuleiro_meu);
int EhPossivel(tabuleiro_meu *tabuleiro, int PosX_atual, int PosY_atual, int PosX_tentar, int PosY_tentar, int PosX_entre, int PosY_entre, char tipo, char lado_meu);
vertice ExecutaJogada(int PosxAtual, int PosyAtual, int PosxNova, int PosyNova, int PosxMeio, int PosyMeio, char tipo, char lado_meu, vertice pai, grafo grafo);
void AnalisaJogadasPossiveis(int Posx, int Posy, char lado_meu, int saltou, vertice atual, grafo grafo);
void ProcuraJogadas(tabuleiro_meu *tabuleiro, char lado_meu, grafo grafo);
void printint (char* s, int i);
void imprime_vertice(vertice v);
void copia_array(int *org, int *dest);
void imprime_array(int *arr);
char * imprime_array_copia(int *arr,char lado_meu);



