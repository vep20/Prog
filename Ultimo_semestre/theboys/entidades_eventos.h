#ifndef ENTIDADES_EVENTOS
#define ENTIDADES_EVENTOS

#include "conjunto.h"
#include "fprio.h"
#include "fila.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 52600//50000 //525600
#define N_TAMANHO_MUNDO 20000//4 //20000
#define N_HABILIDADES 10//4//10
#define N_HEROIS N_HABILIDADES * 5 
#define N_BASES N_HEROIS / 5 
#define N_MISSOES T_FIM_DO_MUNDO/100//15//T_FIM_DO_MUNDO / 100
#define N_COMPOSTOS_V N_HABILIDADES * 3

// Valores dos eventos para definir o tipo na LEF (fila de prioridades já criada em trabalho anterior)
#define EV_CHEGA   0
#define EV_ESPERA  1
#define EV_DESISTE 2
#define EV_AVISA   3
#define EV_ENTRA   4
#define EV_SAI     5
#define EV_VIAJA   6
#define EV_MORRE   7
#define EV_MISSAO  8
#define EV_FIM     9

struct heroi{
    struct base *base_atual;
    struct cjto_t *habilidades;
    int ID;
    int paciencia;
    int velocidade;
    int experiencia;
};

struct local{
    int x;
    int y;
};

struct base{
    struct cjto_t *presentes;
    struct fila_t *espera;
    struct local lb;
    int ID;
    int lotacao;
};

struct missao{
    struct cjto_t *habilidades;
    struct local lm;
    int ID;
};

struct mundo{
    struct heroi herois[N_HEROIS]; // vetor de herois 
    struct base bases[N_BASES]; // vetor de bases
    struct missao missoes[N_MISSOES]; // vetor de missoes
    struct fprio_t *eventos;
    struct local TamanhoMundo; // estatico pois são apenas duas coordenadas simples 
    int nherois; // numero de herois
    int nbases; // numero de bases
    int nmissoes; // numero de missões
    int nhabilidades; // numero de habilidades
    int nCompostoV; // numero de compostos V disponiveis
    int relogio;
};

// Estrutra utilzada para auxiliar a inserer os eventos na LEF
// Como a fprio_insere so aceita um void *item é necessario transformar esses dados 
struct dado_evento{
    int dado1; // ID heroi ou missão
    int dado2; // ID base 
};

// Função mensagem de erro
void erro (char *msg);

// Função que cria e retorna um número aleatório entre min e max
int aleat (int min, int max);

// Função para auxiliar criar dados que irão na LEF
struct dado_evento *insere_dados (int d1, int d2);

// Função que cria os eventos iniciais da simulação, para os herois, missoes e fim do mundo
void eventos_iniciais (struct mundo *m);

/*
// Função que Representa um herói H chegando em uma base
// B no instante T. Ao chegar, o herói analisa o tamanho 
// da fila e decide se espera para entrar ou desiste
void chega (int tempo, struct heroi h, struct base b);

// Função onde um herói H entra na fila de espera da base B. 
// Assim que H entrar na fila, o porteiro da base B deve ser 
// avisado para verificar a fila
void espera (int tempo, struct heroi h, struct base b);

// Função onde um herói H desiste de entrar na base B, escolhe 
// uma base aleatória D e viaja para lá
void desiste (int tempo, struct heroi h, struct base b);

// Função onde o porteiro da base B trata a fila de espera
void avisa (int tempo, struct base b);

// Função onde um herói H entra na base B. Ao entrar, o herói 
// decide quanto tempo vai ficar e agenda sua saída da base
void entra (int tempo, struct heroi h, struct base b);

// Função onde um herói H sai da base B. Ao sair, escolhe uma base
// de destino para viajar; o porteiro de B é avisado, pois uma vaga
// foi liberada:
void sai (int tempo, struct heroi h, struct base b);

// Função onde o herói H se desloca para uma base D 
// (que pode ser a mesma onde já está):
void viaja (int tempo, struct heroi h, struct base d);

// Função onde o herói H morre no instante T. OBS:
// - O herói é retirado da base B e libera uma vaga na base.
// - O porteiro de B deve ser avisado da nova vaga.
// - Eventos futuros de um herói morto devem ser ignorados.
void morre (int tempo, struct heroi h, struct base b);

// Função onde uma missão M é disparada no instante T. São características de uma missão:
// - Cada missão ocorre em um local aleatório e requer um conjunto aleatório de 
//   habilidades; ambos são definidos durante a inicialização.
// - Cada equipe é formada pelo conjunto de heróis presentes em uma base.
// - Uma equipe está apta para a missão se a união das habilidades de seus heróis 
//   contém as habilidades requeridas pela missão.
// - Deve ser escolhida para a missão a equipe da base mais próxima ao local da 
//   missão e que esteja apta para ela. 
// - Ao completar uma missão, os heróis da equipe escolhida ganham pontos de experiência.
// - Um herói pode morrer ao participar de uma missão. :NEW:
// - Se uma missão não puder ser completada, ela é marcada como “impossível” e adiada de 24 horas.
void missoes (int tempo, struct missao m);

// Função onde se encerra a simulação, gerando um relatório com informações sobre heróis, 
// bases e missões.
void fim (int tempo);
*/

#endif