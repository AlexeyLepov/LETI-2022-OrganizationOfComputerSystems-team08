#include <stdio.h>
#include <dos.h>

void main(void)
{
    union REGS  rg;
    int   i, zflag;

    for(;;)
    {
        // ������� � ����� ������ '*'
        putchar('*');
        // ��������� �������� �� �������
        for(i=0; i<1000; i++);
        // �������� ���������� INT 16h ��� �������� ������ ����������
        // ������������� ����, ������� ����� ������� ��� ������� ��
        // ����� �������
        zflag = 1;
        _asm
        {
            mov   ax, 0100h
            int   16h
            // ���� ������� �� ����,
            // ���������� ���������� ���������
            jz    nokey
            // ��� ������� �� ����� �������
            // ���������� ����
            mov   zflag, 0
            nokey:
        }
        if(zflag == 0)
        {
            // ���� ���� �������, ������ ��� ������� ������� �� ������
            // ��� ������ ������� 01h ���������� INT 16h
            rg.h.ah = 0;
            int86(0x16, &rg, &rg);
            // ���� ���� ������ ������� ESC, ��������� ������ ���������,
            // ��� �������, ��� ������������� CapsLock ��������
            if(rg.h.ah == 1)
            {
                // ������������� ��������� ��������� ������� CapsLock,
                // ���� ������� ������������� ��� 0x40 � ����� ���������
                rg.h.ah = 2;
                int86(0x16, &rg, &rg);
                if((rg.h.al & 0x40) == 0) break;
                else printf("\n��� ���������� ������� ESC ��� ����������� ������� CapsLock.\n");
            }
            else printf("\n��� ���������� ������� ESC ��� ����������� ������� CapsLock.\n");
        }
    }
}