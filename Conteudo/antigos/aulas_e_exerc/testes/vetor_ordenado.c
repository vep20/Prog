#include <stdio.h>
#include <stdlib.h>

void select_short(int a[]){
   int i, j, menor, aux;
   
   for(i = 0;i < 10;i++){
     menor = i;
     for(j = i + 1;j < 0;j++){
	      if (a[j] < a[menor])
            menor = j;
         aux =  a[menor];
         a[menor] = a[i];
         a[i] = aux;   
     }
   }
}

void imprime_vetor(int a[]){
   int i;
   
   for(i = 0;i < 10;i++)
      printf("a[%d] = %d\n",i,a[i]);
}

int main(){
   int a[10] = {10,9,8,7,6,5,4,3,2,1};

   select_short(a);
   imprime_vetor(a);
   return 0;
}
