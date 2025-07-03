#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
//..........prototypes
void printmaze();
void moveleft();
void moveright();
void moveup();
void movedown();
void ghost1();
void ghost2();
void ghost3();
void ghost4();
void gotoxy(int x, int y);
void scoredisplay();
void scorecount(int x , int y);
void livesdisplay();
void livescount();
void positionreset();
bool gameover();
void storemazeintofile();
void loadmazefromfile();
bool powerEnergizer();
//..........Global Data Structures
char maze[24][71] = {};
int score = 0;
int lives = 3;
int pacmanX = 10;
int pacmanY = 34;
int ghost1x = 13;
int ghost1y = 7;
const int ghost1xC = 13;
const int ghost1yC = 7;
bool ghost1moving = true;
int ghost2x = 22;
int ghost2y = 51;
const int ghost2xC = 22;
const int ghost2yC = 51;
bool ghost2moving = true;
int ghost3x = 8;
int ghost3y = 28;
const int ghost3xC = 8;
const int ghost3yC = 28;
bool ghost3movingHorizontally = true;
bool ghost3movingVertically = true;
bool alternatemovement = true;
int ghost4x = 10 ;
int ghost4y = 32 ;
const int ghost4xC = 10 ;
const int ghost4yC = 32 ;
bool ghost4moving = true;
int iterationcount = 0 ;
bool powerenergizer;
//.........main function
main()
{
    bool game = true;
    system("cls");
    loadmazefromfile();
    printmaze();
    gotoxy(pacmanY , pacmanX);
    cout<<'P';
    while(game)
    {
        Sleep(300);
        scoredisplay();
        livesdisplay();
        livescount();
        ghost1();
        ghost2();
        ghost3();
        ghost4();
        gameover();
        if(gameover())
        {
            game = false;
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveleft(); 
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveright(); 
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveup(); 
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movedown(); 
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            game = false; // Stop the game
        }
        if(maze[pacmanX][pacmanY] == '*')
        {
            powerenergizer = true;
            maze[pacmanX][pacmanY] = ' ';
            iterationcount = 0 ;
        }
        if(powerenergizer == true)
        {
            bool powerON = powerEnergizer();
            iterationcount ++ ;
            if(!powerON)
            {
                powerenergizer = false;
            }
        }
        else
        {
            livescount();
        }   
    }
}    
//.........functions
void printmaze()
{
    for(int r = 0 ; r < 24 ; r ++)
    {
        for(int c = 0 ; c < 71 ; c ++)
        {
            gotoxy(c,r);
            cout<<maze[r][c];
        }
        cout<<endl;
    }
}
void moveleft()
{
    if(maze[pacmanX][pacmanY -1 ] != '|' && maze[pacmanX][pacmanY-1] != '#' && maze[pacmanX][pacmanY-1] != '%')
    {
        gotoxy(pacmanY, pacmanX);
        cout<< ' ';
        pacmanY = pacmanY - 1;
        gotoxy(pacmanY, pacmanX);
        cout<< 'P';
        scorecount(pacmanX , pacmanY);
    }
}
void moveright()
{
    if(maze[pacmanX][pacmanY + 1] != '|' && maze[pacmanX][pacmanY + 1] != '#' && maze[pacmanX][pacmanY + 1] != '%')
    {
        gotoxy(pacmanY, pacmanX);
        cout<< ' ';
        pacmanY = pacmanY + 1;
        gotoxy(pacmanY, pacmanX);
        cout<< 'P';
        scorecount(pacmanX , pacmanY);
    }
}
void moveup()
{
    if(maze[pacmanX - 1][pacmanY] != '|' && maze[pacmanX - 1][pacmanY] != '#' && maze[pacmanX - 1][pacmanY] != '%')
    {
        gotoxy(pacmanY, pacmanX);
        cout<< ' ';
        pacmanX = pacmanX - 1;
        gotoxy(pacmanY, pacmanX);
        cout<< 'P';
        scorecount(pacmanX , pacmanY);
    }
}
void movedown()
{
    if(maze[pacmanX + 1][pacmanY] != '|' && maze[pacmanX + 1][pacmanY] != '#' && maze[pacmanX + 1][pacmanY] != '%')
    {
        gotoxy(pacmanY, pacmanX);
        cout<< ' ';
        pacmanX = pacmanX + 1;
        gotoxy(pacmanY, pacmanX);
        cout<< 'P';
        scorecount(pacmanX , pacmanY);
    }
}
void ghost1()
{
    if(maze[ghost1x][ghost1y + 1] == '|' || maze[ghost1x][ghost1y + 1] == '%' || maze[ghost1x][ghost1y + 1] == '#' )
    {
        ghost1moving = !ghost1moving;
    }
    else if(maze[ghost1x][ghost1y - 1] == '|' || maze[ghost1x][ghost1y - 1] == '%' || maze[ghost1x][ghost1y - 1] == '#' )
    {
        ghost1moving = !ghost1moving;
    }
    if(ghost1moving)
    {
        if(maze[ghost1x][ghost1y + 1] != '|' && maze[ghost1x][ghost1y + 1] != '%' && maze[ghost1x][ghost1y + 1] != '#' )
        {
            gotoxy(ghost1y , ghost1x);
            if(maze[ghost1x][ghost1y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost1y = ghost1y + 1;
            gotoxy(ghost1y , ghost1x);
            cout<< 'G';
        }
    }
    else
    {
        if(maze[ghost1x][ghost1y - 1] != '|' && maze[ghost1x][ghost1y - 1] != '%' && maze[ghost1x][ghost1y - 1] != '#' )
        {
            gotoxy(ghost1y , ghost1x);
            if(maze[ghost1x][ghost1y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost1y = ghost1y - 1;
            gotoxy(ghost1y , ghost1x);
            cout<< 'G';
        }
    }
}
void ghost2()
{
    if(maze[ghost2x - 1][ghost2y] == '|' || maze[ghost2x - 1][ghost2y ] == '%' || maze[ghost2x - 1][ghost2y ] == '#' )
    {
        ghost2moving = !ghost2moving;
    }
    else if(maze[ghost2x + 1][ghost2y] == '|' || maze[ghost2x + 1][ghost2y] == '%' || maze[ghost2x + 1][ghost2y ] == '#' )
    {
        ghost2moving = !ghost2moving;
    }
    if(ghost2moving)
    {
        if(maze[ghost2x - 1][ghost2y] != '|' && maze[ghost2x - 1][ghost2y] != '%' && maze[ghost2x - 1][ghost2y] != '#' )
        {
            gotoxy(ghost2y , ghost2x);
            if(maze[ghost2x][ghost2y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost2x = ghost2x - 1;
            gotoxy(ghost2y , ghost2x);
            cout<< 'G';
        }
    }
    else
    {
        if(maze[ghost2x + 1][ghost2y] != '|' && maze[ghost2x + 1][ghost2y] != '%' && maze[ghost2x + 1][ghost2y] != '#' )
        {
            gotoxy(ghost2y , ghost2x);
            if(maze[ghost2x][ghost2y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost2x = ghost2x + 1;
            gotoxy(ghost2y , ghost2x);
            cout<< 'G';
        }
    }
}
void ghost3()
{   
    if(alternatemovement)
    {
        if(maze[ghost3x][ghost3y + 1] == '|' || maze[ghost3x][ghost3y + 1] == '%' || maze[ghost3x][ghost3y + 1] == '#' )
        {
            ghost3movingHorizontally = !ghost3movingHorizontally;
        }
        else if(maze[ghost3x][ghost3y - 1] == '|' || maze[ghost3x][ghost3y - 1] == '%' || maze[ghost3x][ghost3y - 1] == '#' )
        {
            ghost3movingHorizontally = !ghost3movingHorizontally;
        }
        if(ghost3movingHorizontally)
        {
            if(maze[ghost3x][ghost3y + 1] != '|' && maze[ghost3x][ghost3y + 1] != '%' && maze[ghost3x][ghost3y + 1] != '#' )
            {
                gotoxy(ghost3y , ghost3x);
                if(maze[ghost3x][ghost3y] == '.')
                {
                    cout<<'.';
                }
                else
                {
                    cout<<' ';
                }
                ghost3y = ghost3y + 1;
                gotoxy(ghost3y , ghost3x);
                cout<< 'G';
            }
        }
        else
        {
            if(maze[ghost3x][ghost3y - 1] != '|' && maze[ghost3x][ghost3y - 1] != '%' && maze[ghost3x][ghost3y - 1] != '#' )
            {
                gotoxy(ghost3y , ghost3x);
                if(maze[ghost3x][ghost3y] == '.')
                {
                    cout<<'.';
                }
                else
                {
                    cout<<' ';
                }
                ghost3y = ghost3y - 1;
                gotoxy(ghost3y , ghost3x);
                cout<< 'G';
            }
        }
    }

    else
    {
        if(maze[ghost3x - 1][ghost3y] == '|' || maze[ghost3x - 1][ghost3y ] == '%' || maze[ghost3x - 1][ghost3y ] == '#' )
        {
            ghost3movingVertically = !ghost3movingVertically;
        }
        else if(maze[ghost3x + 1][ghost3y] == '|' || maze[ghost3x + 1][ghost3y] == '%' || maze[ghost3x + 1][ghost3y ] == '#' )
        {
            ghost3movingVertically = !ghost3movingVertically;
        }
        if(ghost3movingVertically)
        {
            if(maze[ghost3x - 1][ghost3y] != '|' && maze[ghost3x - 1][ghost3y] != '%' && maze[ghost3x - 1][ghost3y] != '#' )
            {
                gotoxy(ghost3y , ghost3x);
                if(maze[ghost3x][ghost3y] == '.')
                {
                    cout<<'.';
                }
                else
                {
                    cout<<' ';
                }
                ghost3x = ghost3x - 1;
                gotoxy(ghost3y , ghost3x);
                cout<< 'G';
            }
        }
        else
        {
            if(maze[ghost3x + 1][ghost3y] != '|' && maze[ghost3x + 1][ghost3y] != '%' && maze[ghost3x + 1][ghost3y] != '#' )
            {
                gotoxy(ghost3y , ghost3x);
                if(maze[ghost3x][ghost3y] == '.')
                {
                    cout<<'.';
                }
                else
                {
                    cout<<' ';
                }
                ghost3x = ghost3x + 1;
                gotoxy(ghost3y , ghost3x);
                cout<< 'G';
            }
        }
    } 
    
    alternatemovement = !alternatemovement;
}
void ghost4()
{
    if(ghost4moving)
    {
        if(pacmanX < ghost4x)
        {
            //ghost move up
            gotoxy(ghost4y,ghost4x);
            if(maze[ghost4x][ghost4y] == '|')
            {
                cout<<'|';
            }
            else if(maze[ghost4x][ghost4y] == '#')
            {
                cout<<'#';
            }
            else if(maze[ghost4x][ghost4y] == '%')
            {
                cout<<'%';
            }
            else if(maze[ghost4x][ghost4y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost4x = ghost4x - 1;
            gotoxy(ghost4y, ghost4x);
            cout<<'G';
        }
        else if(pacmanX > ghost4x)
        {
            //ghost move down
            gotoxy(ghost4y,ghost4x);
            if(maze[ghost4x][ghost4y] == '|')
            {
                cout<<'|';
            }
            else if(maze[ghost4x][ghost4y] == '#')
            {
                cout<<'#';
            }
            else if(maze[ghost4x][ghost4y] == '%')
            {
                cout<<'%';
            }
            else if(maze[ghost4x][ghost4y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost4x = ghost4x + 1;
            gotoxy(ghost4y, ghost4x);
            cout<< 'G';
        }
        if(pacmanY < ghost4y)
        {
            //ghost move left
            gotoxy(ghost4y,ghost4x);
            if(maze[ghost4x][ghost4y] == '|')
            {
                cout<<'|';
            }
            else if(maze[ghost4x][ghost4y] == '#')
            {
                cout<<'#';
            }
            else if(maze[ghost4x][ghost4y] == '%')
            {
                cout<<'%';
            }
            else if(maze[ghost4x][ghost4y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost4y = ghost4y - 1;
            gotoxy(ghost4y, ghost4x);
            cout<< 'G';
        }
        else if(pacmanY > ghost4y)
        {
            //ghost move right
            gotoxy(ghost4y,ghost4x);
            if(maze[ghost4x][ghost4y] == '|')
            {
                cout<<'|';
            }
            else if(maze[ghost4x][ghost4y] == '#')
            {
                cout<<'#';
            }
            else if(maze[ghost4x][ghost4y] == '%')
            {
                cout<<'%';
            }
            else if(maze[ghost4x][ghost4y] == '.')
            {
                cout<<'.';
            }
            else
            {
                cout<<' ';
            }
            ghost4y = ghost4y + 1;
            gotoxy(ghost4y, ghost4x);
            cout<< 'G';
        }
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void scoredisplay()
{
    gotoxy(80 , 10);
    cout<<"Score : "<<score;
}
void scorecount(int x , int y)
{
    if(maze[x][y] == '.')
    {
        score ++ ;
        maze[x][y] = ' ';
    }
}
void livesdisplay()
{
    gotoxy(80 , 15);
    cout<<"Lives : "<<lives;
}
void livescount() 
{
    if((pacmanX == ghost1x && pacmanY == ghost1y) || (pacmanX == ghost2x && pacmanY == ghost2y) || (pacmanX == ghost3x && pacmanY == ghost3y)|| (pacmanX == ghost4x && pacmanY == ghost4y))
    {
        lives = lives - 1;

        positionreset();
    }
}
void positionreset()
{
    if(maze[pacmanX][pacmanY] != 'G')
    {
        gotoxy(pacmanY , pacmanX);
        cout<<' ';
        maze[pacmanX][pacmanY] = ' ';
    }
    pacmanX = 10 ;
    pacmanY = 34 ;
    gotoxy(pacmanY , pacmanX);
    cout<<'P';
    maze[pacmanX][pacmanY] = 'P';
}
bool gameover()
{
    if(lives <= 0)
    {
        system("cls");
        gotoxy(20 , 5);
        cout<<"Game Over!";
        gotoxy(20 , 8);
        cout<<"Total score : "<<score;

        return true;
    }
    return false;
}
void loadmazefromfile()
{
    string line;
    fstream read;
    read.open("maze.txt",ios::in);
    for(int i = 0 ; i < 24 ; i ++)
    {
        getline(read , line);
        for(int j = 0 ; j < 71 ; j ++)
        {
            maze[i][j] = line[j];
        }
    }
    read.close();
}
bool powerEnergizer()
{
    if(pacmanX == ghost1x && pacmanY == ghost1y)
    {
        gotoxy(ghost1y , ghost1x);
        cout<<" ";
        ghost1x = ghost1xC ;
        ghost1y = ghost1yC ;
        gotoxy(ghost1y , ghost1x);
        cout<<"G";
    }
    if(pacmanX == ghost2x && pacmanY == ghost2y)
    {
        gotoxy(ghost2y , ghost2x);
        cout<<" ";
        ghost2x = ghost2xC ;
        ghost2y = ghost2yC ;
        gotoxy(ghost2y , ghost2x);
        cout<<"G";
    }
    if(pacmanX == ghost3x && pacmanY == ghost3y)
    {
        gotoxy(ghost3y , ghost3x);
        cout<<" ";
        ghost3x = ghost3xC ;
        ghost3y = ghost3yC ;
        gotoxy(ghost3y , ghost3x);
        cout<<"G";
    }
    if(pacmanX == ghost4x && pacmanY == ghost4y)
    {
        gotoxy(ghost4y , ghost4x);
        cout<<" ";
        ghost4x = ghost4xC ;
        ghost4y = ghost4yC ;
        gotoxy(ghost4y , ghost4x);
        cout<<"G";
    }
    if(iterationcount == 30 )
    {
        return false ;
    }
    return true;
}