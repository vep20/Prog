#include <stdio.h>
#include "libpilha.h"
#include <stdlib.h>

pilha_t *pilha_cria (){
    pilha_t *p_nova;

    if (!(p_nova = malloc(sizeof(pilha_t))))
        return NULL;
    p_nova->tamanho = 0;
    p_nova->topo = NULL;
    return p_nova;
}

void pilha_destroi (pilha_t **pilha){
    nodo_t *aux;
    while ((*pilha)->topo != NULL){
        aux = (*pilha)->topo;
        (*pilha)->topo = (*pilha)->topo->prox;
        free(aux);
    }
    free(*pilha);
    (*pilha)=NULL;
}

int push (pilha_t *pilha, int dado){
    nodo_t *novo;
    if(!(novo=malloc(sizeof(nodo_t))))
        return 0;
    novo->dado = dado;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho ++;
    return 1;
}

int pop (pilha_t *pilha, int *dado){
    nodo_t *aux;
    if (!pilha_vazia(pilha)){
        aux = pilha->topo;
        *dado = aux->dado;
        pilha->topo = aux->prox;
        pilha->tamanho --;
        free(aux);
        return 1;
    }
    return 0;
}

int pilha_topo (pilha_t *pilha, int *dado){
    nodo_t *aux;
    if (!pilha_vazia(pilha)){
        aux = pilha->topo;
        *dado = aux->dado;
        pilha->topo->dado = *dado;
        return 1;
    }
    return 0;
} 

int pilha_tamanho (pilha_t *pilha){
    return pilha->tamanho;
}

int pilha_vazia (pilha_t *pilha){
    return !pilha->tamanho;
}