/*=========================================================================
UNIVERSIDADE FEDERAL DE SÃO CARLOS - UFSCar - Sorocaba
CIÊNCIA DA COMPUTAÇÃO - COMPUTAÇÃO GRÁFICA
PROFESSOR MURILLO RODRIGO PETRUCELLI HOMEM

GRUPO 6

Daniel Ramos Miola 				438340
Giulianno Raphael Sbrugnera 	408093
Igor Felipe Ferreira Ceridório 	408611
Rafael Paschoal Giordano 		408298

ARQUIVO: 			  main2d.c

OBJETIVO:			  exemplo de execução de algumas rotinas para objetos
					  2D, com a finalidade de demonstrar o uso de funções
					  gráficas implementadas pelo grupo no decorrer do semestre.


RESULTADO DA EXECUÃO: são criados oito objetos, quatro triângulos e quatro
					  quadrados. Eles são criados dois a dois, lado a lado, 
					  de tamanho idêntico. Então, o polígono do lado direito
					  sofre alguma transformação, afim de demonstrar a
					  corretude das implementações de transformações com o uso
					  de coordenadas homogêneas e uso do ponto médio do objeto,
					  para que após transformada, a imagem mantenha-se em seu 
					  lugar de origem.

PARA COMPILAR:		  gcc main2d.c -o <nome_do_executavel> -lm -lX11

==========================================================================*/

/*==========================
  Bibliotecas utilizadas
==========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>

#define EventMask (KeyPressMask | ExposureMask)

/*==========================
  Estruturas utilizadas
==========================*/

//definição de um ponto
typedef struct Point{
	float x, y;	
}point;

//definição para uma cor RGB
typedef struct RGB {
	float r, g, b;
}RGB;

//defnição para uma cor HSV
typedef struct HSV {
	float h, s, v;
}HSV;

//definição para uma lookup table
typedef struct Lookup{
	int numColors;
	RGB colors;
}lookup;

//definição para um objeto 2D
typedef struct Node{
	point ptList;  //coordinates of the point
	point ptListN; //point normalized
	point ptListD; //point discrete
	struct Node *next;
}node;

typedef node *list;

/*==========================
  Protótipos das funções
==========================*/

point sruToSrn(point *pt, point *maxXY, point *minXY);
point srnToSrd(point *ptN, point *viewPortXY);
point middleObject(list *p_L);
void  setUniverse(point *minXY, point *maxXY);
void  setViewPort(point *viewPortXY);
void  initMatrix(int *image, point *viewPortXY);
void  addEndList(list *p_l, point *pt, point *maxXY, point *minXY, point *viewPortXY);
void  printListBresenham(list *p_l, int *input, point *viewPortXY, int color);
void  bresenham(int *input, point *ptOneD, point *ptTwoD, point *viewPortXY, int color);
void  drawWindow(point *viewPortXY);
void  drawWindowLine(point *viewPortXY, int *input, lookup *lkt);
void  multMatrixArray(float *matrix, float *vector, float *result);
void  translate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int dx, int dy);
void  scale(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int sx, int sy);
void  rotate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int a);
void  mirror(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int mOpt);
void  shearing(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int shOpt, int shx, int shy);
void  multThreeByThreeMatrix(float first[][3], float second[][3], float result[][3]);
int   startList(list *p_l);
int   emptyList(list *p_l);

/*==========================
  Início do main
==========================*/

