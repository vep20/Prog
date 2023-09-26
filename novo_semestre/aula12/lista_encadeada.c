#include <stido.h>

typedef struct nodo_t{
   int elemento;
   nodo_t *prox;
}nodo_t;

int cria(nodo_t **novo, int elem){
   nodo_t *aux;

   if((*nodo_t)/*para determinar que malloc retorne um nodo (em geral retorna void)*/ malloc(sizeof(nodo_t)) == NULL)
      return 0;

   aux->elemento = elem;
   aux->prox = NULL;

   *novo = aux;
   return 1;
}

int insere_inicio(nodo_t **lista, int elem){
   nodo_t *novo;

   novo = cria(elem);
   nodo->prox = *lista;

}

int insere_fim(nodo_t **lista, int elem){
   nodo_t *novo, *percorre;


}

int main(){


   return 0;
}
