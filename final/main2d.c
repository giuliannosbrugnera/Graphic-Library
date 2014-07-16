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
main2d.c

OBJETIVO:
exemplo de execução de algumas rotinas para objetos 2D, com a finalidade de 
demonstrar o uso de funções gráficas implementadas pelo grupo no decorrer 
do semestre.

RESULTADO DA EXECUÃO:
são criados oito objetos, quatro triângulos e quatro quadrados. Eles são
criados dois a dois, lado a lado, de tamanho idêntico. Então, o polígono 
do lado direito sofre alguma transformação, afim de demonstrar a corretude
das implementações de transformações com o uso de coordenadas homogêneas
e uso do ponto médio do objeto, para que após transformada, a imagem
mantenha-se em seu lugar de origem.

PARA COMPILAR:
gcc graphiclib.c main2d.c -o <nome_do_executavel> -lm -lX11

==========================================================================*/

/*==========================
  Biblioteca utilizada
==========================*/

#include "graphiclib.h"

/*==========================
  Início do main
==========================*/

int main(){

	//declaração de variáveis
	int i, j; //contadores
	point  minXY, maxXY, viewPortXY, pt; //mínimo e máximo do universo e dimensão da viewport
	point minUniverse, maxUniverse, vp;	

	//definição da quantidade de objetos
	list l[8]; int objColor[8];

	//cria uma lookup table com sete cores
	lookup lkt[7];
	lkt[0].colors.r = 1; lkt[0].colors.g = 1; lkt[0].colors.b = 1;
	lkt[1].colors.r = 0; lkt[1].colors.g = 0; lkt[1].colors.b = 0;
	lkt[2].colors.r = 1; lkt[2].colors.g = 1; lkt[2].colors.b = 0;
	lkt[3].colors.r = 1; lkt[3].colors.g = 0; lkt[3].colors.b = 0;
	lkt[4].colors.r = 0; lkt[4].colors.g = 1; lkt[4].colors.b = 0;	
	lkt[5].colors.r = 0; lkt[5].colors.g = 0; lkt[5].colors.b = 1;
	lkt[6].colors.r = 0; lkt[6].colors.g = 1; lkt[6].colors.b = 1;

	//define o tamanho do universo
	minUniverse.x = 0; minUniverse.y = 0;
	maxUniverse.x = 50; maxUniverse.y = 50;
	setUniverse(&minXY, &maxXY, minUniverse, maxUniverse);

	//define o tamanho do dispositivo discreto
	vp.x = 500; vp.y = 500;
	setViewPort(&viewPortXY, vp);

	//declaracao e inicailizacao do buffer da imagem
	int image[(int)viewPortXY.x * (int)viewPortXY.y];
	initMatrix(image, &viewPortXY);

	//definição das cores das linhas dos objetos
	objColor[0] = 6;
	objColor[1] = 5;
	objColor[2] = 4;
	objColor[3] = 3;
	objColor[4] = 2;
	objColor[5] = 6;
	objColor[6] = 5;
	objColor[7] = 4;

	//inicializacao das listas de pontos dos objetos
	startList(&l[0]);
	startList(&l[1]);
	startList(&l[2]);
	startList(&l[3]);
	startList(&l[4]);
	startList(&l[5]);
	startList(&l[6]);
	startList(&l[7]);

	//definição do primeiro polígono (quadrado)
	pt.x = 10; pt.y = 5;  addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 5;  addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 10; addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 10; addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 5;  addEndList(&l[0], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do segundo polígono (quadrado)
	pt.x = 35; pt.y = 5;  addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 5;  addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 10; addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 10; addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 5;  addEndList(&l[1], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de rotação em 45º no seundo polígono
	rotate(&l[1], &minXY, &maxXY, &viewPortXY, 45);

	//definição do terceiro polígono (triângulo)
	pt.x = 10; pt.y = 15; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 15; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 12; pt.y = 20; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 15; addEndList(&l[2], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do quarto polígono (triângulo)
	pt.x = 35; pt.y = 15; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 15; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 37; pt.y = 20; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 15; addEndList(&l[3], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de espelhamento em torno do eixo X no quarto polígono
	mirror(&l[3], &minXY, &maxXY, &viewPortXY, 0);

	//definição do quinto polígono (triângulo)
	pt.x = 10; pt.y = 25; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 25; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 12; pt.y = 30; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 25; addEndList(&l[4], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do sexto polígono (triângulo)
	pt.x = 35; pt.y = 25; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 25; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 37; pt.y = 30; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 25; addEndList(&l[5], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de cisalhamento com valor 2 para o sexto polígono
	shearing(&l[5], &minXY, &maxXY, &viewPortXY, 0, 1, 1);

	//definição do sétimo polígono (quadrado)
	pt.x = 10; pt.y = 35; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 35; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 15; pt.y = 40; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 40; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 10; pt.y = 35; addEndList(&l[6], &pt, &maxXY, &minXY, &viewPortXY);

	//definição do oitavo polígono (quadrado)
	pt.x = 35; pt.y = 35; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 35; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 40; pt.y = 40; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 40; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);
	pt.x = 35; pt.y = 35; addEndList(&l[7], &pt, &maxXY, &minXY, &viewPortXY);

	//aplicação de escalamento no oitavo polígono
	scale(&l[7], &minXY, &maxXY, &viewPortXY, 2, 2);

	//desenho das linhas dos objetos
	printListBresenham(&l[0], image, &viewPortXY, objColor[0]);
	printListBresenham(&l[1], image, &viewPortXY, objColor[1]);
	printListBresenham(&l[2], image, &viewPortXY, objColor[2]);
	printListBresenham(&l[3], image, &viewPortXY, objColor[3]);
	printListBresenham(&l[4], image, &viewPortXY, objColor[4]);
	printListBresenham(&l[5], image, &viewPortXY, objColor[5]);
	printListBresenham(&l[6], image, &viewPortXY, objColor[6]);
	printListBresenham(&l[7], image, &viewPortXY, objColor[7]);

	//exibição da imagem final
	drawWindowLine(&viewPortXY, image, lkt);

	return 0;
}