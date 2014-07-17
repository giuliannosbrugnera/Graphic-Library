/*=========================================================================
UNIVERSIDADE FEDERAL DE SÃO CARLOS - UFSCar - Sorocaba
CIÊNCIA DA COMPUTAÇÃO - COMPUTAÇÃO GRÁFICA
PROFESSOR MURILLO RODRIGO PETRUCELLI HOMEM

GRUPO 6

438340 - Daniel Ramos Miola		
408093 - Giulianno Raphael Sbrugnera
408611 - Igor Felipe Ferreira Ceridório
408298 - Rafael Paschoal Giordano

ARQUIVO:
graphiclib.c

DESCRIÇÃO:
arquivo que contém a impelementação das funções da biblioteca gráfica 
desenvolvida pelo grupo.

==========================================================================*/

/*==========================
  Biblioteca utilizada
==========================*/

#include "graphiclib.h"

#define EventMask (KeyPressMask | ExposureMask)

/*==========================
  Implementação das funções
==========================*/

/*------------------------------------------------------------------------------
  Bloco de funções comuns
------------------------------------------------------------------------------*/

/*Função 1
  Definição das dimensões do dispositivo discreto*/
void setViewPort(point *viewPortXY, point vp){
	viewPortXY->x = vp.x;
	viewPortXY->y = vp.y;
}

/*Função 2
  Inicialização da matriz onde será guardada a imagem*/
void initMatrix(int *image, point *viewPortXY){
	int i, j;
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[(i * (int)viewPortXY->y) + j] = 0;
		}
	}
}

/*Função 3
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

/*Função 4
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

/*Função 5
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

/*Função 6
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

/*Função 7
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

/*Função 8
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

/*------------------------------------------------------------------------------
  Bloco de funções 2D
------------------------------------------------------------------------------*/

/*Função 9
  Converte um ponto do SRU para o SRN*/
point sruToSrn(point *pt, point *maxXY, point *minXY){
	point ptN;	
	ptN.x = (pt->x - minXY->x) / (maxXY->x - minXY->x);
	ptN.y = (pt->y - minXY->y) / (maxXY->y - minXY->y);
	return ptN;
}

/*Função 10
  Converte um ponto do SRN para o SRD*/
point srnToSrd(point *ptN, point *viewPortXY){
	point ptD;
	ptD.x = round(ptN->x * (viewPortXY->x - 1));
	ptD.y = round(ptN->y * (viewPortXY->y - 1));
	return ptD;
}

/*Função 11
  Calcula o ponto médio de um objeto*/
