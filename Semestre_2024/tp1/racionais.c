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

    /* Utilizado abs por causa da função de subtração*/
    aux_mdc = mdc(abs(r.num),abs(r.den));
    aux.num = r.num/ aux_mdc;
    aux.den = r.den / aux_mdc;
    return aux;
}

/* função de teste*/
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

    if (!r.den)
        return 0;
    return 1;
}

struct racional soma_r (struct racional r1, struct racional r2){
    struct racional aux;
    int aux_mmc;

    if(r1.den == r2.den){
        aux.num = r1.num + r2.num;
        aux.den = r1.den;
    }/* Para os casos que não são necesssarios chamar a função mmc*/

    else{
        aux_mmc = mmc(r1.den,r2.den);
        aux.num = ((aux_mmc / r1.den * r1.num) + (aux_mmc / r2.den * r2.num));
        aux.den = aux_mmc;
    }

    aux = simplifica_r(aux);
    return aux;
}

struct racional subtrai_r (struct racional r1, struct racional r2){
    struct racional aux;
    int aux_mmc;
 
    if(r1.den == r2.den){
        aux.num = r1.num - r2.num;
        aux.den = r1.den;
    }/* Para os casos que não são necesssarios chamar a função mmc*/

    else{
        aux_mmc = mmc(r1.den,r2.den);
        aux.num = ((aux_mmc / r1.den * r1.num) - (aux_mmc / r2.den * r2.num));
        aux.den = aux_mmc;
    }

    aux = simplifica_r(aux);
    return aux;
}

struct racional multiplica_r (struct racional r1, struct racional r2){
    struct racional aux;

    aux.num = r1.num * r2.num;
    aux.den = r1.den * r2.den;
    aux = simplifica_r(aux);
    return aux; 
}

struct racional divide_r (struct racional r1, struct racional r2){
    struct racional aux;
    
    aux.num = r1.num * r2.den;
    aux.den = r1.den * r2.num;
    aux.valido = valido_r(aux);
    aux = simplifica_r(aux);
    return(aux);    
}