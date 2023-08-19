#include <stdio.h>
#include <string.h>

//string são vetores de caracteres.
//estudo de struct e como utliza-las em C
//%s é utlizado para imprimir strings

typedef struct data_t{
   int dia;
   int mes;
   int ano;
}data_t;

typedef struct medicamentos_t{
   char nome[50];
   int hora;
   data_t inicio;
}medicamentos_t;

typedef struct pacientes_t{
   char nome[50];
   short idade;
   float peso;
   medicamentos_t remedio[3];
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

int buscar_paciente(){

};

/*void lista_paciente(){
   
   for(i=0;i
}*/

/*EXEMPLO DADO EM AULA:	
pacientes_t paciente;
strcpy(paciente.nome,"ana"); // para definir string sem necessidade de colocar um caracter por vez
paciente.idade = 23;
paciente.peso = 85.7;*/

int main(){
   char saida = "n";
   pacientes_t paciente[15];
   short comando, atual = 0;
   
   while(saida != "s"){
      printf("Digite 1 para cadastrar um paciente ou 2 para busca-lo ");
      scanf("%d",&comando);

      if (comando == 1 && atual < 15){
         paciente[atual] = cadastrar_paciente();
         atual++;
      }

      /*else if (comando = 2)
         busca_paciente(paciente);
      else 
         printf("comando invalido");*/

                 
      printf("Digite 's' se quiser finalizar o programa ou qualquer outro caracter se quiser continuar");    
      scanf("%s",&saida);
   } 
   
   //lista_pacientes(paciente,atual);
   return 0;
}

