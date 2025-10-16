#include <stdio.h>
#include <stdlib.h>
#include "Entidades_eventos.h"


// imprime mensagem de erro e encerra execução
void erro (char *msg){
  fprintf (stderr, "ERRO: %s\n", msg) ;
  exit (1);
}

int aleat (int min, int max){
  int n_aleat; 

  // Forma de gerar numeros aleatorios entre min e max includos eles mesmos
  n_aleat = min + rand() % (max - min + 1); 
  return n_aleat;
}

void chega (int tempo, struct heroi h, struct base b){

}

void espera (int tempo, struct heroi h, struct base b){

}

void desiste (int tempo, struct heroi h, struct base b){

}

void avisa (int tempo, struct base b){

}

void entra (int tempo, struct heroi h, struct base b){

}

void sai (int tempo, struct heroi h, struct base b){

}

void viaja (int tempo, struct heroi h, struct base d){

}

void morre (int tempo, struct heroi h, struct base b){

}

void missoes (int tempo, struct missao m){

}

void fim (int tempo){

}