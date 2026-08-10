#include <stdio.h>
#include <string.h>

/**
 * ESTRUTURA DE DADOS (STRUCT)
 * A struct Territorio agrupa informações relacionadas a um território
 * de jogo, permitindo que tratemos como uma única unidade de informação.
 */
typedef struct {
    char nome[30];   // Armazena o nome do local
    char cor[10];    // Armazena a cor do exército (ex: Azul, Vermelho)
    int tropas;      // Armazena a quantidade numérica de soldados
} Territorio;

/**
 * Limpa o buffer de entrada após a leitura de números inteiros.
 */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/**
 * Função principal do sistema.
 * Implementa o fluxo de cadastro e exibição dos territórios.
 */
int main(void) {
    // Declaração do vetor de structs para armazenar exatamente 5 territórios.
    Territorio territorios[5];
    int i;

    printf("=== SISTEMA DE GERENCIAMENTO DE TERRITÓRIOS ===\n");
    printf("Por favor, preencha os dados dos 5 territórios abaixo.\n\n");

    // LOOP DE ENTRADA: Coleta os dados para cada um dos 5 itens do vetor.
    for (i = 0; i < 5; i++) {
        printf("--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        if (fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin) != NULL) {
            territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        } else {
            territorios[i].nome[0] = '\0';
        }

        printf("Digite a cor do exército (ex: Azul, Verde): ");
        if (fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin) != NULL) {
            territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        } else {
            territorios[i].cor[0] = '\0';
        }

        printf("Informe a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer();

        printf("-------------------------------\n\n");
    }

    // EXIBIÇÃO DOS DADOS: Percorre o vetor e imprime as informações formatadas.
    printf("\n========================================\n");
    printf("           RELATÓRIO FINAL              \n");
    printf("========================================\n");
    printf("%-15s | %-10s | %-8s\n", "NOME", "COR", "TROPAS");
    printf("----------------------------------------\n");

    for (i = 0; i < 5; i++) {
        // O formatador %-15s alinha o texto à esquerda para melhor legibilidade.
        printf("%-15s | %-10s | %-8d\n",
                territorios[i].nome,
                territorios[i].cor,
                territorios[i].tropas);
    }

    printf("========================================\n");
    printf("Sistema finalizado com sucesso.\n");

    return 0;
}