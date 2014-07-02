/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

#include "graphiclib.h"

#define EventMask (KeyPressMask | ExposureMask)

/*Functions*/

/*--------------------------------------------------------------------------------------------*/
/*void multMatrix(float matrizA[][3], int matrizB[][1], int* matrizC){

	int i, j, x, Aux = 0; //oi

	//multiplica matrizes
	for(i=0; i<3; i++) {
		for(j=0; j<1; j++){
			matrizC[i]=0;
		    for(x=0; x<3; x++){
		    	Aux = Aux + (int)(matrizA[i][x]*matrizB[x][j]);
		    }
		    matrizC[i]=Aux;
		    Aux=0;
		}
		printf("%d\n", matrizC[i]);
	}

}*/

int startList(list *p_l){
	*p_l = NULL;
}

int emptyList(list *p_l){
	if(*p_l == NULL) return 1;
	return 0;
}

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

	/*//prints the normalized and discrete point to check the values
	printf("\nnormalizado: [%.4f %.4f]", newNode->ptListN.x, newNode->ptListN.y);
	printf("\ndiscreto: [%.4f %.4f]\n", newNode->ptListD.x, newNode->ptListD.y);*/

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

void freeList(list *p_l){
	if(!emptyList(p_l)){
		node *auxNode;

		do{
			auxNode = (*p_l)->next;
			free(*p_l);
			*p_l = auxNode;
		} while(auxNode != NULL);

		startList(p_l);
	}
}

void showList(list *p_l){
	node *auxNode;
	auxNode = *p_l;

	while(auxNode != NULL){
		/*printf("\nCoordenadas dos pontos: [%.2f %.2f] ", auxNode->ptList.x, auxNode->ptList.y);
		printf("\nPontos normalizados: [%.2f %.2f] ", auxNode->ptListN.x, auxNode->ptListN.y);
		printf("\nPontos discretos: [%.2f %.2f] ", auxNode->ptListD.x, auxNode->ptListD.y);*/
		auxNode = auxNode->next;
	}

	printf("\n");
}

void printListBresenham(list *p_l, char *input, point *viewPortXY){
	node *auxNode;
	auxNode = *p_l;
	point ptOneD, ptTwoD;

	while(auxNode != NULL){
		ptOneD = auxNode->ptListD;
		if(auxNode->next != NULL){
			ptTwoD = auxNode->next->ptListD;
			bresenham(input, &ptOneD, &ptTwoD, viewPortXY);
		}
		auxNode = auxNode->next;
	}
}

/*--------------------------------------------------------------------------------------------*/
void setUniverse(point *minXY, point *maxXY){
	printf("\nDefina os valores minimos do universo:\n\nCoordenada X: ");
	scanf("%f", &minXY->x);
	printf("Coordenada Y: ");
	scanf("%f", &minXY->y);
	printf("\nDefina os valores maximos do universo:\n\nCoordenada X: ");
	scanf("%f", &maxXY->x);
	printf("Coordenada Y: ");
	scanf("%f", &maxXY->y);
}

void getUniverse(point *minXY, point *maxXY){
	printf("Coordendas minimas do universo: [%.4f, %.4f]\n", minXY->x, minXY->y);
	printf("Coordendas maximas do universo: [%.4f, %.4f]\n\n", maxXY->x, maxXY->y);
}

/*--------------------------------------------------------------------------------------------*/
void setValues(point *ptOne, point *ptTwo){
	printf("\nDefina o primeiro ponto:\n\nCoordenada X: ");
	scanf("%f", &ptOne->x);
	printf("Coordenada Y: ");
	scanf("%f", &ptOne->y);
	printf("\nDefina o segundo ponto:\n\nCoordenada X: ");
	scanf("%f", &ptTwo->x);
	printf("Coordenada Y: ");
	scanf("%f", &ptTwo->y);
}

void getValues(point *ptOne, point *ptTwo){
	printf("Coordendas do primeiro ponto: [%.4f, %.4f]\n", ptOne->x, ptOne->y);
	printf("Coordendas do segundo ponto: [%.4f, %.4f]\n\n", ptTwo->x, ptTwo->y);
}

/*--------------------------------------------------------------------------------------------*/
void setViewPort(point *viewPortXY){
	printf("Defina as dimensoes do dispositivo discreto:\n\nHorizontal: ");
	scanf("%f", &viewPortXY->x);
	printf("Vertical: ");
	scanf("%f", &viewPortXY->y);
}

void getViewPort(point *viewPortXY){
	printf("\nDimensoes do dispositivo discreto: %.0f X %.0f\n\n", viewPortXY->x, viewPortXY->y);
}

/*--------------------------------------------------------------------------------------------*/
void initMatrix(char *image, point *viewPortXY){
	int i, j;
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[(i * (int)viewPortXY->y) + j] = ' ';
		}
	}
}

