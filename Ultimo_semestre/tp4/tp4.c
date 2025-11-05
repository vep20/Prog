<<<<<<< HEAD
// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Programa de teste - NÃO ALTERAR

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define TAMANHO 1000000	// tamanho da lista "imensa"

//------------------------------------------------------------------------------

// imprime o conteúdo da lista, com informações adicionais
void lista_print (char *nome, struct lista_t *l){
  int tam ;

  printf ("%s: [ ", nome) ;
  lista_imprime (l) ;
  tam = lista_tamanho (l) ;
  printf (" ] (%d %s)\n", tam, tam == 1 ? "item" : "itens") ;
}

//------------------------------------------------------------------------------

// imprime o valor encontrado na posição "pos" da lista "l"
void imprime_valor (struct lista_t *l, int pos){
  int valor, status ;

  status = lista_consulta (l, &valor, pos) ;
  printf ("Valor na posição %d: ", pos) ;
  if (status >= 0)
    printf ("%d\n", valor) ;
  else
    printf ("não encontrado\n") ;
}

//------------------------------------------------------------------------------

// imprime a posição do valor "valor" na lista "l"
void imprime_posicao (struct lista_t *l, int valor){
  int pos ;

  pos = lista_procura (l, valor) ;
  printf ("Posição do valor %d: ", valor) ;
  if (pos >= 0)
    printf ("%d\n", pos) ;
  else
    printf ("não encontrado\n") ;
}

//------------------------------------------------------------------------------

// imprime mensagem de erro e encerra execução
void erro (char *msg){
  fprintf (stderr, "ERRO: %s\n", msg) ;
  exit (1) ;
}

//------------------------------------------------------------------------------

