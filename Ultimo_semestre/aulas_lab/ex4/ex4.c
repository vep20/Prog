#include <stdio.h>

int main(){
   int n, ant, quant, soma;

   printf("Digite sua sequencia de numeros, ela vai terminar quando o proximo numero lido for o dobro ou metade do anterior\n");
   scanf("%d",&n);
   soma = n;
   quant = 1;

  do{
      ant = n;
      scanf("%d",&n); 
      soma = soma + n;
      quant++;
   }while((ant != n * n) && (ant/2 != n));

   printf("%d %d %d %d\n",quant, soma, ant, n);
   return 0;
}
