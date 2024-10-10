/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max){
  long n_aleat; 

  /*Forma de gerar numeros aleatorios entre min e max includos eles mesmos*/
  n_aleat = min + rand() % (max - min + 1); 
  return n_aleat;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b){
  a = labs(a);
  b = labs(b);
  /* Valores sempre positivos, visto que há possibilidade de entrarem negativos*/

  if (!a)
    return b;
  else if (!b)
    return a;
  
  if(a > b) 
    return mdc(a%b,b);
  return mdc(a,b%a);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b){

  return (a * b) / mdc (a, b);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r){
  struct racional aux;
  long aux_mdc;

  aux_mdc = mdc(labs(r.num),labs(r.den));
  aux.num = r.num / aux_mdc;
  aux.den = r.den / aux_mdc;

  return aux;
}

struct racional cria_r (long numerador, long denominador){
  struct racional aux; 

  aux.num = numerador;
  aux.den = denominador;
  if (valido_r(aux))  
    aux = simplifica_r(aux);

  return aux;
}

struct racional sorteia_r (long min, long max){
  struct racional aux;

  aux.num = aleat(min,max);
  aux.den = aleat(min,max);
  aux = simplifica_r(aux);

  return aux;
}

void imprime_r (struct racional r){

  if(!valido_r(r)){
    printf("NaN");
    return;
  }
  
  if (r.num == 0)
    printf("0");

  else if(r.den == 1 || r.den == -1)
    printf("%ld", r.num/r.den);

  else if(r.num == r.den)
    printf("1");

  else{
    if(r.num > 0 && r.den < 0) 
      printf("-%ld/%ld", labs(r.num), labs(r.den));
    else if(r.num < 0 && r.den < 0)
      printf("%ld/%ld", labs(r.num), labs(r.den));
    else 
      printf("%ld/%ld", r.num, r.den);
  }
}

int compara_r (struct racional r1, struct racional r2){
  float valor_dec1, valor_dec2;

  if (r1.den == 0 || r2.den == 0) 
    /*Se o denominador de qualquer um dos racionais for zero, eles são considerados iguais*/    
    return 0;

  valor_dec1 = (float)r1.num / (float)r1.den;
  valor_dec2 = (float)r2.num / (float)r2.den;
  
  if (valor_dec1 < valor_dec2)
      return -1;
  else if (valor_dec1 == valor_dec2)
      return 0;
  return 1;
}

int valido_r(struct racional r){

  if (!r.den)
    return 0;
  return 1;
}

int soma_r(struct racional r1, struct racional r2, struct racional *r3){
  struct racional aux;
  long aux_mmc;

  if(!valido_r(r1) || !valido_r(r2))
    return 0;

  if(r1.den == r2.den){
    aux.num = r1.num + r2.num;
    aux.den = r1.den;
  }/* Para os casos que não são necesssarios chamar a função mmc*/

  else{
    aux_mmc = mmc(r1.den,r2.den);
    aux.num = ((aux_mmc / r1.den * r1.num) + (aux_mmc / r2.den * r2.num));
    aux.den = aux_mmc;
  }

  *r3 = simplifica_r(aux);
  return 1;
}

int subtrai_r(struct racional r1, struct racional r2, struct racional *r3){
  struct racional aux;
  long aux_mmc;

  if(!valido_r(r1) || !valido_r(r2))
    return 0;

  if(r1.den == r2.den){
    aux.num = r1.num - r2.num;
    aux.den = r1.den;
  }/* Para os casos que não são necesssarios chamar a função mmc*/

  else{
    aux_mmc = mmc(r1.den,r2.den);
    aux.num = ((aux_mmc / r1.den * r1.num) - (aux_mmc / r2.den * r2.num));
    aux.den = aux_mmc;
  }

  *r3 = simplifica_r(aux);
  return 1;
}

int multiplica_r(struct racional r1, struct racional r2, struct racional *r3){
  struct racional aux;

  if(!valido_r(r1) || !valido_r(r2))
    return 0;

  aux.num = r1.num * r2.num;
  aux.den = r1.den * r2.den;

  *r3 = simplifica_r(aux);
  return 1;
}

int divide_r(struct racional r1, struct racional r2, struct racional *r3){
  struct racional aux;
  
  if(!valido_r(r1) || !valido_r(r2) || !r2.num)
    return 0;
 
  aux.num = r1.num * r2.den;
  aux.den = r1.den * r2.num;

  *r3 = simplifica_r(aux);
  return 1;   
}