/*--------------------------------------------------------------------------------------------*/
point sruToSrn(point *pt, point *maxXY, point *minXY){
	point ptN;	
	ptN.x = (pt->x - minXY->x) / (maxXY->x - minXY->x);
	ptN.y = (pt->y - minXY->y) / (maxXY->y - minXY->y);
	return ptN;
}

point srnToSrd(point *ptN, point *viewPortXY){
	point ptD;
	ptD.x = round(ptN->x * (viewPortXY->x - 1));
	ptD.y = round(ptN->y * (viewPortXY->y - 1));
	return ptD;
}

void getSrn(point *ptOneN, point *ptTwoN){
	printf("Primeiro ponto normalizado: [%.4f, %.4f]\n", ptOneN->x, ptOneN->y);
	printf("Segundo ponto normalizado: [%.4f, %.4f]\n\n", ptTwoN->x, ptTwoN->y);
}

void getSrd(point *ptOneD, point *ptTwoD){
	printf("Primeiro ponto discreto: [%.4f, %.4f]\n", ptOneD->x, ptOneD->y);
	printf("Segundo ponto discreto: [%.4f, %.4f]\n\n", ptTwoD->x, ptTwoD->y);
}

/*--------------------------------------------------------------------------------------------*/
void drawLine(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY){
	int i, j;
	float x1, x2, y1, y2, a, b, x, y;

	x1 = ptOneD->x;
	x2 = ptTwoD->x;
	y1 = ptOneD->y;
	y2 = ptTwoD->y;

	//defines the matrix that will be used to generate the image
	char image[(int)viewPortXY->x][(int)viewPortXY->y];

	//decoding the vector of chars to a matrix to simplify the understanding of attributions
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[i][j] = input[(i * (int)viewPortXY->y) + j];
		}
	}

	//initializing the matrix
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[i][j] = ' ';
		}
	}

	//draw line algorithm
	a = (y2 - y1) / (x2 - x1);
	b = y1 - a * x1;
	i = x1;
	j = viewPortXY->y - y1;

	image[j][i] = '1';

	x = x1++;
	y = a * x + b;

	while(y < y2 - 1.0){
		i = x;
		j = viewPortXY->y - y;
		image[j][i] = '1';
		y = a * (++x) + b;
	}

	//prints the result on screen
	printf("\nLinha pelo primeiro metodo:\n");
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			printf("%c", image[i][j]);
		}
		printf("\n");
	}

	//copying back the matrix to the vector of char
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			input[(i * (int)viewPortXY->y) + j] = image[i][j];
		}
	}
}

void bresenham(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY){
	int i = 0, j = 0, ystep = 0, steep = 0;
	float x0 = 0, x1 = 0, y0 = 0, y1 = 0, aux = 0;

	x0 = ptOneD->x;
	y0 = ptOneD->y;
	x1 = ptTwoD->x;
	y1 = ptTwoD->y;

	
	if(abs(y1 - y0) > abs(x1 - x0)){
		steep = 1;
		aux = x0; x0 = y0; y0 = aux; 
		aux = x1; x1 =  y1; y1 = aux;
	}

	if(x0 > x1){
		aux = x0; x0 = x1; x1 = aux;
		aux = y0; y0 = y1; y1 = aux;
	}

	char image[(int)viewPortXY->x][(int)viewPortXY->y];

	//decoding the vector of chars to a matrix to simplify the understanding of attributions
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[i][j] = input[(i * (int)viewPortXY->y + j)];
		}
	}

	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	int error = deltax/2;
	int y = y0, x;

	if(y0 < y1){
		ystep = 1;
	} else {
		ystep = -1;
	}

	for(x = x0; x < x1; x++){
		if(steep){
			image[y][x] = '1';
		} else {
			image[x][y] = '1';
		}
		error = error - deltay;
		if(error < 0){
			y = y + ystep;
			error = error + deltax;
		}
	}

	//copying back the matrix to the vector of char
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			input[(i * (int)viewPortXY->y) + j] = image[i][j];
		}
	}

	//prints the result on screen
	/*printf("\nLinha pelo algoritmo de Bresenham:\n\n");
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			printf("%c", image[i][j]);
		}
		printf("\n");
	}*/

}

