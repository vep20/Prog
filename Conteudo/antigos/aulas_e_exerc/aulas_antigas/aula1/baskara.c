#include <stdio.h>
#include <math.h>

int main() {         
   int a,b,c; /*declaracao de inteiro*/
   float delta,x1,x2; /*declaracao real*/ 

   scanf("%d %d %d", &a , &b ,&c); 
   /*ponto flutuante(%) que o usuario digita  vai para o endereço de memoria A*/  
   if (a==0)
     printf("a deve ser diferente de 0");
   else{
      delta=(b*b)-4*a*c;
      x1=(-b+sqrt(delta))/2*a;
      x2=(-b-sqrt(delta))/2*a;   
      if (delta<0) 
         printf("delta negativo\n");
      else
         printf("x1 eh %.2f\nx2 eh %.2f\n",x1,x2);//não utiliza & pois não esta utilizando um endereço da memoria
   }
}   
