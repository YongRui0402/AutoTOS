#include <bits/stdc++.h>
#include"cmb.h"
using namespace std;
int dir[5][2] = {{0,0},{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


void ball_count(int ball[5][6],int ball_num[6]){
    memset(ball_num,0, sizeof(ball_num));
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            ball_num[ball[i][j]]++;
        }
    }
}
void SetColor(int color = 7){
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole,color);
}
void ball_col(int b){
    SetColor();
    switch(b){
        case 0:
            SetColor(240);
            break;
        case 1:
            SetColor(176);
            break;
        case 2:
            SetColor(192);
            break;
        case 3:
            SetColor(160);
            break;
        case 4:
            SetColor(224);
            break;
        case 5:
            SetColor(80);
            break;
        default:
            SetColor();
            break;
    }

}
void ball_print(int ball[5][6]){

    for(int i=0;i<5;i++){
        printf("-");
        for(int j=0;j<6;j++){
            ball_col(ball[i][j]);
            //printf(" ");
            printf("%2d",ball[i][j]);
        }
        SetColor();
        printf("-\n");
    }
}
bool  ball_checkrange(int y,int x){
    return y<5&&y>=0&&x<6&&x>=0;
}
void ball_copy(int ans[5][6],int ball[5][6]){
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            ans[i][j]=ball[i][j];
        }
    }
}
int ball_cnum(int ball[5][6],int f){
    int w_ball[5][6]={
        26,24,22,22,24,26,
        24,23,21,21,23,24,
        18,17,15,15,17,18,
        24,23,21,21,23,24,
        26,24,22,22,24,26
    };
    int ball_ch[5][6]={0};
    int sum=0,sumcombo=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(i>0&&i<4)
                if(ball[i][j]==ball[i-1][j]&&ball[i][j]==ball[i+1][j]){
                   if(!ball_ch[i][j]&&!ball_ch[i-1][j]&&!ball_ch[i+1][j]){
                        sumcombo++;
                        if(j<5&&ball[i][j+1]==ball[i][j]&&ball_ch[i][j+1]==1){
                            sumcombo--;
                        }
                        else if(j>0&&ball[i][j-1]==ball[i][j]&&ball_ch[i][j-1]==1){
                            sumcombo--;
                        }
                        else if(j<5&&ball[i-1][j+1]==ball[i-1][j]&&ball_ch[i-1][j+1]==1){
                            sumcombo--;
                        }
                        else if(j>0&&ball[i-1][j-1]==ball[i-1][j]&&ball_ch[i-1][j-1]==1){
                            sumcombo--;
                        }

                   }
                    if(!ball_ch[i][j]){
                        ball_ch[i][j]=1;
                        sum+=w_ball[i][j];
                    }
                    if(!ball_ch[i-1][j]){
                        ball_ch[i-1][j]=1;
                        sum+=w_ball[i-1][j];

                    }
                    if(!ball_ch[i+1][j]){
                        ball_ch[i+1][j]=1;
                        sum+=w_ball[i+1][j];

                    }



                }

            if(j>0&&j<5)
                if(ball[i][j]==ball[i][j-1]&&ball[i][j]==ball[i][j+1]){
                    if(!ball_ch[i][j]&&!ball_ch[i][j-1]&&!ball_ch[i][j+1]){
                            sumcombo++;
                            if(j<3&&ball[i][j+2]==ball[i][j]&&ball_ch[i][j+2]==1){
                                sumcombo--;
                            }
                            else if(ball[i-1][j]==ball[i][j]&&ball_ch[i-1][j]==1){
                                sumcombo--;
                            }
                            else if(ball[i-1][j+1]==ball[i][j]&&ball_ch[i-1][j+1]==1){
                                sumcombo--;
                            }
                            else if(ball[i-1][j-1]==ball[i][j]&&ball_ch[i-1][j-1]==1){
                                sumcombo--;
                            }

                    }
                    if(!ball_ch[i][j]){
                        ball_ch[i][j]=1;
                        sum+=w_ball[i][j];
                    }
                    if(!ball_ch[i][j-1]){
                        ball_ch[i][j-1]=1;
                        sum+=w_ball[i][j-1];
                        //if(j==1||j==4)sum+=800*(5-i);

                    }
                    if(!ball_ch[i][j+1]){
                        ball_ch[i][j+1]=1;
                        sum+=w_ball[i][j+1];

                    }
                }
        }
    }

    //sumcombo=cmb(ball);
    //return sum+sumcombo*1500;
    if(f)return sum+sumcombo*1500/*+cmb(ball)*100*/;
    else return sum;
    //return sumcombo;
}
void ball_move(int ball[5][6],POINT* A,int k){
    if(k<1||k>4)k=0;
    else{
        int cx=dir[k][0],cy=dir[k][1];
        if(ball_checkrange(A->y+cy,A->x+cx)){
            swap(ball[A->y][A->x],ball[A->y+cy][A->x+cx]);
            A->x=A->x+cx;
            A->y=A->y+cy;
        }
    }

}
