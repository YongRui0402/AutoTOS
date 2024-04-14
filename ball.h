#include <bits/stdc++.h>
using namespace std;
int directions[5][2] = {{0,0},{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


void countBalls(int ballGrid[5][6],int ballCount[6]){
    memset(ballCount,0, sizeof(ballCount));
    for(int row=0;row<5;row++){
        for(int col=0;col<6;col++){
            ballCount[ballGrid[row][col]]++;
        }
    }
}
void setConsoleColor(int color = 7){
  HANDLE consoleHandle;
  consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(consoleHandle,color);
}
void setBallColor(int ballType){
    setConsoleColor();
    switch(ballType){
        case 0:
            setConsoleColor(240);
            break;
        case 1:
            setConsoleColor(176);
            break;
        case 2:
            setConsoleColor(192);
            break;
        case 3:
            setConsoleColor(160);
            break;
        case 4:
            setConsoleColor(224);
            break;
        case 5:
            setConsoleColor(80);
            break;
        default:
            setConsoleColor();
            break;
    }
}
void printBalls(int ballGrid[5][6]){
    for(int row=0;row<5;row++){
        printf("-");
        for(int col=0;col<6;col++){
            setBallColor(ballGrid[row][col]);
            printf("%2d",ballGrid[row][col]);
        }
        setConsoleColor();
        printf("-\n");
    }
}
bool  isBallInRange(int y,int x){
    return y<5&&y>=0&&x<6&&x>=0;
}
void copyBalls(int destination[5][6],int source[5][6]){
    for(int row=0;row<5;row++){
        for(int col=0;col<6;col++){
            destination[row][col]=source[row][col];
        }
    }
}
int calculateBallNumber(int ballGrid[5][6],int flag){
    int ballWeights[5][6]={
        26,24,22,22,24,26,
        24,23,21,21,23,24,
        18,17,15,15,17,18,
        24,23,21,21,23,24,
        26,24,22,22,24,26
    };
    int ballChecked[5][6]={0};
    int sum=0,sumCombo=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(i>0&&i<4)
                if(ballGrid[i][j]==ballGrid[i-1][j]&&ballGrid[i][j]==ballGrid[i+1][j]){
                   if(!ballChecked[i][j]&&!ballChecked[i-1][j]&&!ballChecked[i+1][j]){
                        sumCombo++;
                        if(j<5&&ballGrid[i][j+1]==ballGrid[i][j]&&ballChecked[i][j+1]==1){
                            sumCombo--;
                        }
                        else if(j>0&&ballGrid[i][j-1]==ballGrid[i][j]&&ballChecked[i][j-1]==1){
                            sumCombo--;
                        }
                        else if(j<5&&ballGrid[i-1][j+1]==ballGrid[i-1][j]&&ballChecked[i-1][j+1]==1){
                            sumCombo--;
                        }
                        else if(j>0&&ballGrid[i-1][j-1]==ballGrid[i-1][j]&&ballChecked[i-1][j-1]==1){
                            sumCombo--;
                        }

                   }
                    if(!ballChecked[i][j]){
                        ballChecked[i][j]=1;
                        sum+=ballWeights[i][j];
                    }
                    if(!ballChecked[i-1][j]){
                        ballChecked[i-1][j]=1;
                        sum+=ballWeights[i-1][j];

                    }
                    if(!ballChecked[i+1][j]){
                        ballChecked[i+1][j]=1;
                        sum+=ballWeights[i+1][j];

                    }



                }

            if(j>0&&j<5)
                if(ballGrid[i][j]==ballGrid[i][j-1]&&ballGrid[i][j]==ballGrid[i][j+1]){
                    if(!ballChecked[i][j]&&!ballChecked[i][j-1]&&!ballChecked[i][j+1]){
                            sumCombo++;
                            if(j<3&&ballGrid[i][j+2]==ballGrid[i][j]&&ballChecked[i][j+2]==1){
                                sumCombo--;
                            }
                            else if(ballGrid[i-1][j]==ballGrid[i][j]&&ballChecked[i-1][j]==1){
                                sumCombo--;
                            }
                            else if(ballGrid[i-1][j+1]==ballGrid[i][j]&&ballChecked[i-1][j+1]==1){
                                sumCombo--;
                            }
                            else if(ballGrid[i-1][j-1]==ballGrid[i][j]&&ballChecked[i-1][j-1]==1){
                                sumCombo--;
                            }

                    }
                    if(!ballChecked[i][j]){
                        ballChecked[i][j]=1;
                        sum+=ballWeights[i][j];
                    }
                    if(!ballChecked[i][j-1]){
                        ballChecked[i][j-1]=1;
                        sum+=ballWeights[i][j-1];
                        //if(j==1||j==4)sum+=800*(5-i);

                    }
                    if(!ballChecked[i][j+1]){
                        ballChecked[i][j+1]=1;
                        sum+=ballWeights[i][j+1];

                    }
                }
        }
    }

    //sumCombo=cmb(ball);
    //return sum+sumCombo*1500;
    if(flag)return sum+sumCombo*1500/*+cmb(ball)*100*/;
    else return sum;
    //return sumCombo;
}
void ball_move(int ballGrid[5][6],POINT* A,int k){
    if(k<1||k>4)k=0;
    else{
        int cx=directions[k][0],cy=directions[k][1];
        if(isBallInRange(A->y+cy,A->x+cx)){
            swap(ballGrid[A->y][A->x],ballGrid[A->y+cy][A->x+cx]);
            A->x=A->x+cx;
            A->y=A->y+cy;
        }
    }

}
