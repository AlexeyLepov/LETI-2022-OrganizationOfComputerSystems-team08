#include <stdio.h>
#include <dos.h>

void main(void)
{
    union REGS  rg;

    printf("\n����������� ����-���� � ASCII-���� ������.\n��� ���������� ������ ������� ������� ESC.\n\n");

    for(;;)
    {
        // �������� ���������� INT 16h
        rg.h.ah = 0;
        int86(0x16, &rg, &rg);
        // ������� �� ����� ���������� ��������� AH � AL,
        // ����������, ��������������, ����-��� � ASCII-���
        // ������� �������.
        printf("\nScan = %02.2X Ascii = %02.2X", rg.h.ah, rg.h.al);
        // ���� ���� ������ ������� ESC, ��������� ������ ���������
        if(rg.h.ah == 1) break;
    }
}
