/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

#include "graphiclib.h"

int main(){
	int i, j;
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

	int qPoint, qObject; //stores the quantity of points and objects selected by the user

	printf("Quantos objetos a imagem ira possuir: ");
	scanf("%d", &qObject);

	list l[qObject]; //list that will contain the array of objects with its points
	point pt; //point entered by the user that is added to the list

	for(j = 0; j < qObject; j++){
		printf("Quantos pontos o objeto %d ira possuir: ", j+1);
		scanf("%d", &qPoint);

		//starting the list
		startList(&l[j]);

		//fullfils the list with the points provided by the user
		for(i = 0; i < qPoint; i++){
			
			printf("Ponto %d\nCoordenada X: ", i+1);
			scanf("%f", &pt.x);
			printf("Coordenada Y: ");
			scanf("%f", &pt.y);
			printf("\n");

			//adds this point to the list
			addEndList(&l[j], &pt, &maxXY, &minXY, &viewPortXY);

		}

		//calls the function of the list responsible for printing the lines using Bresenham's algorithm
		printListBresenham(&l[j], image, &viewPortXY);
	}

	/*printf("Valores presentes na lista:\n");
	showList(&l);
	printf("\n");


	point testOne, testTwo, testThree;
	testOne = l->ptListD;
	testTwo = l->next->ptListD;
	testThree = l->next->next->ptListD;

	printf("\nValor do ponto D1 no main: %f %f", testOne.x, testOne.y);
	printf("\nValor do ponto D2 no main: %f %f", testTwo.x, testTwo.y);
	printf("\nValor do ponto D3 no main: %f %f", testThree.x, testThree.y);

	//test to print a bresenham line
	bresenham(image, &testOne, &testTwo, &viewPortXY);
	bresenham(image, &testTwo, &testThree, &viewPortXY);
	drawWindowLine(&viewPortXY, image);*/

	//sends the discrete matrix to x, for printing it graphically
	drawWindowLine(&viewPortXY, image);

//===================================================================================================

	/*ESTA PARTE ABAIXO DO TRACEJADO ERA COMO FAZIAMOS ANTES, ACIMA ESTA A TENTATIVA DE TRABALHAR COM LISTAS

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
	drawWindowLine(&viewPortXY, image);*/

	return 0;
}