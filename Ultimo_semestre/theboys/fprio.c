// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

// A COMPLETAR

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

struct fprio_t *fprio_cria (){
    struct fprio_t *nova_fila;

    nova_fila = malloc (sizeof (struct fprio_t));

    if (!nova_fila)
        return NULL;

    nova_fila->prim = NULL;
    nova_fila->num = 0;
    
    return nova_fila;
}

struct fprio_t *fprio_destroi (struct fprio_t *f){
    int aux_tipo, aux_prio;
    void *item;

    if (!f)
        return NULL;

    while (f->prim){ /*percorre e retira da fila até a mesma estar vazia*/ 
        item = fprio_retira(f, &aux_tipo, &aux_prio);
        free(item);
    }

     
    free(f);
    return NULL; 
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
    struct fpnodo_t *novo_nodo, *aux, *aux_item; /*um aux para percorrer a fila*/
    
    if (!f || !item)
        return -1;

    if (f->prim){
        /*verifica se item já não esta na fila*/
        for (aux_item = f->prim; aux_item; aux_item = aux_item->prox){ 
            if (aux_item->item == item)
                return -1;
        }
    }
    
    novo_nodo = malloc (sizeof (struct fpnodo_t));
    if (!novo_nodo)
        return -1;

    novo_nodo->item = item;
    novo_nodo->tipo = tipo;
    novo_nodo->prio = prio;
    novo_nodo->prox = NULL;

    if (!f->num)/*insere em um fila vazia*/
        f->prim = novo_nodo;

    else{
        aux = f->prim;

        if (prio < aux->prio){ /*atualiza a primeira posição, caso necessario*/
            novo_nodo->prox = aux;
            f->prim = novo_nodo;
        }

        else{
            /*importate, testar aux->prox primeiro*/
            while (aux->prox && aux->prox->prio <= prio)/*percorre a fila*/
                aux = aux->prox;

            /*insere no meio, conforme prioridade*/
            novo_nodo->prox = aux->prox;
            aux->prox = novo_nodo;
        }
    }
    f->num++;
    return f->num;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
    struct fpnodo_t *aux;
    void *aux_item;

    if (!f || !f->num || !tipo || !prio)
        return NULL;

    aux = f->prim;
    aux_item = aux->item;  

    f->prim = aux->prox;      

    *tipo = aux->tipo;
    *prio = aux->prio;
    free(aux);
    f->num--;

    return aux_item;
}

int fprio_tamanho (struct fprio_t *f){

    if (!f)
        return -1;
    return f->num;
}

void fprio_imprime (struct fprio_t *f){
    struct fpnodo_t *aux;

    if (!f || !f->num)
        return;

    aux = f->prim;void desiste (struct mundo *m, int tempo, int id_heroi, int id_base);

    printf("(%d %d)", aux->tipo, aux->prio); /*impressão para não haver espaços em branco*/
    aux = aux->prox;
    for(int i = 1; i < f->num; i++){
        printf (" (%d %d)", aux->tipo, aux->prio);
        aux = aux->prox;
    } 
}