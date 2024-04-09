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