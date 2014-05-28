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

/*Objects data structure*/

typedef struct Node{
	point ptList;  //coordinates of the point
	point ptListN; //point normalized
	point ptListD; //point discrete
	struct Node *next;
}node;

typedef node *list;

/*Functions prototypes*/
void multMatrix(float matrizA[][3], int matrizB[][1], int* matrizC);

int startList(list *p_l);
int emptyList(list *p_l);
void addEndList(list *p_l, point *pt, point *maxXY, point *minXY, point *viewPortXY);
void freeList(list *p_l);
void showList(list *p_l);
void printListBresenham(list *p_l, char *input, point *viewPortXY);

void setUniverse(point *minXY, point *maxXY);
void getUniverse(point *minXY, point *maxXY);

void setValues(point *ptOne, point *ptTwo);
void getValues(point *ptOne, point *ptTwo);

void setViewPort(point *viewPortXY);
void getViewPort(point *viewPortXY);

void initMatrix(char *image, point *viewPortXY);

point sruToSrn(point *pt, point *maxXY, point *minXY);
point srnToSrd(point *ptN, point *viewPortXY);
void getSrn(point *ptOneN, point *ptTwoN);
void getSrd(point *ptOneD, point *ptTwoD);

void drawLine(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY);
void bresenham(char *input, point *ptOneD, point *ptTwoD, point *viewPortXY);
void translate(list *p_l);
void rotate(list *p_l);
void scale(list *p_l);
void mirror(list *p_l);

void drawWindow(point *viewPortXY);
void drawWindowLine(point *viewPortXY, char *input);

void rgbTohsv(RGB rgb, HSV *hsv);
void hsvTorgb(HSV hsv, RGB *rgb);


#endif /* __graphiclib_h__ */