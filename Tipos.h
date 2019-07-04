#ifndef __TIPOS__
#define __TIPOS__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

#define SUCESSO 1
#define INSUCESSO 0

typedef struct  
{
	int R, G, B;
	int visitado;
}*ptPIXEL, PIXEL;

typedef struct elementozona //lista de pixeis de um blob
{
	int linhas, colunas;  //linha e coluna dos pixels
	PIXEL *pixels;
	struct elementozona *proximo;
} *ptELEMENTOZONA, ELEMENTOZONA;

typedef struct
{
	char im_max_blobs[30];   //guarda nome img mais blobs
	int img_mais_blobs;		// guarda a quantidade de blobs
	char im_min_dp[30];    // nome para a imagem que tem o blob com menor dp
	int img_menos_dp;     
} *ptANALISEIMAGEM, ANALISEIMAGEM;

typedef struct blobs    //lista de blobs
{
	int linha, coluna;
	struct elementozona *inicio;
	struct blobs *proximo;
	float mediaR, mediaG, mediaB, desv_padraoR, desv_padraoG, desv_padraoB,desv_padraoTotal;
	int npixeis;
}*ptBLOBS, BLOBS;


typedef struct imagem
{
	int NLINHAS, NCOLUNAS, NCANAIS;
	char nome_imagem[50];
	PIXEL **pixels;
	struct imagem *proximo;
	BLOBS *inicio;
	int blobs;

}*ptIMAGEM, IMAGEM;

typedef struct listaimagens
{
	IMAGEM *inicio;
} *ptLISTAimg, LISTAIMG;

#endif 
