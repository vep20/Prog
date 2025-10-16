#ifndef ENTIDADES_EVENTOS
#define ENTIDADES_EVENTOS

#include "conjunto.h"
#include "fprio.h"
#include "lista.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 10//525600
#define N_TAMANHO_MUNDO 4//20000
#define N_HABILIDADES  2//10
#define N_HEROIS 5//50
#define N_BASES 1//10
#define N_MISSOES 5//52560

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
    struct fprio_t *espera;
    struct local *lb;
    int ID;
    int lotacao;
};

struct missao{
    struct cjto_t *habilidades;
    struct local *lm;
    int ID;
    int perigo;
};

struct mundo{
    struct heroi *herois; // vetor de herois 
    struct base *bases; // vetor de bases
    struct missao *missoes; // vetor de missoes
    struct local *TamanhoMundo; 
    int nherois; // numero de herois
    int nbases; // numero de bases
    int nmissoes; // numero de missões
    int nhabilidades; // numero de habilidades
    int relogio;
};

// Função mensagem de erro
void erro (char *msg);

// Função que cria e retorna um número aleatório entre min e max, inclusive.
int aleat (int min, int max);

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

#endif