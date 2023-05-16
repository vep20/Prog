/*2. Com base no programa do item 1, escreva um programa em C que:
 No item “c” do item anterior, em vez de preencher cada posição do vetor com o
valor dos índices do intervalo, preencha o vetor em modo decrescente (ex.: se n
== 10, os índices do vetor vão de 0 até 9; a posição indexada por 0 deve
receber o valor 9, posição 1 recebe 8 e assim por diante até que o índice 9
receba valor 0).*/

#define max 1024
#include <stdio.h>
#include <stdlib.h>

void insere_vetor(int n, int v[]){
    int cont=0;
    for(int i=n-1;i!=0;--i){
        v[cont]=i;
        cont=cont+1;
    }
}

void imprime_inverso(int n,int v[]){
    int cont=0;
    for(int i;i<n;++i){
        printf("v[%d] = %d\n",cont,v[i]);
        cont=cont+1;
    }

}

int main(){
    int n,v[max];

    scanf("%d",&n);
    insere_vetor(n,v);
    imprime_inverso(n,v);
    return 0;
}