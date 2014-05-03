#include "graphiclib.h"

int main(){
	int i;
	point  minXY, maxXY, viewPortXY, ptOne, ptTwo, ptOneN, ptTwoN, ptOneD, ptTwoD;

	//setting universe values
	setUniverse(&minXY, &maxXY);

	//getting universe values
	getUniverse(&minXY, &maxXY);

	//setting the view port size according to user input
	setViewPort(&viewPortXY);

	//getting the view port dimensions
	getViewPort(&viewPortXY);

	//creating the matrix
	char image[(int)viewPortXY.x * (int)viewPortXY.y];

	//initializes the matrix
	initMatrix(image, &viewPortXY);

	list l; //list that will contain the points of the object
	int q; //stores the quantity of points selected by the user
	point pt; //point entered by the user that is added to the list

	printf("Quantos pontos o objeto ira possuir: ");
	scanf("%d", &q);

	//starting the list
	startList(&l);

	//fullfils the list with the points provided by the user
	for(i = 0; i < q; i++){
		
		printf("Ponto %d\nCoordenada X: ", i+1);
		scanf("%f", &pt.x);
		printf("Coordenada Y: ");
		scanf("%f", &pt.y);
		printf("\n");

		//adds this point to the list
		addEndList(&l, &pt, &maxXY, &minXY, &viewPortXY);

	}

	printf("Valores presentes na lista:\n");
	showList(&l);
	printf("\n");

	//break to freeze the program
	getchar(); getchar();
//===================================================================================================

	//ESTA PARTE ABAIXO DO TRACEJADO ERA COMO FAZIAMOS ANTES, ACIMA ESTA A TENTATIVA DE TRABALHAR COM LISTAS

	//setting universe values
	setUniverse(&minXY, &maxXY);

	//getting universe values
	getUniverse(&minXY, &maxXY);

	//setting points values
	setValues(&ptOne, &ptTwo);

	//getting points values
	getValues(&ptOne, &ptTwo);

	//setting the view port size according to user input
	setViewPort(&viewPortXY);

	//getting the view port dimensions
	getViewPort(&viewPortXY);

	//converting sru to srn
	ptOneN = sruToSrn(&ptOne, &maxXY, &minXY);
	ptTwoN = sruToSrn(&ptTwo, &maxXY, &minXY);

	//getting the normalized points
	getSrn(&ptOneN, &ptTwoN);

	//converting srn to srd
	ptOneD = srnToSrd(&ptOneN, &viewPortXY);
	ptTwoD = srnToSrd(&ptTwoN, &viewPortXY);

	//getting the discrete points
	getSrd(&ptOneD, &ptTwoD);

	//initializing the matrix
	initMatrix(image, &viewPortXY);

	//draws a line by the first method seen
	//drawLine(image, &ptOneD, &ptTwoD, &viewPortXY);

	//reinitializing the matrix
	//initMatrix(image, &viewPortXY);

	//draws a line by the bresenham method
	bresenham(image, &ptOneD, &ptTwoD, &viewPortXY);

	//creates a windows using X library according to the coordinates given by the user
	//drawWindow(&viewPortXY);

	//creates a window and draws the Bresenham line
	drawWindowLine(&viewPortXY, image);

	return 0;
}