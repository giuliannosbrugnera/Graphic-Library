/*Daniel Ramos Miola 438340
  Giulianno Raphael Sbrugnera 408093
  Igor Felipe Ferreira Ceridório 408611
  Rafael Paschoal Giordano 408298*/

#include "graphiclib.h"

int main(){
	
	printf("\e[H\e[2J"); //cleans the unix terminal
	printf("----------------------------------\n");
	printf("CG - Biblioteca Grafica de Funcoes\n");
	printf("----------------------------------\n\n");

	/*-----------------------------------------
	Variables declaration
	-----------------------------------------*/
	
	int i, j; //iterators
	point  minXY, maxXY, viewPortXY; //universe min and max and viewport dimensions
	int qPoint, qObject; //stores the quantity of points and objects selected by the user
	int option; //user decides if wants to work with 2D or 3D dimension
	int listNum; //user decides which object he/she wants to apply transformations
	int menu; //stores the menu input by the user

	printf("Deseja trabalhar em qual dimensao?\n\n- [0] para 2D;\n- [1] para 3D.\n\n-> ");
	scanf("%d", &option);
	
	/*=========================================
	2D
	=========================================*/

	if(option == 0){

		printf("\e[H\e[2J"); //cleans the unix terminal
		printf("-------------------------------------\n");
		printf("CG - Biblioteca Grafica de Funcoes 2D\n");
		printf("-------------------------------------\n\n");

		/*-----------------------------------------
		Universe and viewport setting
		-----------------------------------------*/

		setUniverse(&minXY, &maxXY); //setting universe values
		//getUniverse(&minXY, &maxXY); //getting universe values

		setViewPort(&viewPortXY); //setting the view port size according to user input
		//getViewPort(&viewPortXY); //getting the view port dimensions

		/*-----------------------------------------
		Matrix declaration and inicialization
		-----------------------------------------*/

		char image[(int)viewPortXY.x * (int)viewPortXY.y]; //creating the matrix
		initMatrix(image, &viewPortXY); //initializes the matrix

		/*-----------------------------------------
		Objects declaration
		-----------------------------------------*/	
		printf("\nQuantos objetos a imagem ira possuir: ");
		scanf("%d", &qObject);

		list l[qObject]; //list that will contain the array of objects with its points
		point pt; //point entered by the user that is added to the list

		for(j = 0; j < qObject; j++){
			printf("\nQuantos pontos o objeto %d ira possuir: ", j+1);
			scanf("%d", &qPoint);
			printf("\n");

			startList(&l[j]); //starting the list

			//fullfils the list with the points provided by the user
			for(i = 0; i < qPoint; i++){
				
				printf("-> Ponto %d do objeto %d\n\nCoordenada X: ", i+1, j+1);
				scanf("%f", &pt.x);
				printf("Coordenada Y: ");
				scanf("%f", &pt.y);
				printf("\n");

				//adds this point to the list
				addEndList(&l[j], &pt, &maxXY, &minXY, &viewPortXY);
			}
		}

		/*-----------------------------------------
		Menu
		-----------------------------------------*/	

		printf("\e[H\e[2J"); //cleans the unix terminal
		printf("--------------------------\n");
		printf("2D - Menu de operacoes\n");
		printf("--------------------------\n\n");

		printf("- [0] Deslocamento;\n");
		printf("- [1] Rotacao;\n");
		printf("- [2] Escalonamento;\n");
		printf("- [3] Cisalhamento;\n");
		printf("- [4] Espelhamento;\n");
		printf("- [5] Exibir a imagem;\n");
		printf("- [6] Sair;\n");

		printf("\n-> ");
		scanf("%d", &menu);

		//translation option
		if(menu == 0){
			printf("\nQual objeto deseja deslocar: ");
			scanf("%d", &listNum);
			translate(&l[listNum-1]);
		} else if(menu == 6){
			exit(0);
		}

		for(j = 0; j < qObject; j++){
			//calls the function of the list responsible for printing the lines using Bresenham's algorithm
			printListBresenham(&l[j], image, &viewPortXY);
		}

		//TO-DO: misses passing color, here we may pass the look up table (I guess)
		drawWindowLine(&viewPortXY, image);
		
	}

	/*=========================================
	3D
	=========================================*/

	if(option == 1){
		
		printf("\e[H\e[2J"); //cleans the unix terminal
		printf("-------------------------------------\n");
		printf("CG - Biblioteca Grafica de Funcoes 3D\n");
		printf("-------------------------------------\n\n");

		printf("Ainda nao implementado...\n\n");
	}

	return 0;
}