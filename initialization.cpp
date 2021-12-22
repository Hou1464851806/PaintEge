#include<graphics.h>
#include"initialization.h"

int Swidth, Sheight;
int Cwidth, Cheight;
int Dwidth, Dheight;
int fontSize = 20;

void initialize(int w, int h)
{
	//calculate
	Swidth = w;
	Sheight = h;
	Cheight = Sheight * 2 / 3;
	Cwidth = Swidth;
	Dheight = Sheight - Cheight;
	Dwidth = Swidth * 3 / 5;
	//drawUI
	initgraph(Swidth, Sheight, 0);
	ege_enable_aa(true);
	setbkcolor(BLACK);
	setcolor(GREEN);
	ege_line(0, Cheight - 5, Cwidth, Cheight - 5);
	ege_line(Dwidth - 5, Cheight - 5, Dwidth - 5, Swidth);
	//show initial information
	setcolor(GREEN);
	setfont(fontSize, 0, "Times New Roman");
	outtextxy(Dwidth, Cheight, "You haven't created or opened a file!");
	setviewport(0, Cheight, Dwidth - 5 * 2, Sheight);
}