int main(){

	//declaração de variáveis
	int i, j; 								//contadores
	point  minXY, maxXY, viewPortXY, pt;	//mínimo e máximo do universo e dimensão da viewport

	//definição da quantidade de objetos
	list l[8]; int objColor[8];

	//cria uma lookup table com sete cores
	lookup lkt[7];
	lkt[0].colors.r = 1; lkt[0].colors.g = 1; lkt[0].colors.b = 1;
	lkt[1].colors.r = 0; lkt[1].colors.g = 0; lkt[1].colors.b = 0;
	lkt[2].colors.r = 1; lkt[2].colors.g = 1; lkt[2].colors.b = 0;
	lkt[3].colors.r = 1; lkt[3].colors.g = 0; lkt[3].colors.b = 0;
	lkt[4].colors.r = 0; lkt[4].colors.g = 1; lkt[4].colors.b = 0;	
	lkt[5].colors.r = 0; lkt[5].colors.g = 0; lkt[5].colors.b = 1;
	lkt[6].colors.r = 0; lkt[6].colors.g = 1; lkt[6].colors.b = 1;

	//define o tamanho do universo
	setUniverse(&minXY, &maxXY);

	//define o tamanho do dispositivo discreto
	setViewPort(&viewPortXY);

	//declaracao e inicailizacao do buffer da imagem
	int image[(int)viewPortXY.x * (int)viewPortXY.y];
	initMatrix(image, &viewPortXY);

	//definição das cores das linhas dos objetos
	objColor[0] = 6;
	objColor[1] = 5;
	objColor[2] = 4;
	objColor[3] = 3;
	objColor[4] = 2;
	objColor[5] = 6;
	objColor[6] = 5;
	objColor[7] = 4;

	//inicializacao das listas de pontos dos objetos
	startList(&l[0]);
	startList(&l[1]);
	startList(&l[2]);
	startList(&l[3]);
	startList(&l[4]);
	startList(&l[5]);
	startList(&l[6]);
	startList(&l[7]);

	//definição do primeiro polígono (quadrado)
	pt.x = 10; pt.y = 5;  addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 5;  addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 10; addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 10; addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 5;  addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do segundo polígono (quadrado)
	pt.x = 35; pt.y = 5;  addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 5;  addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 10; addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 10; addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 5;  addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de rotação em 45º no seundo polígono
	rotate(&l[1], &minXY, &maxXY, &viewPortXY, 45);

	//definição do terceiro polígono (triângulo)
	pt.x = 10; pt.y = 15; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 15; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 12; pt.y = 20; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 15; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do quarto polígono (triângulo)
	pt.x = 35; pt.y = 15; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 15; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 37; pt.y = 20; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 15; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de espelhamento em torno do eixo X no quarto polígono
	mirror(&l[3], &minXY, &maxXY, &viewPortXY, 0);

	//definição do quinto polígono (triângulo)
	pt.x = 10; pt.y = 25; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 25; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 12; pt.y = 30; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 25; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do sexto polígono (triângulo)
	pt.x = 35; pt.y = 25; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 25; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 37; pt.y = 30; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 25; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de cisalhamento com valor 2 para o sexto polígono
	shearing(&l[5], &minXY, &maxXY, &viewPortXY, 0, 1, 1);

	//definição do sétimo polígono (quadrado)
	pt.x = 10; pt.y = 35; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 35; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 40; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 40; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 35; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do oitavo polígono (quadrado)
	pt.x = 35; pt.y = 35; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 35; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 40; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 40; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 35; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de escalamento no oitavo polígono
	scale(&l[7], &minXY, &maxXY, &viewPortXY, 2, 2);

	//desenho das linhas dos objetos
	printListBresenham(&l[0], image, &viewPortXY, objColor[0]);
	printListBresenham(&l[1], image, &viewPortXY, objColor[1]);
	printListBresenham(&l[2], image, &viewPortXY, objColor[2]);
	printListBresenham(&l[3], image, &viewPortXY, objColor[3]);
	printListBresenham(&l[4], image, &viewPortXY, objColor[4]);
	printListBresenham(&l[5], image, &viewPortXY, objColor[5]);
	printListBresenham(&l[6], image, &viewPortXY, objColor[6]);
	printListBresenham(&l[7], image, &viewPortXY, objColor[7]);

	//exibição da imagem final
	drawWindowLine(&viewPortXY, image, lkt);

	return 0;
}

/*==========================
  Implementação das funções
==========================*/

/*Função 1
  Definição das dimensões mínimas e máximas do universo*/
void setUniverse(point *minXY, point *maxXY){
	minXY->x = 0;
	minXY->y = 0;
	maxXY->x = 50;
	maxXY->y = 50;
}

/*Função 2
  Definição das dimensões do dispositivo discreto*/
