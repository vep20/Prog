#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void troca(struct distancia_missao *a, struct distancia_missao *b){
    struct distancia_missao aux;
    
    aux = *a;
    *a = *b;
    *b = aux;
}

void ordena_vetor (struct distancia_missao *vetor, int n){
  int i, j, min;

  for (i = 0; i < n - 1; i++){
      // Encontra o menor elemento no restante do vetor desordenado
      min = i;
      for (j = i + 1; j < n; j++) {
          if (vetor[j].distancia < vetor[min].distancia)
              min = j;
      }

      // troca os elementos
      troca(&vetor[min], &vetor[i]);
  }
}

long calcula_distancia (struct local origem, struct local destino){
  long aux_distancia, ponto_x, ponto_y;

  ponto_x = (destino.x - origem.x) * (destino.x - origem.x);
  ponto_y = (destino.y - origem.y) * (destino.y - origem.y);
  aux_distancia = sqrt(ponto_x + ponto_y);

  return aux_distancia;
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

  m->total_eventos++;

  switch (tipo_ev){

    case EV_CHEGA :
      // Dado1 = ID heroi, Dado 2 = ID base
      chega (m, m->relogio, dados->dado1, dados->dado2);
      break;

    case EV_ESPERA :
      espera (m, m->relogio, dados->dado1, dados->dado2);
      break;
    
    case EV_DESISTE :
      desiste (m, m->relogio, dados->dado1, dados->dado2);
      break;
    
    case EV_AVISA :
      avisa (m, m->relogio, dados->dado1, dados->dado2);
      break;

    case EV_ENTRA :
      entra (m, m->relogio, dados->dado1, dados->dado2);
      break;

   case EV_SAI :
      sai (m, m->relogio, dados->dado1, dados->dado2);
      break;

   case EV_VIAJA :
      viaja (m, m->relogio, dados->dado1, dados->dado2);
      break;

   case EV_MORRE :
      morre (m, m->relogio, dados->dado1, dados->dado2);
      break;

    case EV_MISSAO :
      missao (m, m->relogio, dados->dado1, dados->dado2);
      break;

    case EV_FIM :
      fim(m, m->relogio);
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
  struct dado_evento *aux_dados;
  int aux_base, aux_temp; // Variaveis para armazenar valores aleatorios que irão na lef

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
    erro ("Ponteiro para o mundo, evento inválido em evento chega");

  // Verifica se o herói está vivo antes de processar qualquer coisa
  if (!m->herois[id_heroi].vivo)
      return;

  if (!m->bases[id_base].presentes || !m->bases[id_base].espera)
    erro ("Ponteiro cjto presente ou fila de espera da base invalido em evento chega");

  // Atualiza base do heroi
  m->herois[id_heroi].ID_base = id_base; 

  // Verifica se há vagas na base e se a fila de espera esta vazia 
  if (cjto_card (m->bases[id_base].presentes) < m->bases[id_base].lotacao && 
      !fila_tamanho(m->bases[id_base].espera))
    espera = true;

  // Verifica se o heroi tem paciencia pra esperar na fila
  else
    espera = m->herois[id_heroi].paciencia > 10 * fila_tamanho(m->bases[id_base].espera);

  // Mensagem de saida principal do evento
  printf ("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", 
    tempo, id_heroi, id_base, cjto_card (m->bases[id_base].presentes), m->bases[id_base].lotacao);

  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro ("Erro ao alocar estrutura de dados do evento: chegada");
  
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
  int tam_atual;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento espera");
  
  // Verifica se o herói está vivo antes de processar qualquer coisa
  if (!m->herois[id_heroi].vivo)
      return;

  if (!m->bases[id_base].espera)
    erro ("Ponteiro para fila de espera da base inválido em evento espera");

  // Adiciona ID do heroi ao fim da fila de espera da base
  if (!fila_insere(m->bases[id_base].espera, id_heroi))
    erro ("Item não inserido na fila de espera na base no evento espera");

  tam_atual = fila_tamanho(m->bases[id_base].espera);
  if (tam_atual > m->bases[id_base].max_fila)
    m->bases[id_base].max_fila = tam_atual;

  // Mensagem de saida principal do evento
  printf ("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, id_heroi, id_base, 
    fila_tamanho(m->bases[id_base].espera) - 1);
    
  // Cria e insere na LEF o evento AVISA
  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro ("Erro ao alocar estrutura de dados do evento: espera");

  if (fprio_insere (m->eventos, aux, EV_AVISA, tempo) == -1)
    erro ("Item não inserido na fila no evento espera"); 

}

void desiste (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;
  int base_destino;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento desiste");
  
  // Verifica se o herói está vivo antes de processar qualquer coisa
  if (!m->herois[id_heroi].vivo)
      return;

  // Mensagem de saida principal do evento
  printf ("%6d: DESIST HEROI %2d BASE %d\n", tempo, id_heroi, id_base);
    
  // Define um valor aleatorio para identificar a base que heroi irá
  base_destino = aleat(0, m->nbases - 1);

  // Cria e insere na LEF o evento VIAJA para base destino
  aux = insere_dados (id_heroi, base_destino);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: desiste");
  
  if (fprio_insere (m->eventos, aux, EV_VIAJA, tempo) == -1)
    erro ("Item não inserido na fila no evento desiste"); 

}
  
void avisa (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento avisa");
  
  if (!m->bases[id_base].espera)
    erro ("Ponteiro para fila de espera da base inválido em evento avisa");

  // Mensagem de saida principal do evento
  printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, id_base,
    cjto_card (m->bases[id_base].presentes), m->bases[id_base].lotacao);
  
  // Teste já realizado
  fila_imprime(m->bases[id_base].espera);
  printf (" ]\n");

  while (cjto_card (m->bases[id_base].presentes) < m->bases[id_base].lotacao && 
    fila_tamanho(m->bases[id_base].espera)){
    
    // Retira primeiro heroi da fila de espera da base
    if (!fila_retira (m->bases[id_base].espera, &id_heroi))
      erro ("Heroi não retirado em evento avisa");
    
    // Insere heroi no conjunto de presentes na base 
    if (cjto_insere(m->bases[id_base].presentes, id_heroi) == -1)
      erro ("Heroi não inserido no conjunto de presentes na base evento avisa");

    printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, id_base, id_heroi);

    aux = insere_dados (id_heroi, id_base);
    if (!aux)
      erro("Erro ao alocar estrutura de dados do evento: avisa");
    
    // Adiciona heroi ao conjunto de herois presentes na base
    if (fprio_insere (m->eventos, aux, EV_ENTRA, tempo) == -1)
      erro ("Item não inserido na fila no evento avisa");   
  }
}
  

