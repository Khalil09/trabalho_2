#include "mancalaUI.h"

extern int simulando;

/* Imprime o tabuleiro na tela */
void tabuleiro(int v[][7]) {
    int i = 0;
    if (simulando != 1){
        system("clear || cls");
        printf(" =="RED"T"RESET"==="RED"F"RESET"==="RED"E"RESET"==="RED"D"RESET"==="RED"C"RESET"==="RED"B"RESET"==="RED"A"RESET"=======\n");
        printf("(|"CYAN"%2i"RESET"| ["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"] |P2|)\n", v[0][i],v[0][i+1],v[0][i+2],v[0][i+3],v[0][i+4],v[0][i+5],v[0][i+6]);
        printf("(|--|--------------------------|--|)\n");
        printf("(|P1| ["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"]["MAG"%2i"RESET"] |"CYAN"%2i"RESET"|)\n", v[1][i],v[1][i+1],v[1][i+2],v[1][i+3],v[1][i+4],v[1][i+5],v[1][i+6]);
        printf(" ======="RED"A"RESET"==="RED"B"RESET"==="RED"C"RESET"==="RED"D"RESET"==="RED"E"RESET"==="RED"F"RESET"==="RED"T"RESET"==\n");
    }
}

/* Funcao para selecionar a dificuldade desejada caso seja um modo Ia vs P1 */
void menu_dific(int *dificuldade, char *primeiro){
    /* Dificuldade, que sera a aultura da arvore */
    int escolha;

    printf("Porfavor escolha a dificuldade: \n");
    printf("1 - Trivial\n");
    printf("2 - Facil\n");
    printf("3 - Normal\n");
    printf("4 - Dificil\n");
    printf("5 - PHD\n");
    scanf("%d", &escolha);
    while((escolha < 1)||(escolha > 5)){
        printf("Opcao invalida!! Escolha de novo:");
        scanf("%d", &escolha);
    }

    switch(escolha)
    {
        case 1:
            *dificuldade = 1;
            break;
        case 2:
            *dificuldade = 3;
            break;
        case 3:
            *dificuldade = 5;
            break;
        case 4:
            *dificuldade = 7;
            break;
        case 5:
            *dificuldade = 9;
            break;
    }
}


/* Funcao para mostrar o menu e retornar a opcao selecionada */
int menu(){

    int escolha;

    /* Menu principal */
    system("clear || cls");
    printf("\n====Bem vindo ao Mancala!====\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("1. Player vs IA\n2. Player vs Player\n3. Regras\n4. Sair\n>>> ");
    scanf("%d", &escolha);
    getchar();
    while((escolha != 1)&&(escolha != 2)&&(escolha != 3)&&(escolha != 4)){
        printf("\nEscolha invalida! Por favor escolha uma opcao valida: ");
        scanf("%d", &escolha);
        getchar();
    }

    /* Tutorial */
    if(escolha == 3){
        system("clear || cls");
        printf("====Regras====\n\n");
        printf("Mancala é um jogo de tabuleiro anciente, e ha diversos variantes.");
        printf("Esta é a versao basica do jogo, conhecida como Kalah.\n");
        printf("\n==Buracos e total==\nOs buracos no tabuleiro inferiores sao referentes ao Jogador 1, e os superiores referente ao Jogador 2");
        printf("\n\n==Semear Pedras==\nEscolha um buraco para retirar todas suas pedras. Movendo no sentido anti-horario, depositando uma em cada buraco");
        printf("\n\n==Armazenadas==\nSe voce chegar no seu armazenamento, deposita uma pedra, se chegar no armazenamento do oponente, o pula.");
        printf("\n\n\nAperte enter para continuar.");
        getchar();
        system("clear || cls");
        printf("====Regras====");
        printf("\n\n==Turno Livre==\nSe a sua ultima peca distribuida cair na sua unidade de armazenamento, ganha um outro turno.");
        printf("\n\n==Captura==\nSe a sua ultima peca distribuida cai em um buraco vazio no seu lado, capture as pecas do inimigo diretamente oposto.");
        printf("\n\n==Fim==\nO jogo termina quanto todos os seis buracos de algum dos lados estao vazios. O jogador que ainda tiver peca no seu lado, ganha os respectivos pontos.");
        printf("\n\n==Vitoria==\nO jogador com maiores pecas em seu armazenamento ganha.");
        printf("\n\n\nAperte enter para encerrar.");
        getchar();
        getchar();
        menu();
    }

    return escolha;
}
