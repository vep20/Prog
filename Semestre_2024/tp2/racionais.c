#include "racionais.h"
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
        return mdc_recursivo(a%b,b);
    return mdc_recursivo (a,b%a);
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
void simplifica_r (struct racional *r);

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/*
 * Implemente aqui as funcoes definidas no racionais.h.
*/
