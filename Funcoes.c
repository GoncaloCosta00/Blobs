#include "Funcoes.h"



ELEMENTOZONA *criar_zona(int nL, int nC)
{
	ELEMENTOZONA *imag = (ELEMENTOZONA *)malloc(sizeof(ELEMENTOZONA));
	imag->linhas = nL;
	imag->colunas = nC;
	return imag;
}


 int existePixel(IMAGEM *im, int linha, int coluna)
{
	 if (linha < 0 || coluna < 0)
		 return INSUCESSO;
	 if ( linha >= im->NLINHAS || coluna >= im->NCOLUNAS)
		 return INSUCESSO;
	 return SUCESSO;
}


PIXEL *acessar_pixel(IMAGEM *im, int linha, int coluna)
{
	return (&im->pixels[linha][coluna]);
}


IMAGEM *criar_imagem()
{
	IMAGEM *imag = (IMAGEM *)malloc(sizeof(IMAGEM));
	imag->inicio = NULL;
	imag->blobs = 0;
	return imag;
}


PIXEL **criarmatriz(int nL, int nC)  // vai criar a matriz que contém os pixeis todos da imagem
{
	PIXEL **m;
	int i;
	m = (PIXEL **)malloc(nL * sizeof(PIXEL *));
	for (i = 0; i < nL; i++)
	{
		m[i] = (PIXEL *)malloc(nC * sizeof(PIXEL));
	}
	return m;
}



ELEMENTOZONA *criar_elemzona(int linha, int coluna, PIXEL *pixelzona)
{
	ELEMENTOZONA *im;
	im = (ELEMENTOZONA *)malloc(sizeof(ELEMENTOZONA));
	im->pixels = pixelzona;
	im->linhas = linha;
	im->colunas = coluna;
	im->proximo = NULL;
	return im;
}


BLOBS *criarBlob()
{
	BLOBS *b;
	b = (BLOBS *)malloc(sizeof(BLOBS));
	b->npixeis = 0;
	b->inicio = NULL;
	b->proximo = NULL;
	b->linha = 0;
	b->coluna = 0;
	b->desv_padraoR = 0;
	b->desv_padraoG = 0;
	b->desv_padraoB = 0;
	b->mediaR = 0;
	b->mediaG = 0;
	b->mediaB = 0;
	return b;
}


int marcar_zona(IMAGEM *imag, BLOBS *b, int i, int j, int R, int G, int B, int d)   // verifica se um pixel é semelhante ao pixel dado, e coloca na zona
{
	if (!existePixel(imag, i, j)) return INSUCESSO;  // este pixel nao existe

	PIXEL *pi = acessar_pixel(imag, i, j);    // Obtém o pixel
	ELEMENTOZONA *z;
	if (pi->visitado == 1) return INSUCESSO;  // Se este pixel já foi visitado

	if (abs(pi->R - R) > d || abs(pi->G - G) > d || abs(pi->B - B) > d) //não corresponde 
	{
		pi->visitado = 1;
		return INSUCESSO;   // pixel não é semelhante ao pixel dado na função
	}
	else
	{
		//imag->inicio->npixeis++;
		b->npixeis++;
		pi->visitado = 1;
		z = criar_elemzona(i, j, pi);
		z->proximo = b->inicio;
		b->inicio = z;
		// verifica os pixeis vizinhos
		if (i < imag->NLINHAS - 1 && i>0)  // pois a matriz começa no 0
		{
			marcar_zona(imag,b, i + 1, j, R, G, B, d);
			marcar_zona(imag,b, i - 1, j, R, G, B, d);
		}
		if (j < imag->NCOLUNAS - 1 && j>0)
		{
			marcar_zona(imag,b, i, j + 1, R, G, B, d);
			marcar_zona(imag,b, i, j - 1, R, G, B, d);
		}
		
	}
	return SUCESSO;
}
void addord(BLOBS *b, IMAGEM **i)
{
	BLOBS *no;
	BLOBS *ant;
	ant = NULL;
	no = (*i)->inicio;
	(*i)->blobs++;
	if (no != NULL)
	{
		while (no != NULL && no->npixeis >= b->npixeis)  // o elemento atual é maior do que o que queremos inserir 
		{
			ant = no;
			no = no->proximo;
		}
		if (ant != NULL)
		{
			ant->proximo = b;
			b->proximo = no;
		}
		else  // parou no 1º blob
		{
			b->proximo = no;
			(*i)->inicio = b;
		}
	}
	else // lista vazia 
	{
		(*i)->inicio = b;
	}
}

