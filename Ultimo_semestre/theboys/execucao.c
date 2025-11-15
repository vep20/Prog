#include <stdio.h>
#include <stdlib.h>
#include "execucao.h"

struct mundo *cria_mundo (){
    struct mundo *aux;

    aux = malloc (sizeof (struct mundo));
    if (!aux){
        erro ("Erro ao criar o mundo!\n");
        return NULL;
    }
    return aux;
}

void inicia_mundo (struct mundo *m){

    // Valores definidos em arquivo .h
    m->TamanhoMundo = malloc (sizeof(struct local));
    if (!m->TamanhoMundo)
        erro ("Erro ao alocar memoria para tamanho do mundo\n");

    m->TamanhoMundo->x = N_TAMANHO_MUNDO;
    m->TamanhoMundo->y = N_TAMANHO_MUNDO;
    m->relogio = T_INICIO;
    m->nhabilidades = N_HABILIDADES;
    m->nherois = N_HEROIS;
    m->nbases = N_BASES;
    m->nmissoes = N_MISSOES;
    m->nCompostoV = N_COMPOSTOS_V;

    /*
    if (!cria_herois(m))// Alloca vetor de herois e preenche os mem bros do mesmo
        erro("Erro ao criar vetor de herois!\n");
    
    if (!cria_bases(m))// Alloca vetor de bases e preenche os mebros do mesmo
        erro("Erro ao criar vetor de bases!\n");

    if (!cria_missoes(m))// Alloca vetor de missões e preenche os mebros do mesmo
        erro("Erro ao criar vetor de missoes!\n"); 
    
    m->missoes = fprio_cria();
    if (!m->missoes)
        erro("Erro na criação LEF");
    */
}

