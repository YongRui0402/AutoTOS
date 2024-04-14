#include <iostream>
#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "ball.h"
#include "movecursor.h"
#include"scanboard.h"
#include"calculatecombos.h"

clock_t  startTime, endTime;
using namespace std;
string tmpmoveSequence="";
POINT ENDPoint={0,0},BEGINPoint={0,0};
int maxScore=0;
int finalGrid[5][6]={0};
void dfs(int ballGrid[5][6],POINT startPoint,POINT currentPoint,string s,int currentDepth,int maxDepth,int flag,int timeLimit){
    endTime = clock();
    if(endTime-startTime>timeLimit){

    }
    else if(currentDepth==maxDepth){
        int temp[5][6]={0};
        POINT copystartPoint=startPoint;
        copyBalls(temp,ballGrid);
        for(int i=0;i<s.length();i++){
            ball_move(temp,&copystartPoint,s[i]-'0');
        }


        int score=calculateBallNumber(temp,flag);
        if(maxScore<score){
            maxScore=score;
            copyBalls(finalGrid,temp);
            BEGINPoint=startPoint;
            ENDPoint=copystartPoint;
            tmpmoveSequence=s;
        }
    }
    else{
        int oppositeDirection=0,sequenceLength=s.length();
        char k=5;
        if(sequenceLength!=0){
                k=s[sequenceLength-1];
                oppositeDirection=k-'0';
                oppositeDirection+=2;
                if(oppositeDirection>4)oppositeDirection-4;
        }

        int directionChecked[5]={1,0,0,0,0};
        while(directionChecked[1]!=1||directionChecked[2]!=1||directionChecked[3]!=1||directionChecked[4]!=1){
            int i = rand()%4+1;

            if(directionChecked[i]==0&&i!=oppositeDirection&&isBallInRange(currentPoint.y+directions[i][1],currentPoint.x+directions[i][0])){

                string t=s+char('0'+i);
                POINT C=POINT{currentPoint.x+directions[i][0],currentPoint.y+directions[i][1]};
                dfs(ballGrid,startPoint,C,t,currentDepth+1,maxDepth,flag,timeLimit);
            }
            directionChecked[i]=1;

        }
    }

}
int main(){
    system("mode con cols=40 lines=18");
    POINT topLeft,bottomRight,clickPoint,gridDimension,tetminalPoint;
    int continueFlag=1;
    scanBoardPoints(&topLeft,&bottomRight,&tetminalPoint);
    srand( time(NULL) );


    while(continueFlag){

        system("cls");
        gridDimension.x=(bottomRight.x-topLeft.x)/6;
        gridDimension.y=(bottomRight.y-topLeft.y)/5;

        int ballGrid[5][6]={0};
        int tempGrid[5][6]={0};

        scanBallGrid(ballGrid,topLeft,bottomRight);
        printBalls(ballGrid);
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
                    scanBallGrid(ballGrid,topLeft,bottomRight);
                    printBalls(ballGrid);
                    cout<<"確定'Enter' 重新截圖 'R' 離開 'Esc'"<<endl<<endl;

                }
                if (ch ==  VK_ESCAPE){
                    system("cls");
                    continueFlag=0;
                    break;
                }
            }
        }
        if(!continueFlag)break;

        system("cls");
        string totalmoveSequence="";
        copyBalls(tempGrid,ballGrid);
        maxScore=0;
        POINT startPoint={0,0},endPoint={0,0};
        printBalls(ballGrid);

        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                copyBalls(tempGrid,ballGrid);
                startPoint={i,j};
                for(int k=1;k<12;k++){
                    startTime = clock();
                    dfs(tempGrid,startPoint,startPoint,"",0,k,1,100);
                }
            }
        }

        endPoint=BEGINPoint;
        startPoint=ENDPoint;
        copyBalls(tempGrid,finalGrid);
        cout<<"Y="<<endPoint.x<<" X="<<endPoint.y<<" 方向"<<0<<" 第"<<0<<"步"<<endl<<endl<<endl;
        cout<<tmpmoveSequence<<endl;
        totalmoveSequence+=tmpmoveSequence;


        while(1){
            string T=tmpmoveSequence;

            for(int i=1;i<33;i++){
                startTime = clock();
                dfs(tempGrid,startPoint,startPoint,"",0,i,1,100);
            }

            if(tmpmoveSequence==T||totalmoveSequence.length()>90)break;
            copyBalls(tempGrid,finalGrid);
            startPoint=ENDPoint;
            cout<<tmpmoveSequence<<endl;
            if(tmpmoveSequence==T||tmpmoveSequence.length()+totalmoveSequence.length()>90)break;
            totalmoveSequence+=tmpmoveSequence;
        }

        clickPoint.x=topLeft.x+gridDimension.x/2+gridDimension.x*endPoint.x;
        clickPoint.y=topLeft.y+gridDimension.y/2+gridDimension.y*endPoint.y;
        SetCursorPos(clickPoint.x,clickPoint.y);

        startPoint=endPoint;
        //mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(400);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        Sleep(600);
        for(int i=0;i<totalmoveSequence.length();i++){

                Sleep(50);
                moveCursor(&clickPoint,gridDimension,totalmoveSequence[i]-'0');
                ball_move(ballGrid,&startPoint,totalmoveSequence[i]-'0');
                setConsolePosition(0,0);
                printBalls(ballGrid);
                cout<<"Y="<<startPoint.x<<" X="<<startPoint.y<<" 方向"<<totalmoveSequence[i]<<" 第"<<i+1<<"步"<<endl;
        }
        Sleep(50);
        SetCursorPos(clickPoint.x+20,clickPoint.y+20);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

        SetCursorPos(tetminalPoint.x,tetminalPoint.y);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        cout<<calculatecombos(ballGrid)<<"combo "<<endl<<endl;

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
                    continueFlag=0;
                    break;
                }
            }
        }
        //Sleep(3000);
    }
    cout<<"結束程式"<<endl;


    return 0;
}