void entra (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;
  int tpb; // Tempo de permanencia na base:

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento entra");

  // Verifica se o herói está vivo antes de processar qualquer coisa
  if (!m->herois[id_heroi].vivo)
      return;
  
  if (!m->bases[id_base].presentes)
    erro ("Ponteiro para cjto presentes da base inválido em evento entra");

  // Calcula quanto tempo o heroi vai ficar na base até que o evento sai seja chamado  
  tpb = 15 + m->herois[id_heroi].paciencia * aleat(1,20);

  // Mensagem de saida principal do evento
  printf ("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, id_heroi, id_base, 
    cjto_card (m->bases[id_base].presentes), m->bases[id_base].lotacao, tempo + tpb); 

  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: entra");
    
  // Cria e insere na LEF o evento SAI
  if (fprio_insere (m->eventos, aux, EV_SAI, tempo + tpb) == -1)
    erro ("Item não inserido na fila no evento entra");  
}

void sai (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;
  int base_destino;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento sai");

  // Verifica se o herói está vivo antes de processar qualquer coisa
  if (!m->herois[id_heroi].vivo)
      return;

  if (!m->bases[id_base].presentes)
    erro ("Ponteiro para cjto presentes da base inválido em evento sai");

  // Retira heroi no conjunto de presentes na base 
  if (cjto_retira(m->bases[id_base].presentes, id_heroi) == -1)
    erro ("Heroi não retirado no conjunto de presentes na base evento sai");

  // Mensagem de saida principal do evento
  printf ("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", tempo, id_heroi, id_base,
    cjto_card (m->bases[id_base].presentes), m->bases[id_base].lotacao);
  
  // Define um valor aleatorio para identificar a base que heroi irá
  base_destino = aleat(0, m->nbases - 1);

  // Cria e insere na LEF o evento VIAJA 
  aux = insere_dados (id_heroi, base_destino);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: sai");

  if (fprio_insere (m->eventos, aux, EV_VIAJA, tempo) == -1)
    erro ("Item não inserido na fila no evento sai");  

  // cria e insere na LEF o evento AVISA 
  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: sai");

  if (fprio_insere (m->eventos, aux, EV_AVISA, tempo) == -1)
    erro ("Item não inserido na fila no evento sai"); 
}

