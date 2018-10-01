#include <stdio.h>
#include "mancalaRules.h"
// #include "mancalaUI.h"
#include "minmax.h"

int flag, simulando;


int main(){
	int m_valores[2][7];
	int escolha, dificuldade,jogada_AI = 0;
    char primeiro;
    t_no *raiz = (t_no*)malloc(sizeof(t_no));
    t_no *aux;

    escolha = 0;
    /*Imprime o Menu e armazena seu retorno*/
    while(escolha != 4){
        popular(m_valores);
        escolha = menu();

        /*Caso o retorno seja 1 o jogador ira jogar contra alguma IA*/
        if(escolha == 1){

            menu_dific(&dificuldade, &primeiro);
            while(m_vazia(m_valores) == 1){
                /*O player 1 tem q receber parametro de escolha == 2*/
                turno_p1(m_valores, 2, 2);
                simulando = 1;
                raiz = cria_no(m_valores, flag, 0, 0);
                printf("Calculando...\n");
                geraArvore(raiz, dificuldade);
                /* Recebe o noh q teoricamente possui a maior heuristica*/
                aux = minimax(raiz, dificuldade);
                jogada_AI = aux->jogada;
                simulando = 0;
                turno_p2(m_valores, 1, jogada_AI);
                /*Aqui vai as funcoes Minmax e atribuidora de heuristica*/
                /*Lembrar de trocar a jogada_AI da funcao de turno_p2*/
            }
            final(m_valores);
        /*Caso 2 o jogador ira jogar contra outro jogador */
        }else if(escolha == 2){

            simulando = 0;
            tabuleiro(m_valores);
            while(m_vazia(m_valores) == 1){
                turno_p1(m_valores, escolha, 0);
                turno_p2(m_valores, escolha, 0);
            }

            final(m_valores);

            getchar();
        }
    }
    return 0;
}
