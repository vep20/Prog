/*Com base no programa do item 1, escreva um programa em C que:
a. No item “c”, receba do usuário cada valor a ser indexado no intervalo [0, n);
b. Imprima o vetor recebido em ordem.
*/

#include <stdio.h>
#define max 1024

void ler(int n,int v[]){
    for(int i=0;i<n;++i)
        scanf("%d",&v[i]);
}

void ordena(int n,int v[]){
    for(int i=0;i<n;++i){
        int menor=i;
        for(int j=i+1;j<n-1;++j){
            if(v[j]<v[menor])
                menor=j;
        int aux=v[menor];
        v[menor]=v[i];
        v[i]=aux;
        }        
    }
}

void imprime(int n,int v[]){
    for(int i=0;i<n;++i)
        printf("vet [%d] = %d\n",i, v[i]);
    }

int main(){
    int v[max];
    int n;

    printf("Digite um numero que define o tamanho do seu vetor\n");
    scanf("%d",&n);
    ler(n,v);
    ordena(n,v);
    imprime(n,v);
}
