#include<iostream>
#include<string.h>
#include<cmath>
#include<windows.h>

using namespace std;

int find_simbol(string str1, char str2[]){
    int d = 0;
    for (int i =0; i<str1.size();i++){
        for (int j=0; j<strlen(str2); j++){
            if (str1[i]==str2[j]) d++;
        }
    }
    return d;
}

void form_binary_long (long numL, bool set[]){
    bool sign;
    numL >= 0 ? sign = true : sign = false;
    switch (sign)
    {
    case true:
        for (int i = 31; i>=0; i--){
            set[i]=numL%2;
            numL/=2;
        }
        break;
    case false:
        for (int i = 31; i>=0; i--){
            set[i]=numL%2;
            numL/=2;
        }
        for (int i=0;i<32;i++){
            set[i]=~set[i]+2;
        }
        int m = 31;
        while ((set[m]!=0)&&(m!=-1)){
            m--;
        }
        if (set[31]==1) set[31]=0;
        set[m] = 1;
        break;
    }
    cout << "binary form of a number: \n";
    cout << "|0-------------------------------31|\n";
    cout << "|";
    for (int i=0; i<32; i++) cout << set[i];
    cout << "  |";
}

void form_binary_double (double numD, bool set[]){
    bool sign;
    double drob, fract;
    int nS, d, m1;
    numD >= 0 ? sign = true : sign = false;
    sign == true ? set[63] = 0 : set[63] = 1;
    if (sign == false) numD*=-1;

    fract = modf(numD, &drob);
    int m=51;
    int a = static_cast<int>(drob);
    nS=0;
    while (a!=0){
        a/=2;
        nS++;
    }
    nS--;
    d=1;
    m1=m-nS;
    a = static_cast<int>(drob);
    for (int i = m1+1; i<=51; i++) {
        set[i]=a%2;
        a/=2;
        m--;
    }
    while (fract!=0){
        fract*=2;
        d=static_cast<int>(fract);
        set[m] = d;
        if (d==1) fract-=1;
        m--;
    }
    nS+=1023;
    m=52;
    while (m!=63){
        set[m] = nS%2;
        nS/=2;
        m++;
    }
    cout << "binary form of a number (S-P-M): \n";
    cout << "63|62" << "           " << "52|51" << "                "<<"                                   0|\n";
    cout <<set[63] << " |  ";
    for (int i =62; i>=52; i--) cout << set[i];
    cout << "  |  ";
    for (int i =51; i>=0; i--) cout << set[i];
    cout<<"|";
}

void shift_right (bool rew[], int quantity, int length){
    bool tmp=0;
    for(int i=0; i<quantity; i++)
        {
            for(int j=length-1; j>=0; j--)
            {
                if (j==length-1)
                    tmp=rew[length-1];
                else
                    rew[j+1]=rew[j];
            }
            rew[0]=tmp;
        }
}
void shift_left (bool rew[], int quantity, int length){
    bool tmp = 0;
    for(int i=0; i<quantity; i++)
        {
            for(int j=0; j<length; j++)
            {
                if (j==0)
                    tmp=rew[0];
                else
                    rew[j-1]=rew[j];
            }
            rew[length-1]=tmp;
        }
}

double back_to_decimal_double(bool set[], bool sign){
    double sumD=0;
    int m, S, d;
    m=0;
    S=0;
    for (int i = 52; i<=62; i++){
        S+=set[i]*pow(2,m);
        m++;
    }
    S-=1023;
    m=51;
    cout << endl;
    for (int i = 1; i<=S;i++){
        sumD+=set[m]*pow(2,S-i);
        m--;
    }
    sumD = sumD + pow(2,S);
    d=-1;
    for (int i=m;i>=0;i--) {
        sumD = sumD + set[i]*(pow(2,d));
            d--;
    }
    if (set[63]==1) sumD= sumD*(-1);
    return sumD;
}

long back_to_decimal_long (bool set[]){
    long sumL=0;
    for (int i=0; i<32; i++) sumL+=set[i]*pow(2,31-i);
    return sumL;
}

