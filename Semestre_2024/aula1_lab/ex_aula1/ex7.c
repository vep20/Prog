#include <stdio.h>

int main(){
    int n, fatorial;

    do{
        printf("Digite o numero que você queira descobrir o fatorial: ");
        scanf("%d",&n);
        if (n < 1)
            printf("Numero não pode ser 0 ou negativo\n");
    }while(n < 1);

    fatorial = n;
    for (int i = n-1; i >= 1; i--){
        fatorial = fatorial * i;
    }
    printf("O fatorial do numero %d é %d\n", n, fatorial);
    return 0;
}