void mostrarblobs(BLOBS *b, IMAGEM *img)
{
	BLOBS *no;
	if (!b) return;
	if (!b->inicio) return;
	no = img->inicio;
	b = img->inicio;
		printf("Imagem: %s\n\n", img->nome_imagem);
		system("pause");
		while (b)
		{
			
			if (!no)
				printf("Não existem blobs!!!\n\n");
			else
			{
				printf("nº de pixeis: %d\n\n", no->npixeis);
				no = no->proximo;
				
			}
			
			b = b->proximo;
			
		}
		system("pause");
}
void calcular_zonas(IMAGEM **imag, int R, int G, int B, int d)
{
	BLOBS *b;
	b = criarBlob();
	for (int i = 0; i < (*imag)->NLINHAS; i++) // Percorre cada pixel da imagem.
	{
		for (int j = 0; j < (*imag)->NCOLUNAS; j++)
		{
			// Tenta marcar a zona do pixel e de todo o blob a ele pertencente
			// Se conseguir, contabiliza mais uma zona
			if (marcar_zona((*imag),b, i, j, R, G, B, d) == SUCESSO)
			{
					if (b->npixeis >= 10) // caso não seja, não faz nada, caso seja aloca espaço para próximo blob *
					// * e adiciona o blob à lista de blobs na imagem.
					{
						addord(b, imag);
						b = criarBlob();
					}
			}

		}
	}
	//caso o blob não tenha sido criado
	if (b->npixeis == 0)
	{
		//(*imag)->inicio = b->proximo;
		free(b);
	}

}

void det_media(IMAGEM *im, BLOBS *b)
{
	ELEMENTOZONA *z;
	z = b->inicio;
	int linha;
	int coluna;
	while(z)
	{
		b->mediaR = b->mediaR + z->pixels->R;
		b->mediaG = b->mediaG + z->pixels->G;
		b->mediaB = b->mediaB + z->pixels->B;
		z = z->proximo;
	}
	b->mediaR = b->mediaR / b->npixeis;
	b->mediaG = b->mediaG / b->npixeis;
	b->mediaB = b->mediaB / b->npixeis;
}

void det_desvio_padrao(IMAGEM *im, BLOBS *b)
{
	ELEMENTOZONA *z;
	z = b->inicio;
	if (b->npixeis > 0)
	{
			b->desv_padraoR = b->desv_padraoR + pow((z->pixels->R) - b->mediaR, 2);
			b->desv_padraoG = b->desv_padraoG + pow((z->pixels->G) - b->mediaG, 2);
			b->desv_padraoB = b->desv_padraoB + pow((z->pixels->B) - b->mediaB, 2);
			z = z->proximo;
	}
		b->desv_padraoR = sqrt(b->desv_padraoR / b->npixeis);
		b->desv_padraoG = sqrt(b->desv_padraoG / b->npixeis);
		b->desv_padraoB = sqrt(b->desv_padraoB / b->npixeis);
		b->desv_padraoTotal = (b->desv_padraoR + b->desv_padraoG + b->desv_padraoB) / 3; 
}


	
void imag_com_mais_blobs(LISTAIMG *limg, ANALISEIMAGEM *img)
{
	IMAGEM *imag;
	imag = limg->inicio;
	// inicialização de img_mais_blobs = 0 no principal.cpp
	while (imag)
	{
		
		if (imag->blobs > img->img_mais_blobs)
		{
			img->img_mais_blobs = imag->blobs;
			strcpy(img->im_max_blobs, imag->nome_imagem);
		}
		imag = imag->proximo;
	}
	
}

