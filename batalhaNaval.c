#include <stdio.h>

#define TAM 10
#define NAVIO 3

// Inicializa o tabuleiro com água (0)
void inicializar(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Verifica se é possível posicionar o navio sem sair do tabuleiro ou sobrepor outro
int podePosicionar(int tabuleiro[TAM][TAM], int l, int c, int dl, int dc) {
    for (int i = 0; i < NAVIO; i++) {
        int x = l + i * dl;
        int y = c + i * dc;
        if (x < 0 || x >= TAM || y < 0 || y >= TAM || tabuleiro[x][y] != 0)
            return 0;
    }
    return 1;
}

// Posiciona o navio se possível
void posicionar(int tabuleiro[TAM][TAM], int l, int c, int dl, int dc) {
    if (podePosicionar(tabuleiro, l, c, dl, dc)) {
        for (int i = 0; i < NAVIO; i++)
            tabuleiro[l + i * dl][c + i * dc] = NAVIO;
    } else {
        printf("Não foi possível posicionar navio em (%d,%d)\n", l, c);
    }
}

// Mostra o tabuleiro na tela
void exibir(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializar(tabuleiro);

    // Dois navios horizontais/verticais
    posicionar(tabuleiro, 0, 0, 0, 1);  // horizontal
    posicionar(tabuleiro, 2, 2, 1, 0);  // vertical

    // Dois navios diagonais
    posicionar(tabuleiro, 4, 4, 1, 1);  // diagonal ↘
    posicionar(tabuleiro, 6, 2, -1, 1); // diagonal ↗

    printf("\nTabuleiro final:\n");
    exibir(tabuleiro);
    return 0;
}

