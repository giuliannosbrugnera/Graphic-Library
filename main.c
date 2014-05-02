#include "graphiclib.h"

int main(){

	point  minXY, maxXY, viewPortXY, ptOne, ptTwo, ptOneN, ptTwoN, ptOneD, ptTwoD;

	//setting initial values
	setValues(&minXY, &maxXY, &ptOne, &ptTwo);

	//getting initial values
	getValues(&minXY, &maxXY, &ptOne, &ptTwo);

	//setting the view port size according to user input
	setViewPort(&viewPortXY);

	//getting the view port dimensions
	getViewPort(&viewPortXY);

	//creating the matrix
	char image[(int)viewPortXY.x * (int)viewPortXY.y];

	//converting sru to srn
	ptOneN = sruToSrn(&ptOne, &maxXY, &minXY);
	ptTwoN = sruToSrn(&ptTwo, &maxXY, &minXY);

	//getting the normalized points
	getSrn(&ptOneN, &ptTwoN);

	//converting srn to srd
	ptOneD = srnToSrd(&ptOneN, &viewPortXY);
	ptTwoD = srnToSrd(&ptTwoN, &viewPortXY);

	//getting the discrete points
	getSrd(&ptOneN, &ptTwoN);

	//initializing the matrix
	initMatrix(image, &viewPortXY);

	//draws a line by the first method seen
	//drawLine(image, &ptOneD, &ptTwoD, &viewPortXY);
	drawLine(image, &ptOneD, &ptTwoD, &viewPortXY);

	//reinitializing the matrix
	initMatrix(image, &viewPortXY);

	//draws a line by the bresenham method
	bresenham(image, &ptOneD, &ptTwoD, &viewPortXY);

	//creates a windows using X library according to the coordinates given by the user
	//drawWindow(&viewPortXY);

	//creates a window and draws the Bresenham line
	drawWindowLine(&viewPortXY, image);

	return 0;
}