/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

#include "graphiclib.h"

#define EventMask (KeyPressMask | ExposureMask)

/*Functions*/

/*--------------------------------------------------------------------------------------------*/
int startList(list *p_l){
	*p_l = NULL;
}

int startList3D(face3D *p_l3D){
	*p_l3D = NULL;
}

int emptyList(list *p_l){
	if(*p_l == NULL) return 1;
	return 0;
}

int emptyList3D(face3D *p_l3D){
	if(*p_l3D == NULL) return 1;
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

void addEndList3D(face3D *face, point3D *pt3D, point3D *maxXYZ, point3D *minXYZ){
	node3D *newNode3D, *auxNode3D;
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

void freeList3D(face3D *face){
	if(!emptyList3D(face)){
		node3D *auxNode3D;

		do{
			auxNode3D = (*face)->next;
			free(*face);
			*face = auxNode3D;
		} while(auxNode3D != NULL);

		startList3D(face);
	}
}

void showList(list *p_l){
	node *auxNode;
	auxNode = *p_l;

	while(auxNode != NULL){
		printf("\nCoordenadas dos pontos: [%.2f %.2f] ", auxNode->ptList.x, auxNode->ptList.y);
		printf("\nPontos normalizados: [%.2f %.2f] ", auxNode->ptListN.x, auxNode->ptListN.y);
		printf("\nPontos discretos: [%.2f %.2f] ", auxNode->ptListD.x, auxNode->ptListD.y);
		auxNode = auxNode->next;
	}

	printf("\n");
}

void showList3D(face3D *face){
	node3D *auxNode3D;
	auxNode3D = *face;

	while(auxNode3D != NULL){
		printf("\nCoordenadas dos pontos 3D: [%.2f %.2f %.2f] ", auxNode3D->ptList3D.x, auxNode3D->ptList3D.y, auxNode3D->ptList3D.z);
		auxNode3D = auxNode3D->next;
	}

	printf("\n");
}

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

void setUniverse3D(point3D *minXYZ, point3D *maxXYZ){
	printf("\nDefina os valores minimos do universo 3D:\n\nCoordenada X: ");
	scanf("%f", &minXYZ->x);
	printf("Coordenada Y: ");
	scanf("%f", &minXYZ->y);
	printf("Coordenada Z: ");
	scanf("%f", &minXYZ->z);
	printf("\nDefina os valores maximos do universo 3D:\n\nCoordenada X: ");
	scanf("%f", &maxXYZ->x);
	printf("Coordenada Y: ");
	scanf("%f", &maxXYZ->y);
	printf("Coordenada Y: ");
	scanf("%f", &maxXYZ->z);
}

void getUniverse3D(point3D *minXYZ, point3D *maxXYZ){
	printf("Coordendas minimas do universo 3D: [%.4f, %.4f, %.4f]\n", minXYZ->x, minXYZ->y, minXYZ->z);
	printf("Coordendas maximas do universo 3D: [%.4f, %.4f, %.4f]\n\n", maxXYZ->x, maxXYZ->y, maxXYZ->z);
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
	printf("\nDefina as dimensoes do dispositivo discreto:\n\nHorizontal: ");
	scanf("%f", &viewPortXY->x);
	printf("Vertical: ");
	scanf("%f", &viewPortXY->y);
}

void getViewPort(point *viewPortXY){
	printf("\nDimensoes do dispositivo discreto: %.0f X %.0f\n\n", viewPortXY->x, viewPortXY->y);
}

/*--------------------------------------------------------------------------------------------*/
void initMatrix(int *image, point *viewPortXY){
	int i, j;
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[(i * (int)viewPortXY->y) + j] = 0;
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
void drawLine(int *input, point *ptOneD, point *ptTwoD, point *viewPortXY){
	int i, j;
	float x1, x2, y1, y2, a, b, x, y;

	x1 = ptOneD->x;
	x2 = ptTwoD->x;
	y1 = ptOneD->y;
	y2 = ptTwoD->y;

	//defines the matrix that will be used to generate the image
	char image[(int)viewPortXY->x][(int)viewPortXY->y];

	//decoding the vector of ints to a matrix to simplify the understanding of attributions
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[i][j] = input[(i * (int)viewPortXY->y) + j];
		}
	}

	//initializing the matrix
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			image[i][j] = 0;
		}
	}

	//draw line algorithm
	a = (y2 - y1) / (x2 - x1);
	b = y1 - a * x1;
	i = x1;
	j = viewPortXY->y - y1;

	image[j][i] = 0;

	x = x1++;
	y = a * x + b;

	while(y < y2 - 1.0){
		i = x;
		j = viewPortXY->y - y;
		image[j][i] = 0;
		y = a * (++x) + b;
	}

	//prints the result on screen
	printf("\nLinha pelo primeiro metodo:\n");
	for(i = 0; i < viewPortXY->x; i++){
		for(j = 0; j < viewPortXY->y; j++){
			printf("%d", image[i][j]);
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
            input[p1y*HEIGHT+p1x] = color;
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

/*--------------------------------------------------------------------------------------------*/
void multMatrixArray(float *matrix, float *vector, float *result){
	
	//multiplicating the matrix by the vector
	result[0] = (matrix[0] * vector[0]) + (matrix[1] * vector[1]) + (matrix[2] * vector[2]);
	result[1] = (matrix[3] * vector[0]) + (matrix[4] * vector[1]) + (matrix[5] * vector[2]);
	result[2] = (matrix[6] * vector[0]) + (matrix[7] * vector[1]) + (matrix[8] * vector[2]);

}

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

void scale(list *p_L, point *minXY, point *maxXY, point *viewPortXY){
	int sx, sy; //variables that stores the scale
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	printf("Quantidade a ser escalonada em relacao ao eixo X do universo: ");
	scanf("%d", &sx);
	printf("Quantidade a ser escalonada em relacao ao eixo Y do universo: ");
	scanf("%d", &sy);

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

void rotate(list *p_L, point *minXY, point *maxXY, point *viewPortXY){
	float a; //variable that store the angle
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	printf("Em quantos graus deseja rotacionar a imagem: ");
	scanf("%f", &a);

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

void mirror(list *p_L, point *minXY, point *maxXY, point *viewPortXY){
	int a; //variable that store the mirror option
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	printf("Em relacao a qual eixo deseja espelhar a imagem:\n\n");
	printf("- [0] Eixo X;\n");
	printf("- [1] Eixo Y;\n");
	printf("- [2] Ambos;\n");
	printf("\n-> ");
	scanf("%d", &a);

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

		if(a == 0)
			multMatrixArray(mirrorMatrixX, p, result);
		if(a == 1)
			multMatrixArray(mirrorMatrixY, p, result);
		if(a == 2)
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

void shearing(list *p_L, point *minXY, point *maxXY, point *viewPortXY){
	int a; //variable that store the shearing option
	float shx, shy; //variables that stores the shearing values
	node *auxNode; //points to the object that will be translated
	point pt, ptN, ptMiddle; //auxiliar points

	auxNode = *p_L;

	//firts of all calculates the image middle point
	ptMiddle = middleObject(p_L);
	//translates the object to the origin using the given middle point
	translate(p_L, minXY, maxXY, viewPortXY, -(ptMiddle.x), -(ptMiddle.y));

	printf("Em relacao a qual eixo deseja aplicar o cisalhamento:\n\n");
	printf("- [0] Eixo X;\n");
	printf("- [1] Eixo Y;\n");
	printf("\n-> ");
	scanf("%d", &a);

	printf("\nQuantidade a ser cisalhada: ");
	if(a == 0)
		scanf("%f", &shx);
	if(a == 1)
		scanf("%f", &shy);

	//shearing matrix declaration
	float shearMatrixX[9] = {1, shx, 0, 0, 1, 0, 0, 0, 1};
	float shearMatrixY[9] = {1, 0, 0, shy, 1, 0, 0, 0, 1};

	//point vector and result array declaration
	float p[3], result[3];

	while(auxNode != NULL){

		p[0] = auxNode->ptList.x;
		p[1] = auxNode->ptList.y;
		p[2] = 1;

		if(a == 0)
			multMatrixArray(shearMatrixX, p, result);
		if(a == 1)
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

// Function number 17
// Implements the multiplication of two matrix 3x3
void multThreeByThreeMatrix(float first[][3], float second[][3], float result[][3]) {
	
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

/* ---------------------------------------------------------------------
   ---------------------- 3D Universe's Functions ----------------------
   --------------------------------------------------------------------- */

// Function 4
// Given two vectors performs the cross product
// In Computer Graphic, a vector is equals a point
// NOTE: this function gives a correct answer only when a and b start at the origin point (0,0,0)
void crossProduct(point3D a, point3D b, point3D *c) {

	c->x = (a.y * b.z) - (a.z * b.y);
	c->y = (a.z * b.x) - (a.x * b.z);
	c->z = (a.x * b.y) - (a.y * b.x);

}

// Function 5
// Implements the normalization of a vector
void normalizeVector(point3D a, point3D *b) {
	
	float length;

	length = sqrt((pow(a.x, 2)) + (pow(a.y, 2)) + (pow(a.z, 2)));
	b->x = a.x / length;
	b->y = a.y / length;
	b->z = a.z / length;

}

// Function 12
// Implements the multiplication of a matrix by a vector
void multMatrixArray3D(float *matrix, float *vector, float *result) {
	
	//multiplicating the matrix by the vector
	result[0] = (matrix[0]  * vector[0]) + (matrix[1]  * vector[1]) + (matrix[2]   * vector[2]) + (matrix[3]  * vector[3]);
	result[1] = (matrix[4]  * vector[0]) + (matrix[5]  * vector[1]) + (matrix[6]   * vector[2]) + (matrix[7]  * vector[3]);
	result[2] = (matrix[8]  * vector[0]) + (matrix[9]  * vector[1]) + (matrix[10]  * vector[2]) + (matrix[11] * vector[3]);
	result[3] = (matrix[12] * vector[0]) + (matrix[13] * vector[1]) + (matrix[14]  * vector[2]) + (matrix[15] * vector[3]);

}

// Function number 13
// Implements the multiplication of two matrix 4x4
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
