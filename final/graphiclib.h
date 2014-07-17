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
graphiclib.h

DESCRIÇÃO:
arquivo que contém o cabeçalho da biblioteca gráfica, com a definição 
das estruturas utilizadas e protótipos das funções.

==========================================================================*/

/*==========================
  Bibliotecas utilizadas
==========================*/

#ifndef __graphiclib_h__
#define __graphiclib_h__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>

/*==========================
  Estruturas utilizadas
==========================*/

//definição de um ponto 2D
typedef struct Point{
	float x, y;	
}point;

typedef struct PointD{
	int x, y;	
}pointD;

//definição de um ponto 3D
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

//definição para um objeto 3D
typedef struct Node3D{
	point3D ptList3D;  //coordinates of the point
	point3D ptList3DN; //point normalized
	pointD ptListD; //point discrete
	struct Node3D *next;
}node3D;

typedef node3D *list3D;

typedef node3D *face3D;

typedef face3D *object3D;

/*==========================
  Protótipos das funções
==========================*/

/*-------------------------
  Bloco de funções comuns
-------------------------*/

void  setViewPort(point *viewPortXY, point vp);
void  initMatrix(int *image, point *viewPortXY);
void  addEndList(list *p_l, point *pt, point *maxXY, point *minXY, point *viewPortXY);
void  bresenham(int *input, point *ptOneD, point *ptTwoD, point *viewPortXY, int color);
void  drawWindow(point *viewPortXY);
void  drawWindowLine(point *viewPortXY, int *input, lookup *lkt);
void  rgbTohsv(RGB rgb, HSV *hsv);
void  hsvTorgb(HSV hsv, RGB *rgb);

/*-------------------------
  Bloco de funções 2D
-------------------------*/

point sruToSrn(point *pt, point *maxXY, point *minXY);
point srnToSrd(point *ptN, point *viewPortXY);
point middleObject(list *p_L);
void  setUniverse(point *minXY, point *maxXY, point minUniverse, point maxUniverse);
void  multMatrixArray(float *matrix, float *vector, float *result);
void  multThreeByThreeMatrix(float first[][3], float second[][3], float result[][3]);
void  printListBresenham(list *p_l, int *input, point *viewPortXY, int color);
void  translate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int dx, int dy);
void  scale(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int sx, int sy);
void  rotate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int a);
void  mirror(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int mOpt);
void  shearing(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int shOpt, int shx, int shy);
void  fill(list *p_L, int *input, int color, point p, point *viewPortXY);
int   startList(list *p_l);
int   emptyList(list *p_l);

/*-------------------------
  Bloco de funções 3D
-------------------------*/

point3D sruToSrn3D(point3D pt, point3D *maxXYZ, point3D *minXYZ);
pointD  srnToSrd3D(point3D pt3DN, point *viewPortXY);
point3D middleObject3D(list3D *p_L);
void 	setUniverse3D(point3D *minXYZ, point3D *maxXYZ, point3D minUniverse, point3D maxUniverse);
void 	crossProduct(point3D a, point3D b, point3D *c);
int 	startList3D(face3D *face);
int 	emptyList3D(face3D *face);
void 	addEndList3D(face3D *face, point3D *pt3D, point3D *maxXYZ, point3D *minXYZ);
void 	conversao(face3D *face, point3D *maxXYZ, point3D *minXYZ, point *viewPortXY);
void 	mudancaDeBase(face3D *face, point3D u, point3D v, point3D w); 
void 	projecaoPerspectiva(face3D *face, point3D p_proj, point3D c_proj);
void 	printListBresenham3D(face3D *face, int *input, point *viewPortXY, int color);
void 	translate3D(face3D *object, int n, point3D *minXYZ, point3D *maxXYZ, point *viewPortXY, int dx, int dy, int dz);
void 	scale3D(face3D *object, int n, point3D *minXYZ, point3D *maxXYZ, point *viewPortXY, int dx, int dy, int dz);
void 	rotate3D(face3D *object, int n, point3D *minXYZ, point3D *maxXYZ, point *viewPortXY, int teta);
void 	multMatrixArray3D(float *matrix, float *vector, float *result);
void 	multFourByFourMatrix(float first[][4], float second[][4], float result[][4]);

#endif /* __graphiclib_h__ */