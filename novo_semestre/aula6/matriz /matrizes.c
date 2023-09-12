#include <stdio.h>

void le_matriz(int m[][5]){
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            scanf("%d", &m[i][j]);
}

void soma_matrizes(int s[][5], int m[][5], int n[][5]){
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            s[i][j] = m[i][j] + n[i][j]; 
}

void multiplica_matrizes(int result[][5], int m1[][5], int m2[][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 5; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void imprime_matriz(int m[][5]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(){
    int m[5][5], n[5][5], soma[5][5], multiplicacao[5][5];    

    printf("Digite os valores da matriz m:\n");
    le_matriz(m);

    printf("Digite os valores da matriz n:\n");
    le_matriz(n);
    
    soma_matrizes(soma, m, n);
    multiplica_matrizes(multiplicacao, m, n);

    printf("Soma:\n");
    imprime_matriz(soma);

    printf("Multiplicação:\n");
    imprime_matriz(multiplicacao);

    return 0;
}
