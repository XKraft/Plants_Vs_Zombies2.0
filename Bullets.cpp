#include"Bullets.h"
Bullets::Bullets(int x, int y)
{
	_X = x;
	_Y = y;
	_x = (_X - 1) / 13;
	_y = _Y / 5;
	_atk = 20;
	_speed = 1;
	move_direction = true;
	freeze = false;
	_move_count = clock();
}
SnowBullet::SnowBullet(int x, int y):Bullets(x, y)
{
	freeze = true;
}
BasketballBullet::BasketballBullet(int x, int y, int destination) : Bullets(x, y)
{
	move_direction = false;
	_destination = destination;
}
bool Bullets::Move()
{
	if(SandGlass(_move_count, _speed))
		if (move_direction)
		{
			if (_X >= 91)
				return true;
			++_X;
			_x = (_X - 1) / 13;
		}
		else
		{
			if (_X < 0)
				return true;
			--_X;
			_x = (_X - 1) / 13;
		}
	return false;
}
void Bullets::Draw()
{
	CursorSetXY(_X, _Y);
	SetPrintColor(f_green);
	cout << "¡ñ";
	SetPrintColor(reset);
}
void SnowBullet::Draw()
{
	CursorSetXY(_X, _Y);
	SetPrintColor(f_blue);
	cout << "¡ñ";
	SetPrintColor(reset);
}
void BasketballBullet::Draw()
{
	CursorSetXY(_X, _Y);
	SetPrintColor(f_red);
	cout << "¡ñ";
	SetPrintColor(reset);
}