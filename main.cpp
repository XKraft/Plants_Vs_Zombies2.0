#include"Global.h"
#include"Game.h"
int main()
{
	SetCMDSize(CMD_COLS, CMD_LINES);
	HideCursor();
	srand((unsigned int)(clock() + time(0)));

	Game game;
	game.MainLoop();
	return 0;
}