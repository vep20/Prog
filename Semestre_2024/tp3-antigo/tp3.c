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

    for (int i = inicio; i < (*tam - 1); i++)
        v[i] = v[i+1];
    v[*tam - 1] = NULL; 
}

void elimina_invalidos(struct racional *v[], int *tam){

    for(int i = 0; i < *tam; i++){
        if (!valido_r(v[i])){
            free(v[i]);
            redimenciona_vetor(v, i, tam); /* Corrigindo para passar o valor real de tam */
            (*tam)--;
            i--; /* Ajustar  o indice */
        } 
    }
}


void troca(struct racional **r1, struct racional **r2){
    struct racional *aux;

    aux = *r1;
    *r1 = *r2;
    *r2 = aux;
}

void ordena_vetor(struct racional *v[], int tam){

    for(int i = 0; i < tam; i++){
        for (int j = i + 1; j < tam; j++){
            if (compara_r(v[j],v[i]) == -1)
                troca(&v[i],&v[j]); /* Alterado os endereços, por isso utiliza ponteiros de ponteiro*/
        }
    }       
}

void soma_vetor(struct racional *v[], int tam){
    struct racional *soma, *temp;

    if(tam == 0 || v[0] == NULL){
        printf("a soma de todos os elementos eh: 0\n");
        return;
    }
    
    soma = v[0];
    for(int i = 1; i < tam; i++){
        temp = soma;
        soma = soma_r(soma, v[i]);

        if(temp != v[0])
            free(temp);
    }
    printf("a soma de todos os elementos eh: ");
    imprime_r(soma);
    printf("\n");

    if (soma != v[0])
        free(soma);
}

void destroi_vetor(struct racional *v[], int tam){

    for(int i = 0; i < tam; i++){
        free(v[i]);
        v[i] = NULL;
    }
    
}

int main (){
    int n;

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    srand(0);

    do{
        printf("Digite um numero entre 0 e 100:");
        scanf("%d",&n);
        if (n < 0 || n > 100)
            printf("Numero n fora do intervalo definido\n");
    }while(n < 0 || n > 100);

    printf("\n");

    v = malloc(sizeof (struct racional *) * n);
    if (v == NULL)
        return 1;

    cria_vetor(v,n);
    imprime_vetor(v,n);
    elimina_invalidos(v,&n);
    imprime_vetor(v,n);
    ordena_vetor(v,n);
    imprime_vetor(v,n);
    soma_vetor(v,n);
    destroi_vetor(v,n);

    free(v);
    v = NULL;
    return 0;
} 