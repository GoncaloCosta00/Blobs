
#ifndef __FUNCOES__
#define __FUNCOES__
#define _CRT_SECURE_NO_WARNINGS
#include "Tipos.h"
#include <string.h>
#include "math.h"


ELEMENTOZONA *criar_zona(int nL, int nC);
PIXEL *acessar_pixel(IMAGEM *im, int linha, int coluna);
IMAGEM *criar_imagem();
PIXEL **criarmatriz(int nL, int nC);
ELEMENTOZONA *criar_elemzona(int linha, int coluna, PIXEL *pixelzona);
BLOBS *criarBlob();
int marcar_zona(IMAGEM *imag,BLOBS *b, int i, int j, int R, int G, int B, int d);
void calcular_zonas(IMAGEM **imag, int R, int G, int B, int d);
int LerFicheiro(char *fi, LISTAIMG *LImag, int R, int G, int B, int d);
void DestruirImagem(IMAGEM *Imag);
void mostrarblobs(BLOBS *b, IMAGEM *i);
void destruir_zoneamento(ELEMENTOZONA *im);
void imag_com_mais_blobs(LISTAIMG *limg, ANALISEIMAGEM *img);
void blob_menor_desvio_padrão(LISTAIMG *limg, ANALISEIMAGEM *img);
void destruirzona(BLOBS *b);
void destruirMatrizpixeis(PIXEL **p, IMAGEM *im);

#endif