/*----Operaçoes em objetos--------------------------------------------------------------------*/
/*void translate(list *p_l) {
	node *auxNode;
	auxNode = *p_l;
	float  t[3][3];
	int pi[3][1], p[3], dx, dy;

	printf("Entre com o deslocamento em X e Y respectivamente: ");
	scanf("%d", &dx);
	scanf("%d", &dy);

	t[0][0]= 1;	t[0][1]= 0;	t[0][2]= dx;
	t[1][0]= 0;	t[1][1]= 1;	t[1][2]= dy;
	t[2][0]= 0;	t[2][1]= 0;	t[2][2]= 1;

	while(auxNode != NULL){
		pi[0][0] = (int)auxNode->ptListD.x;
		pi[1][0] = (int)auxNode->ptListD.y;
		pi[2][0] = 1;

		p[0] = 0;
		p[1] = 0;
		p[2] = 0;

		multMatrix(t, pi, &p);

		auxNode->ptListD.x = (int)p[0];
		auxNode->ptListD.y = (int)p[1];

		auxNode = auxNode->next;
	}
}

void rotate(list *p_l) {
	node *auxNode;
	auxNode = *p_l;
	float t[3][3];
	int pi[3][1], p[3], teta;

	printf("Entre com o angulo de rotacao: ");
	scanf("%d", &teta);

	printf("%d\n", (int)cos(teta) );

	t[0][0]= (float)cos(teta);	t[0][1]= (float)-sin(teta); t[0][2]= 0;
	t[1][0]= (float)sin(teta);	t[1][1]= (float)cos(teta);  t[1][2]= 0;
	t[2][0]= 0;					t[2][1]= 0;			 	 	t[2][2]= 1;



	while(auxNode != NULL){
		pi[0][0] = (int)auxNode->ptListD.x;
		pi[1][0] = (int)auxNode->ptListD.y;
		pi[2][0] = 1;

		p[0] = 0;
		p[1] = 0;
		p[2] = 0;

		multMatrix(t, pi, &p);

		auxNode->ptListD.x = (int)p[0];
		auxNode->ptListD.y = (int)p[1];

		auxNode = auxNode->next;
	}
}

void scale(list *p_l) {
	node *auxNode;
	auxNode = *p_l;
	float t[3][3], escx, escy;
	int pi[3][1], p[3];

	printf("Entre com a escala em x e y respectivamente: ");
	scanf("%f %f", &escx, &escy);

	t[0][0]= escx;	t[0][1]= 0; 	t[0][2]= 0;
	t[1][0]= 0;		t[1][1]= escy;  t[1][2]= 0;
	t[2][0]= 0;		t[2][1]= 0;		t[2][2]= 1;



	while(auxNode != NULL){
		pi[0][0] = (int)auxNode->ptListD.x;
		pi[1][0] = (int)auxNode->ptListD.y;
		pi[2][0] = 1;

		p[0] = 0;
		p[1] = 0;
		p[2] = 0;

		multMatrix(t, pi, &p);

		auxNode->ptListD.x = (int)p[0];
		auxNode->ptListD.y = (int)p[1];

		auxNode = auxNode->next;
	}
}

void mirror(list *p_l) {
	node *auxNode;
	auxNode = *p_l;
	float t[3][3], escx, escy;
	int pi[3][1], p[3];

	t[0][0]= 1;		t[0][1]= 0; 	t[0][2]= 0;
	t[1][0]= 0;		t[1][1]= -1;    t[1][2]= 0;
	t[2][0]= 0;		t[2][1]= 0;		t[2][2]= 1;



	while(auxNode != NULL){
		pi[0][0] = (int)auxNode->ptListD.x;
		pi[1][0] = (int)auxNode->ptListD.y;
		pi[2][0] = 1;

		p[0] = 0;
		p[1] = 0;
		p[2] = 0;

		multMatrix(t, pi, &p);

		auxNode->ptListD.x = (int)p[0];
		auxNode->ptListD.y = (int)p[1];

		auxNode = auxNode->next;
	}
}*/

/*--------------------------------------------------------------------------------------------*/
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

void drawWindowLine(point *viewPortXY, char *input){
	Display               * display;
	XImage                * ximage;
	Window                window;
	XEvent                an_event;
	GC                    gc;
	Visual                * visual;
	XGCValues             values;
	int                   m, n, screen, dplanes;
	int                   width, height, ret = 1;
	RGB          		  * cor, *lineColor;

	width = viewPortXY->x;
	height = viewPortXY->y;

	cor = (RGB *) malloc(sizeof(RGB)); 
	cor->r = 0.0;
	cor->g = 1.0;
	cor->b = 1.0;

	lineColor = (RGB *) malloc(sizeof(RGB)); 
	lineColor->r = 0.0;
	lineColor->g = 0.0;
	lineColor->b = 1.0;

	char image[(int)viewPortXY->x][(int)viewPortXY->y];

	//decoding the vector of chars to a matrix to simplify the understanding of attributions
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
	        ximage -> data[(m*4)*width+n*4] = (char) round((cor->b)*255);
	        ximage -> data[(m*4)*width+n*4+1] = (char) round((cor->g)*255);
	        ximage -> data[(m*4)*width+n*4+2] = (char) round((cor->r)*255);
	        ximage -> data[(m*4)*width+n*4+3] = (char) 0;
	        }
	    }

	    //draws the line
	    for(m=0;m<height;m++) {
	      for(n=0;n<width;n++) {
	        if(image[m][n] == '1'){
		        ximage -> data[(m*4)*width+n*4] = (char) round((lineColor->b)*255);
		        ximage -> data[(m*4)*width+n*4+1] = (char) round((lineColor->g)*255);
		        ximage -> data[(m*4)*width+n*4+2] = (char) round((lineColor->r)*255);
		        ximage -> data[(m*4)*width+n*4+3] = (char) 0;
	    	}
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

/*--------------------------------------------------------------------------------------------*/
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