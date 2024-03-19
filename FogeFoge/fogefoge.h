#define CIMA 'w'
#define ESQUERDA 'a'
#define BAIXO 's'
#define DIREITA 'd'
#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'

// Estrutura que representa uma posição no mapa
typedef struct {
    int x;
    int y;
} POSICAO;

// Estrutura que representa o mapa do jogo
typedef struct {
    int linhas;
    int colunas;
    char **matriz;
} MAPA;

// Protótipos das funções
void lemapa(MAPA *m);
void alocamapa(MAPA *m);
void liberamapa(MAPA *m);
void imprimemapa(MAPA *m);
int podeandar(MAPA *m, char personagem, int x, int y);
void andanomapa(MAPA *m, int xorigem, int yorigem, int xdestino, int ydestino);
int acabou(MAPA *m, POSICAO heroi);
void mover(MAPA *m, POSICAO *heroi, char direcao);
int praondefantasmavai(MAPA *m, int xatual, int yatual, int *xdestino, int *ydestino);
void mover_fantasmas(MAPA *m, POSICAO *fantasmas, int num_fantasmas);
