#include <stdio.h>
#include <stdlib.h>
#include "execucao.h"

struct mundo *cria_mundo (){
    struct mundo *aux;

    aux = malloc (sizeof (struct mundo));
    if (!aux)
        return NULL;

    // Valores definidos em arquivo .h
    aux->TamanhoMundo.x = N_TAMANHO_MUNDO;
    aux->TamanhoMundo.y = N_TAMANHO_MUNDO;
    aux->relogio = T_INICIO;
    aux->nhabilidades = N_HABILIDADES;
    aux->nherois = N_HEROIS;
    aux->nbases = N_BASES;
    aux->nmissoes = N_MISSOES;
    aux->nCompostoV = N_COMPOSTOS_V;
    
    // Alocação criada antes, para não precisar limpar os outro elementos posteriormente
    aux->eventos = fprio_cria ();
    if (!aux->eventos){
        printf ("Erro na criação fila de eventos\n");
        free (aux); // Função deve ser encerrada, por isso aux deve ser liberado
        return NULL;
    }

    cria_herois (aux);// Preenche vetor de herois e os membros do mesmo    
    cria_bases (aux);// Preenche vetor de bases e os membros do mesmo
    cria_missoes (aux);// Preenche vetor de missões os membros do mesmo

    return aux;
}

struct heroi inicia_heroi (int id){
    struct heroi novo_heroi;
    int qnt_hab; // Quantidade de habilidades que o heroi possui
    
    novo_heroi.ID = id;
    novo_heroi.experiencia = 0;
    novo_heroi.paciencia = aleat (0, 100);
    novo_heroi.velocidade = aleat (50, 5000);
    
    // Novo_heroi.ID_base não inciado aqui

    qnt_hab = aleat (1, 3);
    novo_heroi.habilidades = cjto_aleat (qnt_hab, N_HABILIDADES);
    // Cria novo conjunto com cap max = numero maximo de habilidades disponiveis para se ter
    // no mundo. Preenche cada heroi com as "n" qtds habilidades sorteadas.
    // Obs. cjto_aleat não repete habilidades, por isso não é preciso testar
   
    return novo_heroi;
}

int cria_herois (struct mundo *m){

    if (!m)
        return 0;

    for (int i = 0; i < m->nherois; i++){
        m->herois[i] = inicia_heroi (i);
        
        if (!m->herois[i].habilidades)
            erro ("Erro ao criar conjunto de habilidades para um herói");
    }
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

    nova_base.espera = fila_cria();

    return nova_base;
}

int cria_bases (struct mundo *m){

    if (!m)
        return 0;

    for (int i = 0; i < m->nbases; i++){
        m->bases[i] = inicia_base (i);

        if (!m->bases[i].presentes)
            erro ("Erro ao criar conjunto de presentes da base");
        
        if (!m->bases[i].espera)
            erro ("Erro ao criar a fila de espera na base!");
    }  
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

    return nova_missao;
}

int cria_missoes (struct mundo *m){

    if (!m)
        return 0;

    for (int i = 0; i < m->nmissoes; i++){
        m->missoes[i] = inicia_missao (i);

        if (!m->missoes[i].habilidades)
            erro("Erro ao criar o conjunto de habilidades na missão!");
    }
    
    return 1;
}
 
void libera_herois (struct mundo *m){

    if (!m->herois)
        return;

    // Percorre o vetor até a quantidade de herois ainda presentes no mundo
    for (int i = 0; i < m->nherois; i++)
        if (m->herois[i].habilidades)// Verifica se o herois possui habilidades e as destroi
            m->herois[i].habilidades = cjto_destroi(m->herois[i].habilidades);

}

void libera_bases (struct mundo *m){

    if(!m->bases)
        return;

    for (int i = 0; i < m->nbases; i++){
        if (m->bases[i].presentes)// Verifica se há conjunto de presentes e os destroi 
            m->bases[i].presentes = cjto_destroi (m->bases[i].presentes);
        
        if(m->bases[i].espera) // Verifica se há fila de espera e o destroi
            m->bases[i].espera = fila_destroi (m->bases[i].espera);
    }    
}

void libera_missoes (struct mundo *m){

    if (!m->missoes)
        return;

    // Percorre o vetor até a quantidade de herois ainda presentes no mundo
    for (int i = 0; i < m->nmissoes; i++)
        if (m->missoes[i].habilidades)// Verifica se o missoes possui habilidades e as destroi
            m->missoes[i].habilidades = cjto_destroi (m->missoes[i].habilidades);

}

struct mundo *destroi_mundo (struct mundo *m){

    if (!m) 
        return NULL;

    libera_herois (m);// Libera os cjtos de habilidades dos herois
    libera_bases (m);// Libera ponteiros para conjunto de presentes e fila de espera
    libera_missoes (m);// Libera os cjtos de habilidades das missoes
    m->eventos = fprio_destroi (m->eventos);// destroi a LEF do mundo

    free (m);// Libera a estrutura principal

    return NULL;
}