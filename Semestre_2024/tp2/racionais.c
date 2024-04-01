#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* acrescente demais includes que voce queira ou precise */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){
    int n_aleat; 

    /*Forma de gerar numeros aleatorios entre min e max includos eles mesmos*/
    n_aleat = rand() % (max - min + 1) + min; 
    return n_aleat;
}

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
/* dica: a versao recursiva eh bem elegante! */
int mdc (int a, int b){

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
int mmc (int a, int b){

    return (a * b) / mdc (a, b);
}

/* Recebe um numero racional e o retorna simplificado.
 * Por exemplo, ao receber 10/8 devera retornar 5/4.
 * Se ambos numerador e denominador forem negativos, devera retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Quem chama esta funcao deve garantir que o racional r eh valido */
void simplifica_r (struct racional *r){
    int aux_mdc;

    /* Utilizado abs por causa da função de subtração*/
    aux_mdc = mdc(abs(r->num),abs(r->den));
    r->num = r->num/ aux_mdc;
    r->den = r->den / aux_mdc;
}

/*
 * Implemente aqui as funcoes definidas no racionais.h.
*/


/* Função de teste para o usuario*/
struct racional cria_r (int numerador, int denominador){
    struct racional aux; 

    aux.num = numerador;
    aux.den = denominador;
    simplifica_r(&aux);
    /* Validação deve ocorrer pos a simplificação,
     * pois na main (teste) já se define a validade do num e den*/
    aux.valido = valido_r (aux);
    return aux;
}

struct racional sorteia_r (int n){
    struct racional aux;

    aux.num = aleat(0,n);
    aux.den = aleat(0,n);
    simplifica_r(&aux);
    aux.valido = valido_r (aux);
    return aux;
}

int numerador_r(struct racional r){

    return r.num;
}

int denominador_r(struct racional r){

    return r.den;
}

int valido_r(struct racional r){

    if (!r.den)
        return 0;
    return 1;
}

void soma_r(struct racional r1, struct racional r2, struct racional *r3){
    int aux_mmc;

    if(r1.den == r2.den){
        r3->num = r1.num + r2.num;
        r3->den = r1.den;
    }/* Para os casos que não são necesssarios chamar a função mmc*/

    else{
        aux_mmc = mmc(r1.den,r2.den);
        r3->num = ((aux_mmc / r1.den * r1.num) + (aux_mmc / r2.den * r2.num));
        r3->den = aux_mmc;
    }

    simplifica_r(r3);
}

void subtrai_r(struct racional r1, struct racional r2, struct racional *r3){
    int aux_mmc;
 
    if(r1.den == r2.den){
        r3->num = r1.num - r2.num;
        r3->den = r1.den;
    }/* Para os casos que não são necesssarios chamar a função mmc*/

    else{
        aux_mmc = mmc(r1.den,r2.den);
        r3->num = ((aux_mmc / r1.den * r1.num) - (aux_mmc / r2.den * r2.num));
        r3->den = aux_mmc;
    }

    simplifica_r(r3);
}

void multiplica_r(struct racional r1, struct racional r2, struct racional *r3){

    r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;
    simplifica_r(r3);
}

int divide_r(struct racional r1, struct racional r2, struct racional *r3){
    
    r3->num = r1.num * r2.den;
    r3->den = r1.den * r2.num;

    simplifica_r(r3);
    return 0;   
}

int compara_r(struct racional r1, struct racional r2){
    float valor_dec1, valor_dec2;

    valor_dec1 = r1.num / r1.den;
    valor_dec2 = r2.num / r2.den;
    if (valor_dec1 < valor_dec2)
        return -1;
    else if (valor_dec1 == valor_dec2)
        return 0;
    return 1;
}

void imprime_r (struct racional r){

    if(!valido_r(r)){
        printf("INVALIDO ");
        return;
    }

    if (r.num == 0)
        printf("0 ");

    else if(r.den == 1)
        printf("%d ", r.num);

    else if(r.num == r.den)
        printf("1 ");

    else{
        if(r.den < 0) 
            printf("-%d/%d ", r.num, abs(r.den));
        else if(r.num < 0 && r.den < 0)
            printf("%d/%d ", abs(r.num), abs(r.den));
        else 
            printf("%d/%d ", r.num, r.den);
    }
}