void setViewPort(point *viewPortXY){
	viewPortXY->x = 500;
	viewPortXY->y = 500;
}

/*Função 3
  Inicialização da matriz onde será guardada a imagem*/
void initMatrix(int *image, point *viewPortXY){
	int i, j;
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[(i * (int)viewPortXY->y) + j] = 0;
		}
	}
}

/*Função 4
  Inicializa uma lista que conterá os pontos de um objeto*/
int startList(list *p_l){
	*p_l = NULL;
}

/*Função 5
  Verifica se uma lista está vazia ou não*/
int emptyList(list *p_l){
	if(*p_l == NULL) return 1;
	return 0;
}

/*Função 6
  Adiciona um novo ponto a um determinado objeto*/
void addEndList(list *p_l, point *pt, point *maxXY, point *minXY, point *viewPortXY){
	point auxPointN;
	node *newNode, *auxNode;
	newNode = (node*) malloc (sizeof(node));
	
	newNode->ptList.x = pt->x;
	newNode->ptList.y = pt->y;
	newNode->next = NULL;

	//converts the newNode to srn
	newNode->ptListN = sruToSrn(pt, maxXY, minXY);
	auxPointN = sruToSrn(pt, maxXY, minXY);

	//convertes the newNode to srd
	newNode->ptListD = srnToSrd(&auxPointN, viewPortXY);

	//puts the newNode in the end of the list
	if(emptyList(p_l)){
		*p_l = newNode;
	} else {
		auxNode = *p_l;
		while(auxNode->next != NULL){
			auxNode = auxNode->next;
		}
		auxNode->next = newNode;
	}
}

/*Função 7
  Converte um ponto do SRU para o SRN*/
point sruToSrn(point *pt, point *maxXY, point *minXY){
	point ptN;	
	ptN.x = (pt->x - minXY->x) / (maxXY->x - minXY->x);
	ptN.y = (pt->y - minXY->y) / (maxXY->y - minXY->y);
	return ptN;
}

/*Função 8
  Converte um ponto do SRN para o SRD*/
point srnToSrd(point *ptN, point *viewPortXY){
	point ptD;
	ptD.x = round(ptN->x * (viewPortXY->x - 1));
	ptD.y = round(ptN->y * (viewPortXY->y - 1));
	return ptD;
}

/*Função 9
  Traça todas as retas de um objeto dado sua lista de pontos*/
void printListBresenham(list *p_l, int *input, point *viewPortXY, int color){
	node *auxNode;
	auxNode = *p_l;
	point ptOneD, ptTwoD;

	while(auxNode != NULL){
		ptOneD = auxNode->ptListD;
		if(auxNode->next != NULL){
			ptTwoD = auxNode->next->ptListD;
			bresenham(input, &ptOneD, &ptTwoD, viewPortXY, color);
		}
		auxNode = auxNode->next;
	}
}

/*Função 10
  Traça uma reta entre dois pontos. Implementação do algoritmo do ponto médio*/
void bresenham(int *input, point *ptOneD, point *ptTwoD, point *viewPortXY, int color){
	int dx, dy; 
    int sx, sy; 
    int erro; 
    int e2; 
    int p1x, p1y, p2x, p2y;
    int WIDTH = viewPortXY->x;
    int HEIGHT = viewPortXY->y;

    p1x = ptOneD->x;
	p1y = ptOneD->y;
	p2x = ptTwoD->x;
	p2y = ptTwoD->y;

  
    dx = abs(p2x - p1x);
    dy = abs(p2y - p1y);
    p1x < p2x ? (sx = 1) : (sx = -1);
    p1y < p2y ? (sy = 1) : (sy = -1);
    erro = dx - dy;

    while(1){
        if(!(p1x > WIDTH || p1y > HEIGHT || p1x <= 0 || p1y <= 0)){
            input[(p1y)*HEIGHT+p1x] = color;
        }
        if(p1x == p2x && p1y == p2y) 
            break;
        e2 = erro * 2;
        if(e2 > -dy){
            erro -= dy;
            p1x += sx;
        }
        if(e2 < dx){
            erro += dx;
            p1y += sy;
        }   
    }
}

