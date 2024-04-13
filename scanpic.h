#include<bits/stdc++.h>

using namespace std;

/* Globals */
int ScreenX = 0;
int ScreenY = 0;
BYTE* ScreenData = 0;
void ScreenCap(POINT a, POINT b)
{
    HDC hScreen = GetDC(NULL);
    ScreenX = abs(b.x-a.x);
    ScreenY = abs(b.y-a.y);

    HDC hdcMem = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, ScreenX, ScreenY);
    HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, ScreenX, ScreenY, hScreen, a.x, a.y, SRCCOPY);
    SelectObject(hdcMem, hOld);

    BITMAPINFOHEADER bmi = {0};
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = ScreenX;
    bmi.biHeight = -ScreenY;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;// 3 * ScreenX * ScreenY;

    if(ScreenData)
        free(ScreenData);
    ScreenData = (BYTE*)malloc(4 * ScreenX * ScreenY);

    GetDIBits(hdcMem, hBitmap, 0, ScreenY, ScreenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

    ReleaseDC(GetDesktopWindow(),hScreen);
    DeleteDC(hdcMem);
    DeleteObject(hBitmap);
}

inline int PosB(int x, int y)
{
    return ScreenData[4*((y*ScreenX)+x)];
}

inline int PosG(int x, int y)
{
    return ScreenData[4*((y*ScreenX)+x)+1];
}

inline int PosR(int x, int y)
{
    return ScreenData[4*((y*ScreenX)+x)+2];
}

bool ButtonPress(int Key)
{
    bool button_pressed = false;

    while(GetAsyncKeyState(Key))
        button_pressed = true;

    return button_pressed;
}



int pf(POINT c,POINT d){
    int col[6][3]={
    {178,80,128},
    {55,92,132},
    {155,32,18},
    {45,121,35},
    {123,88,16},
    {126,37,132},
    };

    long R=0,G=0,B=0;
    for(int i=c.x;i<c.x+d.x;i++){
       for(int j=c.y;j<c.y+d.y;j++){
            R+=PosR(i,j);
            G+=PosG(i,j);
            B+=PosB(i,j);

        }
    }
    long long t=d.x*d.y;
    R/=t;
    G/=t;
    B/=t;
    //cout<<R<<" "<<G<<" "<<B<<" ";
    int maxx=1024,indx=-1,sum=0;
    for(int i=0;i<6;i++){
        sum=abs(col[i][0]-R)+abs(col[i][1]-G)+abs(col[i][2]-B);
        if(sum<maxx){
            maxx=sum;
            indx=i;
        }
    }
    return indx;
}

void scanball(int ball[5][6],POINT a,POINT b)
{
    POINT c,d;
    //int ball[5][6]={0};

    printf("開始截圖...");
    ScreenCap(a,b);
    printf("截圖完成\n");

    d.x=(b.x-a.x)/6;
    d.y=(b.y-a.y)/5;

    c.x=c.y=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){

           ball[i][j]=pf(c,d);
           c.x+=d.x;
        }
        //cout<<endl;
        c.x=0;
        c.y+=d.y;
    }
    //system("PAUSE");
    //return 0;
}
void scanpoint(POINT* p){

    while(1){
        int ch;
        if (_kbhit()){
            ch = _getch();
            if (ch ==  VK_RETURN){
                GetCursorPos(p);
                break;
            }
        }
    }

}
void scanabp(POINT* a,POINT* b,POINT* t){

    cout<<"請將滑鼠移動至整個版面的左上"<<endl;
    cout<<"確定位置之後按下"<<'"'<<"Enter"<<'"'<<"! "<<endl;
    scanpoint(a);
    cout<<"左上設定完成"<<endl;
    cout<<"請將滑鼠移動至整個版面的右下"<<endl;
    cout<<"確定位置之後按下"<<'"'<<"Enter"<<'"'<<"! "<<endl;
    scanpoint(b);
    cout<<"右下設定完成"<<endl;
    cout<<"請將滑鼠移至終端機-->"<<endl;
    cout<<"確定位置之後按下"<<'"'<<"Enter"<<'"'<<"! "<<endl;
    scanpoint(t);
    cout<<"設定完成"<<endl;

}