int int_vvod(){
    int pos=0, d;
    bool tess, us;
    char str1[100], simbols[]="0123456789-";
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    tess=true;
    while (tess){
    cin >> str1;
    us = true;
    d=0;
    for (int i=0; i<strlen(str1);i++){
        for (int j=0; j<strlen(simbols);j++){
            if (str1[i]==simbols[j]) d++;
        }
    }
    d==strlen(str1) ? us = true : us = false;
    if (us){
        if (((str1[0]!='-')&&(strlen(str1)<strlen("2147483647")))||((str1[0]=='-')&&(strlen(str1)<strlen("-2147483647")))) {pos = atoi(str1); tess=false;}
            if ((strlen(str1)==strlen("2147483647"))||(strlen(str1)==strlen("-2147483647"))){
                if ((strcmp(str1,"2147483647")<=0)||(strcmp(str1,"-2147483647")<=0)) {
                    pos = atoi(str1);
                    tess=false;
                }
            }
            if (tess!=false)cout << "\nnum is too large for int\nenter new one [-2147483648...2147483647]: ";
        }
        else cout << "please, use numbers and mines\nenter new one: ";
    }
    return pos;

}

int main(){
    long numL, sumL = 0;
    double numD, sumD=0.0;
    bool sign, *set, tes = true, tes1 = false, tes2=true, *rew;
    int typ, position, quantity, length, tm, tt;
    int d, m, ccorddot=0;
    char side, str[100];
    char M[] = "0123456789,-", L1[] = "-2147483648", L2[] = "2147483647", D1[] = "-9223372036854775808,0", D2[] = "9223372036854775807,0";
    cout << "Attention! to enter doble, use a comma, not a dot.\n";
    cout << "enter your number: ";
    while (tes){
        cin >> str;
        tes2=true;
        d=0;
        tt=0;
        tm=0;
        d=find_simbol(str, M);
        for (int i=0; i<strlen(str);i++){
            if (str[i]==',') {tt++; ccorddot = i;}
            if (str[i]=='-') tm++;
        }

        if((d==strlen(str))&&(tes2)&&(tm<=1)&&(tt<=1)){
            tes = false;

         }
         if ((tt==0)&&(tes==false)){
            if (((str[0] == '-')&&(strlen(str)>strlen(L1)))||((str[0]!='-')&&(strlen(str)>strlen(L2)))){
                tes = true;
            }
            if (((str[0] == '-')&&(strlen(str)==strlen(L1)))||((str[0]!='-')&&(strlen(str)==strlen(L2)))){
                if(str[0]=='-'){
                    if(strcmp(str,L1)>0) tes = true;
                }
                if(str[0]!='-'){
                    if(strcmp(str,L2)>0) tes = true;
                }
            }
            if (tes==true) {
                cout << "if you entered a number that is too large or too small:\n";
                cout << "\nFor data type long, acceptable values are [-2147483648...2147483647], for data type double - [-9223372036854775808,0...9223372036854775807,0].\n\n";
                cout<< "this number is too large for long type\nenter new one: ";
            }
        }
        if ((tt==1)&&(tes==false)){
            if (((str[0] == '-')&&((ccorddot)>20))||((str[0]!='-')&&((ccorddot)>19))){
                tes = true;
            }
            if (((str[0] == '-')&&((ccorddot)==20))||((str[0]!='-')&&((ccorddot)==19))){
                if(str[0]=='-'){
                    if(strcmp(str,D1)>0) tes = true;
                }
                if(str[0]!='-'){
                    if(strcmp(str,D2)>0) tes = true;
                }
            }
            if (tes==true) {
                cout << "if you entered a number that is too large or too small:\n";
                cout << "\nFor data type long, acceptable values are [-2147483648...2147483647], for data type double - [-9223372036854775808,0...9223372036854775807,0].\n\n";
                cout<< "this number is too large for double type\nenter new one: ";
            }
        }
        if (str[0]=='.') {tes=true; cout << "incorrect using a comma\n";}
        if (d!=strlen(str)) cout << "\nyou can only use numbers , and -\nenter new one: ";
         if (tes2==false) cout << "\nuse , not a . \nenter new one: ";
         if (tm>1) cout << "\nif you want to use a mines, then use it once.\nenter new one: ";
         if (tt>1) cout << "\nif you want to use a comma, then use it once.\nenter new one: ";

    }
    tt == 1 ? typ = 0 : typ = 1;

    //Enter num
    /*-----------------------------------------*/
    switch (typ)
    {
    case 0:{
        cout << "you are using double\n" << endl;
        numD=atof(str);

        set = new bool [64];
        for (int i = 0; i<64; i++) set[i] = 0;
        form_binary_double(numD,set);
        break;
    }
//long
    case 1:
        cout<<"you are using long type\n";
        numL=atoi(str);
        cout << "numL = " << numL << endl;
        set = new bool[32];
        for (int i=0; i<32; i++) set[i] = 0;
        form_binary_long(numL,set);
    }

    cout << endl;
    switch (typ)
    {
    case 0: //double
        cout << "Enter the position: "; //position
        tes = true;
        while (tes){
            position = int_vvod();
            switch (position)
            {
            case 0 ... 51:
                cout << "the position is entered correctly" << endl;
                tes=false;
                break;
            default:
                cout << "the value should be in the range from 0 to 51, enter a new one: ";
            }
        }
        cout << "Enter the length: ";
        tes = true;
        while (tes){//length
            length = int_vvod();
            if (length > 51-position){
                cout << "the value should be in the range from 1 to "<< 51-position << ", enter a new one: ";
            }
            else tes = false;
        }
        cout << "Enter the quantity: ";
        quantity = int_vvod();
        while (quantity<0)
        {
            cout << "quantiy must be >= 0\nenter new one: ";
            quantity = int_vvod();

        }
        break;
    case 1: //long
        cout << "Enter the position: "; //position
        tes = true;
        while (tes){
            position = int_vvod();
            switch (position)
            {
            case 1 ... 31:
                cout << "the position is entered correctly" << endl;
                tes=false;
                break;
            default:
                cout << "the value should be in the range from 1 to 31, enter a new one: ";
            }
        }
        int b = 31-position;
        cout << "Enter the length: ";
        tes = true;
        while (tes){//length
            length = int_vvod();
            if (length > 31-position+1){
                cout << "the value should be in the range from 1 to "<< 31-position+1 << ", enter a new one: ";
            }
            else tes = false;
        }
        cout << "Enter the quantity: ";
        quantity = int_vvod();
        while (quantity<0)
        {
            cout << "quantiy must be >= 0\nenter new one: ";
            quantity = int_vvod();
        }
        break;
    }
    rew = new bool [length];
    for (int i =0; i<length; i++) rew[i]=0;
    m=0;

    for (int i = position; i< position + length; i++){
        rew[m] = set[i];
        m++;
    }
    cout << "Enter the side (r = ->; l = <-): ";
    cin >> side;
    while ((side!='r')&&(side!='l')){
        cout << "enter r or l: ";
        cin >> side;
    }
    cout << endl;

    cout << "the segment before the shift\n";
    for (int i = 0; i<length; i++) cout << rew[i] << " ";
    cout << endl;

    switch (side)
    {
    case 'r':
        shift_right(rew,quantity,length);
        break;

    case 'l':
        shift_left(rew,quantity,length);
        break;
    }

    cout << "the segment after the shift\n";
    for (int i = 0; i<length; i++) cout << rew[i] << " ";
    cout << endl;

    m=0;
    for (int i=position; i<position+length;i++){
        set[i]=rew[m];
        m++;
    }
    cout << endl;
    switch (typ)
    {
    case 0:
        sumD=back_to_decimal_double(set,sign);
        cout << "numD = " << sumD << endl;
        break;
    case 1:
        sumL=back_to_decimal_long(set);
        cout << "binary form of a number: \n";
        cout << "|0-------------------------------31|\n";
        cout << "|";
        for (int i=0; i<32; i++) cout << set[i];
        cout << "  |";
        if (sumL<0) sumL+=1;
        cout << "\nnumL = " << sumL;
    }
    delete [] set;
    delete [] rew;
    return 0;
}
