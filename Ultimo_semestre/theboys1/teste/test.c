#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "execucao.h" // Inclui as funções e definições fornecidas

int main() {
    // Planta a semente randômica
    srand(time(NULL));

    printf("==== Início dos Testes ====\n");

    // Teste 1: Criação e destruição do mundo completo
    printf("\n[Teste 1] Criação e destruição de um mundo completo...\n");
    struct mundo *m = cria_mundo();
    if (!m) {
        fprintf(stderr, "Falha ao criar o mundo!\n");
        return EXIT_FAILURE;
    }

    inicia_mundo(m);
    printf("Mundo inicializado com sucesso!\n");
    printf("Tamanho do mundo: %d x %d\n", m->TamanhoMundo->x, m->TamanhoMundo->y);
    printf("Número de heróis: %d\n", m->nherois);
    printf("Número de bases: %d\n", m->nbases);
    printf("Número de missões: %d\n", m->nmissoes);

    destroi_mundo(m);
    printf("Mundo destruído com sucesso!\n");

    // Teste 2: Criação de múltiplos mundos
    printf("\n[Teste 2] Criação de múltiplos mundos simultaneamente...\n");
    struct mundo *mundo1 = cria_mundo();
    struct mundo *mundo2 = cria_mundo();

    if (!mundo1 || !mundo2) {
        fprintf(stderr, "Falha ao criar mundos adicionais!\n");
        return EXIT_FAILURE;
    }

    inicia_mundo(mundo1);
    inicia_mundo(mundo2);

    printf("Mundos 1 e 2 inicializados com sucesso!\n");

    destroi_mundo(mundo1);
    destroi_mundo(mundo2);
    printf("Mundos 1 e 2 destruídos com sucesso!\n");

    // Teste 3: Operações específicas em heróis
    printf("\n[Teste 3] Criação, manipulação e destruição de heróis...\n");
    int total_herois = 10;
    struct heroi *herois = malloc(sizeof(struct heroi) * total_herois);
    if (!herois) {
        fprintf(stderr, "Falha ao alocar memória para heróis!\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < total_herois; i++) {
        herois[i] = inicia_heroi(i);
        printf("Herói %d criado com paciência %d e velocidade %d.\n", 
            herois[i].ID, herois[i].paciencia, herois[i].velocidade);
    }

    printf("Manipulando heróis...\n");
    herois[0].experiencia += 100;
    printf("Herói 0 agora tem %d experiência.\n", herois[0].experiencia);

    destroi_herois(herois, total_herois);
    printf("Heróis destruídos com sucesso!\n");

    // Teste 4: Operações específicas em bases
    printf("\n[Teste 4] Criação, manipulação e destruição de bases...\n");
    int total_bases = 5;
    struct base *bases = malloc(sizeof(struct base) * total_bases);
    if (!bases) {
        fprintf(stderr, "Falha ao alocar memória para bases!\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < total_bases; i++) {
        bases[i] = inicia_base(i);
        printf("Base %d criada com lotação %d na posição (%d, %d).\n",
            bases[i].ID, bases[i].lotacao, bases[i].lb->x, bases[i].lb->y);
    }

    printf("Manipulando bases...\n");
    bases[1].lotacao += 5;
    printf("Base 1 agora tem lotação %d.\n", bases[1].lotacao);

    destroi_bases(bases, total_bases);
    printf("Bases destruídas com sucesso!\n");

    // Teste 5: Operações específicas em missões
    printf("\n[Teste 5] Criação, manipulação e destruição de missões...\n");
    int total_missoes = 7;
    struct missao *missoes = malloc(sizeof(struct missao) * total_missoes);
    if (!missoes) {
        fprintf(stderr, "Falha ao alocar memória para missões!\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < total_missoes; i++) {
        missoes[i] = inicia_missao(i);
        printf("Missão %d criada com perigo %d na posição (%d, %d).\n", 
            missoes[i].ID, missoes[i].perigo, missoes[i].lm->x, missoes[i].lm->y);
    }

    printf("Manipulando missões...\n");
    missoes[2].perigo += 20;
    printf("Missão 2 agora tem perigo %d.\n", missoes[2].perigo);

    destroi_missoes(missoes, total_missoes);
    printf("Missões destruídas com sucesso!\n");

    // Teste 6: Stress test com muitos elementos
    printf("\n[Teste 6] Stress test com muitos elementos...\n");
    int muitos_herois = 1000, muitas_bases = 500, muitas_missoes = 2000;
    struct mundo *stress_mundo = cria_mundo();
    if (!stress_mundo) {
        fprintf(stderr, "Falha ao criar mundo para stress test!\n");
        return EXIT_FAILURE;
    }

    stress_mundo->nherois = muitos_herois;
    stress_mundo->nbases = muitas_bases;
    stress_mundo->nmissoes = muitas_missoes;

    if (!cria_herois(stress_mundo) || !cria_bases(stress_mundo) || !cria_missoes(stress_mundo)) {
        fprintf(stderr, "Falha ao inicializar elementos para stress test!\n");
        destroi_mundo(stress_mundo);
        return EXIT_FAILURE;
    }

    printf("Stress test inicializado com %d heróis, %d bases, e %d missões.\n",
        muitos_herois, muitas_bases, muitas_missoes);

    destroi_mundo(stress_mundo);
    printf("Stress test finalizado com sucesso!\n");

    printf("\n==== Testes Concluídos ====\n");
    return EXIT_SUCCESS;
}
