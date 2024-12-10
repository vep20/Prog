#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

// Função auxiliar para calcular distância
int calcula_distancia(int x1, int y1, int x2, int y2) {
    return (int) sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Evento ESPERA
void espera(int tempo, struct heroi h, struct base b) {
    int pos = lista_tamanho(b.espera); // Determina a posição para inserir (final da fila)
    if (lista_insere(b.espera, h.ID, pos) == 0) { // Insere no final da lista de espera
        printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, h.ID, b.ID, lista_tamanho(b.espera));
    } else {
        // Caso ocorra um erro na inserção
        printf("ERRO: Não foi possível inserir o herói %d na fila da base %d\n", h.ID, b.ID);
    }

    // Após adicionar o herói à fila, avisa o porteiro
    avisa(tempo, b);
}


// Evento CHEGA
void chega(int tempo, struct heroi h, struct base b) {
    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", tempo, h.ID, b.ID,
           cjto_tamanho(b.presentes), b.lotacao);

    if (cjto_tamanho(b.presentes) < b.lotacao && lista_tamanho(b.espera) == 0) {
        printf("ESPERA\n");
        espera(tempo, h, b);
    } else {
        int espera = h.paciencia > 10 * lista_tamanho(b.espera);
        if (espera) {
            printf("ESPERA\n");
            espera(tempo, h, b);
        } else {
            printf("DESISTE\n");
            desiste(tempo, h, b);
        }
    }
}

// Evento DESISTE
void desiste(int tempo, struct heroi h, struct base b) {
    int nova_base = aleat(0, N_BASES - 1);

    printf("%6d: DESIST HEROI %2d BASE %d\n", tempo, h.ID, b.ID);

    struct base *destino = &b;  // Obtenha referência à nova base
    viaja(tempo, h, *destino);
}

// Evento AVISA
void avisa(int tempo, struct base b) {
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [", tempo, b.ID,
           cjto_tamanho(b.presentes), b.lotacao);
    lista_imprime(b.espera);
    printf("]\n");

    while (cjto_tamanho(b.presentes) < b.lotacao && lista_tamanho(b.espera) > 0) {
        int heroi = lista_remove(b.espera);
        cjto_insere(b.presentes, heroi);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, b.ID, heroi);

        struct heroi h;
        entra(tempo, h, b);
    }
}

// Evento ENTRA
void entra(int tempo, struct heroi h, struct base b) {
    int tempo_permanencia = 15 + h.paciencia * aleat(1, 20);

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, h.ID, b.ID,
           cjto_tamanho(b.presentes), b.lotacao, tempo + tempo_permanencia);

    sai(tempo + tempo_permanencia, h, b);
}

// Evento SAI
void sai(int tempo, struct heroi h, struct base b) {
    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", tempo, h.ID, b.ID,
           cjto_tamanho(b.presentes) - 1, b.lotacao);

    cjto_remove(b.presentes, h.ID);

    int nova_base = aleat(0, N_BASES - 1);
    struct base *destino = &b;  // Obtenha referência à nova base
    viaja(tempo, h, *destino);

    avisa(tempo, b);
}

// Evento VIAJA
void viaja(int tempo, struct heroi h, struct base d) {
    struct base *atual = h.base_atual;

    int distancia = calcula_distancia(atual->lb->x, atual->lb->y, d.lb->x, d.lb->y);
    int tempo_chegada = distancia / h.velocidade;

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
           tempo, h.ID, atual->ID, d.ID, distancia, h.velocidade, tempo + tempo_chegada);

    chega(tempo + tempo_chegada, h, d);
}

// Evento MORRE
void morre(int tempo, struct heroi h, struct base b) {
    printf("%6d: MORRE  HEROI %2d BASE %d\n", tempo, h.ID, b.ID);

    cjto_remove(b.presentes, h.ID);
    avisa(tempo, b);

    // Ignore futuros eventos desse herói
    h.ID = -1;  // Marcador para "morto"
}

// Evento MISSOES
void missoes(int tempo, struct missao m) {
    printf("%6d: MISSAO %d TENT 1 HAB REQ: [", tempo, m.ID);
    cjto_imprime(m.habilidades);
    printf("]\n");

    struct base *melhor_base = NULL;
    int menor_distancia = INT_MAX;

    // Encontra a base apta mais próxima
    for (int i = 0; i < N_BASES; i++) {
        struct base *b = &b;
        if (cjto_contem(b->presentes, m.habilidades)) {
            int distancia = calcula_distancia(b->lb->x, b->lb->y, m.lm->x, m.lm->y);
            if (distancia < menor_distancia) {
                melhor_base = b;
                menor_distancia = distancia;
            }
        }
    }

    if (melhor_base) {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d\n", tempo, m.ID, melhor_base->ID);
    } else {
        printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, m.ID);
        missoes(tempo + 24 * 60, m);  // Reagenda para o dia seguinte
    }
}

// Evento FIM
void fim(int tempo) {
    printf("%6d: FIM\n", tempo);
    // Apresente as estatísticas do mundo aqui
}