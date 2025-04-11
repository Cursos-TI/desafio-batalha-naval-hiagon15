#include <stdio.h>
#include <stdlib.h>

#define LINHAS 10
#define COLUNAS 10
#define NAVIO 3
#define TAM_HABILIDADE 5
#define AREA_AFETADA 5

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

    // --- MATRIZES DE HABILIDADES (5x5) ---
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

    // Cone (↧)
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            if (c >= (TAM_HABILIDADE / 2 - l) && c <= (TAM_HABILIDADE / 2 + l) && l <= TAM_HABILIDADE / 2) {
                cone[l][c] = 1;
            }
        }
    }

    // Cruz
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            if (l == TAM_HABILIDADE / 2 || c == TAM_HABILIDADE / 2) {
                cruz[l][c] = 1;
            }
        }
    }

    // Octaedro (losango)
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            if (abs(l - TAM_HABILIDADE / 2) + abs(c - TAM_HABILIDADE / 2) <= TAM_HABILIDADE / 2) {
                octaedro[l][c] = 1;
            }
        }
    }

    // Função para aplicar habilidade
    int aplicarHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemL, int origemC) {
        for (int l = 0; l < TAM_HABILIDADE; l++) {
            for (int c = 0; c < TAM_HABILIDADE; c++) {
                if (habilidade[l][c] == 1) {
                    int linhaTab = origemL + l - TAM_HABILIDADE / 2;
                    int colunaTab = origemC + c - TAM_HABILIDADE / 2;
                    if (linhaTab >= 0 && linhaTab < LINHAS && colunaTab >= 0 && colunaTab < COLUNAS) {
                        if (tabuleiro[linhaTab][colunaTab] == 0) {
                            tabuleiro[linhaTab][colunaTab] = AREA_AFETADA;
                        }
                    }
                }
            }
        }
        return 0;
    }

    // Aplicando habilidades em pontos de origem
    aplicarHabilidade(cone, 2, 2);       // Cone no topo-esquerdo
    aplicarHabilidade(cruz, 5, 5);       // Cruz no centro
    aplicarHabilidade(octaedro, 7, 2);   // Octaedro na parte inferior

    // --- EXIBE O TABULEIRO FINAL ---
    printf("\nTabuleiro Final:\n");
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            if (tabuleiro[l][c] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[l][c] == 3) {
                printf("# "); // Navio
            } else if (tabuleiro[l][c] == AREA_AFETADA) {
                printf("* "); // Habilidade
            }
        }
        printf("\n");
    }

    return 0;
}