/*Função 11
  Cria uma janela no ambiente X*/
void drawWindow(point *viewPortXY){
	Display *display;
	GC gc;
	Window win, root_window;
  	unsigned long valuemask = 0;
  	XGCValues values;
  	XColor cor;
  	XEvent an_event;
  	int x = 0, y = 0, screennumber, espessura = 4;
 
  	unsigned long white_pixel, black_pixel;
  	display = XOpenDisplay(NULL); 

 	/* Retorna o número do screen referenciado pela função XOpenDisplay(). */
  	screennumber = DefaultScreen(display); 
 	/* Determina o identificador da janela raiz do monitor. Esta janela sempre existirá. */
  	root_window = RootWindow(display, screennumber); 
	/* Valor dos pixels da borda. */
  	black_pixel = BlackPixel(display,screennumber);  
	/* Valor dos pixels no interior (fundo) da janela. */
  	white_pixel = WhitePixel(display, screennumber); 
 	/* Cria uma janela. */
  	win = XCreateSimpleWindow(display,root_window,x,y,viewPortXY->x,viewPortXY->y,espessura,black_pixel,white_pixel);
	 XStoreName(display, win, "Monitor Virtual");
  	/*
 	    O fato de criar a janela não significa que ela vai aparecer na tela. Para isso, usamos
 	    a XMapWindow() para que a janela seja exibida na tela.
 	 */    
  	XMapWindow(display, win); 
 	 /* Cria o contexto gráfico para nossa aplicação. */
  	gc = XCreateGC(display, win, valuemask, &values); 
  	/* Atua praticamente da mesma forma que a XFlush(). */
  	XSync(display, False);  
 	/* Altera a cor da janela associada ao contexto gráfico gc. */ 
  	XSetForeground(display, gc, white_pixel);
 	 /* Altera a cor de fundo da janela associada ao contexto gráfico. */
  	XSetBackground(display, gc, black_pixel); 
	 /* Aloca na variável "cor" as informações sobre a cor vermelha. */
  	XAllocNamedColor(display, XDefaultColormap(display, screennumber), "red", &cor, &cor);  
 	 /* Altera no contexto gráfico a cor que será usada para desenhar um pixel. */
  	XSetForeground(display, gc, cor.pixel);
 	 /* Desenha um pixel nas coordenadas (15,15) com a cor definida pela função anterior. */
  	XDrawPoint(display, win, gc, 15, 15);
 	/* Faz com que o X execute todas as requisições pendentes. */
  	XFlush(display);
  	XSelectInput(display, win, ExposureMask);
  	/* Trata os eventos */ 
  	while(1) {
    	 XNextEvent(display, &an_event);
     	switch(an_event.type) {
  	case Expose:
              	XDrawPoint(display, win, gc, 15, 15);
		        break;
  	/* outros eventos ... */
        }
     }
  	XFreeGC(display,gc);  
  	XCloseDisplay(display);
}

/*Função 12
  Cria uma janela no ambiente X e desenha a imagem armazenada no buffer*/
