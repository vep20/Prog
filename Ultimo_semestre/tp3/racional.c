/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc(long a, long b){
  a = labs(a);
  b = labs(b);
  /* Valores sempre positivos, visto que há possibilidade de entrarem negativos*/

  if (!a)
    return b;
  else if (!b)
    return a;

  if (a > b)
    return mdc(a % b, b);
  return mdc(a, b % a);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b){

  return (a * b) / mdc(a, b);
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r(struct racional *r){
  long aux_mdc;

  if (!valido_r(r) || r == NULL)
    return 0;

  /* Utilizado abs por causa da função de subtração*/
  aux_mdc = mdc(labs(r->num), labs(r->den));
  r->num = r->num / aux_mdc;
  r->den = r->den / aux_mdc;

  if (r->num < 0 && r->den < 0)
    r->num = labs(r->num);
  else if (r->num > 0 && r->den < 0)
    r->num = r->num * -1;
  
  r->den = labs(r->den);

  return 1;
}

struct racional *cria_r(long numerador, long denominador){
  struct racional *aux;

  aux = malloc(sizeof(struct racional));
  if (!(aux))
    return NULL;
  /* Teste de alocação, usado nestas e demais funções da biblioteca*/

  aux->num = numerador;
  aux->den = denominador;
  simplifica_r(aux);
  /* Validação deve ocorrer ápos a simplificação,
   * pois na main (teste) já se define a validade do num e den*/
  return aux;
}

void destroi_r(struct racional *r){

  free(r);
  r = NULL;
}

int valido_r(struct racional *r){

  if (!r->den)
    return 0;
  return 1;
}

void imprime_r(struct racional *r){

  if (!valido_r(r)){
    printf("NaN");
    return;
  }

  if (r->num == 0)
    printf("0");

  else if (r->den == 1 || r->den == -1)
    printf("%ld", r->num / r->den);

  else if (r->num == r->den)
    printf("1");

  else{
    if (r->num > 0 && r->den < 0)
      printf("-%ld/%ld", labs(r->num), labs(r->den));
    else if (r->num < 0 && r->den < 0)
      printf("%ld/%ld", labs(r->num), labs(r->den));
    else
      printf("%ld/%ld", r->num, r->den);
  }
}

int compara_r (struct racional *r1, struct racional *r2){
  float valor_dec1, valor_dec2;

  if (r1->den == 0 || r2->den == 0)
    /*Se o denominador de qualquer um dos racionais for zero, eles são considerados iguais*/
    return 0;

  valor_dec1 = (float)r1->num / (float)r1->den;
  valor_dec2 = (float)r2->num / (float)r2->den;

  if (valor_dec1 < valor_dec2)
    return -1;
  else if (valor_dec1 == valor_dec2)
    return 0;
  return 1;
}

int soma_r(struct racional *r1, struct racional *r2, struct racional *r3){
  long aux_mmc;

  if((!valido_r(r1) || !valido_r(r2)) && (r1 == NULL) && (r2 == NULL))
    return 0;

  if (r1->den == r2->den){
    r3->num = r1->num + r2->num;
    r3->den = r1->den;
  } /* Para os casos que não são necesssarios chamar a função mmc*/

  else{
    aux_mmc = mmc(r1->den, r2->den);
    r3->num = ((aux_mmc / r1->den * r1->num) + (aux_mmc / r2->den * r2->num));
    r3->den = aux_mmc;
  }

  simplifica_r(r3);
  return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3){
  long aux_mmc;

   if((!valido_r(r1) || !valido_r(r2)) && (r1 == NULL) && (r2 == NULL))
    return 0;

  if (r1->den == r2->den){
    r3->num = r1->num - r2->num;
    r3->den = r1->den;
  } /* Para os casos que não são necesssarios chamar a função mmc*/

  else{
    aux_mmc = mmc(r1->den, r2->den);
    r3->num = ((aux_mmc / r1->den * r1->num) - (aux_mmc / r2->den * r2->num));
    r3->den = aux_mmc;
  }

  simplifica_r(r3);
  return 1;
}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3){
  
  if((!valido_r(r1) || !valido_r(r2)) && (r1 == NULL) && (r2 == NULL))
    return 0;

  r3->num = r1->num * r2->num;
  r3->den = r1->den * r2->den;
  simplifica_r(r3);
  return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3){

  if((!valido_r(r1) || !valido_r(r2)) && (r1 == NULL) && (r2 == NULL))
    return 0;

  if (!r2->num)
    return 0;

  r3->num = r1->num * r2->den;
  r3->den = r1->den * r2->num;
  simplifica_r(r3);
  return 1;
}