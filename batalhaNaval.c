#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define HABILIDADE 5

void inicializar(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

void exibir(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            printf("%2d ", tab[i][j]);
        printf("\n");
    }
}

// Função genérica para aplicar habilidade (sem sobrepor navios ou habilidades já aplicadas)
void aplicarHabilidade(int tab[TAM][TAM], int l, int c, int forma[TAM_HAB][TAM_HAB]) {
    int o = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++) {
            int x = l + i - o, y = c + j - o;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM && forma[i][j] == 1 && tab[x][y] == 0)
                tab[x][y] = HABILIDADE;
        }
}

// Habilidade Cruz: afeta linhas e colunas do centro
void criarCruz(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2);
}

// Habilidade Cone: forma triangular apontando para baixo
void criarCone(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i);
}

// Habilidade Octaedro: forma de losango
void criarOctaedro(int m[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = ((abs(i - centro) + abs(j - centro)) <= centro);
}

// Posicionamento de navio horizontal
int posicionarNavioHorizontal(int tab[TAM][TAM], int l, int c) {
    if (c + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (tab[l][c + i] != 0) return 0;
    for (int i = 0; i < NAVIO; i++)
        tab[l][c + i] = 3;
    return 1;
}

// Posicionamento de navio vertical
int posicionarNavioVertical(int tab[TAM][TAM], int l, int c) {
    if (l + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (tab[l + i][c] != 0) return 0;
    for (int i = 0; i < NAVIO; i++)
        tab[l + i][c] = 3;
    return 1;
}

// Posicionamento de navio na diagonal principal
int posicionarNavioDiagonal1(int tab[TAM][TAM], int l, int c) {
    if (l + NAVIO > TAM || c + NAVIO > TAM) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (tab[l + i][c + i] != 0) return 0;
    for (int i = 0; i < NAVIO; i++)
        tab[l + i][c + i] = 3;
    return 1;
}

// Posicionamento de navio na diagonal inversa
int posicionarNavioDiagonal2(int tab[TAM][TAM], int l, int c) {
    if (l + NAVIO > TAM || c - NAVIO + 1 < 0) return 0;
    for (int i = 0; i < NAVIO; i++)
        if (tab[l + i][c - i] != 0) return 0;
    for (int i = 0; i < NAVIO; i++)
        tab[l + i][c - i] = 3;
    return 1;
}

int main() {
    int tab[TAM][TAM];
    int cruz[TAM_HAB][TAM_HAB], cone[TAM_HAB][TAM_HAB], octa[TAM_HAB][TAM_HAB];

    inicializar(tab);

    // Posicionar navios
    posicionarNavioHorizontal(tab, 0, 2);   // (0,2), (0,3), (0,4)
    posicionarNavioVertical(tab, 2, 7);     // (2,7), (3,7), (4,7)
    posicionarNavioDiagonal1(tab, 6, 0);    // (6,0), (7,1), (8,2)
    posicionarNavioDiagonal2(tab, 7, 9);    // (7,9), (8,8), (9,7)

    // Criar habilidades
    criarCruz(cruz);
    criarCone(cone);
    criarOctaedro(octa);

    // Aplicar habilidades
    aplicarHabilidade(tab, 0, 1, cruz);
    aplicarHabilidade(tab, 3, 4, cone);
    aplicarHabilidade(tab, 7, 6, octa);

    // Exibir tabuleiro final
    printf("Tabuleiro Final:\n\n");
    exibir(tab);

    return 0;
}
