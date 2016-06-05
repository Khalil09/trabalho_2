#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct no /*Struct responsavel por cada celula das listas e das arvores*/
{
	int matriz_t[2][7];
	struct no *filhos[6];
	int player; /*Flag para saber de qual player eh a jogada(0:player1 / 1:player2)*/ 
	int heuristica;
}t_no;

/*Cria o no da arvores*/
t_no *criarNo(int v[][7], int p, int heuri)
{
	int i, j;

	t_no *n = (t_no*)malloc(sizeof(t_no));
	n->player = p;
	n->heuristica = heuri;
	/* cria a matriz do no*/
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 7; j++)
		{
			n->matriz_t[i][j] = v[i][j];
		}
	}
	/* Anula todos os ponteiros do no recem criado*/
	n->filhos[0][2] = NULL;
	for(j = 0; j < 7; i++)
	{
		n->filhos[0][j] = NULL;
	}

	return n;
}


/* Imprime o tabuleiro na tela */ 
void tabuleiro(int v[][7])
{
	int i = 0;
	/* Limpa a Tela */
	system("clear || cls");

	printf(" ==T===F===E===D===C===B===A=======\n");
	printf("(|%2i| [%2i][%2i][%2i][%2i][%2i][%2i] |P2|)\n", v[0][i],v[0][i+1],v[0][i+2],v[0][i+3],v[0][i+4],v[0][i+5],v[0][i+6]);
	printf("(|--|--------------------------|--|)\n");
	printf("(|P1| [%2i][%2i][%2i][%2i][%2i][%2i] |%2i|)\n", v[1][i],v[1][i+1],v[1][i+2],v[1][i+3],v[1][i+4],v[1][i+5],v[1][i+6]);
	printf(" ======A===B===C===D===E===F====T==\n");
}

/*Popula as casinhas com o valor 4 e as casinhas do total com 0*/
/*Estado inicial do jogo*/
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

