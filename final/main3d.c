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
main3d.c

OBJETIVO:
exemplo de execução de algumas rotinas para objetos 3D, com a finalidade 
de demonstrar o uso de funções gráficas implementadas pelo grupo no decorrer 
do semestre.

RESULTADO DA EXECUÇÃO:
é criado um prisma triangular idêntico ao usado no código de exemplo dado.

PARA COMPILAR:
gcc graphiclib.c main3d.c -o <nome_do_executavel> -lm -lX11

==========================================================================*/

/*==========================
  Biblioteca utilizada
==========================*/

#include "graphiclib.h"

/*==========================
  Início do main
==========================*/

int main(){

	/*-----------------------------------------
		Variables declaration
	-----------------------------------------*/
	
	point viewPortXY, vp; //universe min and max and viewport dimensions
	point3D minXYZ, maxXYZ, pt3D; //universe3D min and max
	point3D minUniverse, maxUniverse;
	
	/*-----------------------------------------
		Look-up table definition
	-----------------------------------------*/

	//cria uma lookup table com sete cores
	lookup lkt[7];
	lkt[0].colors.r = 1; lkt[0].colors.g = 1; lkt[0].colors.b = 1;
	lkt[1].colors.r = 0; lkt[1].colors.g = 0; lkt[1].colors.b = 0;
	lkt[2].colors.r = 1; lkt[2].colors.g = 1; lkt[2].colors.b = 0;
	lkt[3].colors.r = 1; lkt[3].colors.g = 0; lkt[3].colors.b = 0;
	lkt[4].colors.r = 0; lkt[4].colors.g = 1; lkt[4].colors.b = 0;	
	lkt[5].colors.r = 0; lkt[5].colors.g = 0; lkt[5].colors.b = 1;
	lkt[6].colors.r = 0; lkt[6].colors.g = 1; lkt[6].colors.b = 1;

	/*-----------------------------------------
		Universe and viewport setting
	-----------------------------------------*/

	//define o tamanho do universo
	minUniverse.x = -30; minUniverse.y = -30; minUniverse.z = 30;
	maxUniverse.x = 30; maxUniverse.y = 30; maxUniverse.z = -30;
	setUniverse3D(&minXYZ, &maxXYZ, minUniverse, maxUniverse);

	//define o tamanho do dispositivo discreto
	vp.x = 600; vp.y = 600;
	setViewPort(&viewPortXY, vp);

	/*-----------------------------------------
		Image buffer declaration and inicialization
	-----------------------------------------*/

	int image[(int)viewPortXY.x * (int)viewPortXY.y]; //creating the matrix
	initMatrix(image, &viewPortXY); //initializes the matrix

	/*-----------------------------------------
		Coordnates system
	-----------------------------------------*/

	// Definindo o Sistema de Coordenadas de Visualizacao 
    point3D u, v, w, vu; //Bases u, v e w
 
    vu.x = 0.0;	
    vu.y = 0.0;	
    vu.z = 1.0; 

    w.x = 0.0;	
    w.y = -1.0;	
    w.z = -1.0; 
    
    //funcoes ja normalizam os vetores
    crossProduct(vu, w, &u); // produto vetorial
    crossProduct(u, w, &v); // produto vetorial

    // Definição dos pontos da projecao
    point3D c_proj; //centro de projecao
    point3D p_proj; //plano de projecao
    
    c_proj.x = 0.0;	
    c_proj.y = 0.0;	
    c_proj.z = 40.0;

    p_proj.x = 0.0;	
    p_proj.y = 0.0;	
    p_proj.z = -20.0; 
    

	/*-----------------------------------------
		Objects declaration
	-----------------------------------------*/	
	
	//definição da quantidade de cores das faces
	int faceColor[5];

	//definição das cores das linhas das faces do objeto
	faceColor[0] = 6;
	faceColor[1] = 5;
	faceColor[2] = 4;
	faceColor[3] = 3;
	faceColor[4] = 2;

	// Declaracao do objeto de 5 faces
    face3D objeto3d[5];

    //inicializacao das listas de pontos das faces do objeto
	startList3D(&objeto3d[0]);
	startList3D(&objeto3d[1]);
	startList3D(&objeto3d[2]);
	startList3D(&objeto3d[3]);
	startList3D(&objeto3d[4]);

	//definiçao da primeira face do objeto 3d
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[0], &pt3D, &maxXYZ, &minXYZ);

	// definiçao da segunda face do objeto 3d
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[1], &pt3D, &maxXYZ, &minXYZ);

	// //definiçao da terceira face do objeto 3d
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[2], &pt3D, &maxXYZ, &minXYZ);
	
	//definiçao da quarta face do objeto 3d
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 0;		pt3D.z = 15;	addEndList3D(&objeto3d[3], &pt3D, &maxXYZ, &minXYZ);

	//definiçao da quinta face do objeto 3d
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = -10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = -10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);
	pt3D.x = 10;	pt3D.y = 10;	pt3D.z = 0;		addEndList3D(&objeto3d[4], &pt3D, &maxXYZ, &minXYZ);

	translate3D(objeto3d, 5, &minXYZ, &maxXYZ, &viewPortXY, 5, 2, 1);
	scale3D(objeto3d, 5, &minXYZ, &maxXYZ, &viewPortXY, 2, 2, 2);
	//rotate3D(objeto3d, 5, &minXYZ, &maxXYZ, &viewPortXY, 1);

	/* Realizando mudanca de base */
	mudancaDeBase(&objeto3d[0], u, v, w);
	mudancaDeBase(&objeto3d[1], u, v, w);
	mudancaDeBase(&objeto3d[2], u, v, w);
	mudancaDeBase(&objeto3d[3], u, v, w);
	mudancaDeBase(&objeto3d[4], u, v, w);

	/* Realizando projecao perspectiva das faces do objeto 3D */
	projecaoPerspectiva(&objeto3d[0], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[1], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[2], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[3], p_proj, c_proj);
	projecaoPerspectiva(&objeto3d[4], p_proj, c_proj);

	// normalizaçao e discretizacao dos pontos 3D das faces
	conversao(&objeto3d[0], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[1], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[2], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[3], &maxXYZ, &minXYZ, &viewPortXY);
	conversao(&objeto3d[4], &maxXYZ, &minXYZ, &viewPortXY);

	//desenho das linhas das faces do objeto
	printListBresenham3D(&objeto3d[0], image, &viewPortXY, faceColor[0]);
	printListBresenham3D(&objeto3d[1], image, &viewPortXY, faceColor[1]);
	printListBresenham3D(&objeto3d[2], image, &viewPortXY, faceColor[2]);
	printListBresenham3D(&objeto3d[3], image, &viewPortXY, faceColor[3]);
	printListBresenham3D(&objeto3d[4], image, &viewPortXY, faceColor[4]);

	//exibição da imagem final
	drawWindowLine(&viewPortXY, image, lkt);

	return 0;
}
