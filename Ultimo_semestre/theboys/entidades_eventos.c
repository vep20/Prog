#include <stdio.h>
#include <stdlib.h>
#include "entidades_eventos.h"


// Imprime mensagem de erro e encerra execução
void erro (char *msg){
  fprintf (stderr, "ERRO: %s\n", msg);
  exit (1);
}

int aleat (int min, int max){
  int n_aleat; 

  // Forma de gerar numeros aleatorios entre min e max includos eles mesmos
  n_aleat = min + rand() % (max - min + 1); 
  return n_aleat;
}

void cria_eventos (struct mundo *m, int temp, int tipo, int d1, int d2){
  struct dado_evento *aux;

  aux = malloc (sizeof(struct dado_evento));
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento");

  aux->dado1 = d1;
  aux->dado2 = d2;

  fprio_insere (m->eventos, aux, tipo, temp);
}

void eventos_iniciais (struct mundo *m){
  int aux_base, aux_temp; // Variaveis para armazenar valores aleatorios que irão na lef

  if (!m)
    erro ("Ponteiro para o mundo inválido!\n");

  // Move cada heroi para uma base B nos primeiross 3 dias do mundo e preenche na LEF
  for (int i = 0; i < m->nherois; i++){
    aux_base = aleat (0, m->nbases - 1); // Utilizado por segurança o valor m->nbase 
    aux_temp = aleat (0, 4320); // Primeiros 3 dias apos criação do mundo (60*24*3)

    cria_eventos (m, aux_temp, EV_CHEGA, m->herois[i].ID, aux_base);
  }

  // Inicia as missoes que devem ocorrer em um instante(tempo) aleatorio, até o fim do mundo
  for (int i = 0; i < m->nmissoes; i++){
    aux_temp = aleat (0, T_FIM_DO_MUNDO);

    cria_eventos (m, aux_temp, EV_MISSAO, m->missoes[i].ID, -1);// Segundo dado (d2) não utilizado agora 
  }

  cria_eventos (m, T_FIM_DO_MUNDO, EV_FIM, -1, -1);// Insere o evento fim no fim do mundo
  // Dados não necessarios serem preenchidos  
}

/*
void chega (int tempo, struct heroi h, struct base b){

// atualiza base de H

// se h´a vagas em B e a fila de espera em B est´a vazia:
  // espera = true
// sen~ao:
  // espera = (paci^encia de H) > (10 * tamanho da fila em B)

// se espera:
  // cria e insere na LEF o evento ESPERA (agora, H, B)
// sen~ao:
  // cria e insere na LEF o evento DESISTE (agora, H, B)

// Importante: A Lista de Eventos Futuros (LEF) pode ser implementada
// usando o TAD “fila de prioridades” previamente implementado.
}

void espera (int tempo, struct heroi h, struct base b){
  
// adiciona H ao fim da fila de espera de B
// cria e insere na LEF o evento AVISA (agora, B)

// Importante: A fila de espera de cada base pode ser implementada usando
// o TAD “lista de inteiros” previamente implementado.
}

void desiste (int tempo, struct heroi h, struct base b){
// O her´oi H desiste de entrar na base B, escolhe uma base aleat´oria D e viaja
// para l´a:

// DESISTE (T, H, B):
// escolhe uma base destino D aleat´oria

// cria e insere na LEF o evento VIAJA (agora, H, D)
}

void avisa (int tempo, struct base b){
// enquanto houver vaga em B e houver her´ois esperando na fila:
  // retira primeiro her´oi (H’) da fila de B
  // adiciona H’ ao conjunto de her´ois presentes em B
  // cria e insere na LEF o evento ENTRA (agora, H’, B)
}

void entra (int tempo, struct heroi h, struct base b){
// calcula TPB = tempo de perman^encia na base:
  // TPB = 15 + paci^encia de H * aleat´orio [1...20]
// cria e insere na LEF o evento SAI (agora + TPB, H, B)
}

void sai (int tempo, struct heroi h, struct base b){
// retira H do conjunto de her´ois presentes em B
// escolhe uma base destino D aleat´oria
// cria e insere na LEF o evento VIAJA (agora, H, D)
// cria e insere na LEF o evento AVISA (agora, B)
}

void viaja (int tempo, struct heroi h, struct base d){
// calcula dura¸c~ao da viagem:
  // dist^ancia = dist^ancia cartesiana entre a base atual de H e a base D
  // dura¸c~ao = dist^ancia / velocidade de H
// cria e insere na LEF o evento CHEGA (agora + dura¸c~ao, H, D)
}

void morre (int tempo, struct heroi h, struct base b){
// O her´oi H morre no instante T.
// • O her´oi ´e retirado da base B e libera uma vaga na base.
// • O porteiro de B deve ser avisado da nova vaga.
// • Eventos futuros de um her´oi morto devem ser ignorados.

// MORRE (T, H, B):

// retira H do conjunto de her´ois presentes em B
// muda o status de H para morto
// cria e insere na LEF o evento AVISA (agora, B)
}

void missoes (int tempo, struct missao m){
// calcula a dist^ancia de cada base ao local da miss~ao M
// encontra BMP = base mais pr´oxima da miss~ao cujos her´ois possam cumpri-la

// se houver uma BMP:
  // marca a miss~ao M como cumprida
  // incrementa a experi^encia dos her´ois presentes na BMP

// sen~ao:
  // verifica se existem compostos V disponiveis
  // se existir e T for multiplo de 2500:
  // decrementa a quantidade total de compostos V
  // marca a miss~ao M como cumprida
  // para o heroi mais experiente (H) cria e insere
    // na LEF o evento MORRE (agora, H)
  // incrementa a experiencia dos demais herois presentes na BMP

// senao:
  // cria evento MISSAO (T + 24*60, M) para o dia seguinte  

}

void fim (int tempo){
// encerra a simula¸c~ao
// apresenta estat´ısticas dos her´ois
// apresenta estat´ısticas das bases
// apresenta estat´ısticas das miss~oes
}
*/