void drawWindowLine(point *viewPortXY, int *input, lookup *lkt){
	Display               * display;
	XImage                * ximage;
	Window                window;
	XEvent                an_event;
	GC                    gc;
	Visual                * visual;
	XGCValues             values;
	int                   m, n, screen, dplanes;
	int                   width, height, ret = 1;
	//RGB          		  * cor, *lineColor;

	width = viewPortXY->x;
	height = viewPortXY->y;

	char image[(int)viewPortXY->x][(int)viewPortXY->y];

	//decoding the vector of ints to a matrix to simplify the understanding of attributions
	for(m = 0; m < viewPortXY->x; m++){
		for(n = 0; n < viewPortXY->y; n++){
			image[m][n] = input[(m * (int)viewPortXY->y + n)];
		}
	}


	if ((display = XOpenDisplay(NULL)) == NULL) ret = 0;
	else {  
	  screen = DefaultScreen(display);
	  dplanes = DisplayPlanes(display,screen);   
	  visual = XDefaultVisual(display,screen);

	  if (!(window=XCreateSimpleWindow(display,RootWindow(display,screen),0,0,width,height,1,BlackPixel(display,screen),WhitePixel(display,screen)))) ret = 0;
	  else {
	    XSelectInput(display, window, EventMask);
	    XStoreName(display, window, "Resultado");
	    gc = XCreateGC(display, window, 0, &values);
	  
	    XMapWindow(display,window);
	    XSync(display,False);
	  
	    ximage = XCreateImage(display,visual,dplanes,ZPixmap,0,malloc(width*height*sizeof(int)),width,height,8,0);

	    for(m=0;m<height;m++) {
	      for(n=0;n<width;n++) {
	        ximage -> data[(m*4)*width+n*4] = (char) round((lkt[image[m][n]].colors.r)*255);
	        ximage -> data[(m*4)*width+n*4+1] = (char) round((lkt[image[m][n]].colors.g)*255);
	        ximage -> data[(m*4)*width+n*4+2] = (char) round((lkt[image[m][n]].colors.b)*255);
	        ximage -> data[(m*4)*width+n*4+3] = (char) 0;
	        }
	    }

	   	/* Trata os eventos */
	    while(1) {
	    XNextEvent(display, &an_event);
	    switch(an_event.type) {
		case Expose:
	            XPutImage(display,window,gc,ximage,0,0,0,0,width,height);
	              break;
		/* outros eventos ... */
	         }
	      }

	      }
	    }
}

/*Função 13
  Multiplica uma matriz 3x3 por um vetor de 3 elementos*/
void multMatrixArray(float *matrix, float *vector, float *result){
	result[0] = (matrix[0] * vector[0]) + (matrix[1] * vector[1]) + (matrix[2] * vector[2]);
	result[1] = (matrix[3] * vector[0]) + (matrix[4] * vector[1]) + (matrix[5] * vector[2]);
	result[2] = (matrix[6] * vector[0]) + (matrix[7] * vector[1]) + (matrix[8] * vector[2]);
}

/*Função 14
  Translação (deslocamento) de um objeto*/
void translate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int dx, int dy){
	node *auxNode; //points to the object that will be translated
	point pt, ptN; //auxiliar points

	auxNode = *p_L;
	//translation matrix declaration
	float transMatrix[9] = {1, 0, dx, 0, 1, dy, 0, 0, 1};
	//point vector and result array declaration
	float p[3], result[3];

	while(auxNode != NULL){

		p[0] = auxNode->ptList.x;
		p[1] = auxNode->ptList.y;
		p[2] = 1;

		multMatrixArray(transMatrix, p, result);

		//updating the point values
		auxNode->ptList.x = pt.x = result[0];
		auxNode->ptList.y = pt.y = result[1];

		//converts the translated point to srn
		auxNode->ptListN = ptN = sruToSrn(&pt, maxXY, minXY);
		//converts the translated point to srd
		auxNode->ptListD = srnToSrd(&ptN, viewPortXY);

		auxNode = auxNode->next;
	}
}

/*Função 15
  Escalamento de um objeto*/
void scale(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int sx, int sy){
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	//scaling matrix declaration
	float scaleMatrix[9] = {sx, 0, 0, 0, sy, 0, 0, 0, 1};
	//point vector and result array declaration
	float p[3], result[3];

	while(auxNode != NULL){

		p[0] = auxNode->ptList.x;
		p[1] = auxNode->ptList.y;
		p[2] = 1;

		multMatrixArray(scaleMatrix, p, result);

		//updating the point values
		auxNode->ptList.x = pt.x = result[0];
		auxNode->ptList.y = pt.y = result[1];

		//converts the translated point to srn
		auxNode->ptListN = ptN = sruToSrn(&pt, maxXY, minXY);
		//converts the translated point to srd
		auxNode->ptListD = srnToSrd(&ptN, viewPortXY);

		auxNode = auxNode->next;
	}

	//translates the object to the original point given the middle of it
	translate(p_L, minXY, maxXY, viewPortXY, ptMiddle.x, ptMiddle.y);
}

