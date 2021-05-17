#include"Game.h"
Game::Game()
{
	_sunlight = 0;
	_score = 0;
	_game_state = BUYING;
	_plant = { NULL, 0, 0, 0, 0, clock() };
	_game_time = clock();
}
void Game::MainLoop()
{
	while (_game_state != GAMEOVER)
	{
		Draw();
		GetKey();
		update();
	}
}
void Game::Draw()
{
	map.Draw();

	CursorSetXY(0, STAGE_HEIGHT);
	cout << "'w''s''a''d'���ƹ���ƶ���'b'����'Enter'ȷ����ֲ��'x'ȡ����ֲ" << endl;
	cout << "############################################################################################" << endl;
	cout << "���⣺" << _sunlight << "    " << "������" << _score << "   " << endl;
	cout << "############################################################################################" << endl;

	store.Draw();
}
void Game::GetKey()
{
	char ch = ' ';
	if (_kbhit())
		ch = _getch();
	if (ch >= 'A' && ch <= 'Z')//Ԥ���û�ʹ�ô�д���룬���д�Сдת������
		ch = ch - ('A' - 'a');
	if (_game_state == BUYING)
		switch (ch)
		{
		case 'w':
			store.MoveCursor(0, -1); break;
		case 's':
			store.MoveCursor(0, 1); break;
		case 'a':
			store.MoveCursor(-1, 0); break;
		case 'd':
			store.MoveCursor(1, 0); break;
		case 'b':
			if (store.BuyPlant(_sunlight, _plant))
			{
				_game_state = SELECT; 
				map.ChangeDisplayCursor(true);
			} break;
		}
	if (_game_state == SELECT)
		switch (ch)
		{
		case 'w':
			map.MoveCursor(0, -1); break;
		case 's':
			map.MoveCursor(0, 1); break;
		case 'a':
			map.MoveCursor(-1, 0); break;
		case 'd':
			map.MoveCursor(1, 0); break;
		case 'x':
			_game_state = BUYING;
			map.ChangeDisplayCursor(false);
			store.CancelBuyPlant(_plant);
			break;
		case 13:
			if (map.GrowPlant(_plant._plant, _plant.ID))
			{
				_sunlight -= _plant._cost;
				_game_state = BUYING;
				map.ChangeDisplayCursor(false);
				store.SucceedBuy();
			}
		}
}
void Game::update()
{
	store.Run(_sunlight, _score);
	map.AddZombie(_game_time);	
	map.Attack(_score);
	map.Move();
	map.Function(_sunlight, _score);
	map.Update();
	Gameover();
}
void Game::Gameover()
{
	if (map.GameOver())
	{
		_game_state = GAMEOVER;
		system("cls");
		SetPrintColor(f_red);
		cout << "��ʬ�Ե�������Դ�������" << endl;
		cout << "������" << _score;
		SetPrintColor(reset);
	}
}