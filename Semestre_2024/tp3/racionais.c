#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* coloque demais includes aqui */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (long int min, long int max){
    int n_aleat; 

    /*Forma de gerar numeros aleatorios entre min e max includos eles mesmos*/
    n_aleat = min + rand() % (max - min + 1); 
    return n_aleat;
}


/* Maximo Divisor Comum entre a e b.         */
/* Calcula o mdc pelo metodo de Euclides.    */
/* Dica: a versao recursiva eh bem elegante! */
long int mdc (long int a, long int b){
    a = abs(a);
    b = abs(b);
    /* Valores sempre positivos, visto que há possibilidade de entrarem negativos*/

    if (!a)
        return b;
    else if (!b)
        return a;
    
    if(a > b) 
        return mdc(a%b,b);
    return mdc(a,b%a);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long int mmc (long int a, long int b){
        
    return (a * b) / mdc (a, b);
}

/* Recebe um numero racional e o retorna simplificado no parametro *r.
   Quem chama esta funcao deve garantir que *r seja valido e nao NULL. */
void simplifica_r (struct racional *r){
    int aux_mdc;

    /* Utilizado abs por causa da função de subtração*/
    aux_mdc = mdc(abs(r->num),abs(r->den));
    r->num = r->num / aux_mdc;
    r->den = r->den / aux_mdc;
}

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/* Implemente aqui as funcoes cujos prototipos estao em racionais.h */

struct racional *cria_r (long int numerador, long int denominador){
    struct racional *aux;

    aux = malloc(sizeof(struct racional));
    if(!(aux))
        return NULL;
    aux->num = numerador;
    aux->den = denominador;
    simplifica_r(aux);
    /* Validação deve ocorrer ápos a simplificação,
     * pois na main (teste) já se define a validade do num e den*/
    return aux;
}

struct racional *sorteia_r (long int max){
    struct racional *aux;

    aux = malloc(sizeof(struct racional));
    if(!(aux))
        return NULL;
    aux->num = aleat(-max,max);
    aux->den = aleat(-max,max);
    simplifica_r(&aux);
    return aux;
}

void destroi_r (struct racional **r){

    free(*r);
    *r = NULL;
}

long int numerador_r (struct racional *r){

    return r->num;
}

long int denominador_r (struct racional *r){

    return r->den;
}

int valido_r (struct racional *r){

    if (!r->den)
        return 0;
    return 1;
}

struct racional *soma_r (struct racional *r1, struct racional *r2){
    struct racional *aux;
    int aux_mmc;

    aux = malloc(sizeof(struct racional));
    if(!(aux))
        return NULL;

    if(r1->den == r2->den){
        aux->num = r1->num + r2->num;
        aux->den = r1->den;
    }/* Para os casos que não são necesssarios chamar a função mmc*/

    else{
        aux_mmc = mmc(r1->den,r2->den);
        aux->num = ((aux_mmc / r1->den * r1->num) + (aux_mmc / r2->den * r2->num));
        aux->den = aux_mmc;
    }

    simplifica_r(aux);
    return aux; 
}

struct racional *subtrai_r (struct racional *r1, struct racional *r2){
    struct racional *aux;
    int aux_mmc;

    aux = malloc(sizeof(struct racional));
    if(!(aux))
        return NULL;    

    if(r1->den == r2->den){
        aux->num = r1->num - r2->num;
        aux->den = r1->den;
    }/* Para os casos que não são necesssarios chamar a função mmc*/

    else{
        aux_mmc = mmc(r1->den,r2->den);
        aux->num = ((aux_mmc / r1->den * r1->num) - (aux_mmc / r2->den * r2->num));
        aux->den = aux_mmc;
    }

    simplifica_r(aux);
    return aux; 
}

struct racional *multiplica_r (struct racional *r1, struct racional *r2){
    struct racional *aux;

    aux = malloc(sizeof(struct racional));
    if(!(aux))
        return NULL;

    aux->num = r1->num * r2->num;
    aux->den = r1->den * r2->den;
    simplifica_r(aux);
    return aux;
}

struct racional *divide_r (struct racional *r1, struct racional *r2){
    struct racional *aux;

    aux = malloc(sizeof(struct racional));
    if(!(aux))
        return NULL;
    
    if (!r2->num)
        return 0;

    aux->num = r1->num * r2->den;
    aux->den = r1->den * r2->num;
    simplifica_r(aux);
    return aux;   
}

int compara_r (struct racional *r1, struct racional *r2){
    float valor_dec1, valor_dec2;

    valor_dec1 = r1->num / r1->den;
    valor_dec2 = r2->num / r2->den;
    if (valor_dec1 < valor_dec2)
        return -1;
    else if (valor_dec1 == valor_dec2)
        return 0;
    return 1;
}

void imprime_r (struct racional *r){

    if(!valido_r(r)){
        printf("INVALIDO ");
        return;
    }
    
    if (r->num == 0)
        printf("0 ");

    else if(r->den == 1 || r->den == -1)
        printf("%d ", r->num/r->den);

    else if(r->num == r->den)
        printf("1 ");

    else{
        if(r->num > 0 && r->den < 0) 
            printf("-%d/%d ", abs(r->num), abs(r->den));
        else if(r->num < 0 && r->den < 0)
            printf("%d/%d ", abs(r->num), abs(r->den));
        else 
            printf("%d/%d ", r->num, r->den);
    }
}