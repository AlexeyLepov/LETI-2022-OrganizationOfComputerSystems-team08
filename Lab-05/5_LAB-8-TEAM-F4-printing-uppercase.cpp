#include <stdio.h>
#include <conio.h>




///////////////////////////////////
//                               //
//    System kbhit interrupts    //
//                               //
///////////////////////////////////
int keyPressHandler(int &work)
{
	char ch;
	int capslock = 0;
	if (kbhit())
	{
		ch = getch();
		switch (ch)
		{
			case 61: // In case F3 pressed (3d in hex = 61 in dec) // printing 'A' symbol
			    cprintf("A");
			    break;
			case 62: // In case F4 pressed (3e in hex = 62 in dec) // printing 'a' symbol
                cprintf("a");
                break;
			case 27:
			    work = 0;
			    break;
			default:
			    break;
		}
		return 1;
	}
	return 0;
}




//////////////////////////////////////////
//                                      //
//    drawing the application window    //
//                                      //
//////////////////////////////////////////
void WidnowDrawing(int x1, int y1, int x2, int y2, int textback, int textcol)
{
    window (x1-1, y1-1, x2+1, y2+2);
    textbackground(textback);
    textcolor(textcol);
    clrscr();

    for (int i = 0; i < x2 - x1 + 3; i++) cprintf("\"");
    for(int j = 0; j < (y2 - y1 + 1); j++)
    {
        cprintf("\"");
        for(int k = 0; k < (x2 - x1 + 1); k++) cprintf(" ");
        cprintf("\"");
    };
    for (int l = 0; l < x2 - x1 + 3; l++) cprintf("\"");

    window(x1,y1,x2,y2);
    textbackground(textback);
    textcolor(textcol);
    clrscr();
}




//////////////////////////////////////
//                                  //
//    application initialization    //
//                                  //
//////////////////////////////////////
main()
{
    int work = 1;
    int x1 = 25, y1 = 8, x2 = 55, y2 = 18;

	clrscr();
    textbackground(BLACK);
    WidnowDrawing(x1, y1, x2, y2, BLACK, BLUE);
    _setcursortype (_NOCURSOR);
    textcolor(RED);
    gotoxy(1,1);
    while (work)
    {
        keyPressHandler(work);
    }
    return 0;
}
