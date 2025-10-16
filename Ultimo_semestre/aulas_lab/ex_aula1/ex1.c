#include <stdio.h>

short verifica_triangular(int n){
    int prod, a, b, c;

    a = 1; b = 2, c = 3;
    prod = a * b * c;
    while(prod < n){
        a++; b++; c++;
        prod = a * b * c;
    }
    if (prod == n)
        return 1;
    return 0;
}

int main(){
    int n;

    printf("Digite um numero, se a resposta for 1, ele é tringular: ");
    scanf("%d",&n);
    if (verifica_triangular(n))
        printf("1\n");
    else
        printf("0\n");
    return 0;
}