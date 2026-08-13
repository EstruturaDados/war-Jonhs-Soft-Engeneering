#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5
#define TOTAL_JOGADORES 2
#define TOTAL_MISSOES 5

typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

typedef struct {
    char nome[20];
    char cor[15];
    char *missao;
} Jogador;

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

void exibirMapa(Territorio *territorios, int quantidade) {
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

void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice;

    if (destino == NULL || missoes == NULL || totalMissoes <= 0) {
        return;
    }

    indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

void exibirMissao(const char *missao) {
    if (missao == NULL) {
        return;
    }

    printf("\n=== MISSÃO ===\n");
    printf("%s\n", missao);
    printf("============\n\n");
}

int contarTerritoriosPorCor(const Territorio *mapa, int tamanho, const char *cor) {
    int i;
    int total = 0;

    for (i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, cor) == 0) {
            total++;
        }
    }

    return total;
}

int contarTropasPorCor(const Territorio *mapa, int tamanho, const char *cor) {
    int i;
    int total = 0;

    for (i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, cor) == 0) {
            total += mapa[i].tropas;
        }
    }

    return total;
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    const char *cores[] = {"azul", "vermelha", "verde", "amarela", "roxa"};
    int totalCores = sizeof(cores) / sizeof(cores[0]);
    int i;

    if (missao == NULL || mapa == NULL || tamanho <= 0) {
        return 0;
    }

    if (strstr(missao, "3 territorios") != NULL || strstr(missao, "3 territórios") != NULL) {
        for (i = 0; i < totalCores; i++) {
            if (contarTerritoriosPorCor(mapa, tamanho, cores[i]) >= 3) {
                return 1;
            }
        }
        return 0;
    }

    if (strstr(missao, "vermelha") != NULL) {
        return contarTropasPorCor(mapa, tamanho, "vermelha") == 0;
    }

    if (strstr(missao, "verde") != NULL) {
        return contarTropasPorCor(mapa, tamanho, "verde") == 0;
    }

    if (strstr(missao, "azul") != NULL) {
        return contarTropasPorCor(mapa, tamanho, "azul") == 0;
    }

    if (strstr(missao, "amarela") != NULL) {
        return contarTropasPorCor(mapa, tamanho, "amarela") == 0;
    }

    return 0;
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtaque;
    int dadoDefesa;
    int tropasTransferidas;

    if (atacante == NULL || defensor == NULL) {
        printf("O ataque não pode ser realizado sem territórios válidos.\n");
        return;
    }

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Ataque inválido: só é permitido atacar territórios inimigos.\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("O território %s não possui tropa suficiente para atacar.\n", atacante->nome);
        return;
    }

    dadoAtaque = sortearDado();
    dadoDefesa = sortearDado();

    printf("\n=== BATALHA ENTRE %s E %s ===\n", atacante->nome, defensor->nome);
    printf("Dado do atacante: %d\n", dadoAtaque);
    printf("Dado do defensor: %d\n", dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas;
        strcpy(defensor->cor, atacante->cor);

        printf("Resultado: atacante venceu! %s foi conquistado.\n", defensor->nome);
        printf("O território %s agora pertence à cor %s com %d tropas.\n",
               defensor->nome,
               defensor->cor,
               defensor->tropas);
    } else {
        atacante->tropas--;
        printf("Resultado: defensor venceu! O atacante perdeu 1 tropa.\n");
    }
}

void liberarMemoria(Territorio *territorios, Jogador *jogadores, int totalJogadores) {
    int i;

    if (territorios != NULL) {
        free(territorios);
    }

    if (jogadores != NULL) {
        for (i = 0; i < totalJogadores; i++) {
            free(jogadores[i].missao);
        }
        free(jogadores);
    }
}

int main(void) {
    Territorio *territorios;
    Jogador *jogadores;
    char *missoes[TOTAL_MISSOES] = {
        "Conquistar 3 territórios seguidos.",
        "Eliminar todas as tropas da cor vermelha.",
        "Dominar 3 territórios da cor azul.",
        "Destruir o exército verde.",
        "Conquistar 3 territórios para vencer."
    };
    int opcao;
    int atacante, defensor;
    int i;

    srand((unsigned int)time(NULL));

    territorios = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória para os territórios.\n");
        return 1;
    }

    jogadores = (Jogador *)calloc(TOTAL_JOGADORES, sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro ao alocar memória para os jogadores.\n");
        free(territorios);
        return 1;
    }

    for (i = 0; i < TOTAL_JOGADORES; i++) {
        snprintf(jogadores[i].nome, sizeof(jogadores[i].nome), "Jogador %d", i + 1);
        if (i == 0) {
            strcpy(jogadores[i].cor, "azul");
        } else {
            strcpy(jogadores[i].cor, "vermelha");
        }

        jogadores[i].missao = (char *)malloc(200 * sizeof(char));
        if (jogadores[i].missao == NULL) {
            printf("Erro ao alocar memória para a missão do jogador %d.\n", i + 1);
            liberarMemoria(territorios, jogadores, TOTAL_JOGADORES);
            return 1;
        }

        atribuirMissao(jogadores[i].missao, missoes, TOTAL_MISSOES);
        exibirMissao(jogadores[i].missao);
    }

    cadastrarTerritorios(territorios, TOTAL_TERRITORIOS);
    exibirMapa(territorios, TOTAL_TERRITORIOS);

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
        } else if (strcmp(territorios[atacante].cor, territorios[defensor].cor) == 0) {
            printf("Ataque inválido: só é possível atacar territórios inimigos.\n");
        } else {
            atacar(&territorios[atacante], &territorios[defensor]);
            exibirMapa(territorios, TOTAL_TERRITORIOS);

            for (i = 0; i < TOTAL_JOGADORES; i++) {
                if (verificarMissao(jogadores[i].missao, territorios, TOTAL_TERRITORIOS)) {
                    printf("\nVITÓRIA! %s concluiu a missão: %s\n",
                           jogadores[i].nome,
                           jogadores[i].missao);
                    printf("=== FIM DA SIMULAÇÃO ===\n");
                    liberarMemoria(territorios, jogadores, TOTAL_JOGADORES);
                    return 0;
                }
            }
        }

        printf("Digite 1 para continuar atacando ou 0 para sair: ");
        scanf("%d", &opcao);
        limparBuffer();
    }

    printf("\n=== FIM DA SIMULAÇÃO ===\n");
    liberarMemoria(territorios, jogadores, TOTAL_JOGADORES);
    return 0;
}