point middleObject(list *p_L){
	point ptMiddle, ptMax, ptMin;
	node *auxNode;
	auxNode = *p_L;

	if(auxNode != NULL){
		ptMin.x = auxNode->ptList.x;
		ptMin.y = auxNode->ptList.y;
		ptMax.x = auxNode->ptList.x;
		ptMax.y = auxNode->ptList.y;
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

/*Função 12
  Definição das dimensões mínimas e máximas do universo*/
void  setUniverse(point *minXY, point *maxXY, point minUniverse, point maxUniverse){
	minXY->x = minUniverse.x;
	minXY->y = minUniverse.y;
	maxXY->x = maxUniverse.x;
	maxXY->y = maxUniverse.y;
}

/*Função 13
  Multiplica uma matriz 3x3 por um vetor de 3 elementos*/
void multMatrixArray(float *matrix, float *vector, float *result){
	result[0] = (matrix[0] * vector[0]) + (matrix[1] * vector[1]) + (matrix[2] * vector[2]);
	result[1] = (matrix[3] * vector[0]) + (matrix[4] * vector[1]) + (matrix[5] * vector[2]);
	result[2] = (matrix[6] * vector[0]) + (matrix[7] * vector[1]) + (matrix[8] * vector[2]);
}

/*Função 14
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

/*Função 15
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


/*Função 16
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

/*Função 17
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

/*Função 18
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

/*Função 19
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

/*Função 20
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

/*Função 21
  Realiza o preenchimento de um poligono 2d*/
void fill(list *p_L, int *input, int color, point p, point *viewPortXY){
	
	if(input[(int)p.y*(int)viewPortXY->x+(int)p.x] == 0){
		input[(int)p.y*(int)viewPortXY->x+(int)p.x] = color;
	}

	if(input[(int)p.y*(int)viewPortXY->x+(int)p.x+1] == 0){
		p.x++;
		fill(p_L, input, color, p, viewPortXY);
	}

	if(input[((int)p.y+1)*(int)viewPortXY->x+(int)p.x] == 0){
		p.y++;
		fill(p_L, input, color, p, viewPortXY);
	}

	if(input[(int)p.y*(int)viewPortXY->x+(int)p.x-1] == 0){
		p.x--;
		fill(p_L, input, color, p, viewPortXY);
	}

	if(input[((int)p.y-1)*(int)viewPortXY->x+(int)p.x] == 0){
		p.y--;
		fill(p_L, input, color, p, viewPortXY);
	}
}

/*Função 22
  Inicializa uma lista que conterá os pontos de um objeto*/
int startList(list *p_l){
	*p_l = NULL;
}

/*Função 23
  Verifica se uma lista está vazia ou não*/
int emptyList(list *p_l){
	if(*p_l == NULL) return 1;
	return 0;
}

/*------------------------------------------------------------------------------
  Bloco de funções 3D
------------------------------------------------------------------------------*/

/*Função 24
  Converte um ponto do SRU para o SRN*/
point3D sruToSrn3D(point3D pt, point3D *maxXYZ, point3D *minXYZ){
	point3D ptN;	
	ptN.x = (pt.x - minXYZ->x) / (maxXYZ->x - minXYZ->x);
	ptN.y = (pt.y - minXYZ->y) / (maxXYZ->y - minXYZ->y);
	return ptN;
}

/*Função 25
  Converte um ponto do SRN para o SRD*/
pointD srnToSrd3D(point3D pt3DN, point *viewPortXY){
	pointD ptD;
	ptD.x = round(pt3DN.x * (viewPortXY->x - 1));
	ptD.y = viewPortXY->y - round(pt3DN.y * (viewPortXY->y - 1));
	return ptD;
}

/*Função 26
  Definição das dimensões mínimas e máximas do universo*/
void setUniverse3D(point3D *minXYZ, point3D *maxXYZ, point3D minUniverse, point3D maxUniverse){
	minXYZ->x = minUniverse.x;
	minXYZ->y = minUniverse.y;
	//minXYZ->z = minUniverse.z;
	maxXYZ->x = maxUniverse.x;
	maxXYZ->y = maxUniverse.y;
	//maxXYZ->y = maxUniverse.z;
}

// Function 27
// Given two vectors performs the cross product
// In Computer Graphic, a vector is equals a point
// NOTE: this function gives a correct answer only when a and b start at the origin point (0,0,0)
void crossProduct(point3D a, point3D b, point3D *c) {

	c->x = (a.y * b.z) - (a.z * b.y);
	c->y = (a.z * b.x) - (a.x * b.z);
	c->z = (a.x * b.y) - (a.y * b.x);

	int u = sqrt((c->x*c->x)+(c->y*c->y)+(c->z*c->z));
	c->x = c->x/u;
	c->y = c->y/u;
	c->z = c->z/u;
}

/*Função 28
  Inicializa uma lista que conterá os pontos de um objeto*/
int startList3D(face3D *p_l3D){
	*p_l3D = NULL;
}

/*Função 29
  Verifica se uma lista está vazia ou não*/
int emptyList3D(face3D *p_l3D){
	if(*p_l3D == NULL) return 1;
	return 0;
}

/*Função 30
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

/*Função 31
  Converte uma face para SRN e SRD*/
void conversao(face3D *face, point3D *maxXYZ, point3D *minXYZ, point *viewPortXY){
	node3D *aux;
	aux = *face;

	while (aux != NULL){

		aux->ptList3DN = sruToSrn3D(aux->ptList3D, maxXYZ, minXYZ);
		aux->ptListD = srnToSrd3D(aux->ptList3DN, viewPortXY);

		aux = aux->next;
	}
}

/*Funcao 32
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

/*Funcao 33
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

/*Funcao 34
    Esta funcao realiza o tracado ponto a ponto da face do objeto 3d desejado */
void printListBresenham3D(face3D *face, int *input, point *viewPortXY, int color){
	node3D *aux;
	aux = *face;
	pointD ptOneD, ptTwoD;
	point ptOneDAux, ptTwoDAux;

	while(aux != NULL){
		ptOneD = aux->ptListD;
		
		ptOneDAux.x = (int)ptOneD.x;
		ptOneDAux.y = (int)ptOneD.y;

		if(aux->next != NULL){
			ptTwoD = aux->next->ptListD;

			ptTwoDAux.x = (int)ptTwoD.x;
			ptTwoDAux.y = (int)ptTwoD.y;
			bresenham(input, &ptOneDAux, &ptTwoDAux, viewPortXY, color);
		}
		aux = aux->next;
	}
}

/*Função 35
  Calcula o ponto médio de um objeto 3D*/
point3D middleObject3D(list3D *p_L){
	point3D ptMiddle, ptMax, ptMin;
	node3D *auxNode;
	auxNode = *p_L;

	if(auxNode != NULL){
		ptMin.x = auxNode->ptList3D.x;
		ptMin.y = auxNode->ptList3D.y;
		ptMin.z = auxNode->ptList3D.z;
		ptMax.x = auxNode->ptList3D.x;
		ptMax.y = auxNode->ptList3D.y;
		ptMax.z = auxNode->ptList3D.z;
	}

	while(auxNode != NULL){
		
		//obtaining the minimum points
		if(auxNode->ptList3D.x < ptMin.x)
			ptMin.x = auxNode->ptList3D.x;
		if(auxNode->ptList3D.y < ptMin.y)
			ptMin.y = auxNode->ptList3D.y;
		if(auxNode->ptList3D.z < ptMin.z)
			ptMin.z = auxNode->ptList3D.z;

		//obtaining the maximum points
		if(auxNode->ptList3D.x > ptMax.x)
			ptMax.x = auxNode->ptList3D.x;
		if(auxNode->ptList3D.y > ptMax.y)
			ptMax.y = auxNode->ptList3D.y;
		if(auxNode->ptList3D.z > ptMax.z)
			ptMax.z = auxNode->ptList3D.z;

		//iterates the points list
		auxNode = auxNode->next;
	}

	//calculates the middle point
	ptMiddle.x = ((ptMax.x - ptMin.x)/2) + ptMin.x;
	ptMiddle.y = ((ptMax.y - ptMin.y)/2) + ptMin.y;
	ptMiddle.z = ((ptMax.z - ptMin.z)/2) + ptMin.z;

	return ptMiddle;
}

/* Função 36
   Multiplica uma matriz 4x4 por um vetor de 4 posições*/
void multMatrixArray3D(float *matrix, float *vector, float *result) {
	
	//multiplicating the matrix by the vector
	result[0] = (matrix[0]  * vector[0]) + (matrix[1]  * vector[1]) + (matrix[2]   * vector[2]) + (matrix[3]  * vector[3]);
	result[1] = (matrix[4]  * vector[0]) + (matrix[5]  * vector[1]) + (matrix[6]   * vector[2]) + (matrix[7]  * vector[3]);
	result[2] = (matrix[8]  * vector[0]) + (matrix[9]  * vector[1]) + (matrix[10]  * vector[2]) + (matrix[11] * vector[3]);
	result[3] = (matrix[12] * vector[0]) + (matrix[13] * vector[1]) + (matrix[14]  * vector[2]) + (matrix[15] * vector[3]);

}

/* Function number 37
   Multiplica duas matrizes 4x4*/
void multFourByFourMatrix(float first[][4], float second[][4], float result[][4]) {
	
	int i, j, k;
	float sum;

	for (i = 0; i <= 3; i++) {
		for (j = 0; j <= 3; j++) {
			sum = 0;
			for (k = 0; k <= 3; k++) {
				sum = sum + first[i][k] * second[k][j];
			}
			result[i][j]=sum;
		}
	}

}

/*Função 38
  Translação (deslocamento) de um objeto*/
void translate3D(face3D *object, int n, point3D *minXYZ, point3D *maxXYZ, point *viewPortXY, int dx, int dy, int dz){
	node3D *auxNode; //points to the object that will be translated
	point3D pt; //auxiliar points

	//translation matrix declaration
	float transMatrix[16] = {1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz,0, 0, 0, 1};
	//point vector and result array declaration
	float p[4], result[4];

	int i;
	for (i = 0; i < n; i++){
		auxNode = object[i];
		
		while(auxNode != NULL){

			p[0] = auxNode->ptList3D.x;
			p[1] = auxNode->ptList3D.y;
			p[2] = auxNode->ptList3D.z;
			p[3] = 1;

			multMatrixArray3D(transMatrix, p, result);

			//updating the point values
			auxNode->ptList3D.x = pt.x = result[0];
			auxNode->ptList3D.y = pt.y = result[1];
			auxNode->ptList3D.z = pt.z = result[2];

			//converts the translated point to srn
			auxNode->ptList3DN = sruToSrn3D(auxNode->ptList3D, maxXYZ, minXYZ);
			//converts the translated point to srd
			auxNode->ptListD = srnToSrd3D(auxNode->ptList3DN, viewPortXY);

			auxNode = auxNode->next;
		}
	}
}

/*Função 39
  operaçao de mudanca de escala de um objeto 3d*/
void scale3D(face3D *object, int n, point3D *minXYZ, point3D *maxXYZ, point *viewPortXY, int sx, int sy, int sz){
	node3D *auxNode; //points to the object that will be translated
	point3D pt; //auxiliar points

	//translation matrix declaration
	float transMatrix[16] = {sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1};
	//point vector and result array declaration
	float p[4], result[4];

	int i;
	for (i = 0; i < n; i++){
		auxNode = object[i];
		
		while(auxNode != NULL){

			p[0] = auxNode->ptList3D.x;
			p[1] = auxNode->ptList3D.y;
			p[2] = auxNode->ptList3D.z;
			p[3] = 1;

			multMatrixArray3D(transMatrix, p, result);

			//updating the point values
			auxNode->ptList3D.x = pt.x = result[0];
			auxNode->ptList3D.y = pt.y = result[1];
			auxNode->ptList3D.z = pt.z = result[2];

			//converts the translated point to srn
			auxNode->ptList3DN = sruToSrn3D(auxNode->ptList3D, maxXYZ, minXYZ);
			//converts the translated point to srd
			auxNode->ptListD = srnToSrd3D(auxNode->ptList3DN, viewPortXY);

			auxNode = auxNode->next;
		}
	}
}

/*Função 40
  operaçao de mudanca de escala de um objeto 3d*/
void rotate3D(face3D *object, int n, point3D *minXYZ, point3D *maxXYZ, point *viewPortXY, int teta){
	node3D *auxNode; //points to the object that will be translated
	point3D pt; //auxiliar points
			
	//translation matrix declaration
	float transMatrix[16];

	//point vector and result array declaration
	float p[4], result[4];

	int i;
	for (i = 0; i < n; i++){
		auxNode = object[i];
		
		while(auxNode != NULL){

			p[0] = auxNode->ptList3D.x;
			p[1] = auxNode->ptList3D.y;
			p[2] = auxNode->ptList3D.z;
			p[3] = 1;

			multMatrixArray3D(transMatrix, p, result);

			//updating the point values
			auxNode->ptList3D.x = pt.x = result[0];
			auxNode->ptList3D.y = pt.y = result[1];
			auxNode->ptList3D.z = pt.z = result[2];

			//converts the translated point to srn
			auxNode->ptList3DN = sruToSrn3D(auxNode->ptList3D, maxXYZ, minXYZ);
			//converts the translated point to srd
			auxNode->ptListD = srnToSrd3D(auxNode->ptList3DN, viewPortXY);

			auxNode = auxNode->next;
		}
	}
}