void viaja (struct mundo *m, int tempo, int id_heroi, int id_base){
  struct dado_evento *aux;
  int base_origem;
  int distancia, duracao; // Declarados como inteiros porque é definido para o projeto

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento viaja");
  
  // Verifica se o herói está vivo antes de processar qualquer coisa
  if (!m->herois[id_heroi].vivo)
      return;
  
  base_origem = m->herois[id_heroi].ID_base;

  // Calcula desconsiderando a parte decimal 
  distancia = calcula_distancia (m->bases[base_origem].lb, m->bases[id_base].lb); 
  duracao = distancia / m->herois[id_heroi].velocidade;

  // Mensagem de saida principal do evento
  printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, id_heroi, 
    base_origem, id_base, distancia, m->herois[id_heroi].velocidade ,tempo + duracao);
  
  // cria e insere na LEF o evento CHEGA (agora + dura¸c~ao, H, D)X
  aux = insere_dados (id_heroi, id_base);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: viaja");

  if (fprio_insere (m->eventos, aux, EV_CHEGA, tempo + duracao) == -1)
    erro ("Item não inserido na fila no evento viaja");  

}


void morre (struct mundo *m, int tempo, int id_heroi, int id_missao){
  struct dado_evento *aux;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento morre");

  if (!m->bases[m->herois[id_heroi].ID_base].presentes)
    erro ("Ponteiro para cjto presentes da base inválido em evento morre");

  // Mensagem de saida principal do evento
  printf("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, id_heroi, id_missao);
    
  // Retira heroi no conjunto de presentes na base 
  if (cjto_retira(m->bases[m->herois[id_heroi].ID_base].presentes, id_heroi) == -1)
    erro ("Heroi não retirado no conjunto de presentes na base evento morre");

  // Muda o status de H para morto
  m->herois[id_heroi].vivo = false;

  aux = insere_dados (id_heroi, m->herois[id_heroi].ID_base);
  if (!aux)
    erro("Erro ao alocar estrutura de dados do evento: morre");

  if (fprio_insere (m->eventos, aux, EV_AVISA, tempo) == -1)
    erro ("Item não inserido na fila no evento morre");  
}


void missao (struct mundo *m, int tempo, int id_missao, int id_base){
  struct dado_evento *aux_dado;
  struct distancia_missao aux_dis[m->nbases];
  struct cjto_t *aux_conjunto;
  int base_atual, BPM, heroi_exp, aux_exp; 

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento missao");

  if (!m->missoes[id_missao].habilidades || !m->bases[id_base].presentes)
    erro ("Ponteiro para cjto habilidades da missão ou presentes na base invalido em evento missao");
  
  m->missoes[id_missao].tentativas++;
  
  // Mensagem de saida principal do evento
  printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", tempo, id_missao,
    m->missoes[id_missao].tentativas);
  // Imprime habilidades necessarias para a missão ser concluida
  cjto_imprime (m->missoes[id_missao].habilidades);
  printf (" ]\n");

  // Verifica cada distancia das base e armazena esse valor junto com o id das mesmas
  for (int i = 0; i < m->nbases; i++){
    aux_dis[i].id_base = i;
    aux_dis[i].distancia = calcula_distancia (m->bases[i].lb, m->missoes[id_missao].lm);
  }

  // Ordena o vetor auxiliar de distancia por ordem crescente
  ordena_vetor (aux_dis, m->nbases);

  // Percorre as bases distancias ordenadas
  BPM = -1;
  for (int i = 0; i < m->nbases; i++){
    base_atual = aux_dis[i].id_base;

    // Cria conjunto de habilidades para base atual
    aux_conjunto = cjto_cria(m->nhabilidades);
    if (!aux_conjunto)
      erro ("Criação de conjunto da equipe");

    printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", tempo, id_missao, base_atual, aux_dis[i].distancia);
    cjto_imprime(m->bases[base_atual].presentes);
    printf(" ]\n");

    // Verifica todos os herois para saber se estão presentes na base
    for (int j = 0; j < m->nherois; j++){
      // Verifica se heroi esta na base e vivo
      if(m->herois[j].ID_base == base_atual && m->herois[j].vivo){
        struct cjto_t *temp;
        temp = cjto_uniao (aux_conjunto, m->herois[j].habilidades);

        cjto_destroi (aux_conjunto);
        aux_conjunto = temp;

        printf("%6d: MISSAO %d HAB HEROI %2d: [ ", tempo, id_missao, j);
        cjto_imprime(m->herois[j].habilidades);
        printf(" ]\n");
      }
    }

    printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", tempo, id_missao, base_atual);
    cjto_imprime(aux_conjunto);
    printf(" ]\n");

    if (cjto_contem (aux_conjunto, m->missoes[id_missao].habilidades)){
      BPM = base_atual;
      m->bases[BPM].n_missoes++;

      m->missoes[id_missao].cumprida = true;
      printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, id_missao, BPM);
      cjto_imprime(aux_conjunto);
      printf(" ]\n");

      // Incrementa experiencia dos heróis
      for (int i = 0; i < m->nherois; i++)
        if (m->herois[i].ID_base == BPM && m->herois[i].vivo)
            m->herois[i].experiencia++;

      cjto_destroi (aux_conjunto);
      return; // Encerra o evento 
    }   
  
    cjto_destroi (aux_conjunto);
  }

  // Tentativa com CompostoV
  heroi_exp = - 1;
  aux_exp = - 1;
  if (BPM == -1 && m->nCompostoV && (tempo % 2500 == 0)){

    // Acah base mais proxima que contenha um heroi 
    for (int i = 0; i < m->nbases; i++){
      base_atual = aux_dis[i].id_base;
          
      if (cjto_card(m->bases[base_atual].presentes) > 0){
        BPM = base_atual; // 

      // Busca o herói mais experiente na base
      for (int j = 0; j < m->nherois; j++){
        if (m->herois[j].ID_base == BPM && m->herois[j].vivo){
          if (m->herois[j].experiencia > aux_exp){
            aux_exp = m->herois[j].experiencia;
            heroi_exp = j;
          } 
        }
      }

      break; // Para a busca de bases
      }
    }

    if (BPM != -1 && heroi_exp != -1){
      m->nCompostoV--;
      m->missoes[id_missao].cumprida = true;

      m->bases[BPM].n_missoes++;

      printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", tempo, id_missao, BPM);
      cjto_imprime(m->missoes[id_missao].habilidades); 
      printf(" ]\n");

      // Agenda morte do herói
      aux_dado = insere_dados(heroi_exp, id_missao);
      if (fprio_insere(m->eventos, aux_dado, EV_MORRE, tempo) == -1)
        erro("Erro ao agendar morte por Composto V");

      // Incrementa experiencia dos heróis
      for (int i = 0; i < m->nherois; i++)
        if (m->herois[i].ID_base == BPM && m->herois[i].vivo && i != heroi_exp)
          m->herois[i].experiencia++;
      
      return;
    } 
  }


  // Remarca a missao para o proximo dia
  printf ("%6d: MISSAO %d IMPOSSIVEL\n", tempo, id_missao);

  // Remarca a missao para o proximo dia
  aux_dado = insere_dados (id_missao, id_base);
  if (!aux_dado)
  erro("Erro ao alocar estrutura de dados do evento: missao");

  if (fprio_insere (m->eventos, aux_dado, EV_MISSAO, tempo + 24*60) == -1)
    erro ("Item não inserido na fila no evento missao");  

}

