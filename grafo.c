#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "tabuleiro.h"

grafo constroi_grafo() {

  grafo g = malloc(sizeof(struct grafo));

  if ( ! g ) 
    return NULL;
    
  g->vertices = constroi_lista();
  g->numVertice = 0;
  // g->raiz = novo_vertice(0, NULL, g);

  return g;
}

vertice constroi_vertice (vertice pai, grafo g, tabuleiro_meu * tabuleiro) {

	vertice v = malloc(sizeof(*v));

	if ( !v )
		return NULL;

  // v->id = id;
  	g->numVertice++;
	v->pai = pai;
	v->tabuleiro = tabuleiro;
	v->id = g->numVertice;
	v->filhos  = constroi_lista();

  insere_lista(v, g->vertices);

  // v->rota = malloc(2 * sizeof(int*));
  if( pai != NULL) {
    v->profundidade = pai->profundidade + 1;
    insere_lista(v, pai->filhos);

   // copia_array(pai->movimentos, v->movimentos);


  }
  else {
    v->profundidade = 0;
  }


	return v;
}


lista vertices(grafo g) { return g->vertices; }

void imprime_filhos(vertice ver) {
  lista l = ver->filhos;
  for(no n = primeiro_no(l); n; n = proximo_no(n)) {
    vertice v = conteudo(n);
    printf("\t\"Vertice %d\"\n", v->id);
  }
}

void imprime_lista(lista l) {
  if (l->primeiro == NULL)
    printf("\tLista vazia\n");
  else 
    for(no n = primeiro_no(l); n; n = proximo_no(n)) {
      vertice v = conteudo(n);
	PrintaTabuleiro(v->tabuleiro);
	imprime_array(v->movimentos);
      if (v->pai == NULL) {
        printf("\t\"Vertice %d\" Vertice Raíz", v->id);
        printf(" profundidade: %d", v->profundidade);
        printf("\n");
      }
      else 
        printf("\t\"Vertice %d\" filho de \"Vertice %d\" ", v->id, v->pai->id);
        printf(" profundidade: %d", v->profundidade);
        printf("\n");
        // imprime_array(v->rota);
    }
}

