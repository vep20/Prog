#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libAgenda.h"
#define HORAS_DO_DIA 24
#define DIAS_DO_ANO 365

/* esta função transforma uma data lida pelo usuário para uma struct data
 * em uma data do tipo struct tm definida pela biblioteca time.h. 
 * Esta data é então transformada em segundos com a função mktime, para que
 * os outros membros da struct sejam preenchidos automaticamente, e então
 * reconvertida para uma data do tipo struct tm, reescrevendo a variável 
 * original. Com isso, pode-se obter o membro tm_yday, que representa o
 * dia do ano representado pela data: um inteiro entre 0 e 364 */

int obtemDiaDoAno(struct data d) {
	struct tm tipodata;
	time_t segundos;
	int dia_do_ano;

	tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes-1;
    tipodata.tm_year = d.ano-1900;
    tipodata.tm_isdst = -1;
	tipodata.tm_hour = 0;

	/* converte data para época, isto é, segundos desde 1970 */
	segundos = mktime(&tipodata);
	/* converte época em data, obtendo assim automaticamente
	 * o campo 'dia do ano' (tm_yday) que será o índice do
	 * vetor necessário para marcar um compromisso */
	tipodata = *localtime(&segundos);
	/* da reconversão da data, obtém o dia do ano, um número
	 * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;
	
	return dia_do_ano;
}

struct agenda criaAgenda(int ano){
	struct agenda agenda_inicial; 
	for(int i=0;i <= DIAS_DO_ANO;++i){
		for(int j=0;j < HORAS_DO_DIA;++j){
			agenda_inicial.agenda_do_ano[i].horas[j]=0;
		}
	}
	return agenda_inicial;
}	

struct compromisso leCompromisso(){
	struct compromisso compr;
	scanf("%d",compr.data_compr.dia);
	scanf("%d",compr.data_compr.mes);
	scanf("%d",compr.data_compr.ano);
	scanf("%d",compr.hora_compr);
	return compr;
}

int validaData(struct data d, struct agenda ag){
	int v[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (d.dia<1 && d.dia>31){
		return 0;
	}
	else if(d.mes>12 && d.mes<1 && d.dia > v[d.mes]){

	}

}

/*void listaCompromissos(){
	struct agenda agenda_final; 
	for(int i=0;i <= DIAS_DO_ANO;++i){
		for(int j=0;j < HORAS_DO_DIA;++j){
			if (agenda_final.agenda_do_ano[i].horas[j]=1){
				
				printf("");
			}
		}
	}
} */
