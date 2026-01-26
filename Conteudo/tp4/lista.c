<<<<<<< HEAD
// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct item_t{
  int valor ;                   // valor do item
  struct item_t *ant ;          // item anterior
  struct item_t *prox ; // próximo item
};

// estrutura de uma lista
struct lista_t{
  struct item_t *prim ; // primeiro item
  struct item_t *ult ;          // último item
  int tamanho ;         // número de itens da lista
};

struct lista_t *lista_cria(){
    struct lista_t *nova_lista;

    nova_lista = malloc (sizeof (struct lista_t));

    if (!nova_lista) /*testa para verificar se há espaço para alocação na memoria*/
        return NULL;

    nova_lista->prim = NULL;
    nova_lista->ult = NULL;
=======
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
>>>>>>> 79c6643f210888d3da082903eb3766d1d1dd7b99
    nova_lista->tamanho = 0;

    return nova_lista;
}

<<<<<<< HEAD
struct lista_t *lista_destroi(struct lista_t *lst){
  int aux_item, aux_pos;

    aux_pos = 0;
    while (lst->prim) /*verifica se há algum item na lista*/
        lista_retira (lst, &aux_item, aux_pos);

    free (lst);
    return NULL; 
}

int lista_insere(struct lista_t *lst, int item, int pos){
    struct item_t *novo_item, *aux; /*um aux para percorrer a lista*/
    int aux_pos;

    if (!lst)
        return -1;

    novo_item = malloc (sizeof (struct item_t));
    if (!novo_item)
        return -1;

    novo_item->valor = item;
    novo_item->ant = NULL;
    novo_item->prox = NULL;

    if (!lista_tamanho(lst)){ /*insere o item em uma lista vazia*/
        lst->prim = novo_item;
        lst->ult = novo_item;
    }

    else if (!pos){ /*já insere na primeira posição*/
        novo_item->prox = lst->prim;
        lst->prim->ant = novo_item;
        lst->prim = novo_item;
    }

    else if (pos == -1){ /*inserção no final, definida conforme .h*/
        novo_item->ant = lst->ult;
        lst->ult->prox = novo_item;
        lst->ult = novo_item;
    }

    else{ 
        aux = lst->prim;
        /*avança até a posição desejada*/
        for (aux_pos = 0; aux_pos < pos && aux->prox; aux_pos++) 
            aux = aux->prox;
             
        if (aux_pos < pos - 1){ /*insere no final e atualiza lst->ult*/
            aux->prox = novo_item;
            novo_item->ant = aux;
            lst->ult = novo_item;
        }
        
        else{ /*insere no meio*/
            novo_item->prox = aux;
            novo_item->ant = aux->ant;
            aux->ant->prox = novo_item;
            aux->ant = novo_item;
        }
        
    }

    lst->tamanho++;
    return lst->tamanho;
}

int lista_retira(struct lista_t *lst, int *item, int pos) {
    struct item_t *aux;
    int aux_pos;

    if (!lst || pos >= lst->tamanho || !item || lst->tamanho == 0)
        return -1;

    if (pos == -1 || pos == lst->tamanho - 1) {  /*retira do final*/
        aux = lst->ult;

        if (lst->ult->ant)  /*quando há mais de um item*/
            lst->ult = lst->ult->ant;
        else {  /* quando só há um item na lista*/
            lst->ult = NULL;
            lst->prim = NULL;
        }
        
        if (aux->ant)
            aux->ant->prox = NULL;
    } else {
        aux = lst->prim;
        
        /* avança até a posição desejada*/
        for (aux_pos = 0; aux_pos < pos && aux->prox; aux_pos++)
            aux = aux->prox;

        if (aux == lst->prim) {  /*retira do início*/
            lst->prim = aux->prox;
            if (aux->prox)
                aux->prox->ant = NULL;
        } else {  /*retira do meio*/
            if (aux->ant)
                aux->ant->prox = aux->prox;
            if (aux->prox)
                aux->prox->ant = aux->ant;
        }
    }

    *item = aux->valor;  /*retorna o valor do item retirado*/
    free(aux);
    lst->tamanho--;

    return lst->tamanho;
}

int lista_consulta(struct lista_t *lst, int *item, int pos){
    struct item_t *aux;

    if (!lst || pos > lst->tamanho - 1)
        return -1;
    
    if (pos == -1)
        *item = lst->ult->valor;

    else{ 
        aux = lst->prim;
        for(int i = 0; i < pos; i++)
          aux = aux->prox;
        *item = aux->valor;
    }

    return lst->tamanho;
}

int lista_procura(struct lista_t *lst, int valor){
    struct item_t *aux;
    int aux_pos;

    if (!lst)
        return -1;

    aux = lst->prim;
    for (aux_pos = 0; aux_pos < lst->tamanho - 1 && aux->valor != valor; aux_pos++) 
            aux = aux->prox;

    if (!aux->prox && aux->valor != valor)
        return -1;
    
    return aux_pos;
}

int lista_tamanho(struct lista_t *lst){
    
    if (!lst)
        return -1;
    return lst->tamanho;
}

void lista_imprime(struct lista_t *lst){
    struct item_t *aux;

    if (!lista_tamanho(lst))
        return;
    
    aux = lst->prim;
    printf("%d", aux->valor); /*impressão para não haver espaços em branco*/
    aux = aux->prox;
    for (int i = 1; i < lst->tamanho; i++){
        printf(" %d", aux->valor);
        aux = aux->prox;
    }
}
=======
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
>>>>>>> 79c6643f210888d3da082903eb3766d1d1dd7b99
