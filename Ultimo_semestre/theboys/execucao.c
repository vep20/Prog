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

    
    if (!cria_herois(m))// Preenche vetor de herois e os membros do mesmo
        printf("Erro ao criar vetor de herois, ponteiro mundo invalido!\n");
    
    if (!cria_bases(m))// Preenche vetor de bases e os membros do mesmo
        printf("Erro ao criar vetor de bases, ponteiro mundo invalido!!\n");

    if (!cria_missoes(m))// Preenche vetor de missões os membros do mesmo
        printf("Erro ao criar vetor de missoes, ponteiro mundo invalido!!\n"); 
    
    m->eventos = fprio_cria();
    if (!m->eventos)
        erro("Erro na criação fila de eventos");
}

struct heroi inicia_heroi (int id){
    struct heroi novo_heroi;
    int qnt_hab; // Quantidade de habilidades que o heroi possui
    
    novo_heroi.ID = id;
    novo_heroi.experiencia = 0;
    novo_heroi.paciencia = aleat (0, 100);
    novo_heroi.velocidade = aleat (50, 5000);
    novo_heroi.base_atual = NULL;

    qnt_hab = aleat (1, 3);
    novo_heroi.habilidades = cjto_aleat (qnt_hab, N_HABILIDADES);
    // Cria novo conjunto com cap max = numero maximo de habilidades disponiveis para se ter
    // no mundo. Preenche cada heroi com as "n" qtds habilidades sorteadas.
    // Obs. cjto_aleat não repete habilidades, por isso não é preciso testar
    if (!novo_heroi.habilidades)
        erro ("Erro ao criar conjunto de habilidades para o herói\n");
   
    return novo_heroi;
}

int cria_herois (struct mundo *m){

    if (!m)
        return 0;

    for (int i = 0; i < m->nherois; i++)
        m->herois[i] = inicia_heroi(i);
    
    return 1; 
}

struct base inicia_base (int id){
    struct base nova_base;

    nova_base.lb.x = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_base.lb.y = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_base.ID = id;

    nova_base.lotacao = aleat (3, 10);  
    nova_base.presentes = cjto_cria (nova_base.lotacao);
    // Conjunto vazio (com capacidade para armazenar IDs 
    // de heróis até a lotação da base)
    if (!nova_base.presentes)
        erro ("Erro ao criar conjunto de presentes da base\n");

    nova_base.espera = fila_cria();
    if (!nova_base.espera)
        erro ("Erro ao criar a fila de espera na base!\n");

    return nova_base;
}

int cria_bases (struct mundo *m){

    if (!m)
        return 0;

    for (int i = 0; i < m->nbases; i++)
        m->bases[i] = inicia_base (i);
  
    return 1;
}

struct missao inicia_missao (int id){
    struct missao nova_missao;
    int qnt_hab; // Quantidade de habilidades necessaria para cumprir a missão

    nova_missao.lm.x = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_missao.lm.y = aleat (0, N_TAMANHO_MUNDO - 1);
    nova_missao.ID = id;

    qnt_hab = aleat (6, 10);
    nova_missao.habilidades = cjto_aleat (qnt_hab, N_HABILIDADES);
    // Cria novo conjunto com cap max = numero maximo de habilidades disponiveis para se ter
    // no mundo. Preenche cada base com as "n" qtds habilidades sorteadas.
    // Obs. cjto_aleat não repete habilidades, por isso não é preciso testar
    if (!nova_missao.habilidades)
        erro("Erro ao criar o conjunto de habilidades na missão!\n");

    return nova_missao;
}

int cria_missoes (struct mundo *m){

    if (!m)
        return 0;

    for (int i = 0; i < m->nmissoes; i++)
        m->missoes[i] = inicia_missao (i);
    
    return 1;
}
 
void libera_herois (struct mundo *m){

    if (!m->herois)
        erro ("Vetor de herois vazio");

    // Percorre o vetor até a quantidade de herois ainda presentes no mundo
    for (int i = 0; i < m->nherois; i++)
        if (m->herois[i].habilidades)// Verifica se o herois possui habilidades e as destroi
            m->herois[i].habilidades = cjto_destroi(m->herois[i].habilidades);

}

void libera_bases (struct mundo *m){

    if(!m->bases)
        erro("Vetor de bases vazio");

    for (int i = 0; i < m->nbases; i++){
        if (m->bases[i].presentes)// Verifica se há conjunto de presentes e os destroi 
            m->bases[i].presentes = cjto_destroi (m->bases[i].presentes);
        
        if(m->bases[i].espera) // Verifica se há fila de espera e o destroi
            m->bases[i].espera = fila_destroi(m->bases[i].espera);
    }    
}

void libera_missoes (struct mundo *m){

    if (!m->missoes)
        erro ("Vetor de missoes vazio");

    // Percorre o vetor até a quantidade de herois ainda presentes no mundo
    for (int i = 0; i < m->nmissoes; i++)
        if (m->missoes[i].habilidades)// Verifica se o missoes possui habilidades e as destroi
            m->missoes[i].habilidades = cjto_destroi(m->missoes[i].habilidades);

}

void destroi_mundo(struct mundo *m){

    if (!m) 
        erro ("Ponteiro para o mundo inválido!\n");

    if (m->TamanhoMundo) 
        free(m->TamanhoMundo);// Libera o tamanho do mundo
    m->TamanhoMundo = NULL;

    libera_herois(m);// Libera os cjtos de habilidades dos herois
    libera_bases (m);// Libera ponteiros para conjunto de presentes e fila de espera
    libera_missoes(m);// Libera os cjtos de habilidades das missoes
    fprio_destroi(m->eventos);

    free(m);// Libera a estrutura principal
    m = NULL;
}