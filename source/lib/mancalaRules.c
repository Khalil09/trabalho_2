#include "mancalaRules.h"

extern int flag;
extern int simulando;

/*Popula as casinhas com o valor 4 e as casinhas do total com 0, (Estado inicial do jogo)*/
void popular(int m_valores[][7]){
    int i,j;

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 7; j++)
        {
            m_valores[i][j] = 4;
        }
    }
    m_valores[0][0] = 0;
    m_valores[1][6] = 0;
}

int m_vazia(int m_valores[][7]){
    if(((m_valores[0][1] != 0)||(m_valores[0][2] != 0)||(m_valores[0][3] != 0)||(m_valores[0][4] != 0)||(m_valores[0][5] != 0)||(m_valores[0][6] != 0))&&((m_valores[1][0] != 0)||(m_valores[1][1] != 0)||(m_valores[1][2] != 0)||(m_valores[1][3] != 0)||(m_valores[1][4] != 0)||(m_valores[1][5] != 0))){
        return 1;
    }
    return 0;
}

/* Informa os valores das referencias do player 1 */
int referencia(char v){

    /* Para evitar confusoes as jogadas foram definidas por letras e convertidas
    para numeros para facilitar o tratamento no codigo */

    if((v == 'a')||(v == 'A')){
        return 0;
    }else if((v == 'b')||(v == 'B')){
        return 1;
    }else if((v == 'c')||(v == 'C')){
        return 2;
    }else if((v == 'd')||(v == 'D')){
        return 3;
    }else if((v == 'e')||(v == 'E')){
        return 4;
    }else if((v == 'f')||(v == 'F')){
        return 5;
    }

    return (-1);
}

/* Funcao que administra o turno do jogador 1 */
void turno_p1(int m_valores[][7], int escolha, int jogada_AI){
    char jogada;
    int j_vet, total, i, j, n;

    tabuleiro(m_valores);
    /* Este if define quem ira jogar, o player ou a IA, de acordo com a
     escolha passada no menu */
    if((escolha == 2)||(simulando != 1)){
        /* Le a posicao que quer ser realizada a jogada */
        printf("\nJogador 1 favor realizar sua jogada: ");
        scanf(" %c", &jogada);
        /* Armazena a posicao na coluna de acordo com a referencia passada */
        j_vet = referencia(jogada);
        /* Realiza a verificacao se o jogador nao esta escolhendo nenhuma casa vazia */
        while(m_valores[1][j_vet] == 0 || j_vet == (-1)){
            printf("\nJogada invalida, favor informar uma jogada valida: ");
            scanf(" %c", &jogada);
            j_vet = referencia(jogada);
        }
    /* j_vet para P1 vs IA */
    } else{
        j_vet = jogada_AI;
    }


    /* Armazena a quantidade de sementes na casa informada */
    n = m_valores[1][j_vet];
    /* Zera o atual */
    m_valores[1][j_vet] = 0;
    /* Redistribui as sementes */
    j = 0;
    while(n>0){
        /* sleep(1); */
        j_vet += 1;
        if(j_vet > 6){
            i=0;
            j++;
            m_valores[i][j_vet-j] += 1;
            j++;
            if(j_vet-j == 0){
                j_vet = -1;
            }
        } else{
            i=1;
            m_valores[i][j_vet] += 1;
        }

        n -= 1;
        tabuleiro(m_valores);
        if(simulando == 0)
        {
            sleep(1);
        }
    }


    /* Verifica se o p1 pode pegar as sementes do p2 */
    if((i == 1) && (m_valores[i][j_vet] == 1) && (m_valores[0][j_vet+1] != 0) && (j_vet != 6)){
        total = m_valores[0][j_vet+1] + m_valores[1][j_vet];
        m_valores[0][j_vet+1] = 0;
        m_valores[1][j_vet] = 0;
        m_valores[1][6] += total;
    }

    /* Verifica se o p1 pode jogar denovo */
    if((i==1) && (j_vet == 6) && (m_vazia(m_valores) == 1)){
        tabuleiro(m_valores);
        flag = 1;
        turno_p1(m_valores, escolha, jogada_AI);
    } else{
        flag = 2;
        tabuleiro(m_valores);
    }

}

