#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
bool gameOver;
int speed;
char move;
const int height=400;
const int width=400;
int x,fruitx;
int y,fruity;
int tailx[100], taily[100];
int nTail=0;
int big=1;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
char score[16]="Score is : 0000";

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % height-5;
    fruity = rand() % height-5;
}
void Draw()
{
	cleardevice();
	line (0,0,width,0);
	line (0,0,0,height);
	line (width,0,width,height);
	line (0,height,width,height);
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i==x&&j==y)
			{
				circle(x,y,5);
			}
			else if (i == fruity && j == fruitx)
            {
            	if(big%5==0)
            	{
            		circle(fruitx,fruity,5);
            		
				}
				else
				{
					circle(fruitx,fruity,3);
				}
			}
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        circle(tailx[k],taily[k],3);
                        print = true;
                    }
                    if(x==tailx[k]&&y==taily[k])
                    {
                    	gameOver=true;
					}
                }

			}
			
		}
	}
	outtextxy(410,20,score);
}
void Input()
{
	char prev_move;
	
    if (kbhit())
    {
    	move=getch();
        switch (move)
        {
        case 75:
			dir = LEFT;
			break;
        case 77:
            dir = RIGHT;
            break;
        case 72	:
            dir = UP;
            break;
        case 80:
            dir = DOWN;
			break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

int Logic()
{
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x-=5;
        
        break;
    case RIGHT:
        x+=5;
        break;
    case UP:
        y-=5;
        break;
    case DOWN:
        y+=5;
        break;
	default:
        break;
    }
    if (x >= width)
	{
		x = 0;
	} 
	else if (x < 0)
	{
		x = width - 1;
	}
    if (y >= height) 
	{
		y = 0;
	} 
	else if (y < 0) 
	{
		y = height - 1;
	}
 
    for (int i = 0; i < nTail; i++)
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
 
    if (((x >= fruitx-6)&&(x <= fruitx+6)) && ((y >= fruity-6)&&(y <= fruity+6)))
    {
        if(score[13]=='9')
        {
        	if(score[12]=='9')
        	{
        		score[11]++;
        		score[12]='0';
        		score[13]='0';
			}
			else
			{
				score[12]++;
				score[13]='0';
			}
		}
		else
		{
			score[13]++;
		}
		if(big%5==0)
		{
			if(score[12]=='9')
        	{
        		if(score[11]=='9')
        		{
        			score[10]++;
        			score[11]='0';
        			score[12]='0';
				}
				else
				{
					score[11]++;
					score[12]='0';
				}
			}
			else
			{
				score[12]++;
			}	
		}
        fruitx = rand() % width-8;
        fruity = rand() % height-8;
        nTail++;
        big++;
        
    }
}


int main()
{
	speed=45;
	
	initwindow(7700,700);
	Setup();
	while(gameOver!=true)
	{

		Draw();
        Input();
        Logic();
        Sleep(speed);
		
	}
	Sleep(1000);
	cleardevice();
	circle(200,200,60);
	circle(175,175,5);
	circle(225,175,5);
	arc(200, 235, 0, 180, 20);
	outtextxy(300,250,"Game Over....!");
	system("pause");
    return 0;
}
