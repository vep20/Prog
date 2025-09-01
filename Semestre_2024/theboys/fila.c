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
    void *item;

    if (!f)
        return NULL;

    while (f->prim) {
        item = fila_retira(f);
        free(item);
    }

    free(f);
    return NULL;
}

int fila_insere(struct fila_t *f, void *item) {
    struct fila_nodo_t *novo, *aux ;

    if (!f || !item)
        return -1;

    // Verifica se o item já está na fila
    for (aux = f->prim; aux; aux = aux->prox) {
        if (aux->item == item)
            return -1;
    }

    novo = malloc(sizeof(struct fila_nodo_t));
    if (!novo)
        return -1;

    novo->item = item;
    novo->prox = NULL;

    if (f->fim)
        f->fim->prox = novo;
    else
        f->prim = novo;

    f->fim = novo;
    f->num++;

    return f->num;
}

void *fila_retira(struct fila_t *f) {
    struct fila_nodo_t *aux;
    void *item;

    if (!f || !f->prim)
        return NULL;

    aux = f->prim;
    item = aux->item;

    f->prim = aux->prox;
    if (!f->prim)
        f->fim = NULL;

    free(aux);
    f->num--;

    return item;
}

int fila_tamanho(struct fila_t *f) {
    if (!f)
        return -1;
    return f->num;
}

// nesta versão é imprimido os valores de endereço apontados pelo ponteiro item
void fila_imprime(struct fila_t *f) {
    struct fila_nodo_t *aux;

    if (!f || !f->prim)
        return;

    aux = f->prim;
    printf("(%p)", aux->item);  // imprime o ponteiro do item
    aux = aux->prox;

    while (aux) {
        printf(" (%p)", aux->item);
        aux = aux->prox;
    }
}
