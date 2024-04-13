#include <iostream>
#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "ball.h"
#include "pointF.h"
#include"scanpic.h"

clock_t  Begin, End;
using namespace std;
//int dir[5][2] = {{0,0},{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
string ss="";
POINT ENDA={0,0},BEGINA={0,0};
int maxn=0;
int ans[5][6]={0};
void dfs(int ball[5][6],POINT A,POINT B,string s,int c,int p,int f,int time){
    End = clock();
    if(End-Begin>time){

    }
    else if(c==p){
        int temp[5][6]={0};
        POINT CA=A;
        ball_copy(temp,ball);
        for(int i=0;i<s.length();i++){
            ball_move(temp,&CA,s[i]-'0');
        }


        int num=ball_cnum(temp,f);
        if(maxn<num){
            maxn=num;
            ball_copy(ans,temp);
            BEGINA=A;
            ENDA=CA;
            ss=s;
        }
    }
    else{
        int d=0,len=s.length();
        char k=5;
        if(len!=0){
                k=s[len-1];
                d=k-'0';
                d+=2;
                if(d>4)d-4;
        }

        /*for(int i=1;i<5;i++){
            if(i!=d&&ball_checkrange(B.y+dir[i][1],B.x+dir[i][0])){

                string t=s+char('0'+i);
                POINT C=POINT{B.x+dir[i][0],B.y+dir[i][1]};
                dfs(ball,A,C,t,c+1,p,f);
            }
        }*/
        int ch[5]={1,0,0,0,0};
        while(ch[1]!=1||ch[2]!=1||ch[3]!=1||ch[4]!=1){
            int i = rand()%4+1;

            if(ch[i]==0&&i!=d&&ball_checkrange(B.y+dir[i][1],B.x+dir[i][0])){

                string t=s+char('0'+i);
                POINT C=POINT{B.x+dir[i][0],B.y+dir[i][1]};
                dfs(ball,A,C,t,c+1,p,f,time);
            }
            ch[i]=1;

        }
    }

}
int main(){
    system("mode con cols=40 lines=18");
    POINT a,b,p,d,t;
    int flag=1;
    scanabp(&a,&b,&t);
    srand( time(NULL) );


    while(flag){

        system("cls");
        d.x=(b.x-a.x)/6;
        d.y=(b.y-a.y)/5;

        int ball[5][6]={0};
        int temp[5][6]={0};
        int ball_num[6]={0};
        //Sleep(3000);
        scanball(ball,a,b);
        ball_print(ball);
        cout<<"確定'Enter' 重新截圖 'R' 離開 'Esc'"<<endl<<endl;
        while(1){
            int ch;
            if (_kbhit()){
                ch = _getch();
                if (ch ==  VK_RETURN){
                    break;
                }
                if (ch == 'R'||ch == 'r'){
                    system("cls");
                    scanball(ball,a,b);
                    ball_print(ball);
                    cout<<"確定'Enter' 重新截圖 'R' 離開 'Esc'"<<endl<<endl;

                }
                if (ch ==  VK_ESCAPE){
                    system("cls");
                    flag=0;
                    break;
                }
            }
        }
        if(!flag)break;

        system("cls");
        string S="";
        ball_copy(temp,ball);
        maxn=0;
        S="";
        POINT A={0,0},B={0,0};

        ball_print(ball);

        int maxa=0;

        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                ball_copy(temp,ball);
                A={i,j};
                for(int k=1;k<12;k++){
                    Begin = clock();
                    dfs(temp,A,A,"",0,k,1,100);
                }
            }
        }

        B=BEGINA;
        A=ENDA;
        ball_copy(temp,ans);
        cout<<"Y="<<B.x<<" X="<<B.y<<" 方向"<<0<<" 第"<<0<<"步"<<endl<<endl<<endl;
        cout<<ss<<endl;
        S+=ss;


        while(1){
            string T=ss;

            for(int i=1;i<33;i++){
                Begin = clock();
                dfs(temp,A,A,"",0,i,1,100);
            }

            if(ss==T||S.length()>90)break;
            ball_copy(temp,ans);
            A=ENDA;
            cout<<ss<<endl;
            if(ss==T||ss.length()+S.length()>90)break;
            S+=ss;
        }

        p.x=a.x+d.x/2+d.x*B.x;
        p.y=a.y+d.y/2+d.y*B.y;
        SetCursorPos(p.x,p.y);

        A=B;
        //mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(400);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        Sleep(600);
        for(int i=0;i<S.length();i++){

                Sleep(50);
                point_move(&p,d,S[i]-'0');
                ball_move(ball,&A,S[i]-'0');
                gotoxy(0,0);
                ball_print(ball);
                cout<<"Y="<<A.x<<" X="<<A.y<<" 方向"<<S[i]<<" 第"<<i+1<<"步"<<endl;
        }
        Sleep(50);
        SetCursorPos(p.x+20,p.y+20);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

        SetCursorPos(t.x,t.y);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        cout<<cmb(ball)<<"combo "<<endl<<endl;

        cout<<"繼續'Enter' 離開 'Esc'";

        while(1){
            int ch;
            if (_kbhit()){
                ch = _getch();
                if (ch ==  VK_RETURN){
                    break;
                }
                if (ch ==  VK_ESCAPE){
                    system("cls");
                    flag=0;
                    break;
                }
            }
        }
        //Sleep(3000);
    }
    cout<<"結束程式"<<endl;


    return 0;
}
