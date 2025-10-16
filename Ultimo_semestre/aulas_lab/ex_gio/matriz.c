#include <stdio.h>


int main(){
    int lin, col;
    do{
        printf ("Defina um valor para linhas e para colunas\n");
        printf ("Obs valores devem estar entre 1 e 4\n");
        scanf ("%d %d", &lin, &col);
        if ((lin < 1) || (lin > 4) || (col < 1) || (col > 4))
            printf("Valores foras do intervalo definido\n");
    } while((lin < 1) || (lin > 4) || (col < 1) || (col > 4));    
    return 0;   
}

