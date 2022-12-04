#include <stdio.h>
#include <conio.h>
#include <dos.h>
//#include <WinAble.h>




///////////////////////////////////
//                               //
//    System kbhit interrupts    //
//                               //
///////////////////////////////////
int keyPressHandler(int &work)
{
    union REGS  rg;
    rg.h.ah = 2;
    int86(0x16, &rg, &rg);
	char ch;
	if (kbhit())
	{
		ch = getch();
		switch(ch)
		{
			case 61: // In case F3 pressed (3d in hex = 61 in dec) // printing 'A'/'a' symbol
                if((rg.h.al & 0x40) == 0) // if <CapsLock> not toggled
                {
                    cprintf("a");
                }
                else
                {
                    cprintf("A");
                }
                //::keybd_event(VkKeyScan('A'),0x9e, 0, 0); // 'A' Pressing - by <WinAble.h> lib
                //::keybd_event(VkKeyScan('A'),0x9e, KEYEVENTF_KEYUP,0); // 'A' Releasing  - by <WinAble.h> lib
			    break;
			case 62: // In case F4 pressed (3e in hex = 62 in dec) // works as CapsLock
                if((rg.h.al & 0x40) == 0) // if <CapsLock> not toggled
                {
                    outp(0x60,0xed);
                    outp(0x60,4);
                    //cprintf("NO"); //debbug
                }
                else
                {
                    outp(0x60,0xed);
                    outp(0x60,0);
                    //cprintf("YES"); //debbug
                }
                //::keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY, 0 ); // Pressing down
                //::keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // Releasing key
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
