<<<<<<< HEAD
// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Definição da interface do TAD - NÃO ALTERAR

#ifndef LISTA
#define LISTA

// estrutura de um item da lista
struct item_t;

// estrutura de uma lista
struct lista_t;

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL em erro.
struct lista_t *lista_cria ();

// Remove todos os itens da lista e libera a memória.
// Retorno: NULL.
struct lista_t *lista_destroi (struct lista_t *lst);

// Nas operações insere/retira/consulta/procura, a lista inicia na
// posição 0 (primeiro item) e termina na posição TAM-1 (último item).

// Insere o item na lista na posição indicada;
// se a posição for além do fim da lista ou for -1, insere no fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int lista_insere (struct lista_t *lst, int item, int pos);

// Retira o item da lista da posição indicada.
// se a posição for além do fim da lista ou for -1, retira do fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int lista_retira (struct lista_t *lst, int *item, int pos);

// Informa o valor do item na posição indicada, sem retirá-lo.
// se a posição for além do fim da lista ou for -1, consulta do fim.
// Retorno: número de itens na lista ou -1 em erro.
int lista_consulta (struct lista_t *lst, int *item, int pos);

// Informa a posição da 1ª ocorrência do valor indicado na lista.
// Retorno: posição do valor ou -1 se não encontrar ou erro.
int lista_procura (struct lista_t *lst, int valor);

// Informa o tamanho da lista (o número de itens presentes nela).
// Retorno: número de itens na lista ou -1 em erro.
int lista_tamanho (struct lista_t *lst);

// Imprime o conteúdo da lista do inicio ao fim no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois, sem newline.
void lista_imprime (struct lista_t *lst);
=======
/*
 * TAD lista
 * -> versao com lista ligada com nodo cabeca
 * Autores:
 *    André Ricardo Abed Gregio
 *    Marcos Alexandre Castilho
 *    Luis Carlos Erpen de Bona
 *
 * Versao 1.0.0 de 22/05/2023
 * Versao 2.0.0 de 08/07/2024
 * Versao 3.0.0 de 02/10/2025
*/

#ifndef _lista_t_H
#define _lista_t_H

struct nodo;
struct lista;

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
struct lista *lista_cria ();

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista);

/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_inicio (struct lista *lista, int chave);

/*
 * Insere chave no final da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_fim (struct lista *lista, int chave);

/*
 * Insere chave em ordem na lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_ordenado (struct lista *lista, int chave);

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_inicio (struct lista *lista, int *chave);

/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_fim (struct lista *lista, int *chave);

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a cheve esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_ordenado (struct lista *lista, int chave);

/*
  Retorna 1 se a lista está vazia e 0 caso contrário.
*/
int lista_vazia (struct lista *lista);

/*
  Retorna o numero de elementos da lista
*/
int lista_tamanho (struct lista *lista);

/*
  Retorna 1 se o elemento chave esta presente na lista,
  caso contrário retorna 0.
*/
int lista_pertence (struct lista *lista, int chave);

/*
 * As funcoes abaixo implementam um iterador que vao permitir o usuario
 * de uma lista percorre-la, sem conhecer sua estrutura.
 *
 * Em conjunto, elas simulam um laço, sendo a inicializacao deste
 * a funcao lista_inicia_iterador e o incremento sendo a funcao
 * lista_incrementa_iterador.
 *
 * O ponteiro ptr da struct (iterador) eh inicializado apontando
 * para o primeiro elemento e incrementado ate' o ultimo elemento 
 * da lista.
 *
 * Ver exemplo de uso em testa_lista.c (funcao testa_imprimir_lista)
*/

/*
 * Inicializa ptr usado na funcao incrementa_iterador.
 * A funcao main deve garantir que a lista nao eh vazia.
*/
void lista_inicia_iterador (struct lista *lista);

/*
 * Devolve no parametro *chave o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro da lista).
*/
int lista_incrementa_iterador (struct lista *lista, int *chave);
>>>>>>> 79c6643f210888d3da082903eb3766d1d1dd7b99

#endif
