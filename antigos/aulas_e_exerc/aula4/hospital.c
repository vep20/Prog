#include <stdio.h>
#include <string.h>
#include "hospital.h"


struct medicamentos_t cadastra_medicamento(short i){
   medicamentos_t aux;
   
   printf("Nome remédio %hd: ",i);
   scanf(" %[^\n]", aux.nome);
   printf("Horario: ");;
   scanf("%d",&aux.hora);
   printf("Data inicio: ");
   scanf("%d %d %d", &aux.inicio.dia, &aux.inicio.mes, &aux.inicio.ano);
 
   return aux;
}

struct pacientes_t cadastrar_paciente(){
   pacientes_t aux;

   printf("Nome: ");
   scanf(" %[^\n]", aux.nome);
   printf("Idade: ");
   scanf("%hd", &aux.idade);
   printf("Peso: ");
   scanf("%f", &aux.peso);

   do{
      printf("Defina quantos remedios o paciente tomará (entre 1 e 3): ");
      scanf ("%hd", &aux.quantidade);
   }while(aux.quantidade < 1 || aux.quantidade > 3  );

   for (short i = 0;i < aux.quantidade; i++)
      aux.remedio[i] = cadastra_medicamento(i+1);
   
   return aux;
}

void busca_paciente(pacientes_t pacientes[], short atual){
   char nome_procurado[50];
   short i, encontrado;

   i = 0;
   encontrado = 0;
   printf("Digite o nome do paciente que procura: ");
   scanf(" %[^\n]", nome_procurado);
   while(i <= atual && !encontrado){
      if(strcmp(pacientes[i].nome, nome_procurado) == 0){
         printf("\nPaciente encontrado, segue dados:\n");
         printf("\nNome:%s\n", pacientes[i].nome);
         printf("Idade: %hd\n", pacientes[i].idade);
         printf("Peso: %.2f\n", pacientes[i].peso);
         for(short j = 0; j < pacientes[i].quantidade;j++){
            printf("Remedio %hd: %s\n", j+1, pacientes[i].remedio[j].nome);
            printf("Horario de aplicação: %d\n", pacientes[i].remedio[j].hora);
            printf("Data inicio da aplicação: %d/%d/%d\n", 
            pacientes[i].remedio[j].inicio.dia,
            pacientes[i].remedio[j].inicio.mes, 
            pacientes[i].remedio[j].inicio.ano);
         }
         encontrado = 1;
      }
      i++;
   }
   if (encontrado == 0)
      printf("não encontrado");
}

void lista_pacientes(pacientes_t pacientes[], short atual){
   
   for(int i = 0;i < atual;i++){
      printf("\nNome:%s\n", pacientes[i].nome);
      printf("Idade: %hd\n", pacientes[i].idade);
      printf("Peso: %.2f\n", pacientes[i].peso);
      for(short j = 0; j < pacientes[i].quantidade;j++){
         printf("Remedio %hd: %s\n", j+1, pacientes[i].remedio[j].nome);
         printf("Horario de aplicação: %d\n", pacientes[i].remedio[j].hora);
         printf("Data inicio da aplicação: %d/%d/%d\n", 
         pacientes[i].remedio[j].inicio.dia,
         pacientes[i].remedio[j].inicio.mes, 
         pacientes[i].remedio[j].inicio.ano);
      }
  }
}