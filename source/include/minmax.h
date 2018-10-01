#include <stdlib.h>
#include "mancalaRules.h"

/* Struct responsavel para armazenar as informacoes nos nos das arvores */
typedef struct no{
    /* Matriz para armazenar o estado atual do jogo */
    int mat_estado[2][7];
     /* Vetor de ponteiros para os filhos */
    struct no *filhos[6];
    /* Valor para ser calculado pela funcao minmax */
    int heuristica;
    /* Flag para saber de qual player eh a jogada(1: Jogador 1 / 2: Jogador 2) */
    int player;

    int jogada;
}t_no;

t_no *cria_no(int mat_aux[][7], int p, int jogada, int heur);
t_no *max(t_no *v1, t_no *v2);
t_no *min(t_no *v1, t_no *v2);
t_no *minimax(t_no *no, int dificuldade);
void geraArvore(t_no *raiz, int dificuldade);
