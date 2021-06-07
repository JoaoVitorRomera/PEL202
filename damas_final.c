#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct
{
	char game1[20], game2[20], ganhador[20];
	int cont1, cont2, pont_max;
} dama;


int array_max[24];
int mat_min[24][24];


void expansao_min(char mat[8][8], int no)
{
	int i, j, nota_min, k = 0;

	char min0[8][8], min1[8][8], min2[8][8], min3[8][8];

	//varre a matriz em busca de peças brancas
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{

			//encontra peça preta
			if(mat[i][j] == 2)
			{

				//validaçao de movimento para a esquerda
				if(mat[i - 1][j - 1] == 32)
				{
					//!!casa à esquerda livre!!

					mat_min[no][k] = 1;

					k++;

				}
				//validação de movimento para a direita
				if(mat[i - 1][j + 1] == 32)
				{
					//!!casa a direita livre!!

					mat_min[no][k] = 1;

					k++;
				}

				//validaçao de peça capturavel a esquerda
				if(mat[i - 1][j - 1] == 1)
				{
					//!!peça branca à esquerda!!

					//validação de espaço livre após a peça adversaria
					if(mat[i - 2][j - 2] == 32)
					{
						//!!captura possivel!!

						mat_min[no][k] = -1;

						k++;
					}
				}
				//validaçao de peça capturavel a direita
				if(mat[i - 1][j + 1] == 1)
				{
					//!!peça branca à direita!!

					//validaçao de espaço livre apos a peça adversaria
					if(mat[i - 2][j + 2] == 32)
					{
						//!!captura possivel!!

						mat_min[no][k] = -1;

						k++;
					}
				}

			}
		}
	}
}

