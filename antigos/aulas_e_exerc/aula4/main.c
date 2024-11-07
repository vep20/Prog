#include <stdio.h>
#include <string.h>
#include "hospital.h" 

int main(){
   char saida = 'n';
   pacientes_t paciente[15];
   short comando, atual;
   
   atual = 0;
   while(saida != 's'){
      printf("\nDigite 1 para cadastrar um paciente ou 2 para busca-lo:\n");
      scanf("%hd",&comando);

      if (comando == 1 && atual < 15){
         paciente[atual] = cadastrar_paciente();
         atual++;
      }
      else if (comando == 2)
         busca_paciente(paciente,atual);
      else 
         printf("comando invalido");

                 
      printf("\nDigite 's' se quiser finalizar o programa ou qualquer outro caracter se quiser continuar:\n");    
      scanf(" %c",&saida);
   } 
 
   lista_pacientes(paciente,atual);
   return 0;
}