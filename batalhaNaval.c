#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define HABILIDADE 5
#define TAM_HAB 5

void inicializar(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

void posicionarNavio(int tab[TAM][TAM], int l[], int c[]) {
    for (int i = 0; i < NAVIO; i++)
        tab[l[i]][c[i]] = 3;
}

void aplicarHabilidade(int tab[TAM][TAM], int l, int c, int forma[TAM_HAB][TAM_HAB]) {
    int o = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++) {
            int x = l + i - o, y = c + j - o;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM && forma[i][j] && tab[x][y] == 0)
                tab[x][y] = HABILIDADE;
        }
}

void criarCruz(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2);
}

void criarCone(int m[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            m[i][j] = (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i);
}

int valorAbsoluto(int x) {
    return (x < 0) ? -x : x;
}

void criarOctaedro(int m[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int dist_i = (i < centro) ? centro - i : i - centro;
            int dist_j = (j < centro) ? centro - j : j - centro;
            m[i][j] = (dist_i + dist_j <= centro);
        }
    }
}

void exibir(int tab[TAM][TAM]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            printf("%d ", tab[i][j]);
        printf("\n");
    }
}

int main() {
    int tab[TAM][TAM];
    inicializar(tab);

    int navio1[3] = {0, 0, 0}, col1[3] = {2, 3, 4};
    int navio2[3] = {2, 3, 4}, col2[3] = {7, 8, 9};
    int navio3[3] = {9, 8, 7}, col3[3] = {0, 1, 2};

    posicionarNavio(tab, navio1, col1);
    posicionarNavio(tab, navio2, col2);
    posicionarNavio(tab, navio3, col3);

    int cruz[TAM_HAB][TAM_HAB], cone[TAM_HAB][TAM_HAB], octa[TAM_HAB][TAM_HAB];
    criarCruz(cruz);
    criarCone(cone);
    criarOctaedro(octa);

    aplicarHabilidade(tab, 1, 2, cruz);
    aplicarHabilidade(tab, 4, 5, cone);
    aplicarHabilidade(tab, 8, 7, octa);

    exibir(tab);
    return 0;
}