void expansao_max(char mat[8][8])
{
	int i, j, k, w, nota_max, no = 0, sum = 0, count0 = 0, count1 = 0, flag = 0, location, indice;

	int soma[24];

	int captura[24];

	float p[24];
	float tot[24];
	float prop[24];

	float test;

	char max0[8][8], max1[8][8], max2[8][8], max3[8][8], m4[8][8], m5[8][8], m6[8][8], m7[8][8], m8[8][8], m9[8][8], m10[8][8], m11[8][8];

	//varre a matriz em busca de peças brancas
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{

			//encontra peça branca
			if(mat[i][j] == 1)
			{

				printf("\t\t\t###Peca Branca [%d][%d]###\n", i, j);

				//validaçao de movimento para a esquerda
				if(mat[i + 1][j - 1] == 32)
				{
					//!!casa à esquerda livre!!

					//copia a matriz
					for(k = 0; k < 8; k++)
					{
						for(w = 0; w < 8; w++)
						{
							max0[k][w] = mat[k][w];
						}
					}

					//realiza a prediçao do movimento
					max0[i][j] = 32;
					max0[i + 1][j - 1] = 1;


					printf("\t\t\t- Movimento %d: [%d][%d]\n", no, i + 1, j - 1);

					captura[no] = 0;

					expansao_min(max0, no);

					no++;
				}
				//validação de movimento para a direita
				if(mat[i + 1][j + 1] == 32)
				{
					//!!casa a direita livre!!
					//copia a matriz
					for(k = 0; k < 8; k++)
					{
						for(w = 0; w < 8; w++)
						{
							max1[k][w] = mat[k][w];
						}
					}

					max1[i][j] = 32;
					max1[i + 1][j + 1] = 1;

					printf("\t\t\t- Movimento %d: [%d][%d]\n", no, i + 1, j + 1);

					captura[no] = 0;

					expansao_min(max1, no);

					no++;
				}

				//validaçao de peça capturavel a esquerda
				if(mat[i + 1][j - 1] == 2)
				{
					//!!peça preta à esquerda!!

					//validação de espaço livre após a peça adversaria
					if(mat[i + 2][j - 2] == 32)
					{
						//!!captura possivel!!
						//copia a matriz
						for(k = 0; k < 8; k++)
						{
							for(w = 0; w < 8; w++)
							{
								max2[k][w] = mat[k][w];
							}
						}

						max2[i][j] = 32;
						max2[i + 1][i - 1] = 32;
						max2[i + 2][j - 2] = 1;

						printf("\t\t\t- Movimento %d: [%d][%d] (CAPTURA)\n", no, i + 2, j - 2);

						captura[no] = 1;

						expansao_min(max2, no);

						no++;
					}
				}
				//validaçao de peça capturavel a direita
				if(mat[i + 1][j + 1] == 2)
				{
					//!!peça preta à direita!!

					//validaçao de espaço livre apos a peça adversaria
					if(mat[i + 2][j + 2] == 32)
					{
						//!!captura possivel!!

						//copia a matriz
						for(k = 0; k < 8; k++)
						{
							for(w = 0; w < 8; w++)
							{
								max3[k][w] = mat[k][w];
							}
						}

						max3[i][j] = 32;
						max3[i + 1][j + 1] = 32;

						max3[i + 2][j + 2] = 1;

						printf("\t\t\t- Movimento %d: [%d][%d] (CAPTURA)\n", no, i + 2, j + 2);

						expansao_min(max3, no);

						captura[no] = 1;

						no++;
					}
				}

			}
		}
	}

	// teste

	for(i = 0; i < 24; i++)
	{

		count0 = 0;
		count1 = 0;

		for(j = 0; j < 24; j++)
		{

			if(mat_min[i][j] != 0)
			{

				count0++;

				if(mat_min[i][j] == 1)
				{

					count1++;

				}
			}


		}

		p[i] = count1;
		tot[i] = count0;

	}

	//calcula e printa todas as probabilidades de jogada
	for(i = 0; i < 24; i++)
	{

		test = 1.0 - p[i] / tot[i];

		prop[i] = p[i] / tot[i];

		if(test >= 0)
		{
			printf("\t\t  Movimento: %d, Probabilidade: %.2f", i, test);

			if(captura[i] == 1)
			{
				printf(" (CAPT) \n");
			}
			else
			{
				printf("\n");
			}
		}
	}

	//decisao da jogada

	//encontra jogadas de captura sem risco
	for(i = 0; i < 24; i++)
	{
		if(captura[i] == 1 && prop[i] == 1)
		{
			flag = 1;
			indice = i;
		}
	}
	if(flag == 1)
	{
		printf("\n\t\t\tO movimento indicado e %d\n", indice);
	}

	//encontra a jogada com menor probabilidade
	else if(flag == 0)
	{

		location = 0;

		for (w = 1; w < 24; w++)
		{
			if (prop[w] > prop[location])
			{
				location = w;
			}
		}

		printf("\n\t\t\tO movimento indicado e: %d\n", location);
	}

	flag = 0;

	//zera a matriz
	for(i = 0; i < 24; i++)
	{
		for(j = 0; j < 24; j++)
		{
			mat_min[i][j] = 0;
		}
	}

	no = 0;

}

