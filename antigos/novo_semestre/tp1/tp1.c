/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int main (){
    srand(0);
    int n, max;
    struct racional r1, r2, soma, sub, mult, div;
    
    do{
        printf("Digite um numero entre 0 e 100:");
        scanf("%d",&n);
        if (n < 0 || n > 100)
            printf("Numero n fora do intervalo definido\n");
    }while(n < 0 || n > 100);

    do{
        printf("Digite outro numero entre 0 e 30:");
        scanf("%d",&max);
        if(max < 0 || max > 30)
            printf("Maximo fora do intervalo definido\n");
    }while(max < 0 || max > 30); //Garantia de que os numeros lidos estão no intervalos pré determinados
       

    for(int i = 1; i <= n; i++){
        printf("%d: ",i);
        r1 = sorteia_r(max);
        r2 = sorteia_r(max);

        imprime_r(r1);
        imprime_r(r2);

        if(!valido_r(r1) || !valido_r(r2)){
            printf("NUMERO INVALIDO\n");
            return 1;//retorno de erro para o programa 
        }

        soma = soma_r(r1,r2);
        sub = subtrai_r(r1,r2);
        mult = multiplica_r(r1,r2);
        div = divide_r(r1,r2);

        if(!valido_r(div)){
            printf("NUMERO INVALIDO\n");
            return 1;//retorno de erro para o programa 
        }

        imprime_r(soma);
        imprime_r(sub);
        imprime_r(mult);
        imprime_r(div);
        printf("\n");
    }
     
    return 0;
}
