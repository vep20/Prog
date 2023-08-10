/* 
 * Feito por Marcos Castilho em 06/04/2023
 * para a disciplina CI1001 - Programacao 1
 * obs.: a funcao obtemDiaDoAno foi feita
 * pelo prof. Andre Gregio.
 */

#include <stdio.h>
#include <time.h>
#include "libAgenda.h"

#define LIVRE 0
#define OCUPADA 1

int obtemDiaDoAno(struct data d){
    struct tm tipodata={0};
    time_t segundos;
    int dia_do_ano;

    tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes - 1;
    tipodata.tm_year = d.ano - 1900;
    tipodata.tm_isdst = -1;
    tipodata.tm_hour = 0;

    /* converte data para epoca, isto eh, segundos desde 1970 */
    segundos = mktime(&tipodata);

    /* converte epoca em data, obtendo assim automaticamente
     * o campo 'dia do ano' (tm_yday) que sera o indice do
     * vetor necessario para marcar um compromisso */
    tipodata = *localtime(&segundos);

    /* da reconversao da data, obtem o dia do ano, um numero
     * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;

    return dia_do_ano;
}

struct agenda criaAgenda(int ano){
	struct agenda nova_agenda;
	nova_agenda.ano=ano;
	for(int dia=0;dia<DIAS_DO_ANO;dia++){
		for(int hora=0;hora<HORAS_DO_DIA;hora++){
			nova_agenda.agenda_do_ano[dia].horas[hora]=0;
		}
	}
	return nova_agenda;
}	

int obtemAno(struct agenda *ag){
	return ag->ano;
}

int obtemHora(struct compromisso *compr){
	return compr->hora_compr;
}

int validaData(struct agenda *ag, struct data *d){
	int v[]={31,28,31,30,31,30,31,31,30,31,30,31};

	if(d->mes<1 || d->mes>12)
		return 0;
	else if (d->dia<1 || d->dia>v[d->mes-1])
		return 0;
	else if(d->ano != obtemAno(ag))
		return 0;
	else 
		return 1;
}

int validaHora(struct compromisso *compr){
	if(obtemHora(compr) < 0 || obtemHora(compr) >= HORAS_DO_DIA)
		return 0;
	else
		return 1;
}

int leCompromisso(struct agenda *ag, struct compromisso *compr){	
	scanf("%d",&compr->data_compr.dia);
	scanf("%d",&compr->data_compr.mes);
	scanf("%d",&compr->data_compr.ano);
	scanf("%d",&compr->hora_compr);

	if(validaData(ag,&compr->data_compr) && validaHora(compr))
		return 1;
	else
		return 0;
}

void marcaCompromisso(struct agenda *ag, struct compromisso *compr){
	int i = obtemDiaDoAno(compr->data_compr);
	ag->agenda_do_ano[i].horas[compr->hora_compr]=OCUPADA;
}

int verificaDisponibilidade(struct agenda *ag, struct compromisso *compr){
	int i = obtemDiaDoAno(compr->data_compr);
	if (ag->agenda_do_ano[i].horas[compr->hora_compr]==OCUPADA)
		return 0;
	else 
		return 1;
}

void listaCompromissos(struct agenda *ag){ 
	for(int i=0;i < DIAS_DO_ANO;i++){
		for(int j=0;j < HORAS_DO_DIA;j++){
			if (ag->agenda_do_ano[i].horas[j]==OCUPADA){
				printf ("dia: %3d, ", i);
				printf ("ano: %4d, ", obtemAno (ag));
				printf ("hora: %2d, compromisso!\n",j);
			}
		}
	}
} 