void jogador1(char matriz[8][8], char jogador, int oposto)
{
	system("color 20");
	int i, j, l, c, li, co, opcao = 0;

	do
	{
		system("cls");
		if(jogador == 1)
			printf("\n\n----------------    A VEZ E A DO JOGADOR DE PECAS BRANCAS  ----------\n\n");
		if(jogador == 2)
			printf("\n\n----------------    A VEZ E A DO JOGADOR DE PECAS PRETAS  ------------\n\n");

		expansao_max(matriz);

		printf("\n\t \t\t   0 1 2 3 4 5 6 7 \n");
		for(i = 0; i < 8; i++)
		{
			printf("\n\t\t\t%d  ", i);
			for(j = 0; j < 8; j++)
				printf("%c ", matriz[i][j]);
		}

		printf("\n\n\t***************  CORDENADA DA PECA  **********************");
		printf("\n\tLINHA: ");
		scanf("%d", &l);
		printf("\n\tCOLUNA: ");
		scanf("%d", &c);

		printf("\n\n\t****COORDENADA DA POSICAO QUE A PECA VAI OCUPAR****");
		printf("\n\tLINHA: ");
		scanf("%d", &li);
		printf("\n\tCOLUNA: ");
		scanf("%d", &co);
		if((li + co) % 2 == 0)
		{
			if((jogador == 1 && l < li) || (jogador == 2 && l > li))
			{
				printf("linha\n");

				if(c - 1 == co || c + 1 == co)
				{
					if(co == c - 1)
					{
						matriz[li][co] = jogador;
						matriz[l][c] = 32;
						opcao++;
					}
					if(co == c + 1)
					{
						matriz[li][co] = jogador;
						matriz[l][c] = 32;
						opcao++;
					}
				}

				if(matriz[l + 1][c + 1] == oposto)
				{
					if(c + 2 == co)
					{
						matriz[li][co] = jogador;
						matriz[l][c] = 32;
						opcao++;
						matriz[l + 1][c + 1] = 32;
					}
				}

				if(matriz[l + 1][c - 1] == oposto)
				{
					if(c - 2 == co)
					{
						matriz[li][co] = jogador;
						matriz[l][c] = 32;
						matriz[l + 1][c - 1] = 32;
						opcao++;
					}
				}

				if(matriz[l - 1][c + 1] == oposto)
				{
					if(c + 2 == co)
					{
						matriz[li][co] = jogador;
						matriz[l][c] = 32;
						opcao++;
						matriz[l - 1][c + 1] = 32;
					}
				}

				if(matriz[l - 1][c - 1] == oposto)
				{
					if(c - 2 == co)
					{
						matriz[li][co] = jogador;
						matriz[l][c] = 32;
						matriz[l - 1][c - 1] = 32;
						opcao++;
					}
				}
			}
			else printf("\n\n\t\t__________MOVIMENTO INVALIDO!!_________\n\t\t_________JOGUE NOVAMENTE________\n");//CASO O JOGADOR ESCOLHA UMA POCISAO INVALIDA
		}
		system("pause");
	}
	while(opcao != 1);
}

void ganhador(char matriz[8][8])
{
	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			if(matriz[i][j] == 2)
				dama.cont1++;
			if(matriz[i][j] == 1)
				dama.cont2++;
		}
	if(dama.cont1 > dama.cont2)
	{
		printf("\n\tVENCEDOR........-> %s TOTAL DE PECAS: %d\n\n", dama.game1, dama.cont1);
		strcpy(dama.ganhador, dama.game1);
		dama.pont_max = dama.cont1;
	}
	else
	{
		if(dama.cont1 < dama.cont2)
		{
			printf("\n\tVENCEDOR........-> %s TOTAL DE PECAS: %d\n\n", dama.game2, dama.cont2);
			strcpy(dama.ganhador, dama.game2);
			dama.pont_max = dama.cont2;
		}
		else
		{
			printf("\n\tEmpate!\n\t%s: %d\n\t%s: %d\n\n\n", dama.game1, dama.cont1, dama.game2, dama.cont2);
			strcpy(dama.ganhador, "jogo empatado");
			dama.pont_max = dama.cont2;
		}
	}
}




