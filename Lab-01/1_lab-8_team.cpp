#include<iostream>
#include<string.h>
#include<cmath>

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
        for (int i=0; i<32; i++) cout << set[i];
        cout<<endl;
        for (int i=0;i<32;i++){
            set[i]=~set[i]+2;
        }
        for (int i=0; i<32; i++) cout << set[i];
        cout<<endl;
        int m = 31;
        while ((set[m]!=0)&&(m!=-1)){
            m--;
        }
        if (set[31]==1) set[31]=0;
        set[m] = 1;
        break;
    }
    cout << "binary form of a number: \n";
    for (int i=0; i<32; i++) cout << set[i];
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
    cout << set[63] << " ";
    for (int i =62; i>=52; i--) cout << set[i];
    cout << " ";
    for (int i =51; i>=0; i--) cout << set[i];
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

int main(){
    long numL, sumL = 0;
    double numD, drob, fract, sumD=0.0;
    bool sign, *set, tes = true, tes1 = false, tes2=true, *rew, tmp, rset[20], tmines=false, ttchk = false;
    int typ, position, quantity, length, S, p, nS, tm, tt;
    int d, m, m1;
    char side, str[100];
    char M[] = "0123456789.-";
    cout << "enter your number: ";
    while (tes){
        cin >> str;
        tes2=true;
        d=0;
        tt=0;
        tm=0;
        d=find_simbol(str, M);
        for (int i=0; i<strlen(str);i++){
            if (str[i]=='.') tt++;
            if (str[i]=='-') tm++;
        }
        if((d==strlen(str))&&(tes2)&&(tm<=1)&&(tt<=1)){
            tes = false;
            cout << "if you entered a number that is too large or too small,";
            cout << "it will be changed according to the data type.\nFor data type long, acceptable values are [-2147483648...2147483647], for data type double - [-9223372036854775808.0...9223372036854775807.0].\n";
         }
         if (d!=strlen(str)) cout << "\nyou can only use numbers . and -\nenter new one: ";
         if (tes2==false) cout << "\nuse . not a , \nenter new one: ";
         if (tm>1) cout << "\nif you want to use a mines, then use it once.\nenter new one: ";
         if (tt>1) cout << "\nif you want to use a dot, then use it once.\nenter new one: ";
         cout << endl;
         
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
            cin >> position;
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
            cin >> length;
            if (length > 51-position){
                cout << "the value should be in the range from 1 to "<< 51-position << ", enter a new one: ";
            }
            else tes = false;
        }
        cout << "Enter the quantity: ";
        cin >> quantity;
        break;
    case 1: //long
        cout << "Enter the position: "; //position 
        tes = true;
        while (tes){
            cin >> position;
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
            cin >> length;
            if (length > 31-position+1){
                cout << "the value should be in the range from 1 to "<< 31-position+1 << ", enter a new one: ";
            }
            else tes = false;
        }
        cout << "Enter the quantity: ";
        cin >> quantity;
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
        for (int i=0; i<32; i++) cout << set[i];
        if (sumL<0) sumL+=1;
        cout << "\nnumL = " << sumL;
    }
    delete [] set;
    delete [] rew;
    return 0;
}