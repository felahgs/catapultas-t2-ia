#include <stdlib.h>
#include <stdio.h>
#include "tabuleiro.h"


void printint (char* s, int i) {
  printf("%s: %d\n",s, i);
}

void imprime_vertice(vertice v) {
  printint("Vertice", v->id);
}

void copia_array(int *org, int *dest) {
  for (int i = 0; i <= org[0]+2; i++) {
    dest[i] = org[i];
  }
}

void imprime_array(int *arr){
  printf("%d ", arr[0]/2);
  if(arr[1] == 0)
	printf("m ");
  else if(arr[1] == 1)
	printf("s ");

  for (int i = 2; i < arr[0]+2; i++) {
    printf("%d ",  arr[i]+1);
  }
  printf("\n");
}


char * imprime_array_copia(int *arr,char lado_meu){
char buffer[1000];
char *final;
final = malloc(sizeof(char)*10000);
if(lado_meu == 'x')
	sprintf(buffer,"x ");
if(lado_meu == 'o')
	sprintf(buffer,"o ");
strcat(final,buffer);

  
  if(arr[1] == 0)
{
	sprintf(buffer,"m ");
	strcat(final,buffer);
}
  else if(arr[1] == 1)
{
	sprintf(buffer,"s ");
	strcat(final,buffer);
}
if(arr[1] == 1)
{
	sprintf(buffer,"%d ", arr[0]/2);
	strcat(final,buffer);
}

  for (int i = 2; i < arr[0]+2; i++) {
    sprintf(buffer,"%d ",  arr[i]+1);
	strcat(final,buffer);
  }
  sprintf(buffer,"\n");
strcat(final,buffer);
	return(final);
}
