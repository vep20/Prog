#include <stdio.h>
#include <math.h>

short valor_quadrado(int n){
    short determinante1, determinante2;
    int ant, quadrado;

    determinante1 = 1;
    determinante2 = 0;
    while(n != 0){
       if (!determinante2){
            ant = n;
            determinante2 = 1;
        }
        else {
            determinante2 = 0;
            quadrado = sqrt(n);
        }
        if(!determinante2 && ant != quadrado && determinante1)
            determinante1 = 0;
        scanf("%d", &n);
    }
    if (determinante1 && !determinante2)
        return 1;
    return 0;
}

int main(){
    int n;
    
    printf("Digite a sequencia para verificar se é uma serie 'Valor quadrado'\n");
    printf("Quando quiser finalizar, digite 0\n");
    scanf("%d", &n);
    if (valor_quadrado(n))
        printf("1\n");
    else
        printf("0\n");
    return 0;
}