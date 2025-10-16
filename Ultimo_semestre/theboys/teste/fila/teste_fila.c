#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void fila_imprime_valores_inteiros(struct fila_t *f) {
    struct fila_nodo_t *aux;

    if (!f || !f->prim) {
        printf("(Fila vazia)\n");
        return;
    }

    aux = f->prim;
    printf("(%d)", *(int *)(aux->item));
    aux = aux->prox;

    while (aux) {
        printf(" (%d)", *(int *)(aux->item));
        aux = aux->prox;
    }
    printf("\n");
}

int main () {
    struct fila_t *nova_fila;
    int *item;

    nova_fila = fila_cria ();
    if (!nova_fila)
        printf("erro ao criar nova fila");

    else{
        printf("nova fila criada com sucesso");
        for (int i = 0; i < 6; i++){
            item = malloc (sizeof (int));
            if (!item){
                printf ("erro ao alocar item");
                return -1;
            }
            *item = i;
            fila_insere (nova_fila, item);
        }

        printf ("\n\nendereços:\n");
        fila_imprime(nova_fila);
        printf("\nvalores:\n");
        fila_imprime_valores_inteiros(nova_fila);
        printf("tam = %d", fila_tamanho(nova_fila));

        item = fila_retira(nova_fila);
        free(item);

        printf ("\n\nende   reços:\n");
        fila_imprime(nova_fila);
        printf("\nvalores\n");
        fila_imprime_valores_inteiros(nova_fila);
        printf("tam = %d", fila_tamanho(nova_fila));

        nova_fila = fila_destroi(nova_fila);
        printf("\ntam = %d\n", fila_tamanho(nova_fila)); 

        fila_imprime(nova_fila);
    }
    
    return 0;
}