#include "lista.h"
#include <stdio.h>
#include <stdlib.h> 
/* coloque demais includes aqui */

struct lista *lista_cria (){
    struct lista *nova_lista;

    nova_lista = (struct lista *) malloc (sizeof(struct lista));

    if (!nova_lista)
        return NULL; 

    nova_lista->ini = NULL;
    nova_lista->ptr = NULL;
    nova_lista->tamanho = 0;

    return nova_lista;
}

/*void lista_destroi (struct lista **lista){
}

int lista_insere_inicio (struct lista *lista, int chave){
}

int lista_insere_fim (struct lista *lista, int chave){
}

int lista_insere_ordenado (struct lista *lista, int chave){
}*/

int lista_remove_inicio (struct lista *lista, int *chave){
    struct nodo *aux;

    if(lista->ini == NULL)
        return 0;

    aux = lista->ini;
    *chave = aux->chave;
    /*recebe o valor onde aux aponta, ao inves de apontar para o mesmo endereço*/
    lista->ini = lista->ini->prox;
    lista->tamanho--;
    
    free(aux);/*libera aux da memoria, utilizando apenas nesta funação*/

    return 1;
}

/*int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}*/

int lista_vazia (struct lista *lista){

    if(lista->ini == NULL)
        return 1;
    return 0;
}   

/*int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}*/