void blob_menor_desvio_padrão(LISTAIMG *limg, ANALISEIMAGEM *img)
{
	BLOBS *b;
	IMAGEM *im;
	float menor_dp;
	menor_dp = 300.00;
	im = limg->inicio;
	while (im)
	{
		b = im->inicio;
		while (b)
		{
		
			if (b->desv_padraoTotal < menor_dp)
			{
				menor_dp = b->desv_padraoTotal;
				strcpy(img->im_min_dp, im->nome_imagem);
			}
			b = b->proximo;
		}
		im = im->proximo;
	}
	printf("A imagem que contém o blob com menor desvio padrão é:%s\n\n", img->im_min_dp);
}


void destruir_zoneamento(ELEMENTOZONA *im)
{
	ELEMENTOZONA *aux; // para os pixeis
	while (im)
	{
		aux = im;
		im = im->proximo;
		free(aux);
	}
}

void destruirzona(BLOBS *b)
{
	BLOBS *aux;
	while (b)
	{
		aux = b;
		b = b->proximo;
		destruir_zoneamento(aux->inicio);
		free(aux);
	}
}
void destruirMatrizpixeis(PIXEL **p,IMAGEM *im)
{
	int i, j;
	for (i = 0; i < im->NLINHAS; i++)
	{
		free(p[i]); // apaga as colunas
	}
	free(p); // apaga as linhas

}
void DestruirImagem(IMAGEM *Imag)
{
	IMAGEM *aux;
	while (Imag)
	{
		aux = Imag;
		Imag = Imag->proximo;
		destruirzona(aux->inicio);
		destruirMatrizpixeis(aux->pixels,aux);
		free(aux);
	}
}




int LerFicheiro(char *fi, LISTAIMG *LImag,int R,int G,int B,int d) // fi é variável para o nome do ficheiro
{
	int i, j, nC, nL, ncanais;
	FILE *f;
	PIXEL *p;
	PIXEL **m;
	IMAGEM *Imag;
	BLOBS *b;
	ELEMENTOZONA *e;
	e = (ELEMENTOZONA *)malloc(sizeof(ELEMENTOZONA));
	b = (BLOBS *)malloc(sizeof(BLOBS));
	Imag = (IMAGEM *)malloc(sizeof(IMAGEM));
	p = (PIXEL *)malloc(sizeof(PIXEL));
	f = fopen(fi, "r");  // abre um ficheiro qualquer
	while (!feof(f))
	{
		system("cls");
		printf("A analisar imagem\n\n");
		Imag = criar_imagem();
		fscanf(f,"%s", &Imag->nome_imagem);
		if (feof(f))
		{
			free(Imag);
			break;
		}
		fscanf(f, "%d", &Imag->NLINHAS);
		fscanf(f, "%d", &Imag->NCOLUNAS);
		fscanf(f, "%d", &Imag->NCANAIS);
		
		if (Imag->NCANAIS != 3) // caso o nº de canais que conste no ficheiro seja diferente de 3,  fecha o ficheiro. 
		{
			fclose(f);
			printf("\nNúmero de canais incorreto!!!\n\n");
			return NULL;
		} 
		Imag->pixels= criarmatriz(Imag->NLINHAS, Imag->NCOLUNAS);
		for (i = 0; i < Imag->NLINHAS; i++)
		{
			for (j = 0; j < Imag->NCOLUNAS; j++)
			{
				fscanf(f, "%d", &Imag->pixels[i][j].R);
				fscanf(f, "%d", &Imag->pixels[i][j].G);
				fscanf(f, "%d", &Imag->pixels[i][j].B);
				Imag->pixels[i][j].visitado = 0;
			}

		}
		calcular_zonas(&Imag, R, G, B, d);
			
		//adiciona a imagem acabada de criar na lista de imagens 
		Imag->proximo = LImag->inicio;
		LImag->inicio = Imag;
		b = Imag->inicio;
		
		while (b)
		{
			det_media(Imag, b);
			det_desvio_padrao(Imag, b);
			b = b->proximo;
			
		}
	}
	
	fclose(f);
	return INSUCESSO;
}



