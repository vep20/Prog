#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void teste_criar()
{
    printf("Teste 1: Criar fila\n");
    struct fila_t *f = fila_cria();
    if (f == NULL)
        printf("  ERRO: fila_cria retornou NULL!\n");
    else
        printf("  OK: fila criada com sucesso\n");
   
    printf("  Tamanho esperado = 0, obtido = %d\n", fila_tamanho(f));

    f = fila_destroi(f);
    printf("\n");
}

void teste_retira_vazia()
{
    printf("Teste 2: Retirar de fila vazia\n");
    struct fila_t *f = fila_cria();

    int x;
    if (!fila_retira(f, &x))
        printf("  OK: Retirar de fila vazia não deu segfault\n");
    else
        printf("  ERRO: Retirou item de fila vazia!\n");

    f = fila_destroi(f);
    printf("\n");
}

void teste_inserir()
{
    printf("Teste 3: Inserir elementos\n");
    struct fila_t *f = fila_cria();

    fila_insere(f, 10);
    fila_insere(f, 20);
    fila_insere(f, 30);

    printf("  Esperado: tamanho = 3, obtido = %d\n", fila_tamanho(f));
    printf("  Conteúdo da fila:\n");
    fila_imprime(f);

    f = fila_destroi(f);
    printf("\n");
}

void teste_retirar()
{
    printf("Teste 4: Retirar elementos na ordem correta\n");
    struct fila_t *f = fila_cria();

    fila_insere(f, 100);
    fila_insere(f, 200);
    fila_insere(f, 300);

    printf("  Retirando itens:\n");

    int x;
    while (fila_retira(f, &x))
        printf("    Retirei: %d\n", x);

    printf("  Fila agora tem tamanho = %d\n", fila_tamanho(f));

    f = fila_destroi(f);
    printf("\n");
}

void teste_destroi_nula()
{
    printf("Teste 5: Destruir fila vazia\n");
    struct fila_t *f = fila_cria();
    f = fila_destroi(f);

    if (f == NULL)
        printf("  OK: fila_destroi retornou NULL\n");
    else
        printf("  ERRO: fila_destroi não aterrrou ponteiro\n");

    printf("\n");
}

void teste_destroi_com_itens()
{
    printf("Teste 6: Destruir fila COM itens\n");
    struct fila_t *f = fila_cria();

    for (int i = 0; i < 5; i++)
        fila_insere(f, i);

    f = fila_destroi(f);

    if (f == NULL)
        printf("  OK: destruiu fila (verificar valgrind)\n");
    else
        printf("  ERRO: ponteiro não está NULL\n");

    printf("\n");
}

int main()
{
    teste_criar();
    teste_retira_vazia();
    teste_inserir();
    teste_retirar();
    teste_destroi_nula();
    teste_destroi_com_itens();

    printf("Todos os testes executados.\n");
    return 0;
}
