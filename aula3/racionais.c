#include <stdio.h>
#include <stdlib.h>

typedef struct racionais{
    int a;
    int b;
}racionais_t;

racionais_t le_racional (racionais_t a){
    scanf("%d %d",&a.a,&a.b);
    return a;
}

racionais_t simplifica(racionais_t b){
    racionais_t a;
    a.a=b.a;
    a.b=b.b;
    while (a.a!=0 && a.b){
        if (a.a>a.b)
            a.a=a.a % a.b;
        else
            a.b=a.b % a.a;
        }    
    if (a.a == 0){
        b.a=b.a/a.b;
        b.b=b.b/a.b;
    } 
    else {
        b.a=b.a/a.a;
        b.b=b.b/a.a;
    }
    return b;
}

racionais_t soma_racional(racionais_t a, racionais_t b){
    racionais_t c;
    c.a= (a.a*b.b) + (a.b*b.a);
    c.b =a.b*b.b;
    simplifica(c);
    return c;
}
    
racionais_t subtrai_racional(racionais_t a, racionais_t b){
    racionais_t c;
    c.a= (a.a*b.b) - (a.b*b.a);
    c.b =a.b*b.b;
    return c;
}

racionais_t multiplica_racional(racionais_t a, racionais_t b){
    racionais_t c;
    c.a= a.a*b.a;
    c.b =a.b*b.b;
    return c;
}

racionais_t divide_racional(racionais_t a, racionais_t b){
    racionais_t c;
    c.a= a.a*b.b;
    c.b =a.b*b.a;
    return c;
}

void imprime(racionais_t a){
    printf("%d / %d\n",a.a, a.b);
}

int main(){
    racionais_t r1,r2, soma, sub, mult, div;
    r1 = le_racional(r1);
    while (r1.b!=0){
        r2 = le_racional(r2);
        if (r2.b!=0){
            soma = soma_racional(r1,r2);
            sub = subtrai_racional(r1,r2);
            mult = multiplica_racional(r1,r2);
            div = divide_racional(r1,r2);
            imprime(soma); imprime(sub); imprime(mult);imprime(div);
        }
        r1 = le_racional(r1);
    }
    return 0;
}