/*Função 16
  Rotação de um objeto*/
void rotate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int a){
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));	

	//rotation matrix declaration
	float rotateMatrix[9] = {cos(a), -sin(a), 0, sin(a), cos(a), 0, 0, 0, 1};
	//point vector and result array declaration
	float p[3], result[3];

	while(auxNode != NULL){

		p[0] = auxNode->ptList.x;
		p[1] = auxNode->ptList.y;
		p[2] = 1;

		multMatrixArray(rotateMatrix, p, result);

		//updating the point values
		auxNode->ptList.x = pt.x = result[0];
		auxNode->ptList.y = pt.y = result[1];

		//converts the rotated point to srn
		auxNode->ptListN = ptN = sruToSrn(&pt, maxXY, minXY);
		//converts the rotated point to srd
		auxNode->ptListD = srnToSrd(&ptN, viewPortXY);

		auxNode = auxNode->next;
	}

	//translates the object to the original point given the middle of it
	translate(p_L, minXY, maxXY, viewPortXY, ptMiddle.x, ptMiddle.y);
}

/*Função 17
  Espelhamento de um objeto. @param mOpt: 0 espelha em X; 1 espelha em Y; 2 espelha em XY*/
void mirror(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int mOpt){
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	//mirror matrix declaration
	float mirrorMatrixX[9] = {1, 0, 0, 0, -1, 0, 0, 0, 1};
	float mirrorMatrixY[9] = {-1, 0, 0, 0, 1, 0, 0, 0, 1};
	float mirrorMatrixXY[9] = {-1, 0, 0, 0, -1, 0, 0, 0, 1};
	
	//point vector and result array declaration
	float p[3], result[3];

	while(auxNode != NULL){

		p[0] = auxNode->ptList.x;
		p[1] = auxNode->ptList.y;
		p[2] = 1;

		if(mOpt == 0)
			multMatrixArray(mirrorMatrixX, p, result);
		if(mOpt == 1)
			multMatrixArray(mirrorMatrixY, p, result);
		if(mOpt == 2)
			multMatrixArray(mirrorMatrixXY, p, result);	

		//updating the point values
		auxNode->ptList.x = pt.x = result[0];
		auxNode->ptList.y = pt.y = result[1];

		//converts the translated point to srn
		auxNode->ptListN = ptN = sruToSrn(&pt, maxXY, minXY);
		//converts the translated point to srd
		auxNode->ptListD = srnToSrd(&ptN, viewPortXY);

		auxNode = auxNode->next;
	}

	//translates the object to the original point given the middle of it
	translate(p_L, minXY, maxXY, viewPortXY, ptMiddle.x, ptMiddle.y);
}

/*Função 18
  Cisalhamento de um objeto. @param shOpt: 0 cisalha em X; 1 cisalha em Y*/
void shearing(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int shOpt, int shx, int shy){
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	//shearing matrix declaration
	float shearMatrixX[9] = {1, shx, 0, 0, 1, 0, 0, 0, 1};
	float shearMatrixY[9] = {1, 0, 0, shy, 1, 0, 0, 0, 1};

	//point vector and result array declaration
	float p[3], result[3];

	while(auxNode != NULL){

		p[0] = auxNode->ptList.x;
		p[1] = auxNode->ptList.y;
		p[2] = 1;

		if(shOpt == 0)
			multMatrixArray(shearMatrixX, p, result);
		if(shOpt == 1)
			multMatrixArray(shearMatrixY, p, result);

		//updating the point values
		auxNode->ptList.x = pt.x = result[0];
		auxNode->ptList.y = pt.y = result[1];

		//converts the translated point to srn
		auxNode->ptListN = ptN = sruToSrn(&pt, maxXY, minXY);
		//converts the translated point to srd
		auxNode->ptListD = srnToSrd(&ptN, viewPortXY);

		auxNode = auxNode->next;
	}

	//translates the object to the original point given the middle of it
	translate(p_L, minXY, maxXY, viewPortXY, ptMiddle.x, ptMiddle.y);
}

/*Função 19
  Calcula o ponto médio de um objeto*/
