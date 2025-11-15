// programa principal do projeto "The Boys - 2025/2"
// Autor: Victor Eduardo de Paula, GRR 20203937

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "execucao.h"


void impr_heroi (struct heroi *heroi){
  
  if (!heroi){
    erro("impossivel imprimir, heroi não allocado");
    return;  
  }
  printf ("");
}

void test_impr (struct mundo *mundo){

  if (!mundo){
    erro("impossivel imprimir, mundo não alocado");
    return;
  }
  
  printf ("nherois: %d\n", mundo->nherois);
  for (int i = 0; i < N_HEROIS; i++){

  }

}


int main (){
  struct mundo *novo_mundo;
  srand(0);

  // inicia o mundo
  novo_mundo = cria_mundo();
  if(!novo_mundo)
    erro ("Não criou mundo\n"); // função
  
  inicia_mundo(novo_mundo);

/*
  // executa o laço de simulação
  while (novo_mundo->relogio < T_FIM_DO_MUNDO){

    

    novo_mundo->relogio++;
  }
  // destruoi o mundo
  destroi_mundo(novo_mundo);
  return 0;
*/

}