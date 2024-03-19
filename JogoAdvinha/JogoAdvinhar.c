#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
//#include "jogoAdvinhar.h"

struct estatisticasJogador {
    int jogador;
    int numeroTentativas;
    int numeroChutes;
    double pontos;
    double pontoTotal;
    int palpites;
};

void abertura(){
	printf("***********************************************\n");
    printf("Bem vindo ao jogo de advinhação\n");
    printf("***********************************************\n");
};

int descobrirJogadores(){
	int numJogadores;
	printf("Quantos jogadores vão arriscar ?\n");
    scanf("%d", &numJogadores);
    printf("***********************************************\n");
    return numJogadores;
};

void dificuldades(){
	printf("*                                             *\n"); 
    printf("*       Aumento dos Pontos por Nível         *\n");
    printf("*                                             *\n");
    printf("***********************************************\n");
    printf("*                                             *\n");
    printf("*  - Nível  de Dificuldade \"Hard\":            *\n");
    printf("*    Os pontos são multiplicados por 10.     *\n");
    printf("*                                             *\n");
    printf("*  - Nível  de Dificuldade \"Normal\":          *\n");
    printf("*    Os pontos são multiplicados por 5.      *\n");
    printf("*                                             *\n");
    printf("*  - Nível  de Dificuldade \"Easy\":            *\n");
    printf("*    Os pontos permanecem os mesmos.         *\n");
    printf("*                                             *\n");
    printf("***********************************************\n");
};


void exibirPlacar(struct estatisticasJogador jogadores[], int numJogadores){
    int k;
    printf("***********************************************\n");
    printf("*                 PLACAR                      *\n");
    printf("***********************************************\n");
    for (k = 0; k < numJogadores; k++) {
        printf("*   JOGADOR %d - Pontuação: %.2lf\n", jogadores[k].jogador, jogadores[k].pontoTotal);
    }
    printf("***********************************************\n");
}

void exibirCampeao(struct estatisticasJogador jogador) {
    printf("\n\n*****************************\n");
    printf("*     CAMPEÃO      *\n");
    printf("*****************************\n");
    printf("*        JOGADOR %d         *\n", jogador.jogador);
    printf("*  Pontos  | %.2lf  *\n", jogador.pontoTotal);
    printf("*****************************\n");
};

