// programa principal do projeto "The Boys - 2025/1"
// Autor: Victor Eduardo de Paula, GRR 20203937

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "execucao.h"
#include "Entidades_eventos.h"

int main (){
  struct mundo *novo_mundo;
  srand(0);

  // inicia o mundo
  novo_mundo = cria_mundo();
  if(!novo_mundo)
    erro ("Não criou mundo\n"); // função
  
  inicia_mundo(novo_mundo);

  // executa o laço de simulação
  while (novo_mundo->relogio < T_FIM_DO_MUNDO){

    

    novo_mundo->relogio++;
  }
  // destruoi o mundo
  destroi_mundo(novo_mundo);
  return 0;
}