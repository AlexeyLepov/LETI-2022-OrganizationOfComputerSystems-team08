//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//    //////////////////////////////////////////////////////////////////////    //
//    //                                                                  //    //
//    //    Program for working with the text mode of the video system    //    //
//    //                                                                  //    //
//    //////////////////////////////////////////////////////////////////////    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#include <conio.h>
#include <dos.h>

///////////////////////
//                   //
//    Coordinates    //
//                   //
///////////////////////
int x1 = 25;
int y1 = 8;
int x2 = 55;
int y2 = 18;

////////////////////////
//                    //
//    Main program    //
//                    //
////////////////////////
void main()
{
	enum colors {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY,
		DARKGRAY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};

	char colors_name[][16] = {
		"BLACK",
		"BLUE",
		"GREEN",
		"CYAN",
		"RED",
		"MAGENTA",
		"BROWN",
		"LIGHTGRAY",
		"DARKGRAY",
		"LIGHTBLUE",
		"LIGHTGREEN",
		"LIGHTCYAN",
		"LIGHTRED",
		"LIGHTMAGENTA",
		"YELLOW",
		"WHITE"
	};

	colors background;
	colors text;
	window(x1, y1, x2, y2);
	for (int i = 0; i < 8; i++)
	{
		background = colors(i);
		textbackground(background);
		for (int j = 0; j < 16; j++)
		{
			text = colors(j);
			textcolor(text);
			insline();
			cprintf("\r");
			cprintf("Text color: %s \r\nBackground color: %s\r\n\n", colors_name[text], colors_name[background]);
			delay(1200); // time deley for 1.2 seconds
		}
	}
	getch();
}
