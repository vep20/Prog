#ifndef EXECUCAO
#define EXECUCAO

#include "entidades_eventos.h"

// Função que cria e devolve uma struct mundo,
// retorna NULL em caso de erro.
struct mundo *cria_mundo ();

// Função que inicia os membros de uma struct mundo.
void inicia_mundo (struct mundo *m);

// Função que destroi e da free em um ponteiro para struct mundo.
void destroi_mundo (struct mundo *m);

/*
// Função que preenche o vetor de herois do mundo
int cria_herois (struct mundo *m);

// Função que inicia os membros de uma struct heroi.
struct heroi inicia_heroi (int id);

// Função que preenche o vetor de bases do mundo
int cria_bases (struct mundo *m);

// Função que inicia os membros de uma struct heroi.
struct base inicia_base (int id);

// Função que preenche o vetor de missoes do mundo
int cria_missoes (struct mundo *m);

// Função que destroi e da free em um ponteiro para struct mundo.
struct missao inicia_missao (int id);

void destroi_heroi(struct heroi *h);

void destroi_herois(struct heroi *herois, int nherois);

void destroi_base(struct base *b);

void destroi_bases(struct base *bases, int nbases);

void destroi_missao(struct missao *m);

void destroi_missoes(struct missao *missoes, int nmissoes);
*/

#endif