/*
struct heroi inicia_heroi (int id){
    struct heroi novo_heroi;
    int n_hab, hab;

    novo_heroi.ID = id;
    novo_heroi.experiencia = 0;
    novo_heroi.paciencia = aleat (0, 100);
    novo_heroi.velocidade = aleat (50, 5000);

    n_hab = aleat (1, 3);
    novo_heroi.habilidades = cjto_cria (N_HABILIDADES);
    if (!novo_heroi.habilidades)
        erro ("Erro ao criar conjunto de habilidades para o herói\n");

    for (int i = 0; i < n_hab; i++){
        do{
            hab = aleat (1, N_HABILIDADES);
        } while (cjto_pertence (novo_heroi.habilidades, hab));
        // Verifica se habilidade já não esta no cjto
        cjto_insere(novo_heroi.habilidades, hab);
    }
    
    novo_heroi.base_atual = NULL;
    return novo_heroi;
}

int cria_herois (struct mundo *m){
    struct heroi *aux;

    if (!m)
        erro ("Ponteiro para o mundo inválido!\n");

    aux = malloc (sizeof (struct heroi) * m->nherois);
    if (!aux)
        return 0;

    for (int i = 0; i < m->nherois; i++)
        aux[i] = inicia_heroi(i);
    
    m->herois = aux; 
    return 1; 
}

struct base inicia_base (int id){
    struct base nova_base;

    nova_base.lb = malloc (sizeof (struct local));
    if (!nova_base.lb)
        erro ("Erro ao alocar memoria para local da base\n");

    nova_base.lb->x = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_base.lb->y = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_base.ID = id;
    nova_base.lotacao = aleat (3, 10);  
   
    // Conjunto vazio (com capacidade para armazenar IDs 
    // de heróis até a lotação da base)
    nova_base.presentes = cjto_cria (nova_base.lotacao);
    if (!nova_base.presentes)
        erro ("Erro ao criar conjunto de habilidades para o herói\n");


    nova_base.espera = fprio_cria();
    if (!nova_base.espera)
        erro ("Erro ao criar a fila de espera na base!\n");

    return nova_base;
}

int cria_bases (struct mundo *m){
    struct base *aux;

    if (!m)
        erro ("Ponteiro para o mundo inválido!\n");

    aux = malloc (sizeof (struct base) * m->nbases);
    if (!aux)
        return 0;

    for (int i = 0; i < m->nbases; i++)
        aux[i] = inicia_base (i);
    
    m->bases = aux;  
    return 1;
}

struct missao inicia_missao (int id){
    struct missao nova_missao;
    int n_hab, hab;

    nova_missao.lm = malloc (sizeof (struct local));
    if (!nova_missao.lm)
        erro ("Erro ao alocar memoria para local da missao\n");

    nova_missao.lm->x = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_missao.lm->y = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_missao.ID = id;
    n_hab = aleat (6, 10);
    nova_missao.habilidades = cjto_cria (N_HABILIDADES);
    if (!nova_missao.habilidades)
        erro("Erro ao criar o conjunto de habilidades missões!\n");

    for (int i = 0; i < n_hab; i++){
        do{
            hab = aleat (1, N_HABILIDADES);
        } while (cjto_pertence (nova_missao.habilidades, hab));
        // Verifica se habilidade já não esta no cjto
        cjto_insere(nova_missao.habilidades, hab);
    }

    return nova_missao;
}

int cria_missoes (struct mundo *m){
    struct missao *aux;

    if (!m)
        erro ("Ponteiro para o mundo inválido!\n");

    aux = malloc (sizeof (struct missao) * m->nmissoes);
    if (!aux)
        return 0;

    for (int i = 0; i < m->nmissoes; i++)
        aux[i] = inicia_missao (i);
    
    m->missoes = aux;  

    return 1;
}

void destroi_heroi(struct heroi *h){
    
    if (!h) 
        erro ("Ponteiro para o heroi inválido!\n");

    cjto_destroi(h->habilidades);// Libera o conjunto de habilidades
    h->habilidades = NULL;
}

void destroi_herois(struct heroi *herois, int nherois){
    
    if (!herois) 
        erro ("Ponteiro para o herois inválido!\n");

    for (int i = 0; i < nherois; i++) 
        destroi_heroi(&herois[i]);
    
    free(herois);
    herois = NULL;
}

void destroi_base(struct base *b){
    
    if (!b) 
        erro ("Ponteiro para a base inválido!\n");

    if (b->lb) 
        free(b->lb);// Libera a localização da base
    b->lb = NULL;

    cjto_destroi(b->presentes);// Libera o conjunto de heróis presentes
    b->presentes = NULL;

    fprio_destroi(b->espera);// Libera a fila de prioridade
    b->espera = NULL;
}

void destroi_bases(struct base *bases, int nbases){
   
    if (!bases) 
        erro ("Ponteiro para as bases inválido!\n");

    for (int i = 0; i < nbases; i++)
        destroi_base(&bases[i]);

    free(bases);
    bases = NULL;
}

void destroi_missao(struct missao *m){

    if (!m) 
        erro ("Ponteiro para as bases inválido!\n");

    if (m->lm) 
        free(m->lm);// Libera a localização da missão
    m->lm = NULL;

    cjto_destroi(m->habilidades);// Libera o conjunto de habilidades requeridas
    m->habilidades = NULL;
}

void destroi_missoes(struct missao *missoes, int nmissoes){

    if (!missoes) 
        erro ("Ponteiro para as bases inválido!\n");

    for (int i = 0; i < nmissoes; i++) 
        destroi_missao(&missoes[i]);
    
    free(missoes);
    missoes = NULL;
}

*/

void destroi_mundo(struct mundo *m){

    if (!m) 
        erro ("Ponteiro para o mundo inválido!\n");

    if (m->TamanhoMundo) 
        free(m->TamanhoMundo);// Libera o tamanho do mundo
    m->TamanhoMundo = NULL;

    /*
    destroi_herois(m->herois, m->nherois);// Libera os heróis
    destroi_bases(m->bases, m->nbases);// Libera as bases
    destroi_missoes(m->missoes, m->nmissoes);// Libera as missões
    */

    free(m);// Libera a estrutura principal
    m = NULL;
}
