#include <stdio.h>
#include <conio.h>
#include <dos.h>




/////////////////////////////
//                         //
//    interrupt handler    //
//                         //
/////////////////////////////
int Interrupt()
{        
    ///////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                       //
    //    If the interrupt capabilities are not enough, replace it at your discretion !!!    //
    //                                                                                       //
    ///////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////
    //                             //
    //    For INT 21h interrupt    //
    //                             //
    /////////////////////////////////
    union REGS reg;
    reg.h.ah = 0x7;        
    int86(0x21, &reg, &reg);
    return reg.h.al;
    
    /////////////////////////////////
    //                             //
    //    For INT 16h interrupt    //
    //                             //
    /////////////////////////////////
    // union REGS reg;
    // reg.h.ah = 0x2;        
    // int86(0x16, &reg, &reg);
    // return reg.h.al;
}




////////////////////////////
//                        //
//    keypress handler    //
//                        //
////////////////////////////
int KeysHandler(int &y,  int &work)
{
    int ch;
    ch = Interrupt();
    switch(ch)
    {
        case 80: y++; break; // In case down arrow pressed (4b in hex = 80 in dec)
        case 72: y--; break; // In case up arrow pressed (48 in hex = 72 in dec)
        case 27: work = 0; break; // Exit
        default: break; // Do nothing
    }
    return 1;
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
    clrscr();
    textcolor(textcol);

    for (int i = 0; i < x2 - x1 + 3; i++) cprintf("#");
    for(int j = 0; j < (y2 - y1 + 1); j++)
    {
        cprintf("#");
        for(int k = 0; k < (x2 - x1 + 1); k++) cprintf(" ");
        cprintf("#");
    };
    for (int l = 0; l < x2 - x1 + 3; l++) cprintf("#");

    window(x1,y1,x2,y2);
    textbackground(textback);
    clrscr();
    textcolor(textcol);
}




/////////////////////////////////////
//                                 //
//    application initializator    //
//                                 //
/////////////////////////////////////
main()
{
    clrscr();
    textbackground(BLACK);
    int textcol, textback, work = 1;
    int x1 = 25, y1 = 8, x2 = 55, y2 = 18;
    int x = (x2 - x1) / 2, y = (y2 - y1) / 2;

    WidnowDrawing(x1, y1, x2, y2, BLACK, RED);
    _setcursortype (_NOCURSOR);
    gotoxy(x,y);
    cprintf("[]");

    while (work)
    {
        if (KeysHandler(y, work))
        {
            if (y == 0) y=y2-y1+1;
            if (y == y2-y1+2) y=1;
            clrscr();
            gotoxy(x,y);
            cprintf("[]");
        }
    }
    return 0;
}
