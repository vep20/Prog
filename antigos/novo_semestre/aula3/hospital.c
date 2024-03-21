#include <stdio.h>
#include <string.h>

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
   short quantidade;
   medicamentos_t remedio[3];
}pacientes_t;

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

int main(){
   char saida = 'n';
   pacientes_t paciente[15];
   short comando, atual;
   
   atual = 0;
   while(saida != 's'){
      printf("Digite 1 para cadastrar um paciente ou 2 para busca-lo:\n");
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

