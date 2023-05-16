#include "libAgenda.h"

int main(){
	char comando_saida;
    struct agenda age;
    struct compromisso comp;

    printf("Entre com o ano:\n");
    scanf("%d\n",&age.ano);
    age = criaAgenda(age.ano);

    printf("Entre com dia, mes, ano, hora:\n");
    comp = leCompromisso();
    validaData(comp.data_compr,age);

    printf("Digite um char qualquer ou s para sair\n");
    scanf(" %c",&comando_saida);
    

    while (comando_saida!='s'){


        listaCompromissos(age);
        printf("Digite um char qualquer ou s para sair\n");
        scanf(" %c",&comando_saida);
    }
	return 0;
}
