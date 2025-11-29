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

struct dado_evento *insere_dados (int d1, int d2){
  struct dado_evento *aux;

  aux = malloc (sizeof(struct dado_evento));
  if (!aux)
    return NULL;

  // Unifica dados em uma estrutura propria
  aux->dado1 = d1;
  aux->dado2 = d2; 

  return aux;
}

void seleciona_evento (struct mundo *m, struct dado_evento *dados, int tipo_ev){

  switch (tipo_ev){

    case EV_CHEGA :
      // Dado1 = ID heroi, Dado 2 = ID base
      chega(m, m->relogio, dados->dado1, dados->dado2);
      break;

    case EV_ESPERA :
      espera(m, m->relogio, dados->dado1, dados->dado2);
      break;
    
    case EV_DESISTE :
      desiste(m, m->relogio, dados->dado1, dados->dado2);
      break;
    
      default:
      // Mensagem teste para eventos ainda não criados, retirar apos conclusão do trabalho 
      printf ("%6d: Evento (Tipo: %d) ainda não criado\n", m->relogio, tipo_ev);
      break;
  }

  // strutura dados livre para haver vazamento de memorias 
  free (dados);
}

void eventos_iniciais (struct mundo *m){
  int aux_base, aux_temp; // Variaveis para armazenar valores aleatorios que irão na lef
  struct dado_evento *aux_dados;

  if (!m)
    erro ("Ponteiro para o mundo inválido em eventos iniciais!");

  // Move cada heroi para uma base B nos primeiross 3 dias do mundo e preenche na LEF
  for (int i = 0; i < m->nherois; i++){
    aux_base = aleat (0, m->nbases - 1); // Utilizado por segurança o valor m->nbase 
    aux_temp = aleat (0, 4320); // Primeiros 3 dias apos criação do mundo (60*24*3)

    aux_dados = insere_dados (m->herois[i].ID, aux_base);
    if (!aux_dados)
      erro("Erro ao alocar estrutura de dados do evento: herois");

    if (fprio_insere (m->eventos, aux_dados, EV_CHEGA, aux_temp) == -1){
      printf ("%d\n",m->herois[i].ID);
      erro ("Item não inserido na fila, chegada heroi");
    }
  }

  // Inicia as missoes que devem ocorrer em um instante(tempo) aleatorio, até o fim do mundo
  for (int i = 0; i < m->nmissoes; i++){
    aux_temp = aleat (0, T_FIM_DO_MUNDO);

    aux_dados = insere_dados (m->missoes[i].ID, -1);// Segundo dado (d2) não utilizado agora 
    if (!aux_dados)
      erro("Erro ao alocar estrutura de dados do evento: missoes");
    
    if (fprio_insere (m->eventos, aux_dados, EV_MISSAO, aux_temp) == -1){
      printf ("%d\n",m->missoes[i].ID);
      erro ("Item não inserido na fila, criação missão"); 
    }
  }

  aux_dados = insere_dados (-1,-1);
  if (!aux_dados)
    erro ("Erro ao alocar estrutura de dados do evento: fim do mundo");

  if (fprio_insere (m->eventos, aux_dados, EV_FIM, T_FIM_DO_MUNDO) == -1)
    // Dados não necessarios serem preenchidos  
    erro ("Item não inserido na fila, fim do mundo");
}

void chega (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;
  bool espera;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento inválido em evento chega!");

  // Atualiza base do heroi
  m->herois->ID_base = id_base; 

  // Verifica se há vagas na base e se a fila de espera esta vazia 
  if (cjto_card (m->bases[id_base].presentes) < m->bases[id_base].lotacao && 
      !fila_tamanho(m->bases[id_base].espera))
    espera = true;

  // Verifica se o heroi tem paciencia pra esperar na fila
  else
    espera = m->herois[id_heroi].paciencia > 10 * fila_tamanho(m->bases[id_base].espera);

  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro ("Erro ao alocar estrutura de dados do evento: chegada");
  
  // Mensagem de saida principal do evento
  printf ("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", 
    tempo, id_heroi, id_base, cjto_card (m->bases[id_base].presentes), m->bases[id_base].lotacao);

  if (espera){
    // Insere e verifica o evento na LEF
    if (fprio_insere (m->eventos, aux, EV_ESPERA, tempo) == -1)
      erro ("Item não inserido na fila no evento chegada"); 

    printf ("ESPERA\n");
  }
  
  else{
    if (fprio_insere (m->eventos, aux, EV_DESISTE, tempo) == -1)
      erro ("Item não inserido na fila no evento chegada"); 

    printf ("DESISTE\n");
  }
}

void espera (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;

  if (!m || !m->eventos || !m->bases[id_base].espera)
    erro ("Ponteiro para o mundo, evento ou fila de espera da base inválido em evento espera!");
  
  // Adiciona ID do heroi ao fim da fila de espera da base
  if (!fila_insere(m->bases[id_base].espera, id_heroi))
    erro("Item não inserido na fila de espera na base no evento espera");
    
  // cria e insere na LEF o evento AVISA (agora, B)
  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: espera");

  // Insere e verifica o evento na LEF
  if (fprio_insere (m->eventos, aux, EV_AVISA, tempo) == -1)
    erro ("Item não inserido na fila no evento espera"); 

  // Mensagem de saida principal do evento
  printf ("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, id_heroi, id_base, 
    fila_tamanho(m->bases[id_base].espera) - 1);
}
  
void desiste (struct mundo *m, int tempo, int id_heroi, int id_base){


  // O her´oi H desiste de entrar na base B, escolhe uma base aleat´oria D e viaja
  // para l´a:
  
  // DESISTE (T, H, B):
  // escolhe uma base destino D aleat´oria
  
  // cria e insere na LEF o evento VIAJA (agora, H, D)
}
  
/*
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