#include <stdio.h>

int main(){
    int n, ant, atual, fibo;

    do{
        printf("Digite a quantidade de numeros da sequencia de fibonacci que voce queira ver impresso\n");
        scanf("%d",&n);
        if (n < 1)
            printf("Numero não pode ser 0 ou negativo\n");
    }while(n < 1);

    ant = 0;
    atual = 1;
    fibo = 1;
    printf("1, ");
    for (int i = 1;i < n; i++){
        if (i+1 != n)
            printf("%d, ", fibo);
        else
            printf("%d\n",fibo);
        ant = atual;
        atual = fibo; 
        fibo = ant + atual;
    }
    return 0;
}
