#pragma once
#include "EasyGraphics.h"

using namespace std;

class myPuzzle :
	public EasyGraphics
{
public:
	myPuzzle();
	~myPuzzle();


	virtual void onDraw();


	string shuffle[4][4] = { {"aa", "ab","ac", "ad"},
							 {"ba", "bb","bc", "bd"}, 
							 {"ca", "cb","cc", "cd"}, 
							 {"da", "db","dc", "XX"}};

	string sol[4][4] = { {"aa", "ab","ac", "ad"},
							 {"ba", "bb","bc", "bd"},
							 {"ca", "cb","cc", "cd"},
							 {"da", "db","dc", "XX"} };

	enum direction {none, up, down, left, right};

	direction direct = none;

	virtual void drawFrame();
	virtual void drawGrid();
	virtual void shuffleButton();
	virtual void solButton();
	virtual void startButton();
	virtual void drawTimer();
	virtual void drawMoveCounter();

	void onTimer(UINT nIDEvent);
	string timeStamp;
	UINT timeTick;
	UINT timer_id = 1;
	void start();

	void onLButtonDown(UINT nFlags, const int x, const int y);
	void shuffleGrid();
	void solGrid();

	virtual void whichGrid();
	string coX, coY, space;
	int posX, posY;
	bool empty = false;
	bool play = false;
	int startTime, move, moveCounter;
	const double anim_time = 20.0;

	void swapUp(int posX, int posY);
	void swapDown(int posX, int posY);
	void swapLeft(int posX, int posY);
	void swapRight(int posX, int posY);

	bool solved();
	bool solve;


};

