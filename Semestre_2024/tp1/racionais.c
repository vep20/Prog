#include "racionais.h"  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* acrescente demais includes que voce queira ou precise */

/* 
 * Implemente aqui as funcoes definidas no racionais.h 
 * caso queira, você pode definir neste arquivo funcoes
 * adicionais que serao internas e so podem ser usadas
 * aqui.
*/


int aleat (int min, int max){
    int n_aleat;

    /*Forma de gerar numeros aleatorios entre min e max includos eles mesmos*/
    n_aleat = rand() % (max - min + 1) + min; 
    return n_aleat;
}

int mdc (int a, int b){

    /* Utilizando o metodo de euclides ensinado em alg1
     * onde se compara 2 numeros e o maior deles recebe o 
     * resto da divisão dele pelo menor*/
    while (a && b){
        if (a > b)
            a = a % b;  
        else
            b = b % a; 
    }

    if (!a)
        return b;
    return a;
}

int mmc (int a, int b){

    return (a * b) / mdc (a, b);
}

struct racional simplifica_r (struct racional r){
    struct racional aux;
    int aux_mdc;

    aux_mdc =  mdc(abs(r.num), abs(r.den));
    /* Utiliza abs por causa da função de subtração*/
    aux.num = r.num / aux_mdc;
    aux.den = r.den / aux_mdc;
}

/*função de teste*/
struct racional cria_r (int numerador, int denominador){
    struct racional aux; 

    aux.num = numerador;
    aux.den = denominador;
    aux = simplifica_r(aux);
    /* Validação deve ocorrer pos a simplificação,
     * pois na main (teste) já se define a validade do num e den*/
    aux.valido = valido_r (aux);
    return aux;
}

struct racional sorteia_r (int n){
    struct racional aux;

    aux.num = aleat(0,n);
    aux.den = aleat(0,n);
    aux = simplifica_r(aux);
    aux.valido = valido_r (aux);
    return aux;
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

int valido_r (struct racional r){

    return ;
}