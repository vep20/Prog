#include <stdio.h>
#include "libpilha.h"

pilha_t *pilha_cria (){
    pilha_t *p_nova;

    if (!(p_nova = malloc(sizeof(pilha_t))))
        return NULL;
    p_nova->tamanho = 0;
    p_nova->topo = NULL;
    return p_nova;
}

void pilha_destroi (pilha_t **pilha){
    pilha_t *aux;
    while (*pilha->topo != NULL){
        aux = *pilha->topo;

    }
}

int push (pilha_t *pilha, int dado){

}

int pop (pilha_t *pilha, int *dado){

}

int pilha_topo (pilha_t *pilha, int *dado){

} 

int pilha_tamanho (pilha_t *pilha){

}

int pilha_vazia (pilha_t *pilha){

}