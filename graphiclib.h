/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

/* graphiclib.h */

#ifndef __graphiclib_h__
#define __graphiclib_h__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>

/*Points data structure*/

typedef struct Point{
	float x, y;	
}point;

typedef struct Point3D{
	float x, y, z;	
}point3D;

/*Color data structure*/

typedef struct RGB {
	float r, g, b;
}RGB;

typedef struct HSV {
	float h, s, v;
}HSV;

/*Look-up table structure*/
typedef struct Lookup{
	int numColors;
	RGB colors;
}lookup;

/*Objects data structure*/

// objects 2D
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
	struct Node3D *next;
}node3D;

typedef node3D *face3D;

typedef face3D *object3D;

/*Functions prototypes*/

int startList(list *p_l);
int emptyList(list *p_l);
void addEndList(list *p_l, point *pt, point *maxXY, point *minXY, point *viewPortXY);
void freeList(list *p_l);
void showList(list *p_l);
void printListBresenham(list *p_l, int *input, point *viewPortXY, int color);

void setUniverse(point *minXY, point *maxXY);
void getUniverse(point *minXY, point *maxXY);

void setValues(point *ptOne, point *ptTwo);
void getValues(point *ptOne, point *ptTwo);

void setViewPort(point *viewPortXY);
void getViewPort(point *viewPortXY);

void initMatrix(int *image, point *viewPortXY);

point sruToSrn(point *pt, point *maxXY, point *minXY);
point srnToSrd(point *ptN, point *viewPortXY);
void getSrn(point *ptOneN, point *ptTwoN);
void getSrd(point *ptOneD, point *ptTwoD);

void drawLine(int *input, point *ptOneD, point *ptTwoD, point *viewPortXY);
void bresenham(int *input, point *ptOneD, point *ptTwoD, point *viewPortXY, int color);

void multMatrixArray(float *matrix, float *vector, float *result);

point middleObject(list *p_L);

void translate(list *p_L, point *minXY, point *maxXY, point *viewPortXY, int dx, int dy);
void scale(list *p_L, point *minXY, point *maxXY, point *viewPortXY);
void rotate(list *p_L, point *minXY, point *maxXY, point *viewPortXY);
void mirror(list *p_L, point *minXY, point *maxXY, point *viewPortXY);
void shearing(list *p_L, point *minXY, point *maxXY, point *viewPortXY);

void drawWindow(point *viewPortXY);
void drawWindowLine(point *viewPortXY, int *input, lookup *lkt);

void rgbTohsv(RGB rgb, HSV *hsv);
void hsvTorgb(HSV hsv, RGB *rgb);

int startList3D(face3D *face);
int emptyList3D(face3D *face);
void addEndList3D(face3D *face, point3D *pt3D, point3D *maxXYZ, point3D *minXYZ);
void freeList3D(face3D *face);
void showList3D(face3D *face);

void setUniverse3D(point3D *minXYZ, point3D *maxXYZ);
void getUniverse3D(point3D *minXYZ, point3D *maxXYZ);

void multThreeByThreeMatrix(float first[][3], float second[][3], float result[][3]);
void multMatrixArray3D(float *matrix, float *vector, float *result);
void multFourByFourMatrix(float first[][4], float second[][4], float result[][4]);
void crossProduct(point3D a, point3D b, point3D *c);
void normalizeVector(point3D a, point3D *b);

#endif /* __graphiclib_h__ */
