#include<bits/stdc++.h>

using namespace std;

// Global variables for screen width, height and data
int screenWidth = 0;
int screenHeight = 0;
BYTE* screenData = 0;

// Function to capture screen from top left to bottom right points
void captureScreen(POINT topLeft, POINT bottomRight)
{
    // Get device context of the screen
    HDC screenDC = GetDC(NULL);
    // Calculate screen width and height
    screenWidth = abs(bottomRight.x - topLeft.x);
    screenHeight = abs(bottomRight.y - topLeft.y);

    // Create compatible device context and bitmap
    HDC memoryDC = CreateCompatibleDC(screenDC);
    HBITMAP bitmap = CreateCompatibleBitmap(screenDC, screenWidth, screenHeight);
    // Select the bitmap into the memory device context
    HGDIOBJ oldObject = SelectObject(memoryDC, bitmap);
    // Copy color data for the rectangle to the bitmap
    BitBlt(memoryDC, 0, 0, screenWidth, screenHeight, screenDC, topLeft.x, topLeft.y, SRCCOPY);
    // Restore the old bitmap
    SelectObject(memoryDC, oldObject);

    // Set up the bitmap info
    BITMAPINFOHEADER bitmapInfo = {0};
    bitmapInfo.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.biPlanes = 1;
    bitmapInfo.biBitCount = 32;
    bitmapInfo.biWidth = screenWidth;
    bitmapInfo.biHeight = -screenHeight;
    bitmapInfo.biCompression = BI_RGB;
    bitmapInfo.biSizeImage = 0;

    // Free old screen data and allocate new one
    if(screenData)
        free(screenData);
    screenData = (BYTE*)malloc(4 * screenWidth * screenHeight);

    // Get the color data from the bitmap
    GetDIBits(memoryDC, bitmap, 0, screenHeight, screenData, (BITMAPINFO*)&bitmapInfo, DIB_RGB_COLORS);

    // Clean up
    ReleaseDC(GetDesktopWindow(), screenDC);
    DeleteDC(memoryDC);
    DeleteObject(bitmap);
}

// Function to find the color of the ball in the grid
int findBallColor(POINT BallGrid_topLeft,POINT BallGrid_WH){
    // Define the colors
    int color[6][3]={
        {178,80,128},
        {55,92,132},
        {155,32,18},
        {45,121,35},
        {123,88,16},
        {126,37,132}};

    // Variables to store the sum of pixel colors
    long long redPixelsum=0,greenPixelsum=0,bluePixelsum=0;

    // Loop through the pixels in the grid
    for(int i=BallGrid_topLeft.x;i<BallGrid_topLeft.x+BallGrid_WH.x;i++){
       for(int j=BallGrid_topLeft.y;j<BallGrid_topLeft.y+BallGrid_WH.y;j++){
            // Calculate the pixel index
            int pixelindex = 4*((j*screenWidth)+i);
            // Add the color values to the sums
            bluePixelsum += screenData[pixelindex];
            greenPixelsum += screenData[pixelindex+1];
            redPixelsum += screenData[pixelindex+2];
        }
    }

    // Calculate the mean color values
    long long pixelcount=BallGrid_WH.x*BallGrid_WH.y,redPixelmean,greenPixelmean,bluePixelmean;
    redPixelmean = redPixelsum/pixelcount;
    greenPixelmean = greenPixelsum/pixelcount;
    bluePixelmean = bluePixelsum/pixelcount;

    // Find the color that is closest to the mean color
    int maxx=1e10,indx=-1,sum=0;
    for(int i=0;i<6;i++){
        sum=abs(color[i][0]-redPixelmean)+abs(color[i][1]-greenPixelmean)+abs(color[i][2]-bluePixelmean);
        if(sum<maxx){
            maxx=sum;
            indx=i;
        }
    }
    return indx;
}

// Function to scan the ball grid
void scanBallGrid(int ballGrid[5][6],POINT topLeft,POINT bottomRight)
{
    printf("開始截圖...");
    // Capture the screen
    captureScreen(topLeft,bottomRight);
    printf("截圖完成\n");
    
    // Variables to store the top left and width and height of each ball grid
    POINT perBallGrid_topLeft={0,0},perBallGrid_WH;
    perBallGrid_WH.x=(bottomRight.x-topLeft.x)/6;
    perBallGrid_WH.y=(bottomRight.y-topLeft.y)/5;

    // Loop through the ball grid
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
           // Find the color of the ball and store it in the grid
           ballGrid[i][j]=findBallColor(perBallGrid_topLeft,perBallGrid_WH);
           perBallGrid_topLeft.x+=perBallGrid_WH.x;
        }
        perBallGrid_topLeft.x=0;
        perBallGrid_topLeft.y+=perBallGrid_WH.y;
    }

}

// Function to scan the cursor position
void scanCursorPosition(POINT* cursorPosition){

    while(1){
        int ch;
        if (_kbhit()){
            ch = _getch();
            if (ch ==  VK_RETURN){
                // Get the cursor position when Enter is pressed
                GetCursorPos(cursorPosition);
                break;
            }
        }
    }

}

// Function to scan the board and terminal points
void scanBoardPoints(POINT* boardTopLeft,POINT* boardBottomRight,POINT* terminalPoint){

    cout<<"請將滑鼠移動至整個版面的左上"<<endl;
    cout<<"確定位置之後按下"<<'"'<<"Enter"<<'"'<<"! "<<endl;
    // Scan the cursor position for the top left of the board
    scanCursorPosition(boardTopLeft);
    cout<<"左上設定完成"<<endl;
    cout<<"請將滑鼠移動至整個版面的右下"<<endl;
    cout<<"確定位置之後按下"<<'"'<<"Enter"<<'"'<<"! "<<endl;
    // Scan the cursor position for the bottom right of the board
    scanCursorPosition(boardBottomRight);
    cout<<"右下設定完成"<<endl;
    cout<<"請將滑鼠移至終端機-->"<<endl;
    cout<<"確定位置之後按下"<<'"'<<"Enter"<<'"'<<"! "<<endl;
    // Scan the cursor position for the terminal point
    scanCursorPosition(terminalPoint);
    cout<<"設定完成"<<endl;

}