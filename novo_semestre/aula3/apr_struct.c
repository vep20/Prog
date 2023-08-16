#include <stdio.h>
#include <stdiolib.h>
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
   medicamento_t remedio[3];
}pacientes_t;

struct cadastrar_paciente(){
   

   return cadastro;
};

void buscar_paciente(paciente__t paciente){

};

/*EXEMPLO DADO EM AULA:	
pacientes_t paciente;
strcpy(paciente.nome,"ana"); // para definir string sem necessidade de colocar um caracter por vez
paciente.idade = 23;
paciente.peso = 85.7;*/

int main(){
   char saida = n;
   paciente_t paciente;
   short comando;

   while(saida !=s){
      printf("Digite 1 para cadastrar um paciente ou 2 para buscar ");
      scanf("%d",&comando);
      if (comando = 1){
         
      }
      else if (comando = 2)
         busca_paciente(paciente);
      else 
         printf("comando invalido");
             

      printf("Digite 's' se quiser finalizar o programa ou qualquer outro caracter se quiser continuar");    
      scanf("%s",&saida);
   } 
   imprime paciente(
   return 0;
}
