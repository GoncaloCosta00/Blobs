#define _CRT_SECURE_NO_WARNINGS

#include "Funcoes.h"
#include <string.h>
#include <locale>
#include <Windows.h>  // para fazer a pausa (sleep)


int Menu()
{
	system("cls");
	printf("\nPARA PODER VER AS INFORMA��ES DO FICHEIRO TER� DE LER PRIMEIRO O FICHEIRO (op��o 1)\n\n\n");
	printf("    __________________________________________________  \n");
	printf("   |                                                  | \n");
	printf("   |   1- Ler ficheiro                                | \n");
	printf("   |   2- Mostrar blobs e imagem com mais blobs       | \n");
	printf("   |   3- Ver imagens com blobs ordenados             | \n");
	printf("   |   4- Imagem com menor desvio padr�o              | \n");
	printf("   |   5- Sair                                        | \n");
	printf("   |__________________________________________________| \n");
	printf("\n\nQual op��o?\n\n");
	char op[10];
	int opcao;
	scanf("%s", op);
	opcao = atoi(op);
	return opcao;
}


LISTAIMG *criarlista()
{
	LISTAIMG *l;
	l = (LISTAIMG *)malloc(sizeof(LISTAIMG));
	l->inicio = NULL;
	return l;
}

int verificafich(char *fi)
{
	FILE *f;
	if (!(f = fopen(fi, "r")))
	{
		printf("\nN�o existe Ficheiro...\n");
		exit(0);
	}
}

int verificacor(int R, int G, int B)
{
	if (R < 0 || R>255|| G < 0 || G>255|| B < 0 || B>255)
	{
		printf("\nValor de cor inv�lida!!!\n\nA cor tem de estar entre 0 e 255\n");
		exit(0);
	}
}

void main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "portuguese");
	char f[20];
	LISTAIMG *Limg;
	Limg = criarlista();
	ANALISEIMAGEM *imagem;
	imagem = (ANALISEIMAGEM *)malloc(sizeof(ANALISEIMAGEM));
	imagem->img_mais_blobs = 0;
	int i, j, R, G, B, d, linha, coluna, zona;
	int opcao;
	IMAGEM *aux = NULL;
	char im_mais_blobs[30];
	BLOBS *b;
	b = (BLOBS *)malloc(sizeof(BLOBS));
	
	if (argc != 8)
	{
	
		system("cls");
		printf("\nN� parametros incorreto\n");
		printf("\nOs par�metros devem ser:\n\nProjeto.exe Testes ficheiro.txt R G B ALL\n");
		printf("ou\nProjeto.exe Testes ficheiro.txt R G B MENUS\n");
		printf("ou\nProjeto.exe Testes ficheiro.txt R G B MEM\n");
		Sleep(3000);
		system("cls");
		return;
	}
	else
	{
			if (strcmp("Testes", argv[1]) != 0)
			{
				system("cls");
				printf("\nPar�metro errado!!\n");
				printf("\nOs par�metros devem ser:\n\nProjeto.exe Testes ficheiro.txt R G B ALL\n");
				printf("ou\nProjeto.exe Testes ficheiro.txt R G B MENUS\n");
				printf("ou\nProjeto.exe Testes ficheiro.txt R G B MEM\n");
				Sleep(3000);
				system("cls");
				return;
				
			}
			strcpy(f, argv[2]);
			verificafich(f);
			R = atoi(argv[3]); //atoi converte de string para int
			G = atoi(argv[4]);
			B = atoi(argv[5]);
			verificacor(R, G, B);
			d = atoi(argv[6]);

			if (strcmp("MENUS", argv[7]) != 0 && strcmp("ALL", argv[7]) != 0 && strcmp("MEM", argv[7]) != 0)
			{
				system("cls");
				printf("\nPar�metro errado!!\n");
				printf("\nOs par�metros devem ser:\n\nProjeto.exe Testes ficheiro.txt R G B ALL\n");
				printf("ou\nProjeto.exe Testes ficheiro.txt R G B MENUS\n");
				printf("ou\nProjeto.exe Testes ficheiro.txt R G B MEM\n");
				Sleep(3000);
				system("cls");
				return;
			}

			if (strcmp("MENUS", argv[7]) == 0)
			{
				do
				{
					opcao = Menu();
					switch (opcao)
					{
					case 1:
						LerFicheiro(f, Limg, R, G, B, d);
						printf("Ficheiro lido com sucesso\n\n");
						break;
					case 2:
					{
						aux = Limg->inicio;
						while (aux)
						{
							b = aux->inicio;
							printf("\nNome da imagem:%s \nN�mero de blobs:%d\n\n", aux->nome_imagem, aux->blobs);
							system("pause");
							while (b)
							{
								printf("\n\nM�dia do blob:\n");
								printf("M�dia R: %.2f\n", b->mediaR);
								printf("M�dia G: %.2f\n", b->mediaG);
								printf("M�dia B: %.2f\n", b->mediaB);
								printf("\n\nDesvio padr�o do blob:\n");
								printf("Desvio padr�o R: %.2f\n", b->desv_padraoR);
								printf("Desvio padr�o G: %.2f\n", b->desv_padraoG);
								printf("Desvio padr�o B: %.2f\n", b->desv_padraoB);
								b = b->proximo;
							}

							system("pause");
							aux = aux->proximo;
						}
						imag_com_mais_blobs(Limg, imagem);
						printf("\n\nA imagem com mais blobs �: %s \n\n\n", imagem->im_max_blobs);
						break;
					}
					case 3:
						aux = Limg->inicio;
						while (aux)
						{
							b = aux->inicio;
							mostrarblobs(b, aux);
							aux = aux->proximo;
						}
						break;
					case 4:
						blob_menor_desvio_padr�o(Limg, imagem);
						break;
					case 5:
						break;
					default:printf("\nOpcao invalida!\n\n");
						fflush(stdin);
						break;
					}
					system("pause");
					system("cls");
				} while (opcao != 5);
			}
			if ((strcmp("ALL", argv[7]) == 0))
			{
				//----------------- LER FICHEIRO----------------------
					LerFicheiro(f, Limg, R, G, B, d);
					printf("Ficheiro lido com sucesso\n");
					
				// ----------------MOSTRA IMAGEM COM MAIS BLOBS----------------
					imag_com_mais_blobs(Limg, imagem);
					printf("\n\nA imagem com mais blobs �: %s \n\n\n", imagem->im_max_blobs);


				//-----------------BLOBS COM MENOR DESVIO PADR�O----------
					blob_menor_desvio_padr�o(Limg, imagem);
			
				
			}
			if ((strcmp(argv[7], "MEM") == 0))
			{
				while (SUCESSO) // repete isto infinitas vezes 
				{
					// LER FICHEIRO
					LerFicheiro(f, Limg, R, G, B, d);
					printf("Ficheiro lido com sucesso\n\n");


					// MOSTRA IMAGEM COM MAIS BLOBS
					imag_com_mais_blobs(Limg, imagem);
					printf("\n\Na imagem com mais blobs �: %s \n\n\n", imagem->im_max_blobs);


					//BLOBS COM MENOR DESVIO PADR�O
					blob_menor_desvio_padr�o(Limg, imagem);
					DestruirImagem(Limg->inicio);
					Limg = criarlista();
					Sleep(250); // vai fazer uma "pausa" de 0.250 segundos 
				}

			}
			
			DestruirImagem(Limg->inicio);
	}
}
