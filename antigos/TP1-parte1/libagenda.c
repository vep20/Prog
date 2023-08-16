#include <stdio.h>
#include <stdlib.h>
#include "libagenda.h"

agenda_t* cria_agenda(){
    
    return agenda;  
}


/*compromisso_t* cria_compromisso (horario_compromisso_t hc, int id,  char* descricao);

void destroi_agenda(agenda_t* agenda);

int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr);

int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr);

void imprime_agenda_mes(agenda_t* agenda);

int mes_atual_agenda(agenda_t *agenda);

void prim_mes_agenda(agenda_t* agenda);

int prox_mes_agenda(agenda_t* agenda);

int ant_mes_agenda(agenda_t* agenda);

compromisso_t* compr_agenda(agenda_t* agenda, int dia);

compromisso_t* prox_compr(compromisso_t* compr);

horario_compromisso_t hc_compr(compromisso_t* compr); 
int id_compr(compromisso_t* compr); 
char* descricao_compr(compromisso_t* compr);

void imprime_agenda_mes(agenda_t* agenda);
