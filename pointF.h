#include <bits/stdc++.h>

using namespace std;
//int dir[5][2] = {{0,0},{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void  gotoxy( SHORT x , SHORT y ){
    HANDLE  out = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD     coordinate;
    CONSOLE_SCREEN_BUFFER_INFO  csbi;  // 新增的程式碼

    GetConsoleScreenBufferInfo( out , &csbi );     // 新增的程式碼
    coordinate.X = csbi.srWindow.Left + x;           // 修改的程式碼
    coordinate.Y = csbi.srWindow.Top + y;            // 修改的程式碼

    SetConsoleCursorPosition( out , coordinate );
}
void key_control(int ball[5][6],int ball_num[6],POINT* A){
    int ch;
     if (_kbhit()){

            ch = _getch();

            switch(ch){
                case 77:
                    ball_move(ball,A,1);
                    break;

                case 72:
                    ball_move(ball,A,2);
                    break;

                case 75:
                    ball_move(ball,A,3);
                    break;

                case 80:
                    ball_move(ball,A,4);
                    break;

                default:
                    break;
            }
            ball_print(ball);
            cout<<A->x<<" "<<A->y<<endl;
            //cout<<A->x+1<<" "<<5-A->y<<endl;
    }
}
void point_move(POINT* p,POINT d,int k){
    if(k<1||k>4)k=0;
    else{

        p->x=p->x+dir[k][0]*d.x;
        p->y=p->y+dir[k][1]*d.y;
        SetCursorPos(p->x,p->y);
    }
}