/* Funcao para mostrar o menu e retornar a opcao selecionada */
int menu(){
	
	int escolha;
	
	system("clear || cls");
	printf("\n====Bem vindo ao Mancala!====\n");
	printf("Escolha uma das opcoes abaixo: \n");
	printf("1. Player vs IA\n2. Player vs Player\n3. IA vs IA\n4. Regras\n5. Sair\n>>> ");
	scanf("%d", &escolha);
	getchar();

	while((escolha != 1)&&(escolha != 2)&&(escolha != 3)&&(escolha != 4)&&(escolha != 5)){
		printf("\nEscolha invalida! Por favor escolha uma opcao valida: ");
		scanf("%d", &escolha);
	}
	
	/* Mostra o tutorial */
	if(escolha == 4){
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
		menu();
	}
	
	return escolha;
}
/*=====================================================================*/
/* Informa os valores das referencias do player 1 */
int referencia(char v){
	
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
char *turno_p1(int m_valores[][7], int jogada_AI, int *flag){
	char jogada;
	int j_vet, total, i, j, n, m_aux[2][7];

	/*checa se esta sendo jogada por um player ou por uma AI*/
	if((jogada_AI >= 65 && jogada_AI <= 70) || (jogada_AI >= 97 && jogada_AI <= 102))
	{ 
		j_vet = jogada_AI;
	}
	else
	{
		/* Le a posicao que quer ser realizada a jogada */
		printf("\nJogador 2 favor realizar sua jogada: ");
		scanf("%c", &jogada);
		getchar();
		/* Armazena a posicao na coluna de acordo com a referencia passada */
		j_vet = referencia(jogada);
	}

	while(m_valores[1][j_vet] == 0 || j_vet == (-1)){
		printf("\nJogada invalida, favor informar uma jogada valida: ");
		scanf(" %c", &jogada);
		j_vet = referencia(jogada);
	}
	
	/* Armazena a quantidade de sementes na casa informada */
	n = m_valores[1][j_vet];
	/* Zera o atual */
	m_valores[1][j_vet] = 0;
	/* Redistribui as sementes */
	j = 0;
	while(n>0){
		sleep(1);
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
	}
	
	if((i == 1) && (m_valores[i][j_vet] == 1) && (m_valores[0][j_vet+1] != 0) && (j_vet != 6)){
		total = m_valores[0][j_vet+1] + m_valores[1][j_vet];
		m_valores[0][j_vet+1] = 0;
		m_valores[1][j_vet] = 0;
		m_valores[1][6] += total;
	} 
	
	if((i==1) && (j_vet == 6)){
		*flag = 0;
		/*tabuleiro(m_valores);
		turno_p1(m_valores);*/
	} else{
		
		*flag = 1;/*tabuleiro(m_valores);*/
	}
	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 7; j++)
		{
			m_valores[i][j] = m_aux[i][j];
		}
	}
	return m_aux;
}
/*=====================================================================*/
/* Informa os valores das referencias do player 2, pois é invertido. */
int referencia2(char v){
	
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

char *turno_p2(int m_valores[][7], int jogada_AI, int *flag){
	char jogada;
	int j_vet, total, i, j, n, m_aux[2][7];
	
	/*checa se esta sendo jogada por um player ou por uma AI*/
	if((jogada_AI >= 65 && jogada_AI <= 70) || (jogada_AI >= 97 && jogada_AI <= 102))
	{ 
		j_vet = jogada_AI;
	}
	else
	{
		/* Le a posicao que quer ser realizada a jogada */
		printf("\nJogador 2 favor realizar sua jogada: ");
		scanf("%c", &jogada);
		getchar();
		/* Armazena a posicao na coluna de acordo com a referencia passada */
		j_vet = referencia2(jogada);
	}
	
	/* Realiza a verificacao se o jogador nao esta escolhendo nenhuma casa vazia */
	while(m_valores[0][j_vet] == 0 || j_vet == (-1)){
		printf("\nJogada invalida, favor informar uma jogada valida: ");
		scanf(" %c", &jogada);
		j_vet = referencia2(jogada);
	}
	
	/* Armazena a quantidade de sementes na casa informada */
	n = m_valores[0][j_vet];
	/* Zera o atual */
	m_valores[0][j_vet] = 0;
	/* Redistribui as sementes */
	j = 0;
	while(n>0){
		sleep(1);
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
	}
	
	if((i == 0) && (m_valores[i][j_vet] == 1) && (m_valores[1][j_vet-1] != 0) && (j_vet != 0)){
		total = m_valores[1][j_vet-1] + m_valores[0][j_vet];
		m_valores[1][j_vet-1] = 0;
		m_valores[0][j_vet] = 0;
		m_valores[0][0] += total;
	} 
	
	if((i==0) && (j_vet == 0)){
		*flag = 1;
		/*tabuleiro(m_valores);
		turno_p2(m_valores);*/
	} else{
		*flag = 0;
		/*tabuleiro(m_valores)*/;
	}	

	for(i = 0; i < 2; i++)
	{
		for(j = 0; j < 7; j++)
		{
			m_valores[i][j] = m_aux[i][j];
		}
	}
	return m_aux;

}

t_no *geraArvore(int m_valores[][7], int dificuldade, t_no *raiz, int *flag)
{
	int i, j;
	int m_aux[2][7];

	if(dificuldade > 0)
	{
		/* Copia o tabuleiro para outra matriz para que n altere a original*/
		for(i = 0; i < 2; i++)
		{
			for(j = 0; j < 7; j++)
			{
				m_aux[i][j] = m_valores[i][j];
			}
		}  
		/* Cria a arvore ate a dificuldade solicitada*/
		for(i = 1; i < 7; i++)
		{
			if(m_aux[0][i] != 0)
			{
				if(flag = 0){
					raiz->filhos[i] = gerarArvore(m_aux, dificuldade-1, criarNo(turno_p1(m_aux, i+1, &(*flag)), 1, 0));
				}
				else{
					raiz->filhos[i] = gerarArvore(m_aux, dificuldade-1, criarNo(turno_p2(m_aux, i+1, &(*flag)), 1, 0));
				}
			}
		}
		return raiz;
	}
}

int main()
{
	int m_valores[2][7];
	int escolha, j, escolha_d;
	char escolha_PvAI;
	int flag; /*Flag que define o jogador atual 0 para primeiro player, 1 para o segundo*/
	int dificuldade;

	/*Imprime o Menu e armazena seu retorno*/
	while(escolha != 5){
	escolha = menu();
	
	/*Caso o retorno seja 1 o jogador ira jogar contra alguma IA*/
	if(escolha == 1)
	{
		printf("Escolha a dificuldade: \n");
		printf("1 - Deboa\n");
		printf("2 - Razoavel\n");
		printf("3 - Dificil\n");
		printf("4 - Chuck Norris\n");
		scanf("%d", &escolha_d);
		
		switch(escolha_d)
		{
			case 1:
				dificuldade = 10;
				break;
			case 2:
				dificuldade = 20;
				break;
			case 3:
				dificuldade = 30;
				break;
			case 4:
				dificuldade = 40;
				break;
		}


		printf("Prefere ser o primeiro a jogar?(S/N): ");
		scanf(" %c", &escolha_PvAI);

		while(escolha_PvAI != 'S' && escolha_PvAI != 's' && escolha_PvAI != 'S' && escolha_PvAI != 's')
		{
			printf("Tu eh retardado?!?! >>>>>(S/N)<<<<<\n");
			scanf(" %c", &escolha_PvAI);
		}

		t_no *raiz = criarNo(m_valores, 1, 0);
		if(escolha_PvAI == 'S' || escolha_PvAI == 's')
			flag = 0;
		else
			flag = 1;

		if(flag = 0)
			turno_p1(m_valores, 'z', &flag);
		else
		{
			turno_p2(m_valores, 'z', &flag);
			geraArvore(m_valores, dificuldade, raiz, &flag);
		}	
	
	/*Caso 2 o jogador ira jogar contra outro jogador */	
	}else if(escolha == 2){
		popular(m_valores);
		tabuleiro(m_valores);
		while(((m_valores[0][1] != 0)||(m_valores[0][2] != 0)||(m_valores[0][3] != 0)||(m_valores[0][4] != 0)||(m_valores[0][5] != 0)||(m_valores[0][6] != 0))
			&&((m_valores[1][0] != 0)||(m_valores[1][1] != 0)||(m_valores[1][2] != 0)||(m_valores[1][3] != 0)||(m_valores[1][4] != 0)||(m_valores[1][5] != 0)))
		{
			if(flag = 0)
				turno_p1(m_valores, 'z', &flag);
			
			else
				turno_p2(m_valores, 'z', &flag);
			
		}
		
		for(j=1;j<7;j++){
			m_valores[0][0] += m_valores[0][j];
			m_valores[0][j] = 0;
		}
		
		for(j=0;j<6;j++){
			m_valores[1][6] += m_valores[1][j];
			m_valores[1][j] = 0;
		}
		
		tabuleiro(m_valores);
		
		if(m_valores[0][0] > m_valores[1][6]){
			printf("\nParabéns! O Jogador 2 Ganhou!\n");
		} else if(m_valores[0][0] < m_valores[1][6]){
			printf("\nParabéns! O Jogador 1 Ganhou!\n");
		} else {
			printf("\nEmpate!\n");
		}
		
		getchar();
	
	/*Caso 3 o jogador ira simular uma partida de IA contra IA*/	
	} else if(escolha == 3){
		printf("Rekt\n");
	}
	return 0;
	}
}