int main (){
  struct lista_t *l1, *l2;
  int status, pos, valor, tam;

  // cria lista l1
  printf ("Criando lista:\n") ;
  l1 = lista_cria () ;
  if (! l1)
    erro ("não criou a lista l1") ;
  lista_print ("L1", l1) ;
  printf ("\n") ;

  printf ("Inserindo itens:\n") ;

  // insere itens [ 5 6 7 ] no início de l1 e imprime
  for (int i = 5; i <= 7; i++){
    printf ("Inserindo %d no início\n", i) ;
    status = lista_insere (l1, i, 0) ;
    if (status < 0)
      erro ("não inseriu no início da lista l1") ;
    lista_print ("L1", l1) ;
  }

  // insere itens [ 6 7 8] no final de l1 e imprime
  for (int i = 6; i <= 8; i++){
    printf ("Inserindo %d no fim\n", i) ;
    status = lista_insere (l1, i, -1) ;
    if (status < 0)
      erro ("não inseriu no final da lista l1") ;
    lista_print ("L1", l1) ;
  }
  
  // insere itens [ 1 2 3] no meio de l1 e imprime
  for (int i = 1; i <= 3; i++){
    pos = lista_tamanho (l1) / 2 ;
    printf ("Inserindo %d no meio (posição %d)\n", i, pos) ;
    status = lista_insere (l1, i, pos) ;
    if (status < 0)
      erro ("não inseriu no meio da lista l1") ;
    lista_print ("L1", l1) ;
  }

  printf ("\n") ;

  // consulta e imprime todas as posições da lista
  printf ("Consultando posições:\n") ;
  lista_print ("L1", l1) ;
  for (int i = 0;  i <= lista_tamanho (l1) ; i++)
    imprime_valor (l1, i) ;
  printf ("\n") ;

  // procura valores 5 6 7 8 9 na lista
  printf ("Procurando valores:\n") ;
  lista_print ("L1", l1) ;
  for (int i = 4;  i <= 9 ; i++)
    imprime_posicao (l1, i) ;
  printf ("\n") ;

  printf ("Retirando itens:\n") ;

  // retira item na 1ª posição da lista
  lista_print ("L1", l1) ;
  status = lista_retira (l1, &valor, 0) ;
  if (status >= 0)
    printf ("Retirou valor %d do início\n", valor) ;
  else
    erro ("não retirou valor do início da lista l1") ;
  lista_print ("L1", l1) ;

  // retira item na 3ª posição da lista
  pos = 5 ;
  status = lista_retira (l1, &valor, pos) ;
  if (status >= 0)
    printf ("Retirou valor %d da posição %d\n", valor, pos) ;
  else
    erro ("não retirou valor do meio da lista l1") ;
  lista_print ("L1", l1) ;

  // retira item na última posição da lista
  status = lista_retira (l1, &valor, -1) ;
  if (status >= 0)
    printf ("Retirou valor %d do fim\n", valor) ;
  else
    erro ("não retirou valor do fim da lista l1") ;
  lista_print ("L1", l1) ;
  printf ("\n") ;

  
  // esvazia lista e a destroi
  printf ("Esvaziando a lista:\n") ;
  lista_print ("L1", l1) ;
  while (lista_tamanho (l1) > 0){
    status = lista_retira (l1, &valor, 0) ;
    if (status >= 0)
      printf ("Retirou %d\n", valor) ;
    else
      erro ("não retirou valor do inicio da lista l0") ;
    lista_print ("L1", l1) ;
  }
  printf ("Lista vazia!\n") ;
  printf ("\n") ;

  // destroi a lista
  printf ("Destruindo a lista:\n") ;
  l1 = lista_destroi (l1) ;
  if (l1)
    erro ("não destruiu a lista") ;
  printf ("\n") ;

  printf ("Testando com lista imensa (%d itens):\n\n", TAMANHO) ;

  // cria lista l2
  printf ("Inserindo itens:\n") ;
  l2 = lista_cria () ;
  if (! l2)
    erro ("não criou a lista") ;
  lista_print ("L2", l2) ;

  // insere muitos itens em ordem crescente
  printf ("Inserindo %d itens no final\n", TAMANHO) ;
  for (int i = 0 ; i < TAMANHO; i++){
    status = lista_insere (l2, i, -1) ;
    if (status < 0)
      erro ("não inseriu no fim da lista") ;
  }
  printf ("Tamanho da lista: %d itens\n", lista_tamanho (l2)) ;
  printf ("\n") ;

  // consulta e imprime os valores em algumas posições
  printf ("Consultando posições:\n") ;
  imprime_valor (l2, 0) ;
  imprime_valor (l2, -1) ;
  imprime_valor (l2, TAMANHO / 2) ;
  imprime_valor (l2, TAMANHO + 1) ;
  printf ("\n") ;

  // procura e imprime as posições de alguns valores
  printf ("Procurando valores:\n") ;
  imprime_posicao (l2, 3715) ;
  imprime_posicao (l2, -2) ;
  imprime_posicao (l2, TAMANHO / 2) ;
  imprime_posicao (l2, TAMANHO + 1) ;
  printf ("\n") ;

  // destroi a lista
  printf ("Destruindo a lista:\n") ;
  l2 = lista_destroi (l2) ;
  if (l2)
    erro ("não destruiu a lista") ;
  printf ("\n") ;

  // testa operações inválidas sobre lista ou valor inexistentes
  printf ("Testando operações com parâmetros inválidos:\n") ;
  l2 = lista_cria () ;

  // insere com lista NULL
  status = lista_insere (NULL, 42, 0) ;
  if (status != -1)
    erro ("lista_insere não retornou erro") ;

  // retira com lista NULL
  status = lista_retira (NULL, &valor, 0) ;
  if (status != -1)
    erro ("lista_retira não retornou erro") ;

  // retira com valor NULL
  status = lista_retira (l2, NULL, 0) ;
  if (status != -1)
    erro ("lista_retira não retornou erro") ;

  // consulta com lista NULL
  status = lista_consulta (NULL, &valor, 0) ;
  if (status != -1)
    erro ("lista_consulta não retornou erro") ;

  // consulta com valor NULL
  status = lista_consulta (l2, NULL, 0) ;
  if (status != -1)
    erro ("lista_consulta não retornou erro") ;

  // procura com lista NULL
  status = lista_procura (NULL, 0) ;
  if (status != -1)
    erro ("lista_procura não retornou erro") ;
  
  // tamanho com lista NULL
  tam = lista_tamanho (NULL) ;
  if (tam != -1)
    erro ("lista_tamanho não retornou erro") ;

  l2 = lista_destroi (l2) ;
  printf ("\n") ;

  printf ("Agora falta analisar no Valgrind\n") ;

  return (0) ;
}
=======
/* 
 * Programa para testar a liblista.
 * feito por Marcos Castilho em 05/04/2022
*/

#include <stdio.h>
#include "lista.h"
#define MAX 5

void imprimir_lista (struct lista *l){
    int chave;

    if (lista_vazia (l)){
        printf ("lista vazia\n");
        return;
    }

    lista_inicia_iterador (l);
    lista_incrementa_iterador (l,&chave);
    printf ("%d", chave);
    while (lista_incrementa_iterador (l, &chave))
        printf (" %d", chave);
    printf("\n");
}

struct lista *teste_criar_lista (){
    struct lista *l;

    if (!(l = lista_cria ()))
        fprintf (stderr, "Falha na alocacao da lista\n");

    return l;
}

void teste_lista_vazia (struct lista *l){
    if (lista_vazia (l))
        printf ("lista esta vazia");
    else
        printf ("lista nao esta vazia");
}

void teste_insere_inicio (struct lista *l, int limite){
    int i;

    for (i=1; i <= limite; i++){
        if (! lista_insere_inicio (l, i + 10)){
            printf ("Lista cheia, nao inseriu.\n");
            return;
        }
        imprimir_lista (l);
    }
}

void teste_insere_fim (struct lista *l, int limite){
    int i;

    for (i=1; i <= limite; i++){
        if (! lista_insere_fim (l, i + 10)){
            printf ("Lista cheia, nao inseriu.\n");
            return;
        }
        imprimir_lista (l);
    }
}

