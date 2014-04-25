/* graphiclib.h */

#ifndef __graphiclib_h__
#define __graphiclib_h__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/Xlib.h>

/*Point data structure*/

typedef struct Point{
	float x, y;
} point;

/*Color data structure*/

typedef struct RGB {
	float r, g, b;
}RGB;

typedef struct HSV {
	float h, s, v;
}HSV;

typedef struct pointList {
	point pt;
	struct pointList *next;
}PointList;

typedef struct edgeList {
	int pt1, pt2;
	struct edgeList *next;
}EdgeList;

typedef struct object {
	PointList points;
	EdgeList edges;
}Object;

/*Functions prototypes*/

void setValues(point *minXY, point *maxXY, point *ptOne, point *ptTwo);
void getValues(point *minXY, point *maxXY, point *ptOne, point *ptTwo);

void setViewPort(point *viewPortXY);
void getViewPort(point *viewPortXY);

void initMatrix(char *image, point *viewPortXY);

point sruToSrn(point *pt, point *maxXY, point *minXY);
point srnToSrd(point *ptN, point *viewPortXY);
void getSrn(point *ptOneN, point *ptTwoN);
void getSrd(point *ptOneD, point *ptTwoD);

void drawLine(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY);
void bresenham(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY);

void drawWindow(point *viewPortXY);
void drawWindowLine(point *viewPortXY, char *input);

void rgbTohsv(RGB rgb, HSV *hsv);
void hsvTorgb(HSV hsv, RGB *rgb);

void create(Object *obj);
// int vazia(LISTA_LIGADA *lista);
// int inserir(LISTA_LIGADA *lista, ITEM *item);

#endif /* __graphiclib_h__ */