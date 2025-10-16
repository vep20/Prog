#include <stdio.h>

int main(){
    int k, atual;

    printf("Digite quantos numeros perfeitos você quer: ");
    scanf("%d",&k);
    atual = 6;

    for(int i = 0; i < k; atual++){
        int soma = 0;
        for (int multiplica = 1; multiplica <= atual/2; multiplica++){
            if(atual % multiplica == 0)
                soma = soma + multiplica; 
        }
        if (soma == atual){
            printf("%d ", atual);
            i++;
        }
    }
    printf("\n");
    return 0;
}