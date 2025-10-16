/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

void cria_vetor(struct racional *v[], int tam){
  int aux_num, aux_den;

  for (int i = 0; i < tam; i++){
    scanf("%d %d", &aux_num, &aux_den);
    v[i] = cria_r(aux_num, aux_den);
  }
}

void imprime_vetor(struct racional *v[], int tam){

  for (int i = 0; i < tam; i++){
    if (v[i] == NULL)
      printf("NULL");
    else
      imprime_r(v[i]);
    if (i < tam-1)
      printf(" ");
  }
  printf("\n");
}

void redimensiona(struct racional *v[], int inicio, int *tam){

  for (int i = inicio; i < (*tam - 1); i++)
    v[i] = v[i + 1];
  v[*tam - 1] = NULL;
}

void elimina_invalidos(struct racional *v[], int *tam){

  for (int i = 0; i < *tam; i++){
    if (!valido_r(v[i])){
      free(v[i]);
      redimensiona(v, i, tam); /* Corrigindo para passar o valor real de tam */
      (*tam)--;
      i--; /* Ajustar  o indice */
    }
  }
}

void troca(struct racional **r1, struct racional **r2){
  struct racional *aux;

  aux = *r1;
  *r1 = *r2;
  *r2 = aux;
}

void ordena_vetor(struct racional *v[], int tam){

  for (int i = 0; i < tam; i++){
    for (int j = i + 1; j < tam; j++){
      if (compara_r(v[j], v[i]) == -1)
        troca(&v[i], &v[j]); /* Alterado os endereços, por isso utiliza ponteiros de ponteiro*/
    }
  }
}

struct racional *soma_vetor(struct racional *v[], int tam){
  struct racional *soma, *temp;

  if (tam == 0 || v[0] == NULL)
    return NULL;

  soma = cria_r(numerador_r(v[0]), denominador_r(v[0]));

  for (int i = 1; i < tam; i++){

    if (!valido_r(v[i]))
      return NULL;

    temp = cria_r(numerador_r(soma), denominador_r(soma));
    soma_r(soma, v[i], soma);

    if (temp != v[0])
      free(temp);
  }

  return soma;
}

void destroi_vetor(struct racional *v[], int tam){

  for (int i = 0; i < tam; i++){
    free(v[i]);
    v[i] = NULL;
  }
}

int main(){
  int n;

  /* vetor de ponteiros para racionais */
  struct racional **v, *soma; /* equivalente a struct racional *v[] */
  srand(0);

  do{
    scanf("%d", &n);
    if (n < 0 || n > 100)
      printf("Numero n fora do intervalo definido\n");
  } while (n < 0 || n > 100);

  v = malloc(sizeof(struct racional *) * n);
  if (v == NULL)
    return 1;

  cria_vetor(v, n);
  printf("VETOR = ");
  imprime_vetor(v, n);
  elimina_invalidos(v, &n);
  printf("VETOR = ");
  imprime_vetor(v, n);
  ordena_vetor(v, n);
  printf("VETOR = ");
  imprime_vetor(v,n);
  soma = soma_vetor(v,n);
  
  if(soma == NULL)
    printf("SOMA = 0");
  else{
    printf("SOMA = ");
    imprime_r(soma);
    destroi_r(&soma);
  }

  printf("\n");
  destroi_vetor(v, n);
  printf("VETOR = ");
  imprime_vetor(v, n);

  free(v);
  v = NULL;
  return 0;
}
