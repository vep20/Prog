#include "libAgenda.h"
#include <stdio.h>

int main(){
    struct agenda age;
    struct compromisso comp;
    char comando_saida='o';
    int ano;

    scanf("%d",&ano); //entrada do valor de ano
    age = criaAgenda(ano);

    while (comando_saida!='s'){ //laço com criterio de parada dado pelo usuario
        if (!leCompromisso(&age,&comp))
            printf("Data e/ou hora invalidos, compromisso nao inserido\n");
        
        else {
            if (!verificaDisponibilidade(&age,&comp))
                printf ("Data/Hora ocupada, compromisso nao inserido\n");
            else{
                marcaCompromisso(&age,&comp);
                printf("Compromisso inserido com sucesso!\n");
            }
        }
        scanf(" %c",&comando_saida);
    }
    listaCompromissos(&age);
	return 0;
}