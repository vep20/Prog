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

struct medicamentos_t cadastra_medicamento(short i);

struct pacientes_t cadastrar_paciente();

void busca_paciente(pacientes_t pacientes[], short atual);

void lista_pacientes(pacientes_t pacientes[], short atual);