#include <stdio.h>
#include <stdlib.h>

int mdc_recursivo (int a, int b){

    if (!a)
        return b;
    else if (!b)
        return a;
    
    if(a > b) 
        return mdc_recursivo(a%b,b);
    return mdc_recursivo (a,b%a);
}

int mdc (int a, int b){

    /* Utilizando o metodo de euclides ensinado em alg1
     * onde se compara 2 numeros e o maior deles recebe o 
     * resto da divisão dele pelo menor*/
    while (a && b){
        if (a > b)
            a = a % b;  
        else
            b = b % a; 
    }

    if (!a)
        return b;
    return a;
}

int main(){
    int a, b, resultado_normal, resultado_recursivo;

    scanf("%d %d",&a,&b);
    resultado_normal = mdc(a,b);
    resultado_recursivo = mdc_recursivo(a,b);
    printf("o resultado normal é: %d\n", resultado_normal);
    printf("o resultado recursivo é: %d\n", resultado_recursivo);
}