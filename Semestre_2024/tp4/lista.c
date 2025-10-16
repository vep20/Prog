#include "lista.h"
#include <stdio.h>
#include <stdlib.h> 
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */


struct lista *lista_cria (){
    struct lista *nova_lista;

    nova_lista = (struct lista *) malloc(sizeof(struct lista));

    if (!nova_lista)/*testa para verificar se há espaço para alocação na memoria*/
        return NULL; 

    nova_lista->ini = NULL;
    nova_lista->ptr = NULL;
    nova_lista->tamanho = 0;

    return nova_lista;
}

void lista_destroi (struct lista **lista){
    int aux_chave;

    if (lista == NULL || *lista == NULL)
        return;

    while (!lista_vazia(*lista))
        lista_remove_fim(*lista,&aux_chave);

    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *aux;

    if(lista->tamanho > 5)    
        return 0;

    aux = (struct nodo *) malloc(sizeof(struct nodo));
    if (aux == NULL)
        return 0;

    aux->chave = chave;
    aux->prox = lista->ini; 
    lista->ini = aux;
    lista->tamanho++;
    
    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *aux, *novo_nodo;

    if (lista->tamanho > 5)    
        return 0;

    novo_nodo = (struct nodo *) malloc(sizeof(struct nodo));
    if (novo_nodo == NULL)
        return 0;
    
    novo_nodo->chave = chave;
    novo_nodo->prox = NULL;

    if (lista_vazia(lista))
        lista->ini = novo_nodo;
    

    else{
        aux = lista->ini;/*utiliza um auxiliar para percorrer a lista*/
        while (aux->prox != NULL)/*percorre a lista até encontrar o ultima posição atual*/
            aux = aux->prox;
        aux->prox = novo_nodo;
    }

    return 1;   
}

int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *aux, *novo_nodo;;

    if(lista->tamanho > 5)    
        return 0;

    novo_nodo = (struct nodo *) malloc(sizeof(struct nodo));
    if (novo_nodo == NULL)
        return 0;
    
    novo_nodo->chave = chave;
    novo_nodo->prox = NULL; 

    if (lista_vazia(lista) || chave < lista->ini->chave){
    /*pois nos dois casos o elemento será inserido no começo*/
        novo_nodo->prox = lista->ini;
        lista->ini = novo_nodo;
    }

    else{
        aux = lista->ini;
        while (aux->prox != NULL && aux->prox->chave < novo_nodo->chave)
            aux = aux->prox;
        novo_nodo->prox = aux->prox;
        aux->prox = novo_nodo;
    }
    
    lista->tamanho++;
    return 1;   
}

int lista_remove_inicio (struct lista *lista, int *chave){
    struct nodo *aux;

    if (lista_vazia(lista))
        return 0;

    aux = lista->ini;
    *chave = aux->chave;
    /*recebe o valor onde aux aponta, ao inves de apontar para o mesmo endereço*/
    lista->ini = aux->prox;
    lista->tamanho--;
    
    free(aux);/*libera aux da memoria, utilizando apenas nesta função*/
    aux = NULL;
    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    struct nodo *aux;

    if (lista_vazia(lista))
        return 0;
    
    aux = lista->ini; 
    if (aux->prox == NULL){
       *chave = aux->chave;
        free(aux);
        lista->ini = NULL;
    }

    else{
        while (aux->prox->prox != NULL)/*percorre até a penultima posição*/
            aux = aux->prox;

        *chave = aux->prox->chave;
        free(aux->prox);
        aux->prox = NULL;
    }

    lista->tamanho--;

    return 1;
}


int lista_remove_ordenado (struct lista *lista, int chave){
    struct nodo *aux, *temp_ant;

    if (lista_vazia(lista))
        return 0;

    aux = lista->ini; 
    if (aux->prox == NULL) {
        if (aux->chave == chave) {
            free(aux);
            lista->ini = NULL;
            lista->tamanho--;
            return 1;/*remove o primeiro e unico elemento da lista*/
        }
        return 0;
    }

    temp_ant = NULL;
    while(aux->prox != NULL && aux->chave < chave){
        temp_ant = aux;
        aux = aux->prox;
    }

    if (temp_ant == NULL)/*caso a chave procurda seja o primeiro elemento da lista*/
        lista->ini = aux->prox;
    
    else    
        temp_ant->prox = aux->prox;
    
    free(aux);
    aux = NULL;
    lista->tamanho--;

    return 1;
}

int lista_vazia (struct lista *lista){

    if (lista->ini == NULL)
        return 1;
    return 0;
}   

int lista_tamanho (struct lista *lista){
   
    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
    struct nodo *aux;

    if (lista_vazia(lista))
        return 0;

    aux = lista->ini;
    while (aux->prox != NULL && aux->chave != chave)
        aux = aux->prox;

    if (aux->prox == NULL && aux->chave != chave)
        return 0;
    
    return 1;
}

void lista_inicia_iterador (struct lista *lista){

    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){

    if (lista->ptr == NULL)
        return 0;
    
    *chave = lista->ptr->chave;     
    lista->ptr = lista->ptr->prox;
    return 1;
}