/* Informa os valores das referencias do player 2, pois é invertido. */
int referencia2(char v){

    /* Para evitar confusoes as jogadas foram definidas por letras e convertidas
     para numermo facilitar o tratamento no codigo */

    if((v == 'a')||(v == 'A')){
        return 6;
    }else if((v == 'b')||(v == 'B')){
        return 5;
    }else if((v == 'c')||(v == 'C')){
        return 4;
    }else if((v == 'd')||(v == 'D')){
        return 3;
    }else if((v == 'e')||(v == 'E')){
        return 2;
    }else if((v == 'f')||(v == 'F')){
        return 1;
    }

    return -1;
}

/* Funcao que administra o turno do jogador 1 */
void turno_p2(int m_valores[][7], int escolha, int jogada_AI){

    char jogada;
    int j_vet, total, i, j, n;


    /* Este if define quem ira jogar, o player ou a IA, de acordo com a
     escolha passada no menu */
    if(escolha == 2){
        /* Le a posicao que quer ser realizada a jogada */
        printf("\nJogador 2 favor realizar sua jogada: ");
        scanf(" %c", &jogada);
        /* Armazena a posicao na coluna de acordo com a referencia passada */
        j_vet = referencia2(jogada);
        /* Realiza a verificacao se o jogador nao esta escolhendo nenhuma casa vazia */
        while(m_valores[0][j_vet] == 0 || j_vet == (-1)){
            printf("\nJogada invalida, favor informar uma jogada valida: ");
            scanf(" %c", &jogada);
            j_vet = referencia2(jogada);
        }
     } else {
        j_vet = jogada_AI;
     }
    /* Armazena a quantidade de sementes na casa informada */
    n = m_valores[0][j_vet];
    /* Zera o atual */
    m_valores[0][j_vet] = 0;
    /* Redistribui as sementes */
    j = 0;
    while(n>0){
        /* sleep(1); */
        j_vet -= 1;
        if(j_vet < 0){
            i=1;
            j++;
            m_valores[1][j_vet+j] += 1;
            j++;
            if(j_vet+j==6){
                j_vet = 7;
            }
        } else{
            i=0;
            m_valores[0][j_vet] += 1;
        }
        n -= 1;
        tabuleiro(m_valores);
        if(simulando == 0)
        {
           sleep(1);
        }
    }

    /* Verifica se o p2 pode pegar as sementes do p1 */
    if((i == 0) && (m_valores[i][j_vet] == 1) && (m_valores[1][j_vet-1] != 0) && (j_vet != 0)){
        total = m_valores[1][j_vet-1] + m_valores[0][j_vet];
        m_valores[1][j_vet-1] = 0;
        m_valores[0][j_vet] = 0;
        m_valores[0][0] += total;
    }

    /* Verifica se o p2 pode jogar denovo */
    if((i==0) && (j_vet == 0) && (m_vazia(m_valores) != 1)){
        tabuleiro(m_valores);
        turno_p2(m_valores, escolha, jogada_AI);
    } else{
        flag = 1;
        tabuleiro(m_valores);
    }
}

/* Pega todas as sementes que sobram e coloca no total */
void final(int m_valores[][7]){
    int j;

    for(j=1;j<7;j++){
        m_valores[0][0] += m_valores[0][j];
        m_valores[0][j] = 0;
    }

    for(j=0;j<6;j++){
        m_valores[1][6] += m_valores[1][j];
        m_valores[1][j] = 0;
    }

    tabuleiro(m_valores);

    /* Imprime a mensagem de vencedor */
    if(m_valores[0][0] > m_valores[1][6]){
        printf("\nParabéns! O Jogador 2 Ganhou!\n");
        getchar();

    } else if(m_valores[0][0] < m_valores[1][6]){
        printf("\nParabéns! O Jogador 1 Ganhou!\n");
        getchar();

    } else {
        printf("\nEmpate!\n");
        getchar();

    }

}