int main() {
    setlocale(LC_ALL, "portuguese");

    int numJogadores;
    int chute;
    int i, j, k;
    int numerodeTentativas;
    int palpites = 0;

	abertura();

    numJogadores=descobrirJogadores();
	
	dificuldades();
   
    struct estatisticasJogador estatisticas[numJogadores];

    for (k = 0; k < numJogadores; k++) {
        estatisticas[k].numeroChutes = 0;
        estatisticas[k].palpites = 0;
        estatisticas[k].jogador = k + 1;
        estatisticas[k].pontoTotal = 0; // Inicializa o total de pontos do jogador
        for (j = 1; j <= 3; j++) {
        	
        	int segundos = time(0);
            srand(segundos);
            int numeroGrande = rand();
            int numAlvo = numeroGrande % 100;
        	int dificuldade;
            
			printf("\nVez do PLAYER %d\n", estatisticas[k].jogador);
			printf("***********************************************\n");
            printf("\nRodada %d de 3\n", j);
            printf("***********************************************\n");

            printf("Insira qual o nÍvel de dificuldade da rodada %d\n", j);
			printf("(1) HARD (2) NORMAL (3) EASY\n");
			
			scanf("%d", &dificuldade);

			while(dificuldade < 1 || dificuldade > 3){
				printf("RESPOSTA INVALIDA\n");
				printf("INSIRA APENAS 1, 2, OU 3\n");
				scanf("%d", &dificuldade);
			}
				
			
            printf("Escolha o seu número de tentativas da rodada %d\n", j);
            scanf("%d", &numerodeTentativas);
            while(numerodeTentativas < 1 ){
				printf("RESPOSTA INVALIDA\n");
				printf("VOCÊ TEM QUE TENTAR NO MÍNIMO UMA VEZ\n");
				scanf("%d", &numerodeTentativas);
			}

            estatisticas[k].numeroTentativas = numerodeTentativas;

            for (i = 1; i <= numerodeTentativas; i++) {
            	
                printf("\nTentativa %d de %d\n", i, numerodeTentativas);
                printf("Qual o seu chute de 0 a 100?\n");
                scanf("%d", &chute);
                estatisticas[k].numeroChutes++;
                estatisticas[k].palpites++;

                if (chute < 0 || chute > 100) {
                    printf("Chute inválido! Por favor, escolha um número entre 0 e 100.\n");
                    i--; // Descontar tentativa inv?lida
                    continue;
                }

                if (chute == numAlvo) {
                    printf(":) Parabéns! Voc? acertou!\n");
                    printf("Acertou em %d Tentativas\n", estatisticas[k].numeroChutes);
                    switch (dificuldade) {
                        case (1):
                            estatisticas[k].pontos += 10.0 * (100.0 / (double)numerodeTentativas) * 10;
                            printf("Ganhou %.2f pontos na rodada %d", estatisticas[k].pontos, j);
                            break;

                        case (2):
                            estatisticas[k].pontos += 10.0 * (100.0 / (double)numerodeTentativas) * 5;
                            printf("Ganhou %.2f pontos na rodada %d", estatisticas[k].pontos, j);
                            break;

                        case (3):
                            estatisticas[k].pontos += 10.0 * (100.0 / (double)numerodeTentativas) * 1;
                            printf("Ganhou %.2f pontos na rodada %d", estatisticas[k].pontos, j);
                            break;
                    }
                    estatisticas[k].pontoTotal += estatisticas[k].pontos; // Atualiza o total de pontos
                    break; // Termina o loop se o jogador acertar
                } else if (i < numerodeTentativas) {
                    if (chute < numAlvo) {
                        switch (dificuldade) {
                            case (1):
                                printf("Seu chute foi %d\n", chute);
                                printf("Está errado, tente novamente\n");
                                break;

                            case (2):
                                printf("Seu chute foi %d\n", chute);
                                printf("Seu chute foi menor que o número secreto. Tente um número maior\n");
                                break;

                            case (3):
                                if (numAlvo - chute <= 10) {
                                    printf("Seu chute foi %d\n", chute);
                                    printf("Seu chute foi menor que o número secreto. Tente um número um pouco maior\n");
                                    printf("Tá quente");

                                } else if (numAlvo - chute <= 20) {
                                    printf("Seu chute foi %d\n", chute);
                                    printf("Seu chute foi menor que o número secreto. Tente um n?mero maior\n");
                                    printf("Tá morno");

                                } else {
                                    printf("Seu chute foi %d\n", chute);
                                    printf("Seu chute foi menor que o número secreto. Tente um n?mero muito maior\n");
                                    printf("Tá frio");

                                }
                                break;
                        }
                    } else {
                        switch (dificuldade) {
                            case (1):
                                printf("Seu chute foi %d\n", chute);
                                printf("Está errado, tente novamente\n");
                                break;
                            case (2):
                                printf("Seu chute foi %d\n", chute);
                                printf("Seu chute foi maior que o número secreto. Tente um n?mero menor\n");
                                break;
                            case (3):
                                if (chute - numAlvo <= 10) {
                                    printf("Seu chute foi %d\n", chute);
                                    printf("Seu chute foi maior que o número secreto. Tente um n?mero um pouco menor\n");
                                    printf("Tá quente");
                                } else if (chute - numAlvo <= 20) {
                                    printf("Seu chute foi %d\n", chute);
                                    printf("Seu chute foi maior que o número secreto. Tente um n?mero menor\n");
                                    printf("Tá morno");
                                } else {
                                    printf("Seu chute foi %d\n", chute);
                                    printf("Seu chute foi maior que o número secreto. Tente um n?mero muito menor\n");
                                    printf("Tá frio");
                                }
                                break;
                        }
                    }
                }
            }

            if (i > numerodeTentativas) {
                printf("\nSuas tentativas acabaram!\n");
                printf("O número secreto era: %d\n", numAlvo);
                printf("GAME OVER\n");
            }
        }
        Sleep(5000); // Pausa por 5 segundos antes de limpar a tela
        system("cls"); // Limpa a tela
    }

    // Exibe o placar de todos os jogadores
    exibirPlacar(estatisticas, numJogadores);
    

    // Verifica se todos os jogadores pontuaram zero
    int todosPontuaramZero = 1;
    for (k = 0; k < numJogadores; k++) {
        if (estatisticas[k].pontoTotal != 0) {
            todosPontuaramZero = 0;
            break;
        }
    }

    // Se todos os jogadores pontuaram zero, declara empate
    if (todosPontuaramZero) {
        printf("\nNenhum jogador pontuou. é um empate!\n");
    } else {
        // Encontra o jogador com a maior pontua??o
        int jogadorMaiorPontuacao = 0;
        double maiorPontuacao = estatisticas[0].pontoTotal;
        for (k = 1; k < numJogadores; k++) {
            if (estatisticas[k].pontoTotal > maiorPontuacao) {
                maiorPontuacao = estatisticas[k].pontoTotal;
                jogadorMaiorPontuacao = k;
            }
        }

        // Exibe o Campe?o
        exibirCampeao(estatisticas[jogadorMaiorPontuacao]);
    }

    Sleep(5000); // Pausa por 5 segundos antes de limpar a tela
    system("cls"); // Limpa a tela

    return 0;
}
