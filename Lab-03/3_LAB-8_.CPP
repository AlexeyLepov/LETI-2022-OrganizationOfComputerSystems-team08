#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <graphics.h>
#include <string.h>

void Draw_Graphic(int N, int X1, int Y1,int Y2, int Y3, double x0, double xm, double dx, float &Fmax)
{
	double x;
	float F;
	int i;
	for (x = x0; x <= xm; x += dx)
	{
		F = (float)(pow((sin(x)),3.0)+pow((cos(x)),2.0));
		if (Fmax < F)
			Fmax = F;
	}
	for (i = 0, x = x0; i < N; i++, x += dx)
	{
		F = (float)(pow((sin(x)),3.0)+pow((cos(x)),2.0));
		putpixel(X1 + i +100 , Y3 - (int)((float)(Y3 - Y1) / (2.6 / F)), YELLOW);
	}
}

int main(){
 clrscr();
	int driver = DETECT, mode;

	initgraph(&driver, &mode, "c://turboc3//bgi");

	int Xmax = getmaxx(), Ymax = getmaxy();
	int X1 = 40, X2 = Xmax - 40, Y1 = 50, Y2 = Ymax - 70, N = X2 - X1 - 73 - 26, Y3 = (Y2-Y1)/2+30;
	float F, Fmax = 0.;
	double x0 = 3 * M_PI / 2, xm = 8 * M_PI, dx = (xm - x0) / (N);

	setlinestyle(0, 20, 3);
	setcolor(YELLOW);
	rectangle(10, 10, Xmax - 10, Ymax - 10);
	setfillstyle(SOLID_FILL, BLACK);
	floodfill(20, 20, YELLOW);
	Draw_Graphic(N, X1, Y1, Y2, Y3, x0, xm, dx, Fmax);
	setcolor(WHITE);

	setlinestyle(0, 1, 1);
	line(X1, Y3, X1, Y2 - 320);
	line(X1, Y3, X1, Y2 - 80);
	line(X1, Y3, X2, Y3);
	setcolor(YELLOW);

	outtextxy(X1 + 8, Y2-327, "f(x)");
	outtextxy(X2 + 8, Y3 - 4, "x");
	setcolor(WHITE);

	int i;


	for (i = -4; i < 5; ++i)
		line(X1 - 5, Y3 - i * 30, X1 + 5, Y3 - i * 30);
	for (i = 1; i < 9; ++i){
		line(X1 + 70 * i, Y3 + 5, X1 + 70 * i, Y3 - 5);
	}

	char xi[14][2];
	for (i = 4; i < 33; i += 4)
	{
		sprintf(xi[i / 4 - 1], "%dpi", i/4);
		outtextxy(X1 + 32.2 * i / 2 + i - 3, Y3 + 7, xi[i / 4 - 1]);
	}

	char yi[14][2];
	int k =0;
	int j=2;
	for (i = 0; i < 5; i += 2)
	{
		sprintf(yi[k], "%d", i / 2);
		outtextxy(X1 - 20, Y3 - 30 * i - i, yi[k]);
		k++;
	}
	for (i=-2; i>-5; i-=2){
	 sprintf(yi[k], "%d", i/2);
	 outtextxy(X1-20, Y3 - 30 * i + i, yi[k]);
	 k++;
	}

	k=0;

	char cFmax[10], str[24]; //Вывод максимального значения функции
	sprintf(cFmax, "%f", Fmax);
	strcpy(str, "Fmax = ");
	strcat(str, cFmax);
	setcolor(YELLOW);
	outtextxy(30, Ymax - 35, "F = sin^3(x) + cos^2(x)");
	outtextxy(300, Ymax - 35, str);
	getch();
	closegraph();
	return 0;

}
