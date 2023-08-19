#include <stdio.h>
#include <string.h>
#define n 2

typedef struct pacientes_t{
   char nome[50];
   short idade;
   float peso;
}pacientes_t;

struct pacientes_t cadastrar_paciente(){
   pacientes_t aux;

   printf("\nNome:\n");
   fgets(aux.nome, sizeof(aux.nome),stdin);
   printf("Idade:\n");
   scanf("%hd", &aux.idade);
   printf("Peso:\n");
   scanf("%f", &aux.peso);
   getchar();

   return aux;
}

void imprime_paciente (pacientes_t p[],int y){
   for(int i = 0;i < y;i++){
      printf("\nNome:%s", p[i].nome);
      printf("Idade: %hd\n", p[i].idade);
      printf("Peso: %.2f\n", p[i].peso);
  }
}


int main(){
   pacientes_t p[n];

   p[0] = cadastrar_paciente();
   p[1] = cadastrar_paciente();

   imprime_paciente(p,n);

   return 0;
}

