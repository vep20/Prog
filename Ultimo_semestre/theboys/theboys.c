// programa principal do projeto "The Boys - 2025/2"
// Autor: Victor Eduardo de Paula, GRR 20203937

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "execucao.h"

int main (){
  struct mundo *novo_mundo;
  struct dado_evento *ev;
  int tipo, tempo;
  //srand(0);

  // Cria um mundo baseado na struct mundo 
  // Inicia os elementos da struct mundo se criada
  novo_mundo = cria_mundo();
  if (!novo_mundo)
    erro ("Erro ao criar o mundo!");

  eventos_iniciais (novo_mundo);


  // Executa o laço de simulação
  while (novo_mundo->relogio < T_FIM_DO_MUNDO){

    // Variaveis tipo e tempo retornam valores com função fprio_retira
    // fprio_retira possui retorno generico
    ev = fprio_retira(novo_mundo->eventos, &tipo, &tempo);

    // Caso não haja mais nada na LEF
    if (!ev)
      break;

    // Atualiza o relógio conforme tempo de evento
    novo_mundo->relogio = tempo;

    seleciona_evento(novo_mundo, ev, tipo);
  }

  // destroi o mundo
  novo_mundo = destroi_mundo(novo_mundo);
  return 0;
}