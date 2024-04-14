#include <bits/stdc++.h>

using namespace std;

// Function to set the console cursor position
void  setConsolePosition( SHORT posX , SHORT posY ){
    HANDLE  consoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD     cursorCoordinate;
    CONSOLE_SCREEN_BUFFER_INFO  consoleInfo;  

    GetConsoleScreenBufferInfo( consoleOutput , &consoleInfo );     
    cursorCoordinate.X = consoleInfo.srWindow.Left + posX;           
    cursorCoordinate.Y = consoleInfo.srWindow.Top + posY;            

    SetConsoleCursorPosition( consoleOutput , cursorCoordinate );
}

// Function to move the cursor
void moveCursor(POINT* cursorPosition,POINT direction,int directionIndex){
    if(directionIndex<1||directionIndex>4) directionIndex=0;
    else{
        cursorPosition->x = cursorPosition->x + directions[directionIndex][0]*direction.x;
        cursorPosition->y = cursorPosition->y + directions[directionIndex][1]*direction.y;
        SetCursorPos(cursorPosition->x,cursorPosition->y);
    }
}