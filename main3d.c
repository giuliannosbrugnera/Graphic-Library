/*=========================================================================
UNIVERSIDADE FEDERAL DE SÃO CARLOS - UFSCar - Sorocaba
CIÊNCIA DA COMPUTAÇÃO - COMPUTAÇÃO GRÁFICA
PROFESSOR MURILLO RODRIGO PETRUCELLI HOMEM

GRUPO 6

Daniel Ramos Miola 				438340
Giulianno Raphael Sbrugnera 	408093
Igor Felipe Ferreira Ceridório 	408611
Rafael Paschoal Giordano 		408298

ARQUIVO: 			  main3d.c

OBJETIVO:			  exemplo de execução de algumas rotinas para objetos
					  3D, com a finalidade de demonstrar o uso de funções
					  gráficas implementadas pelo grupo no decorrer do semestre.


RESULTADO DA EXECUÃO: é criado um prisma triangular identico ao usado no codigo de
					  exemplo dado.

PARA COMPILAR:		  gcc main3d.c -o <nome_do_executavel> -lm -lX11

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

typedef struct PointD{
	int x, y;	
}pointD;

typedef struct Point3D{
	float x, y, z;	
}point3D;

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

// objects 3D
typedef struct Node3D{
	point3D ptList3D;  //coordinates of the point
	point3D ptList3DN; //point normalized
	pointD ptListD; //point discrete
	struct Node3D *next;
}node3D;

typedef node3D *face3D;

/*==========================
  Protótipos das funções
==========================*/

void setUniverse3D(point3D *minXYZ, point3D *maxXYZ);
void setViewPort(point *viewPortXY);
void initMatrix(int *image, point *viewPortXY);
void crossProduct(point3D a, point3D b, point3D *c);
int startList3D(face3D *face);
int emptyList3D(face3D *face);
void addEndList3D(face3D *face, point3D *pt3D, point3D *maxXYZ, point3D *minXYZ);
point3D sruToSrn(point3D pt, point3D *maxXYZ, point3D *minXYZ);
pointD srnToSrd(point3D pt3DN, point *viewPortXY);
void conversao(face3D *face, point3D *maxXYZ, point3D *minXYZ, point *viewPortXY);
void mudancaDeBase(face3D *face, point3D u, point3D v, point3D w); 
void projecaoPerspectiva(face3D *face, point3D p_proj, point3D c_proj);
void printListBresenham3D(face3D *face, int *input, point *viewPortXY, int color);
void bresenham(int *input, pointD *ptOneD, pointD *ptTwoD, point *viewPortXY, int color);
void drawWindowLine(point *viewPortXY, int *input, lookup *lkt);

/*==========================
  Início do main
==========================*/

