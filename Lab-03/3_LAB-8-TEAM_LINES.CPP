#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <graphics.h>
#include <string.h>

void make_graph(int N, int Y1, int Y3, double x0, double xm, double dx, float &fmax)
{
	double x, x1;
	float f, f1;
	int i;
	for (x = x0; x <= xm; x += dx)
	{
		f = (float)(pow((sin(x)),3.0)+pow((cos(x)),2.0));
		if (fmax < f)
			fmax = f;
	}
	setlinestyle(0,1,1);
	setcolor(YELLOW);
	x1 = x0;
	f1 = (float)(pow((sin(x0)),3.0)+pow((cos(x0)),2.0));
	for (i = 0, x = x0; i < N; i++, x += dx)
	{
		f = (float)(pow((sin(x)),3.0)+pow((cos(x)),2.0));
	//	putpixel(X1 + i +100 , Y3 - (int)((float)(Y3 - Y1) / (2.6 / f)), YELLOW);
		line( x1+i+100 , Y3-(int)((float)(Y3-Y1)/(2.6/f1)) , x+i+100 , Y3-(int)((float)(Y3-Y1)/(2.6/f)) );
		x1 = x;
		f1 = f;
	}
}

int main(){
 clrscr();
	int driver = DETECT, mode;

	initgraph(&driver, &mode, "c://turboc3//bgi");

	int Xmax = getmaxx(), Ymax = getmaxy();
	int X1 = 40, X2 = Xmax - 40, Y1 = 50, Y2 = Ymax - 70, N = X2 - X1 - 73 - 26, Y3 = (Y2-Y1)/2+30;
	float F, fmax = 0.;
	double x0 = 3 * M_PI / 2, xm = 8 * M_PI, dx = (xm - x0) / (N);

	setlinestyle(0, 20, 3);
	setcolor(YELLOW);
	rectangle(10, 10, Xmax - 10, Ymax - 10);

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

	make_graph(N, Y1, Y3, x0, xm, dx, fmax);

	char cfmax[10], str[24];
	sprintf(cfmax, "%f", fmax);
	strcpy(str, "fmax = ");
	strcat(str, cfmax);
	setcolor(YELLOW);
	outtextxy(90, Ymax - 135, "f(x) = sin^3(x) + cos^2(x)");
	outtextxy(390, Ymax - 135, str);


	getch();
	closegraph();
	return 0;

}
