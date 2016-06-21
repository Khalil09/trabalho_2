/*

 Universidade de Brasilia - Instituto de Ciencias Exatas
 Departamento de Ciencia da Computacao
 Trabalho 2 de Estrutura de Dados - Game Trees
 Turma A - Professor Eduardo A. P. Alchieri
 Alunos:
 - Renato Avellar Nobre 150146698
 - Khalil Carsten ........

 00 de Junho de 2016

 Descricao de organizacao do codigo:
 Foi utilizado no projeto uma arvore de jogos em que seus nos contem uma struct
 para um vetor de ponteiros, uma matriz para guardar o estado do jogo, uma flag para armazenar quem ira jogar
 e uma heuristica para armazenar o valor da jogada.



 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int flag, simulando, jog_val, jog_val2;

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

/* Imprime o tabuleiro na tela */
void tabuleiro(int v[][7]) {
    int i = 0;
    if (simulando != 1){
        system("clear || cls");
        printf(" ==T===F===E===D===C===B===A=======\n");
        printf("(|%2i| [%2i][%2i][%2i][%2i][%2i][%2i] |P2|)\n", v[0][i],v[0][i+1],v[0][i+2],v[0][i+3],v[0][i+4],v[0][i+5],v[0][i+6]);
        printf("(|--|--------------------------|--|)\n");
        printf("(|P1| [%2i][%2i][%2i][%2i][%2i][%2i] |%2i|)\n", v[1][i],v[1][i+1],v[1][i+2],v[1][i+3],v[1][i+4],v[1][i+5],v[1][i+6]);
        printf(" ======A===B===C===D===E===F====T==\n");
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
/* Verifica se algum dos lados do tabuleiro esta vazio para finalizar o jogo */

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

void geraArvore(t_no *raiz, int dificuldade)
{
    /*Transfere a matriz original do no para a matriz_aux*/
    int i, j, k, mat_aux[2][7];

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
                    jog_val2 = jog_val2;
                    raiz->filhos[i-1] = cria_no(mat_aux, 2, i, jog_val2);
                    geraArvore(raiz->filhos[i-1], dificuldade-1);
                }
            }
        }
    }
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
