#include<Windows.h>
#include "myPuzzle.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int show)
{
	myPuzzle dt;
	dt.create(hInstance, 800, 600, 100, true);
	return 0;
}