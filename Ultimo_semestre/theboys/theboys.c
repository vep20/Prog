// programa principal do projeto "The Boys - 2025/2"
// Autor: Victor Eduardo de Paula, GRR 20203937

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "execucao.h"

void impr_herois (struct mundo *mundo){
  struct heroi aux;

  if (!mundo || !mundo->herois)
    erro("impossivel imprimir, mundo ou vetor de herois não allocado");
  

  for (int i = 0; i < mundo->nherois; i++){
    aux = mundo->herois[i];

    printf("Heroi ID: %d\n", aux.ID);
    printf(" - Paciencia: %d\n", aux.paciencia);
    printf(" - Velocidade: %d\n", aux.velocidade);
    printf(" - Experiencia: %d\n", aux.experiencia);

    printf (" - Habilidades: ");
    
    if (!cjto_card(aux.habilidades)){
      printf("(nenhuma habilidade)");
    }

    else{
      cjto_imprime(aux.habilidades);
    }
    
    printf("\n\n");
  }
}

void impr_bases (struct mundo *mundo){
  struct base aux;

  if (!mundo || !mundo->bases)
    erro("impossivel imprimir, mundo ou vetor de herois não allocado");

  for (int i = 0; i < mundo->nbases; i++){
    aux = mundo->bases[i];

    printf("Base ID: %d\n", aux.ID);
    printf(" - Lotação: %d\n", aux.lotacao);
    printf(" - Coordenadas: %d %d\n", aux.lb.x, aux.lb.y);

    if (!aux.espera->num)
      printf (" - Não há herois na fila de espera\n");

    if (!cjto_card(aux.presentes))
      printf (" - Não há nenhum heroi na base\n");

    printf ("\n");
  }

}

void impr_missoes(struct mundo *mundo){
  struct missao aux;

  if (!mundo || !mundo->missoes)
    erro("impossivel imprimir, mundo ou vetor de missoes não allocado");

  for (int i = 0; i < mundo->nmissoes; i++){
    aux = mundo->missoes[i];
    
    printf("Missao ID: %d\n", aux.ID);
    printf(" - Coordenadas: %d %d\n", aux.lm.x, aux.lm.y);
    printf (" - Habilidades: ");
    
    if (!cjto_card(aux.habilidades)){
      printf("(nenhuma habilidade)");
    }

    else{
      cjto_imprime(aux.habilidades);
    }
    
    printf("\n\n");
  }  
}

void test_impr (struct mundo *mundo){

  if (!mundo)
    erro("impossivel imprimir, mundo não alocado");

  printf("tamanho x:%d y:%d\n",mundo->TamanhoMundo.x,mundo->TamanhoMundo.y);
  printf("relogio:%d\n", mundo->relogio);
  printf("nherois:%d\n",mundo->nherois);
  printf("nbases:%d\n",mundo->nbases);
  printf("nmissoes:%d\n",mundo->nmissoes);
  printf("nhabilidades:%d\n",mundo->nhabilidades);
  printf("nCompostoV:%d\n",mundo->nCompostoV);
  printf ("nherois: %d\n", mundo->nherois);
  printf("\n");

  if (!mundo->eventos || mundo->eventos->num == 0 || !mundo->eventos->prim) {
    printf("Nenhum evento cadastrado.\n");
    return;
  }

  struct fpnodo_t *aux;

    aux = mundo->eventos->prim;
    printf ("ID heroi | ID base : %d %d\n",((struct dado_evento *)aux->item)->dado1, ((struct dado_evento *)aux->item)->dado2);
    printf (" tipo | prioridade(%d %d)\n\n", aux->tipo, aux->prio);
    aux = aux->prox;

    for(int i = 1; i < mundo->eventos->num; i++){
      if (aux->tipo == EV_CHEGA)
        printf ("ID heroi | ID base : %d %d\n",((struct dado_evento *)aux->item)->dado1, ((struct dado_evento *)aux->item)->dado2);
        
      else if (aux->tipo == EV_MISSAO)
        printf ("ID missao :  %d\n",((struct dado_evento *)aux->item)->dado1);

      else
        printf ("Evento fim");

      printf (" tipo | prioridade(%d %d)", aux->tipo, aux->prio);
      printf ("\n\n");
      aux = aux->prox;
    } 

  /*
  impr_herois (mundo);
  printf("\n");
  impr_bases (mundo);
  printf("\n");
  impr_missoes(mundo);  
  */
}


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

  // função de teste RETIRAR DEPOIS 
  //test_impr(novo_mundo);


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