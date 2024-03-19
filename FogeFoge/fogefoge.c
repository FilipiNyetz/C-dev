#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fogefoge.h" // Inclui o arquivo de cabeçalho

#define CIMA 'w'
#define ESQUERDA 'a'
#define BAIXO 's'
#define DIREITA 'd'
#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'

#define MAX_FANTASMAS 5 // Defina o número máximo de fantasmas

int i,j;

void lemapa(MAPA *m) {
    FILE *f;
    f = fopen("mapa.txt", "r");
    if (f == NULL) {
        printf("Erro na leitura do mapa");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
    m->matriz = malloc(sizeof(char *) * m->linhas);

    for (i = 0; i < m->linhas; i++) {
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}

void alocamapa(MAPA *m) {
    m->matriz = malloc(sizeof(char *) * m->linhas);

    for (i = 0; i < m->linhas; i++) {
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
}

void liberamapa(MAPA *m) {
    for (i = 0; i < m->linhas; i++) {
        free(m->matriz[i]);
    }
    free(m->matriz);
}

void imprimemapa(MAPA *m) {
    for (i = 0; i < m->linhas; i++) {
        printf("%s\n", m->matriz[i]);
    }
}

int podeandar(MAPA *m, char personagem, int x, int y) {
    return (x >= 0 && x < m->linhas && y >= 0 && y < m->colunas && m->matriz[x][y] != '|' && m->matriz[x][y] != '-' && m->matriz[x][y] != FANTASMA);
}

void andanomapa(MAPA *m, int xorigem, int yorigem, int xdestino, int ydestino) {
    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = VAZIO;
}

int acabou(MAPA *m, POSICAO heroi) {
    return (m->matriz[heroi.x][heroi.y] == FANTASMA);
}

void mover(MAPA *m, POSICAO *heroi, char direcao) {
    int proximox = heroi->x;
    int proximoy = heroi->y;

    switch (direcao) {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case DIREITA:
            proximoy++;
            break;
        case BAIXO:
            proximox++;
            break;
        default:
            printf("Direcao invalida!\n");
            return;
    }

    if (podeandar(m, VAZIO, proximox, proximoy)) {
        andanomapa(m, heroi->x, heroi->y, proximox, proximoy);
        heroi->x = proximox;
        heroi->y = proximoy;
    } else {
        printf("Nao pode mover para la!\n");
    }
}

int praondefantasmavai(MAPA *m, int xatual, int yatual, int *xdestino, int *ydestino) {
    int direcoes[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
    int tentativas = 0;

    while (tentativas < 4) {
        int posicao = rand() % 4;
        int proximo_x = xatual + direcoes[posicao][0];
        int proximo_y = yatual + direcoes[posicao][1];

        if (podeandar(m, VAZIO, proximo_x, proximo_y)) {
            *xdestino = proximo_x;
            *ydestino = proximo_y;
            return 1;
        }

        tentativas++;
    }

    // Se nenhuma direção válida for encontrada, permanece na posição atual
    *xdestino = xatual;
    *ydestino = yatual;
    return 0;
}

void mover_fantasmas(MAPA *m, POSICAO *fantasmas, int num_fantasmas) {
    for (i = 0; i < num_fantasmas; i++) {
        int xatual = fantasmas[i].x;
        int yatual = fantasmas[i].y;
        int xdestino, ydestino;
        
        if (praondefantasmavai(m, xatual, yatual, &xdestino, &ydestino)) {
            andanomapa(m, xatual, yatual, xdestino, ydestino);
            fantasmas[i].x = xdestino;
            fantasmas[i].y = ydestino;
        }
    }
}

int main() {
    srand(time(NULL));
    MAPA m;
    POSICAO heroi;
    POSICAO fantasmas[MAX_FANTASMAS];
    int num_fantasmas = 0;

    lemapa(&m);

    for (i = 0; i < m.linhas; i++) {
        for (j = 0; j < m.colunas; j++) {
            if (m.matriz[i][j] == HEROI) {
                heroi.x = i;
                heroi.y = j;
            } else if (m.matriz[i][j] == FANTASMA) {
                fantasmas[num_fantasmas].x = i;
                fantasmas[num_fantasmas].y = j;
                num_fantasmas++;
            }
        }
    }

    do {
        imprimemapa(&m);
        char comando;
        scanf(" %c", &comando);

        int proximox = heroi.x;
        int proximoy = heroi.y;

        switch (comando) {
            case ESQUERDA:
                proximoy--;
                break;
            case CIMA:
                proximox--;
                break;
            case DIREITA:
                proximoy++;
                break;
            case BAIXO:
                proximox++;
                break;
            default:
                printf("Direcao invalida!\n");
                continue;
        }

        for (i = 0; i < num_fantasmas; i++) {
            if (proximox == fantasmas[i].x && proximoy == fantasmas[i].y) {
                printf("Perdeu!\n");
                return 0;
            }
        }

        if (podeandar(&m, VAZIO, proximox, proximoy)) {
            mover(&m, &heroi, comando);
        } else {
            printf("Nao pode mover para la!\n");
        }

        mover_fantasmas(&m, fantasmas, num_fantasmas);

        for (i = 0; i < num_fantasmas; i++) {
            if (heroi.x == fantasmas[i].x && heroi.y == fantasmas[i].y) {
                printf("Perdeu!\n");
                return 0;
            }
        }
    } while (!acabou(&m, heroi));

    andanomapa(&m, heroi.x, heroi.y, heroi.x, heroi.y);

    imprimemapa(&m);

    liberamapa(&m);

    return 0;
}

