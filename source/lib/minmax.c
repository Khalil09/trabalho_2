#include "minmax.h"

typedef struct no t_no;

extern int flag;
extern int simulando;

void geraArvore(t_no *raiz, int dificuldade) {
    /*Transfere a matriz original do no para a matriz_aux*/
    int i, j, k, mat_aux[2][7];

    int jog_val, jog_val2;

    simulando = 1;

    /* Sao ifs diferentes para cada player, pois os enderecos de jogada na matriz sao diferentes*/
    if(dificuldade > 0){

        if(flag == 1)
        {
            for(i = 0; i < 6; i++)
            {
               for(j = 0; j < 2; j++)
                {
                    for(k = 0; k < 7; k++)
                    {
                        mat_aux[j][k] = raiz->mat_estado[j][k];
                    }
                }
                if(mat_aux[1][i] != 0){
                    jog_val = mat_aux[1][6];
                    turno_p1(mat_aux, 1, i);
                    jog_val = (mat_aux[1][6] - jog_val) * -1;
                    raiz->filhos[i] = cria_no(mat_aux, 1, i, jog_val);
                    geraArvore(raiz->filhos[i], dificuldade-1);
                }
            }
        }
        else
        {
            for(i = 1; i < 7; i++)
            {
                for(j = 0; j < 2; j++)
                {
                    for(k = 0; k < 7; k++)
                    {
                        mat_aux[j][k] = raiz->mat_estado[j][k];
                    }
                }
                if(mat_aux[0][i] != 0)
                {
                    jog_val2 = mat_aux[0][0];
                    turno_p2(mat_aux, 1, i);
                    jog_val2 = mat_aux[0][0] - jog_val2;
                    // jog_val2 = jog_val2; // POSSIVEL ERRO
                    raiz->filhos[i-1] = cria_no(mat_aux, 2, i, jog_val2);
                    geraArvore(raiz->filhos[i-1], dificuldade-1);
                }
            }
        }
    }
}

/*Cria o no da arvores*/
t_no *cria_no(int mat_aux[][7], int p, int jogada, int heur){
    int i, j;

    /* Aloca espaco para uma estrutura t_no */
    t_no *n = (t_no*)malloc(sizeof(t_no));

    /* Passa a matriz do jogo para a estrutura do no */
    for(i=0;i<2;i++){
        for(j=0;j<7;j++){
            n->mat_estado[i][j] = mat_aux[i][j];
        }
    }

    /* Assume a heuristica passada como parametro */
    n->heuristica = 0;
    /* Assume o valor da flag passado como parametro */
    n->player = p;
    n->jogada = jogada;
    n->heuristica = heur;
    /* Anula todos os ponteiros do no recem criado */
    for(i=0;i<6;i++){
        n->filhos[i] = NULL;
    }
    /* Retorna o no */
    return n;
}

t_no *max(t_no *v1, t_no *v2){
    if(v1->heuristica > v2->heuristica){
        return v1;
    } else {
        return v2;
    }
}

t_no *min(t_no *v1, t_no *v2){
    if(v1->heuristica < v2->heuristica){
        return v1;
    } else{
        return v2;
    }
}


t_no *minimax(t_no *no, int dificuldade){

    int i, qtd_filhos = 0;
    t_no *v;
    t_no *melhor_valor = (t_no*)malloc(sizeof(t_no));
    for(i=0;i<6;i++){
        if(no->filhos[i] != NULL){
            qtd_filhos += 1;
        }
    }

    if((dificuldade == 0) || (qtd_filhos == 0)){
        return no;
    }

    if(no->player == 1){
        melhor_valor->heuristica = 50;
        for(i=0;i<6;i++){
            if(no->filhos[i] != NULL)
            {
                v = minimax(no->filhos[i], dificuldade - 1);
                melhor_valor = min(melhor_valor, v);
            }
        }
        return melhor_valor;
    } else{
        melhor_valor->heuristica = -50;
        for(i=0;i<6;i++){
            if(no->filhos[i] != NULL)
            {
                v = minimax(no->filhos[i], dificuldade - 1);
                melhor_valor = max(melhor_valor, v);
            }
        }
        return melhor_valor;
    }
}
