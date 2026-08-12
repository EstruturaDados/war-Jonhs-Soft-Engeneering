#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void cadastrarTerritorios(Territorio *territorios, int quantidade) {
    int i;

    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");

    for (i = 0; i < quantidade; i++) {
        printf("--- Território %d ---\n", i + 1);

        printf("Nome: ");
        if (fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin) != NULL) {
            territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        } else {
            territorios[i].nome[0] = '\0';
        }

        printf("Cor do exército: ");
        if (fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin) != NULL) {
            territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        } else {
            territorios[i].cor[0] = '\0';
        }

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer();

        printf("\n");
    }
}

void exibirTerritorios(Territorio *territorios, int quantidade) {
    int i;

    printf("\n=== MAPA ATUAL ===\n");
    printf("%-15s | %-12s | %-8s\n", "NOME", "COR", "TROPAS");
    printf("--------------------------------------------\n");

    for (i = 0; i < quantidade; i++) {
        printf("%-15s | %-12s | %-8d\n",
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }

    printf("--------------------------------------------\n\n");
}

int sortearDado(void) {
    return (rand() % 6) + 1;
}

int simularAtaque(Territorio *territorios, int atacante, int defensor) {
    int dadoAtaque, dadoDefesa;
    int vencedor;

    if (atacante == defensor) {
        printf("O atacante e o defensor não podem ser o mesmo território.\n");
        return 0;
    }

    if (territorios[atacante].tropas <= 0 || territorios[defensor].tropas <= 0) {
        printf("Território inválido para ataque.\n");
        return 0;
    }

    dadoAtaque = sortearDado();
    dadoDefesa = sortearDado();

    printf("\n=== BATALHA ENTRE %s E %s ===\n",
           territorios[atacante].nome,
           territorios[defensor].nome);
    printf("Dado do atacante: %d\n", dadoAtaque);
    printf("Dado do defensor: %d\n", dadoDefesa);

    vencedor = (dadoAtaque >= dadoDefesa);

    if (vencedor) {
        territorios[defensor].tropas--;
        printf("Resultado: atacante venceu! %s perdeu 1 tropa.\n",
               territorios[defensor].nome);

        if (territorios[defensor].tropas <= 0) {
            territorios[defensor].tropas = 0;
            printf("Território conquistado: %s foi tomado por %s!\n",
                   territorios[defensor].nome,
                   territorios[atacante].cor);
            strcpy(territorios[defensor].cor, territorios[atacante].cor);
            territorios[defensor].tropas = 1;
            printf("O território %s agora pertence à cor %s com 1 tropa.\n",
                   territorios[defensor].nome,
                   territorios[defensor].cor);
            return 1;
        }
    } else {
        printf("Resultado: defensor venceu! Empate favorece o atacante, mas desta vez o defensor ganhou a rodada.\n");
    }

    printf("Status atual: %s = %d tropas | %s = %d tropas\n",
           territorios[atacante].nome,
           territorios[atacante].tropas,
           territorios[defensor].nome,
           territorios[defensor].tropas);

    return 0;
}

int main(void) {
    Territorio *territorios;
    int opcao;
    int atacante, defensor;

    srand((unsigned int)time(NULL));

    territorios = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memoria para os territórios.\n");
        return 1;
    }

    cadastrarTerritorios(territorios, TOTAL_TERRITORIOS);
    exibirTerritorios(territorios, TOTAL_TERRITORIOS);

    printf("=== FASE DE ATAQUE ===\n");
    printf("Digite 1 para continuar atacando ou 0 para sair: ");
    scanf("%d", &opcao);
    limparBuffer();

    while (opcao != 0) {
        printf("Escolha o território atacante (1 a %d): ", TOTAL_TERRITORIOS);
        scanf("%d", &atacante);
        limparBuffer();

        printf("Escolha o território defensor (1 a %d): ", TOTAL_TERRITORIOS);
        scanf("%d", &defensor);
        limparBuffer();

        atacante--;
        defensor--;

        if (atacante < 0 || atacante >= TOTAL_TERRITORIOS ||
            defensor < 0 || defensor >= TOTAL_TERRITORIOS) {
            printf("Escolha inválida. Use números entre 1 e %d.\n", TOTAL_TERRITORIOS);
        } else {
            simularAtaque(territorios, atacante, defensor);
            exibirTerritorios(territorios, TOTAL_TERRITORIOS);
        }

        printf("Digite 1 para continuar atacando ou 0 para sair: ");
        scanf("%d", &opcao);
        limparBuffer();
    }

    printf("\n=== FIM DA SIMULAÇÃO ===\n");
    free(territorios);
    return 0;
}