int main(){

	/*-----------------------------------------
		Variables declaration
	-----------------------------------------*/
	
	point viewPortXY; //universe min and max and viewport dimensions
	point3D minXYZ, maxXYZ, pt3D; //universe3D min and max
	
	/*-----------------------------------------
		Look-up table definition
	-----------------------------------------*/

	//cria uma lookup table com sete cores
	lookup lkt[7];
	lkt[0].colors.r = 1; lkt[0].colors.g = 1; lkt[0].colors.b = 1;
	lkt[1].colors.r = 0; lkt[1].colors.g = 0; lkt[1].colors.b = 0;
	lkt[2].colors.r = 1; lkt[2].colors.g = 1; lkt[2].colors.b = 0;
	lkt[3].colors.r = 1; lkt[3].colors.g = 0; lkt[3].colors.b = 0;
	lkt[4].colors.r = 0; lkt[4].colors.g = 1; lkt[4].colors.b = 0;	
	lkt[5].colors.r = 0; lkt[5].colors.g = 0; lkt[5].colors.b = 1;
	lkt[6].colors.r = 0; lkt[6].colors.g = 1; lkt[6].colors.b = 1;

	/*-----------------------------------------
		Universe and viewport setting
	-----------------------------------------*/

	//define o tamanho do universo
	setUniverse3D(&minXYZ, &maxXYZ);

	//define o tamanho do dispositivo discreto
	setViewPort(&viewPortXY);

	/*-----------------------------------------
		Image buffer declaration and inicialization
	-----------------------------------------*/

	int image[(int)viewPortXY.x * (int)viewPortXY.y]; //creating the matrix
	initMatrix(image, &viewPortXY); //initializes the matrix

	/*-----------------------------------------
		Coordnates system
	-----------------------------------------*/

	// Definindo o Sistema de Coordenadas de Visualizacao 
    point3D u, v, w; //Bases u, v e w
 
    v.x = 0.0;	
    v.y = 1.0;	
    v.z = 0.0; 
    w.x = 0.0;	
    w.y = 0.0;	
    w.z = -1.0; 
    
    crossProduct(v, w, &u); // produto vetorial

    // Definição dos pontos da projecao
    point3D c_proj; //centro de projecao
    point3D p_proj; //plano de projecao
    
    c_proj.x = 0.0;	
    c_proj.y = 0.0;	
    c_proj.z = -45.0;

    p_proj.x = 0.0;	
    p_proj.y = 0.0;	
    p_proj.z = 40.0; 
    

	/*-----------------------------------------
		Objects declaration
	-----------------------------------------*/	
	
	//definição da quantidade de cores das faces
	int faceColor[5];

	//definição das cores das linhas das faces do objeto
	faceColor[0] = 6;
	faceColor[1] = 5;
	faceColor[2] = 4;
	faceColor[3] = 3;
	faceColor[4] = 2;

	// Declaracao do objeto de 5 faces
    face3D objeto3d[5];

    //inicializacao das listas de pontos das faces do objeto
	startList3D(&objeto3d[0]);
	startList3D(&objeto3d[1]);
	startList3D(&objeto3d[2]);
	startList3D(&objeto3d[3]);
	startList3D(&objeto3d[4]);

	//definiçao da primeira face do objeto 3d
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);

	// definiçao da segunda face do objeto 3d
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);

	// //definiçao da terceira face do objeto 3d
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	
	//definiçao da quarta face do objeto 3d
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);

	//definiçao da quinta face do objeto 3d
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);

	/* Realizando mudanca de base */
	mudancaDeBase(&objeto3d[0], u, v, w);
	mudancaDeBase(&objeto3d[1], u, v, w);
	mudancaDeBase(&objeto3d[2], u, v, w);
	mudancaDeBase(&objeto3d[3], u, v, w);
	mudancaDeBase(&objeto3d[4], u, v, w);

	/* Realizando projecao perspectiva das faces do objeto 3D */
	projecaoPerspectiva(&objeto3d[0], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[1], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[2], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[3], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[4], p_proj, c_proj);

	// normalizaçao e discretizacao dos pontos 3D das faces
	conversao(&objeto3d[0], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[1], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[2], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[3], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[4], &maxXYZ, &minXYZ, &viewPortXY);

	//desenho das linhas das faces do objeto
	printListBresenham3D(&objeto3d[0], image, &viewPortXY, faceColor[0]);
	printListBresenham3D(&objeto3d[1], image, &viewPortXY, faceColor[1]);
	printListBresenham3D(&objeto3d[2], image, &viewPortXY, faceColor[2]);
	printListBresenham3D(&objeto3d[3], image, &viewPortXY, faceColor[3]);
	printListBresenham3D(&objeto3d[4], image, &viewPortXY, faceColor[4]);

	//exibição da imagem final
	drawWindowLine(&viewPortXY, image, lkt);

	return 0;
}

/*==========================
  Implementação das funções
==========================*/

/*Função 1
  Definição das dimensões mínimas e máximas do universo*/
void setUniverse3D(point3D *minXYZ, point3D *maxXYZ){
	minXYZ->x = -30;
	minXYZ->y = -30;
	//minXYZ->z = -30;
	maxXYZ->x = 30;
	maxXYZ->y = 30;
	//maxXYZ->y = -30;
}

/*Função 2
  Definição das dimensões do dispositivo discreto*/
