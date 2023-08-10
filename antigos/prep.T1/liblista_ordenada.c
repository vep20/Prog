#include <stdio.h>
#include <stdlib.h>
#include "liblista_ordenada.h"

lista_t *lista_cria (){
    lista_t *nova;
    if(!(nova = malloc(sizeof(lista_t)))){
        return NULL;
    }
    nova->ini->prox = NULL;
    nova->ini->elemento->chave = NULL;
    return nova;
}

void lista_destroi (lista_t **l){
    nodo_t *aux;
    while ((*l)->ini != NULL){
        aux = (*l)->ini;
        (*l)->ini = (*l)->ini->prox;
        free(aux);        
    }
    free(*l);
    *l=NULL;
}

int lista_insere_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux;
    
}

int lista_remove_ordenado (lista_t *l, elemento_t *elemento){

}