void fim (struct mundo *m, int tempo){
  int mortos, cumpridas, min_tent, max_tent;
  double soma_tent, media_tent, perc_cumpridas, perc_mortalidade;

  if (!m || !m->eventos)
    erro ("Ponteiro para o mundo ou evento fila de espera da base inválido em evento missao");

  mortos = 0;
  cumpridas = 0;
  min_tent = -1;
  max_tent = 0;
  soma_tent = 0.0;
  media_tent = 0.0;
  perc_cumpridas = 0.0;
  perc_mortalidade = 0.0;

  printf ("%d: FIM\n", tempo);

  for (int i = 0; i < m->nherois; i++){
    if (m->herois[i].vivo){
      printf ("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ",
        m->herois[i].ID, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].experiencia);
    }
    else{
      mortos++;
      printf ("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ",
        m->herois[i].ID, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].experiencia);
    }
    cjto_imprime (m->herois[i].habilidades);
    printf (" ]\n");
  }

  for (int i = 0; i < m->nbases; i++){
    printf ("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
      m->bases[i].ID, m->bases[i].lotacao, m->bases[i].max_fila, m->bases[i].n_missoes);
  }

  for (int i = 0; i < m->nmissoes; i++){
    if (m->missoes[i].cumprida)
      cumpridas++;

    soma_tent += m->missoes[i].tentativas;

    if (min_tent == -1 || m->missoes[i].tentativas < min_tent)
      min_tent = m->missoes[i].tentativas;

    if (m->missoes[i].tentativas > max_tent)
      max_tent = m->missoes[i].tentativas;
  }

  if (m->nmissoes > 0){
    media_tent = soma_tent / m->nmissoes;
    perc_cumpridas = ((double)cumpridas / m->nmissoes) * 100.0;
  }

  if (m->nherois > 0)
    perc_mortalidade = ((double)mortos / m->nherois) * 100.0;

  if (min_tent == -1)
    min_tent = 0;

  printf ("EVENTOS TRATADOS: %ld\n", m->total_eventos);
  printf ("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", cumpridas, m->nmissoes, perc_cumpridas);
  printf ("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_tent, max_tent, media_tent);
  printf ("TAXA MORTALIDADE: %.1f%%\n", perc_mortalidade);
}