#include <stdio.h>
#include <string.h>

/* Imprime o tabuleiro na tela */ 
void tabuleiro(int v[][7])
{
	int i = 0;
	/* Limpa a Tela */
	system("clear || cls");

	printf(" ==T===F===E===D===C===B===A=======\n");
	printf("(|%2i| [%2i][%2i][%2i][%2i][%2i][%2i] |P2|)\n", v[0][i],v[0][i+1],v[0][i+2],v[0][i+3],v[0][i+4],v[0][i+5],v[0][i+6]);
	printf("(|--|--------------------------|--|)\n");
	printf("(|P1| [%2i][%2i][%2i][%2i][%2i][%2i] |%2i|)\n",
		   v[1][i],v[1][i+1],v[1][i+2],v[1][i+3],v[1][i+4],v[1][i+5],v[1][i+6]);
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
	
	printf("\n====Bem vindo ao Mancala!====\n");
	printf("Escolha uma das opcoes abaixo: \n");
	printf("1. Player vs IA\n2. Player vs Player\n3. IA vs IA\n4. Regras\n>>> ");
	scanf("%d", &escolha);

	while((escolha != 1)&&(escolha != 2)&&(escolha != 3)&&(escolha != 4)){
		printf("\nEscolha invalida! Por favor escolha uma opcao valida: ");
		scanf("%d", &escolha);
	}
	
	/* Mostra o tutorial */
	if(escolha == 4){
		printf("====Regras====");
		printf("Renato > Khalil");
		printf("Renato > Khalil");
		printf("Renato > Khalil");
		printf("Renato > Khalil");
		printf("Aperte enter para retornar");
		getchar();
		menu();
	}
	
	return escolha;
}

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
	
	return -1;
}

/* Funcao que administra o turno do jogador 1 */
void turno_p1(int m_valores[][7]){
	char jogada;
	int j_vet, j, n;
	/* Le a posicao que quer ser realizada a jogada */
	printf("\nJogador 1 favor realizar sua jogada: ");
	scanf(" %c", &jogada);
	getchar();
	/* Armazena a posicao na coluna de acordo com a referencia passada */
	j_vet = referencia(jogada);
	/* Realiza a verificacao se o jogador nao esta escolhendo nenhuma casa vazia */
	while(m_valores[1][j_vet] == 0){
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
		j_vet += 1;
		if(j_vet > 6){
			j++;
			m_valores[0][j_vet-j] += 1;
			j++;
			if(j_vet-j == 1){
				j_vet = 0;
			}	
		} else{
			m_valores[1][j_vet] += 1;	
		}
		
		n -= 1;		
	}
	
	tabuleiro(m_valores);
}

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

void turno_p2(int m_valores[][7]){
	char jogada;
	int j_vet, j, n;
	/* Le a posicao que quer ser realizada a jogada */
	printf("\nJogador 2 favor realizar sua jogada: ");
	scanf("%c", &jogada);
	getchar();
	/* Armazena a posicao na coluna de acordo com a referencia passada */
	j_vet = referencia2(jogada);
	/* Realiza a verificacao se o jogador nao esta escolhendo nenhuma casa vazia */
	while(m_valores[0][j_vet] == 0){
		printf("\nJogada invalida, favor informar uma jogada valida: ");
		scanf("%c", &jogada);
		j_vet = referencia2(jogada);
	}
	
	/* Armazena a quantidade de sementes na casa informada */
	n = m_valores[0][j_vet];
	/* Zera o atual */
	m_valores[0][j_vet] = 0;
	/* Redistribui as sementes */
	j = 0;
	while(n>0){
		j_vet -= 1;
		if(j_vet < 0){
			j++;
			m_valores[1][j_vet+j] += 1;
			j++;
			if(j_vet+j==5){
				j_vet = 6;
			}
		} else{
			m_valores[0][j_vet] += 1;
		}
		n -= 1;
	}
	
	tabuleiro(m_valores);
}

int main()
{
	int m_valores[2][7];
	int escolha;
	
	/*Imprime o Menu e armazena seu retorno*/
	escolha = menu();
	
	/*Caso o retorno seja 1 o jogador ira jogar contra alguma IA*/
	if(escolha == 1){
		
	/*Caso 2 o jogador ira jogar contra outro jogador */	
	}else if(escolha == 2){
		popular(m_valores);
		tabuleiro(m_valores);
		getchar();
		while(1){
			turno_p1(m_valores);
			turno_p2(m_valores);
		}
		
		
	/*Caso 3 o jogador ira simular uma partida de IA contra IA*/	
	} else if(escolha == 3){
		
	}
	
	return 0;
}