int main(int argc, char *argv[])
{

	char matriz[8][8];
	int i, j, jogador = 2, oposto = 1, opcao = 0, opcao2;
	dama.cont1 = dama.cont2 = 0;

	matriz[0][0] = 1;
	matriz[0][1] = 219;
	matriz[0][2] = 1;
	matriz[0][3] = 219;
	matriz[0][4] = 1;
	matriz[0][5] = 219;
	matriz[0][6] = 1;
	matriz[0][7] = 219;
	matriz[1][0] = 219;
	matriz[1][1] = 1;
	matriz[1][2] = 219;
	matriz[1][3] = 1;
	matriz[1][4] = 219;
	matriz[1][5] = 1;
	matriz[1][6] = 219;
	matriz[1][7] = 1;
	matriz[2][0] = 1;
	matriz[2][1] = 219;
	matriz[2][2] = 1;
	matriz[2][3] = 219;
	matriz[2][4] = 1;
	matriz[2][5] = 219;
	matriz[2][6] = 1;
	matriz[2][7] = 219;
	matriz[3][0] = 219;
	matriz[3][1] = 32;
	matriz[3][2] = 219;
	matriz[3][3] = 32;
	matriz[3][4] = 219;
	matriz[3][5] = 32;
	matriz[3][6] = 219;
	matriz[3][7] = 32;
	matriz[4][0] = 32;
	matriz[4][1] = 219;
	matriz[4][2] = 32;
	matriz[4][3] = 219;
	matriz[4][4] = 32;
	matriz[4][5] = 219;
	matriz[4][6] = 32;
	matriz[4][7] = 219;
	matriz[5][0] = 219;
	matriz[5][1] = 2;
	matriz[5][2] = 219;
	matriz[5][3] = 2;
	matriz[5][4] = 219;
	matriz[5][5] = 2;
	matriz[5][6] = 219;
	matriz[5][7] = 2;
	matriz[6][0] = 2;
	matriz[6][1] = 219;
	matriz[6][2] = 2;
	matriz[6][3] = 219;
	matriz[6][4] = 2;
	matriz[6][5] = 219;
	matriz[6][6] = 2;
	matriz[6][7] = 219;
	matriz[7][0] = 219;
	matriz[7][1] = 2;
	matriz[7][2] = 219;
	matriz[7][3] = 2;
	matriz[7][4] = 219;
	matriz[7][5] = 2;
	matriz[7][6] = 219;
	matriz[7][7] = 2;
	do
	{
		system("color 47");

		printf("\n\t__________________________________________________________\n");
		printf("\t__________________________________________________________\n");
		printf("\t__________________________________________________________\n");
		printf("\t__________________                    ____________________\n");
		printf("\t__________________                    ____________________\n");
		printf("\t__________________  JOGO  DE  DAMAS   ____________________\n");
		printf("\t__________________                    ____________________\n");
		printf("\t__________________________________________________________\n");
		printf("\t__________________________________________________________\n");
		printf("\t__________________________________________________________\n\t\t\t\t\t\n\n");
		printf("\tEscolha uma das op%c%ces abaixo:\n\n", 135, 228);
		printf("\t%c 1 Jogar.\n\t%c 2 Ajuda.\n\t%c 3 Sair.\n\n", 16, 16, 16, 162, 16);
		printf("\tOp%c%co: ", 135, 198);
		scanf("%d", &opcao2);
		system("cls");
		switch(opcao2)
		{
		case 1:
			system("cls");

			int tempo = clock();
			while(clock() - tempo < 50000000)
			{

				jogador = 1;
				oposto = 2;
				jogador1(matriz, jogador, oposto);

				jogador = 2;
				oposto = 1;
				jogador1(matriz, jogador, oposto);
			}
			system("cls");
			system("color 20");

			ganhador(matriz);
			system("pause");
			system("cls");
			break;
		case 2:
			system("color 90");
			printf("\n_____________________________O QUE E O JOGO?_______________________________");
			printf("\n\t     O jogo de Damas e constituido por um Tabuleiro quadratico,\n\tdividido em 64 quadrados,com 24 Pecas,sendo 12 de cor branca\n\te 12 de cor preta. Exitem  8 linhas que estao na posicao  vertical,\n\te com 8 culunas na posicao horizantal.\n");
			printf("\n_____________________________  O OBJETIVO  _______________________________");
			printf("\n\n\t      Comer o maior Numero de Pecas Possiveis.Quem \n\tDurante os 3 Minutos tiver  mais Pecas e o Vencedor!\n\n");

			printf("\n______________________________REGRAS O JOGO_________________________________");
			printf("\n\n\t1-Nao e permitido comer para tras.\n\t2-Pode comer uma peca,nao duas de uma vez.\n\t3-So anda uma casa por vez.\n\t4- O Jogo dura  3 Minutos.\n\t5-Nao e permitido Jogar com uma Peca do adversario.\n");
			printf("____________________________________________________________________________\n\n");
			system("pause");
			system("cls");
			break;

		case 3:
			system("color 70");
			printf("\n\n\n\n\t\t\t  FIM DO JOGO\n\n\n\n\n");
			break;
		}
	}
	while(opcao2 != 4);

	system("PAUSE");
	return 0;
}
