#include <stdio.h>

int main(){
    int n, mult, aux, soma_alg;

    printf("Digite o numero que sera multiplicado por 37: ");
    scanf("%d",&n);
    mult = n * 37;
    soma_alg = 0;
    while(mult){
        aux = mult % 10;
        soma_alg = soma_alg + aux;
        mult = mult / 10; 
    }
    if (soma_alg == n)
        printf("SIM\n");
    else
        printf("NAO\n");
    return 0;
}