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
	struct Node3D *next;
}node3D;

typedef node3D *face3D;

typedef face3D *object3D;

/*==========================
  Protótipos das funções
==========================*/

//bloco de funções comuns

//bloco de funções 2D

//bloco de funções 3D

point sruToSrn(point *pt, point *maxXY, point *minXY);
point srnToSrd(point *ptN, point *viewPortXY);
point middleObject(list *p_L);
void  setUniverse(point *minXY, point *maxXY, point minUniverse, point maxUniverse);
void  setViewPort(point *viewPortXY, point vp);
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

#endif /* __graphiclib_h__ */