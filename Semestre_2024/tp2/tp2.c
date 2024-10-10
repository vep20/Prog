/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define max 100

void cria_vetor (struct racional v[], int tam){
  long aux_num, aux_den;

  for (int i = 0; i < tam; i++){
    scanf("%ld %ld", &aux_num, &aux_den);
    v[i] = cria_r(aux_num, aux_den);
  }
}

void imprime_vetor(struct racional v[], int tam){

  for(int i = 0; i < tam; i++){
    imprime_r(v[i]);
    printf(" ");
  }
  printf("\n");        
}

void redimenciona_vetor(struct racional v[], int inicio, int *tam){

  for (int i = inicio; i < (*tam - 1); i++)
    v[i] = v[i+1];
  (*tam)--;
}

void elimina_invalidos(struct racional v[], int *tam){

  for(int i = 0; i < *tam; i++){
    if (!valido_r(v[i])){
      redimenciona_vetor(v, i, tam); /* Corrigindo para passar o valor real de tam */
      i--; /* Ajustar  o indice */
    } 
  }
}


void troca(struct racional *r1, struct racional *r2){
  struct racional aux;

  aux = *r1;
  *r1 = *r2;
  *r2 = aux;
}

void ordena_vetor(struct racional v[], int tam){

  for(int i = 0; i < tam; i++){
    for (int j = i + 1; j < tam; j++){
      if (compara_r(v[j],v[i]) == -1)
        troca(&v[i],&v[j]); /* Alterado os endereços, por isso utiliza ponteiros de ponteiro*/
    }
  }       
}

void soma_vetor(struct racional v[], int tam, struct racional *resultado){
  struct racional soma;
  

  if(!tam)
    resultado->num = 0;

  else{
    soma = v[0]; 

    for(int i = 1; i < tam; i++){
      soma_r(soma, v[i], &soma);  
    }
    *resultado = soma;
  }
}  

int main (){
  struct racional vetor[max], soma;
  int n;
  srand(0);

  do{
    printf("Digite um numero entre 0 e 100:");
    scanf("%d",&n);
    if (n < 0 || n > 100)
      printf("Numero n fora do intervalo definido\n");
  }while(n < 0 || n > 100);

  printf("\n");

  cria_vetor(vetor, n);
  printf("VETOR = ");
  imprime_vetor(vetor, n);
  elimina_invalidos(vetor, &n);
  printf("VETOR = ");
  imprime_vetor(vetor, n);
  ordena_vetor(vetor, n);
  printf("VETOR = ");
  imprime_vetor(vetor,n);
  soma_vetor(vetor,n,&soma);
  printf("SOMA = ");
  imprime_r(soma);
  printf("\n");
  return 0;
} 