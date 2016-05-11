#include <stdio.h>
#include <string.h>

void tabuleiro(int v[][7])
{
	int i = 0;
	system("clear || cls");

	printf(" ==================================\n");
	printf("(|%2i| [%2i][%2i][%2i][%2i][%2i][%2i] |  |)\n",
		   v[0][i],v[0][i+1],v[0][i+2],v[0][i+3],v[0][i+4],v[0][i+5],v[0][i+6]);
	printf("(|  | [%2i][%2i][%2i][%2i][%2i][%2i] |%2i|)\n",
		   v[1][i],v[1][i+1],v[1][i+2],v[1][i+3],v[1][i+4],v[1][i+5],v[1][i+6]);
	printf(" ======1===2===3===4===5===6=======\n");
}

void main()
{
	int m_valores[2][7];
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
	tabuleiro(m_valores);
}