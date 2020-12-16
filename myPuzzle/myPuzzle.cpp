#include "myPuzzle.h"
#include<vector>
#include <random>
#include <time.h>
using namespace std;

myPuzzle::myPuzzle()
{

	setImmediateDrawMode(false);
	srand((int)time(0));
	timeTick = 0;
	moveCounter = 0;
}


myPuzzle::~myPuzzle()
{
}


void myPuzzle::onDraw()
{
	clearScreen(WHITE);
	setTextColour(BLACK);
	setFont(25, L"Arial");
	drawText("My Puzzle", 300, 50);


	drawFrame();
	drawGrid();
	drawTimer();
	drawMoveCounter();
	shuffleButton();
	startButton();
	solButton();
	whichGrid();

	if (solve)
	{
		killTimer(timer_id);
	}
	EasyGraphics::onDraw();
}

void myPuzzle::drawFrame()
{
	setPenColour(BLACK, 3);
	setBackColour(WHITE);
	drawRectangle(230,150,288, 290, true);

}

void myPuzzle::drawGrid()
{
	string x = "bmp\\aa.bmp";
	wstring wx(x.begin(), x.end());
	
	//drawBitmap(wx.c_str(), 235, 153, 48, 48);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			string pic = "bmp\\" + shuffle[j][i] + ".bmp";
			
			posX = 235 + (i * 70);
			posY= 155 + (j * 70);
			
			wstring wspic(pic.begin(), pic.end());
			drawBitmap(wspic.c_str(), posX, posY, 68, 68);
		}
	}

}

void myPuzzle::shuffleButton()
{
	setPenColour(BLACK, 3);
	setBackColour(GREY);
	setTextColour(BLACK);
	setFont(15, L"Arial");
	
	drawRectangle(210, 490, 100, 50, true);
	drawText("Shuffle", 230, 505);
}

void myPuzzle::solButton()
{
	setPenColour(BLACK, 3);
	setBackColour(GREY);
	setTextColour(BLACK);
	setFont(15, L"Arial");

	drawRectangle(440, 490, 100, 50, true);
	drawText("Solution", 460, 505);
}


void myPuzzle::startButton()
{
	setPenColour(BLACK, 3);
	setBackColour(GREY);
	setTextColour(BLACK);
	setFont(15, L"Arial");

	drawRectangle(325, 490, 100, 50, true);
	drawText("Start", 355, 505);
}

void myPuzzle::onLButtonDown(UINT nFlags, const int x, const int y)
{
	if (x>230 && x<330 && y > 490 && y < 540)
	{
		shuffleGrid();
	}
	else if (x > 325 && x < 425 && y > 490 && y < 540)
	{
		start();
		shuffleGrid();
		moveCounter = 0;
	}
	else if (x > 430 && x < 530 && y > 490 && y < 540)
	{
		solGrid();
	}
	else if (x>235 && x<515 && y>155 && y < 435)
	{
		posX = (x - 235) / 70;
		posY = (y - 155) / 70;

		// in this case x is y, and y is x
		coX = to_string(posX);
		coY = to_string(posY);

		if (posX < 4 && shuffle[posY][posX+1]=="XX" && play==true)
		{
			space = "Adjacent to Space";
			swapRight(posX, posY);
			moveCounter++;
		}
		else if (posX > 0 && shuffle[posY][posX-1] == "XX" && play == true)
		{
			space = "Adjacent to Space";
			swapLeft(posX, posY);
			moveCounter++;
		}
		else if (posY < 4 && shuffle[posY+1][posX] == "XX" && play == true)
		{
			space = "Adjacent to Space";
			swapDown(posX, posY);
			moveCounter++;
			
		}
		else if (posY > 0 && shuffle[posY - 1][posX] == "XX" && play == true)
		{
			space = "Adjacent to Space";
			swapUp(posX, posY);
			moveCounter++;
		}
		else
		{
			space = "";
		}

	}
	solve = solved();
	onDraw();
}

void myPuzzle::shuffleGrid()
{
	vector<string> shufGrid = { "aa", "ab","ac", "ad", "ba", "bb", "bc", "bd","ca", "cb","cc", "cd","da", "db","dc", "XX"};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int randPick = rand()%shufGrid.size();

			shuffle[i][j] = shufGrid[randPick];
			shufGrid.erase(shufGrid.begin()+ randPick);
		}
	}

}


void myPuzzle::solGrid()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
	
			shuffle[i][j] = sol[i][j];
			
		}
	}
}

void myPuzzle::whichGrid()
{
	setTextColour(BLACK);
	setFont(15, L"Arial");
	drawText("Grid Coordinate", 600, 200);
	
	string xandy = coY + coX;
	wstring wxandy(xandy.begin(), xandy.end());
	drawText(wxandy.c_str(), 600, 230);
	drawText(space.c_str(), 600, 250);

	
}

void myPuzzle::drawTimer()
{
	setTextColour(BLACK);
	setFont(15, L"Arial");
	timeStamp = to_string(timeTick / 100.0);
	drawText("Timer : ", 600, 95);
	drawText(timeStamp.c_str(), 600, 115);
}

void myPuzzle::drawMoveCounter()
{
	setTextColour(BLACK);
	setFont(15, L"Arial");
	string counter = to_string(moveCounter);
	drawText("Moves : ", 600, 135);
	drawText(counter.c_str(), 680, 135);
}


void myPuzzle::onTimer(UINT nIDEvent)
{
	if (nIDEvent == timer_id)
	{
		timeTick++;
		onDraw();
	}
}

void myPuzzle::start()
{
	timeTick = 0;
	setTimer(timer_id, 10);
	play = true;
}

void myPuzzle::swapUp(const int posX, const int posY)
{
	shuffle[posY - 1][posX] = shuffle[posY][posX];
	shuffle[posY][posX] = "XX";
	/*const int time = 10000;
	const int px = 68;
	int diff = GetTickCount() - startTime;
	diff = diff % time;
	move = px * (diff / anim_time);*/
	direct = up;
}

void myPuzzle::swapDown(const int posX, const int posY)
{
	shuffle[posY + 1][posX] = shuffle[posY][posX];
	shuffle[posY][posX] = "XX";
	const int time = 10000;
	const int px = 68;
	int diff = GetTickCount() - startTime;
	diff = diff % time;
	move = px * diff / time;
	direct = down;
}

void myPuzzle::swapLeft(const int posX, const int posY)
{
	shuffle[posY][posX-1] = shuffle[posY][posX];
	shuffle[posY][posX] = "XX";
	const int time = 10000;
	const int px = 68;
	int diff = GetTickCount() - startTime;
	diff = diff % time;
	move = px * diff / time;
	direct = down;
}

void myPuzzle::swapRight(const int posX, const int posY)
{
	shuffle[posY][posX + 1] = shuffle[posY][posX];
	shuffle[posY][posX] = "XX";
	const int time = 10000;
	const int px = 68;
	int diff = GetTickCount() - startTime;
	diff = diff % time;
	move = px * diff / time;
	direct = down;
}

bool myPuzzle::solved()
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (shuffle[j][i] != sol[j][i])
			{
				return false;
			}
		}
	}

	return true;
}








