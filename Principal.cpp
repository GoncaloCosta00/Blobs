#define _CRT_SECURE_NO_WARNINGS

#include "Funcoes.h"
#include <string.h>
#include <locale>
#include <Windows.h>  // para fazer a pausa (sleep)


int Menu()
{
	system("cls");
	printf("\nPARA PODER VER AS INFORMAÇÕES DO FICHEIRO TERÁ DE LER PRIMEIRO O FICHEIRO (opção 1)\n\n\n");
	printf("    __________________________________________________  \n");
	printf("   |                                                  | \n");
	printf("   |   1- Ler ficheiro                                | \n");
	printf("   |   2- Mostrar blobs e imagem com mais blobs       | \n");
	printf("   |   3- Ver imagens com blobs ordenados             | \n");
	printf("   |   4- Imagem com menor desvio padrão              | \n");
	printf("   |   5- Sair                                        | \n");
	printf("   |__________________________________________________| \n");
	printf("\n\nQual opção?\n\n");
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
		printf("\nNão existe Ficheiro...\n");
		exit(0);
	}
}

int verificacor(int R, int G, int B)
{
	if (R < 0 || R>255|| G < 0 || G>255|| B < 0 || B>255)
	{
		printf("\nValor de cor inválida!!!\n\nA cor tem de estar entre 0 e 255\n");
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
		printf("\nNº parametros incorreto\n");
		printf("\nOs parâmetros devem ser:\n\nProjeto.exe Testes ficheiro.txt R G B ALL\n");
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
				printf("\nParâmetro errado!!\n");
				printf("\nOs parâmetros devem ser:\n\nProjeto.exe Testes ficheiro.txt R G B ALL\n");
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
				printf("\nParâmetro errado!!\n");
				printf("\nOs parâmetros devem ser:\n\nProjeto.exe Testes ficheiro.txt R G B ALL\n");
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
							printf("\nNome da imagem:%s \nNúmero de blobs:%d\n\n", aux->nome_imagem, aux->blobs);
							system("pause");
							while (b)
							{
								printf("\n\nMédia do blob:\n");
								printf("Média R: %.2f\n", b->mediaR);
								printf("Média G: %.2f\n", b->mediaG);
								printf("Média B: %.2f\n", b->mediaB);
								printf("\n\nDesvio padrão do blob:\n");
								printf("Desvio padrão R: %.2f\n", b->desv_padraoR);
								printf("Desvio padrão G: %.2f\n", b->desv_padraoG);
								printf("Desvio padrão B: %.2f\n", b->desv_padraoB);
								b = b->proximo;
							}

							system("pause");
							aux = aux->proximo;
						}
						imag_com_mais_blobs(Limg, imagem);
						printf("\n\nA imagem com mais blobs é: %s \n\n\n", imagem->im_max_blobs);
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
						blob_menor_desvio_padrão(Limg, imagem);
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
					printf("\n\nA imagem com mais blobs é: %s \n\n\n", imagem->im_max_blobs);


				//-----------------BLOBS COM MENOR DESVIO PADRÃO----------
					blob_menor_desvio_padrão(Limg, imagem);
			
				
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
					printf("\n\Na imagem com mais blobs é: %s \n\n\n", imagem->im_max_blobs);


					//BLOBS COM MENOR DESVIO PADRÃO
					blob_menor_desvio_padrão(Limg, imagem);
					DestruirImagem(Limg->inicio);
					Limg = criarlista();
					Sleep(250); // vai fazer uma "pausa" de 0.250 segundos 
				}

			}
			
			DestruirImagem(Limg->inicio);
	}
}
