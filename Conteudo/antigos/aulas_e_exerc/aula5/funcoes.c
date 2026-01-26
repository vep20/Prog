#include <stdio.h>
#include <stdlib.h>
#include <math.h>

short e_positivo(float n){
    
    if (n >= 0)
        return 1;
    return 0;
}

short e_nulo(float n){

    if (n == 0)
        return 1;
    return 0;
}

float calculo_delta(float a, float b, float c){
    float aux;

    aux = (b*b) - (4 * a * c);
    return aux;
}

float baskara(float a, float b, float c, float delta, short deter){
    float aux;
    
    if(deter) 
        aux = (-b + sqrt(delta)) / (2 * a);
    else
        aux = (-b - sqrt(delta)) / (2 * a);
    return aux;
}

int main(){
    float a, b, c, delta, raiz1, raiz2;

    do{
        printf("Digite os elementos da equação 'a', 'b' e 'c':\n");
        scanf("%f %f %f", &a, &b, &c);
        if (e_nulo(a))
            printf("'a' deve ser diferente de 0\n");
    }while(e_nulo(a));

    delta = calculo_delta(a,b,c);

    if (e_positivo(delta)){
        raiz1 = baskara(a,b,c,delta,1);
        raiz2 = baskara(a,b,c,delta,0);
        printf("As raizes são reais, onde x1 = %.2f e x2 = %.2f\n",raiz1,raiz2);
    }

    else{
        float parte_real = -b / (2 * a);
        float parte_imaginaria = sqrt(-delta) / (2 * a);
        printf("As raizes são complexas, onde x1 = %.2f + %.2fi e x2 = %.2f - %.2fi\n",
               parte_real,parte_imaginaria, parte_real, parte_imaginaria);
    }       


    return 0;
}