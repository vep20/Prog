#include <stdio.h>
#define max 100

int pilha_vazia(int topo){
  return topo == 0;
}

int pilha_cheia(int topo){
    return topo == max;
}

void empilha(char v[], int *topo, int elemento){
    v[*topo] = elemento;
    (*topo)++;
}

void desempilha(char v[], int *topo){
    (*topo)--;
}

void imprime_pilha(char v[], int topo){
    for(int i = 0; i < topo; i++)
        printf("posição %d = %c ",i,v[i]);
    printf("\n");
}

int main(){
    int define, topo = 0;
    char v[max], comando = 'c', elemento;

    while (comando != 's'){
    
        printf("Digite 1 se quer empilhar e 2 caso queira desempilhar: ");
        scanf("%d",&define);

        if (define == 1){
            if (pilha_cheia(topo))
                printf("Impossivel empilhar, a pilha esta cheia\n");
            else{
                printf("Digite o elemento que você qd uer empilhar: ");
                getchar();
                elemento = getchar();
                empilha(v,&topo,elemento);
            }
        }

        else if (define == 2){
            if (pilha_vazia(topo))
                printf("Impossivel desemmpilhar, a pilha esta vazia\n");
            else
                desempilha(v,&topo);
        }

        else
            printf("Numero invalido\n");

        printf("Digite 's' caso queira finalizar o programa:\n");
        scanf(" %c",&comando);

    }

    imprime_pilha(v, topo);

    return 0;
}