point middleObject(list *p_L){
	point ptMiddle, ptMax, ptMin;
	node *auxNode;
	auxNode = *p_L;

	if(auxNode != NULL){
		ptMin.x = auxNode->ptList.x;
		ptMin.y = auxNode->ptList.y;
		ptMax.x = auxNode->ptList.x;
		ptMin.y = auxNode->ptList.y;
	}

	while(auxNode != NULL){
		
		//obtaining the minimum points
		if(auxNode->ptList.x < ptMin.x)
			ptMin.x = auxNode->ptList.x;
		if(auxNode->ptList.y < ptMin.y)
			ptMin.y = auxNode->ptList.y;

		//obtaining the maximum points
		if(auxNode->ptList.x > ptMax.x)
			ptMax.x = auxNode->ptList.x;
		if(auxNode->ptList.y > ptMax.y)
			ptMax.y = auxNode->ptList.y;

		//iterates the points list
		auxNode = auxNode->next;
	}

	//calculates the middle point
	ptMiddle.x = ((ptMax.x - ptMin.x)/2) + ptMin.x;
	ptMiddle.y = ((ptMax.y - ptMin.y)/2) + ptMin.y;

	return ptMiddle;
}

/*Função 20
  Multiplica duas matrizes 3x3*/
void multThreeByThreeMatrix(float first[][3], float second[][3], float result[][3]){

	int i, j, k;
	float sum;

	for (i = 0; i <= 2; i++) {
		for (j = 0; j <= 2; j++) {
			sum = 0;
			for (k = 0; k <= 2; k++) {
				sum = sum + first[i][k] * second[k][j];
			}
			result[i][j]=sum;
		}
	}
}

/*Função 21
  Converte uma cor RGB para HSV*/
void rgbTohsv(RGB rgb, HSV *hsv) {
	float max, min;

	min = rgb.r;

	if (rgb.g < min)
		min = rgb.g;
	if (rgb.b < min)
		min = rgb.b;

	max = rgb.r;

	if (rgb.g > max)
		max = rgb.g;
	if (rgb.b > max)
		max = rgb.b;

	if ((max = rgb.r) && (rgb.g >= rgb.b)) {
		hsv->h = 60 * ((rgb.g - rgb.b) / (max - min)) + 0;
	} else if ((max = rgb.r) && (rgb.g < rgb.b)) {
		hsv->h = 60 * ((rgb.g - rgb.b) / (max - min)) + 360;
	} else if ((max = rgb.g)) {
		hsv->h = 60 * ((rgb.b - rgb.r) / (max - min)) + 120;
	} else {
		hsv->h = 60 * ((rgb.r - rgb.g) / (max - min)) + 240;
	}

	hsv->s = (max - min) / max;
	hsv->v = max;
}

/*Função 22
  Converte uma cor HSV para RGB*/
void hsvTorgb(HSV hsv, RGB *rgb) {
	float f, p, q, t;
	int hi;

	if (hsv.s == 0) {
		rgb->r = hsv.v;
		rgb->g = hsv.v;
		rgb->b = hsv.v;
	} else {
		hi = floor(hsv.h / 60);
		hi = hi  % 6;
		f = (hsv.h / 60) - hi;
		p = hsv.v * (1 - hsv.s);
		q = hsv.v * (1 - (f * hsv.s));
		t = hsv.v * (1 - (1 - f) * hsv.s);

		switch (hi)
		{
			case 0:
				rgb->r = hsv.v;
				rgb->g = t;
				rgb->b = p;
			break;

			case 1:
				rgb->r = q;
				rgb->g = hsv.v;
				rgb->b = p;
			break;

			case 2:
				rgb->r = p;
				rgb->g = hsv.v;
				rgb->b = t;
			break;

			case 3:
				rgb->r = p;
				rgb->g = q;
				rgb->b = hsv.v;
			break;

			case 4:
				rgb->r = t;
				rgb->g = p;
				rgb->b = hsv.v;
			break;

			case 5:
				rgb->r = hsv.v;
				rgb->g = p;
				rgb->b = q;
			break;
		}
	}
}