void setViewPort(point *viewPortXY){
	viewPortXY->x = 600;
	viewPortXY->y = 600;
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

// Function 4
// Given two vectors performs the cross product
// In Computer Graphic, a vector is equals a point
// NOTE: this function gives a correct answer only when a and b start at the origin point (0,0,0)
void crossProduct(point3D a, point3D b, point3D *c) {

	c->x = (a.y * b.z) - (a.z * b.y);
	c->y = (a.z * b.x) - (a.x * b.z);
	c->z = (a.x * b.y) - (a.y * b.x);

}

/*Função 5
  Inicializa uma lista que conterá os pontos de um objeto*/
int startList3D(face3D *p_l3D){
	*p_l3D = NULL;
}

/*Função 6
  Verifica se uma lista está vazia ou não*/
int emptyList3D(face3D *p_l3D){
	if(*p_l3D == NULL) return 1;
	return 0;
}

/*Função 7
  Adiciona um novo ponto a um determinado objeto*/
void addEndList3D(face3D *face, point3D *pt3D, point3D *maxXYZ, point3D *minXYZ){
	node3D *newNode3D, *auxNode3D;
	point3D auxPoint3DN;
	newNode3D = (node3D*) malloc (sizeof(node3D));
	
	newNode3D->ptList3D.x = pt3D->x;
	newNode3D->ptList3D.y = pt3D->y;
	newNode3D->ptList3D.z = pt3D->z;
	newNode3D->next = NULL;

	//puts the newNode3D in the end of the list
	if(emptyList3D(face)){
		*face = newNode3D;
	} else {
		auxNode3D = *face;
		while(auxNode3D->next != NULL){
			auxNode3D = auxNode3D->next;
		}
		auxNode3D->next = newNode3D;
	}
}

/*Função 8
  Converte um ponto do SRU para o SRN*/
point3D sruToSrn(point3D pt, point3D *maxXYZ, point3D *minXYZ){
	point3D ptN;	
	ptN.x = (pt.x - minXYZ->x) / (maxXYZ->x - minXYZ->x);
	ptN.y = (pt.y - minXYZ->y) / (maxXYZ->y - minXYZ->y);
	return ptN;
}

/*Função 9
  Converte um ponto do SRN para o SRD*/
pointD srnToSrd(point3D pt3DN, point *viewPortXY){
	pointD ptD;
	ptD.x = round(pt3DN.x * (viewPortXY->x - 1));
	ptD.y = viewPortXY->y - round(pt3DN.y * (viewPortXY->y - 1));
	return ptD;
}

/*Função 10
  Converte uma face para SRN e SRD*/
void conversao(face3D *face, point3D *maxXYZ, point3D *minXYZ, point *viewPortXY){
	node3D *aux;
	aux = *face;

	while (aux != NULL){

		aux->ptList3DN = sruToSrn(aux->ptList3D, maxXYZ, minXYZ);
		aux->ptListD = srnToSrd(aux->ptList3DN, viewPortXY);

		aux = aux->next;
	}
}

/*Funcao 11
    Esta funcao faz uma multiplicacao com a matriz de mudanca de base,
    utilizada para a conversao do ponto no R3 para um ponto no R2 */
void mudancaDeBase(face3D *face, point3D u, point3D v, point3D w){ 
    node3D *aux;
    aux = *face;

    float base[9]; 
    float res[3], coordenadas[3]; 
    int i, j; 
    
    base[0] = u.x;	base[1] = v.x;	base[2] = w.x;	
    base[3] = u.y;	base[4] = v.y;	base[5] = w.y;	
    base[6] = u.z;	base[7] = v.z;	base[8] = w.z; 

    
    while (aux != NULL){
	      
	    res[0] = res[1] = res[2] = 0; 

	    coordenadas[0] = aux->ptList3D.x; 
	    coordenadas[1] = aux->ptList3D.y; 
	    coordenadas[2] = aux->ptList3D.z; 	 
	      
	    for(i = 0; i < 3; i ++)
	        for(j = 0; j < 3; j++)
	            res[i] += base[i*3 + j]*coordenadas[j]; 
	      
	    aux->ptList3D.x = res[0]; 
	    aux->ptList3D.y = res[1]; 
	    aux->ptList3D.z = res[2]; 

	    aux = aux->next;
    }     
} 

/*Funcao 12
    Esta funcao faz a projecao do vetor no R3 para um vetor no R2 */
void projecaoPerspectiva(face3D *face, point3D p_proj, point3D c_proj){ 
    node3D *aux;
	aux = *face;
      
    while (aux != NULL){
	    aux->ptList3D.x = aux->ptList3D.x * ((p_proj.z - c_proj.z) / (aux->ptList3D.z - c_proj.z)); 
	    aux->ptList3D.y = aux->ptList3D.y * ((p_proj.z - c_proj.z) / (aux->ptList3D.z - c_proj.z)); 
	    aux->ptList3D.z = p_proj.z; 

	    aux = aux->next;
    }  
} 

/*Funcao 13
    Esta funcao realiza o tracado ponto 
    a ponto da face do objeto 3d desejado */
void printListBresenham3D(face3D *face, int *input, point *viewPortXY, int color){
	node3D *aux;
	aux = *face;
	pointD ptOneD, ptTwoD;

	while(aux != NULL){
		ptOneD = aux->ptListD;
		if(aux->next != NULL){
			ptTwoD = aux->next->ptListD;
			bresenham(input, &ptOneD, &ptTwoD, viewPortXY, color);
		}
		aux = aux->next;
	}
}

/*Funcao 14
    Esta funcao realiza o algoritmo de bresenham */
void bresenham(int *input, pointD *ptOneD, pointD *ptTwoD, point *viewPortXY, int color){
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

/*Função 15
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