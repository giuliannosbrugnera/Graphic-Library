/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

#include "graphiclib.h"

int main(){
	int i, j, option;
	point  minXYZ, maxXYZ, viewPortXY;

	printf("Quais as dimensoes do seu(s) objeto(s)?\n-[0] para 2D;\n-[1] para 3D.\n-> ");
	scanf("%d", &option);

	//setting universe values
	setUniverse(&minXYZ, &maxXYZ, option);

	//getting universe values
	getUniverse(&minXYZ, &maxXYZ, option);

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
		printf("\n");

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
			addEndList(&l[j], &pt, &maxXYZ, &minXYZ, &viewPortXY, option);

		}

		//calls the function of the list responsible for printing the lines using Bresenham's algorithm
		//scale(&l[j]);
		printListBresenham(&l[j], image, &viewPortXY);
	}

	//sends the discrete matrix to x, for printing it graphically
	drawWindowLine(&viewPortXY, image);

	return 0;
}