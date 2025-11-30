#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_t *fila_cria() {
    struct fila_t *nova_fila ;
    
    nova_fila = malloc (sizeof (struct fila_t));
    
    if (!nova_fila)
        return NULL;

    nova_fila->prim = NULL;
    nova_fila->fim = NULL;
    nova_fila->num = 0;
    return nova_fila;
}

struct fila_t *fila_destroi(struct fila_t *f) {
    int item_aux;

    if (!f)
        return NULL;

    while (fila_retira(f, &item_aux));

    free(f);
    return NULL;
}

int fila_insere(struct fila_t *f, int item) {
    struct fila_nodo_t *novo;

    if (!f)
        return 0;

    /*    
    // Verifica se o item já está na fila
    for (aux = f->prim; aux; aux = aux->prox) {
        if (aux->item == item)
            return 0;
    }*/

    novo = malloc(sizeof(struct fila_nodo_t));
    if (!novo)
        return 0;

    novo->item = item;
    novo->prox = NULL;

    if (f->fim)
        f->fim->prox = novo;
    else
        f->prim = novo; //insere no comeco

    f->fim = novo;
    f->num++;

    return 1;
}

int fila_retira(struct fila_t *f, int *item){                     
    struct fila_nodo_t *aux;

    if (!f || !f->prim || !item)
        return 0;

    aux = f->prim;
    *item = aux->item;

    f->prim = aux->prox;
    if (!f->prim)
        f->fim = NULL;

    free(aux);
    f->num--;

    return 1;
}

int fila_tamanho(struct fila_t *f) {
    if (!f)
        return -1;
    return f->num;
}

void fila_imprime(struct fila_t *f) {
    struct fila_nodo_t *aux;

    if (!f || !f->prim)
        return;

    aux = f->prim;
    printf("%2d", aux->item);
    //printf("(%d)", aux->item);  //imprime o item
    aux = aux->prox;

    while (aux) {
        printf(" %2d", aux->item);
        //printf(" (%d)", aux->item);
        aux = aux->prox;
    }
}