void teste_remove_inicio (struct lista *l){
    int chave;

    /* remove todo mundo */
    while (! lista_vazia (l))
        if (lista_remove_inicio (l, &chave))
            imprimir_lista (l);
}

void teste_remove_fim (struct lista *l){
    int chave;

    /* remove todo mundo */
   while (! lista_vazia (l))
        if (lista_remove_fim (l, &chave))
            imprimir_lista (l);
}

void teste_insere_ordenado (struct lista *l){
    lista_insere_ordenado (l, 13); imprimir_lista (l);
    lista_insere_ordenado (l, 15); imprimir_lista (l);
    lista_insere_ordenado (l, 11); imprimir_lista (l);
    lista_insere_ordenado (l, 12); imprimir_lista (l);
    lista_insere_ordenado (l, 14); imprimir_lista (l);
}

void teste_remove_ordenado (struct lista *l){
    lista_remove_ordenado (l, 13); imprimir_lista (l);
    lista_remove_ordenado (l, 15); imprimir_lista (l);
    lista_remove_ordenado (l, 11); imprimir_lista (l);
    lista_remove_ordenado (l, 12); imprimir_lista (l);
    lista_remove_ordenado (l, 14); imprimir_lista (l);
}

void teste_de_pertinencia (struct lista *l){
    lista_insere_inicio (l, 13);
    lista_insere_inicio (l, 15);
    lista_insere_inicio (l, 11);
    lista_insere_inicio (l, 12);
    lista_insere_inicio (l, 14);
    imprimir_lista (l);
    if (lista_pertence (l, 11)) printf ("11 pertence\n");
    if (lista_pertence (l, 12)) printf ("12 pertence\n");
    if (lista_pertence (l, 13)) printf ("13 pertence\n");
    if (lista_pertence (l, 14)) printf ("14 pertence\n");
    if (lista_pertence (l, 15)) printf ("15 pertence\n");
    if (! lista_pertence (l, 10)) printf ("10 nao pertence\n");
    if (! lista_pertence (l, 16)) printf ("16 nao pertence\n");
}

int main (void)
{
    struct lista *l;
    int chave;

    printf ("Teste 1: criar lista e ver se esta vazia:\n");
    printf ("Esperado: tem que imprimir mensagem 'lista esta vazia'\n");
    l = teste_criar_lista ();
    teste_lista_vazia (l);
    printf ("\n\n");

    printf ("Teste 2: tenta remover elemento com lista vazia:\n");
    printf ("Esperado: nao pode ter dado segfault\n");
    if (! lista_remove_inicio (l, &chave))
        printf ("\tOK: remover da lista vazia nao deu segfault.\n");
    printf ("\n\n");
    
    printf ("Teste 3: inserir 5 elementos no inicio:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez com o maior elemento no inicio. \n");
    printf ("\nATENCAO: se nao imprimir a lista corretamente o erro pode estar:\n");
    printf ("- ou na insercao\n");
    printf ("- ou na implementacao das funcoes que controlam o iterador\n");
    printf ("- voce pode implementar TEMPORARIAMENTE uma funcao que imprime a lista acessando os nodos diretamente, ate encontrar o problema.\n");
    teste_insere_inicio (l, MAX); 
    printf ("\n\n");

    printf ("Teste 4: esvaziar a lista retirando do inicio:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez sem o primeiro elemento\n");
    printf ("          Ao final, mostrar a mensagem 'lista vazia'\n");
    teste_remove_inicio (l); 
    printf ("\n\n");

    printf ("Teste 5: inserir 5 elementos no fim:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez com o maior elemento no fim\n");
    teste_insere_fim (l, MAX); 
    printf ("\n\n");

    printf ("Teste 6: esvaziar a lista retirando do fim:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez sem o maior elemento\n");
    printf ("          Ao final, mostrar a mensagem 'lista vazia'\n");
    teste_remove_fim (l); 
    printf ("\n\n");

    printf ("Teste 7: inserir 5 elementos em ordem:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, sempre ordenada\n");
    printf ("Esperado: tem que mostrar remover de 11 ate 15\n");
    teste_insere_ordenado (l); 
    printf ("\n\n");

    printf ("Teste 8: remover 5 elementos em ordem:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, sempre ordenada\n");
    printf ("          Ao final, mostrar a mensagem 'lista vazia'\n");
    teste_remove_ordenado (l); 
    printf ("\n\n");

    printf ("Teste 9: teste de pertinencia \n");
    printf ("Esperado: apos imprimir a lista, tem que mostrar que de 11 a 15 pertence\n");
    printf ("          E que 10 e 16 nao pertencem\n");
    teste_de_pertinencia (l); 
    printf ("\n\n");

    printf ("Teste 10: destruir uma lista com elementos:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    lista_destroi (&l);
    printf ("\n\n");

    printf ("Teste 11: destruir uma lista vazia:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    l = lista_cria ();
    lista_destroi (&l);
    printf ("\n\n");

    return 0;
}
>>>>>>> 79c6643f210888d3da082903eb3766d1d1dd7b99
