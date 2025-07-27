#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int height = 20;
const int width = 20;

int x,y,fruitX,fruitY,score;

int tailX[100],tailY[100],nTail;

enum eDirection{STOP=0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

void Setup(){
    gameOver = false;
    x=width/2;
    y=height/2;
    fruitX=rand() %width;
    fruitY=rand() %height;
}

void Draw(){

    system("cls");

    for(int i = 0; i<width; i++){
        cout<<'#';
    }
    cout<<endl;

    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            if(j==0 || j==width-1){
                cout<<'#';
            } else if (i==y && j==x)
            {
                cout<<'O';
            } else if (i==fruitY && j==fruitX)
            {
                cout<<'F';
            } else {
                bool print=false;

                for(int k=0;k<nTail;++k){
                    if(i==tailY[k] && j==tailX[k]){
                        cout << 'o';
                        print = true;
                    }
                }
                if(!print) cout << ' ';
            }
        }
        cout<<endl;
    }

    for(int i = 0; i<height; i++) cout<<'#';

    cout<<endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
        }
    }
}

void Logic(){

    int prevX=tailX[0];
    int prevY=tailY[0];
    tailX[0]=x;
    tailY[0]=y;
    int prev2X,prev2Y;

    for(int i=1;i<nTail;++i){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir){
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    if(x<1 || x>width-2 || y<0 || y>height-1) gameOver=true;


    for(int i = 0;i<nTail;++i){
        if(y==tailY[i] && x==tailX[i]){
            gameOver=true;
        }
    }

    if(x==fruitX && y==fruitY){
        score++;
        fruitX=rand() %width;
        fruitY=rand() %height;
        nTail++;
    }
}



int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    
}