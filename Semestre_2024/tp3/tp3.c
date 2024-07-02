/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

void cria_vetor (struct racional *v[], int tam){
    int aux_num, aux_den;

    for (int i = 0; i < tam; i++){
        scanf("%d %d", &aux_num, &aux_den);
        v[i] = cria_r(aux_num,aux_den);
    }
}

void imprime_vetor(struct racional *v[], int tam){

    for(int i = 0; i < tam; i++)
        imprime_r(v[i]);
    printf("\n");        
}

void redimenciona_vetor(struct racional *v[], int inicio, int *tam){

    for (int i = inicio; i < *tam - 1; i++)
        v[i] = v[i+1];

}

void elimina_invalidos(struct racional *v[], int *tam){
    for(int i = 0; i < *tam; i++){
        if (!valido_r(v[i])){
            redimenciona_vetor(v, i, tam); // Corrigindo para passar o valor real de tam
            v[*tam] = NULL;
            (*tam)--;
            i--;
        } 
    }
}


void troca(struct racional *r1, struct racional *r2){
    struct racional aux;

    aux = *r1;
    *r1 = *r2;
    *r2 = aux;
}

void ordena_vetor(struct racional *v[], int tam){

    for(int i = 0; i < tam; i++){
        for (int j = i+1; j < tam; j++){
            if (compara_r(v[j],v[j+1]))
                troca(v[j],v[j+1]);
        }
    }   
}

void destroi_vetor(struct racional *v[], int tam){

    for(int i = 0; i < tam; i++){
        free(v[i]);
        v[i] = NULL;
    }
}

int main (){
    int n   ;

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    srand(0);

    do{
        printf("Digite um numero entre 0 e 100:");
        scanf("%d",&n);
        if (n < 0 || n > 100)
            printf("Numero n fora do intervalo definido\n");
    }while(n < 0 || n > 100);

    v = malloc(sizeof (struct racional *) * n);
    if (v == NULL)
        return 1;

    cria_vetor(v,n);
    imprime_vetor(v,n);
    elimina_invalidos(v,&n);
    imprime_vetor(v,n);
    ordena_vetor(v,n);
    imprime_vetor(v,n);
    destroi_vetor(v,n);

    destroi_r(v);    
    return 0;
} 