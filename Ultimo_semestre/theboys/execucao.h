#ifndef EXECUCAO
#define EXECUCAO

#include "entidades_eventos.h"

// Função que cria e devolve uma struct mundo,
// retorna NULL em caso de erro.
struct mundo *cria_mundo ();

// Função que destroi e da free em um ponteiro para struct mundo.
struct mundo *destroi_mundo (struct mundo *m);

// Função que preenche o vetor de herois do mundo
int cria_herois (struct mundo *m);

// Função que inicia os membros de uma struct heroi.
struct heroi inicia_heroi (int id);

// Função para liberar os conjuntos de cada heroi (se existente no mundo)
void libera_herois (struct mundo *m);

// Função que preenche o vetor de bases do mundo
int cria_bases (struct mundo *m);

// Função que inicia os membros de uma struct base.
struct base inicia_base (int id);

void libera_bases (struct mundo *m);

// Função que preenche o vetor de missoes do mundo
int cria_missoes (struct mundo *m);

// Função que preenche os membros de uma struct missao.
struct missao inicia_missao (int id);

// Função para liberar os conjuntos de cada missao (se existente no mundo)
void libera_missoes (struct mundo *m);

#endif