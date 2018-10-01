#include <stdlib.h>
#include <stdio.h>

#define RED "\x1b[31;1m"
#define RESET "\x1b[0m"
#define CYAN "\x1b[36m"
#define MAG "\x1b[35m"

//
void tabuleiro(int v[][7]);
//
void menu_dific(int *dificuldade, char *primeiro);
//
int menu();
