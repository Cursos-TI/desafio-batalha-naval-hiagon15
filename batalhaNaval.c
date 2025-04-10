#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10
#define NAVIO 3

int main() {
    int tabuleiro[LINHAS][COLUNAS] = {0};
    int i;

    // --- 1. NAVIO HORIZONTAL ---
    int linhaH = 8, colunaH = 3;
    int podeColocarH = 1;

    if (colunaH + NAVIO - 1 < COLUNAS) {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != 0) {
                podeColocarH = 0;
                break;
            }
        }

        if (podeColocarH) {
            for (i = 0; i < NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = 3;
            }
        } else {
            printf("Erro: Sobreposição no navio horizontal!\n");
        }
    } else {
        printf("Erro: Navio horizontal fora do limite!\n");
    }

    // --- 2. NAVIO VERTICAL ---
    int linhaV = 5, colunaV = 7;
    int podeColocarV = 1;

    if (linhaV + NAVIO - 1 < LINHAS) {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] != 0) {
                podeColocarV = 0;
                break;
            }
        }

        if (podeColocarV) {
            for (i = 0; i < NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = 3;
            }
        } else {
            printf("Erro: Sobreposição no navio vertical!\n");
        }
    } else {
        printf("Erro: Navio vertical fora do limite!\n");
    }

    // --- 3. NAVIO DIAGONAL PRINCIPAL (↘️) ---
    int linhaD1 = 0, colunaD1 = 0;
    int podeColocarD1 = 1;

    if (linhaD1 + NAVIO - 1 < LINHAS && colunaD1 + NAVIO - 1 < COLUNAS) {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaD1 + i][colunaD1 + i] != 0) {
                podeColocarD1 = 0;
                break;
            }
        }

        if (podeColocarD1) {
            for (i = 0; i < NAVIO; i++) {
                tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
            }
        } else {
            printf("Erro: Sobreposição no navio diagonal principal!\n");
        }
    } else {
        printf("Erro: Navio diagonal principal fora do limite!\n");
    }

    // --- 4. NAVIO DIAGONAL SECUNDÁRIA (↙️) ---
    int linhaD2 = 0, colunaD2 = 9;
    int podeColocarD2 = 1;

    if (linhaD2 + NAVIO - 1 < LINHAS && colunaD2 - (NAVIO - 1) >= 0) {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaD2 + i][colunaD2 - i] != 0) {
                podeColocarD2 = 0;
                break;
            }
        }

        if (podeColocarD2) {
            for (i = 0; i < NAVIO; i++) {
                tabuleiro[linhaD2 + i][colunaD2 - i] = 3;
            }
        } else {
            printf("Erro: Sobreposição no navio diagonal secundária!\n");
        }
    } else {
        printf("Erro: Navio diagonal secundária fora do limite!\n");
    }

    // --- EXIBE O TABULEIRO ---
    printf("\nTabuleiro Final:\n");
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            printf("%d ", tabuleiro[l][c]);
        }
        printf("\n");
    }

    return 0;
}
