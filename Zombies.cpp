#include"Zombies.h"
using namespace std;
Zombies::Zombies()
{
	_name = "普通僵尸";
	_hp = 270;
	_move_speed = 47;
	_atk_speed = 10;
	_atk = 40;
	_score = 50;
	move = true;
	snow = false;
	changeroad = false;
	step_over = false;
	_grid_move = 0;
	_move_count = clock();
	_atk_count = clock();
	_changroad_count = clock();
}
ConheadZombie::ConheadZombie()
{
	_name = "路障僵尸Δ";
	_hp = 270 + 370;
	_conhead = true;
	_score = 60;
}
PoleVaultingZombie::PoleVaultingZombie()
{
	_name = "撑杆僵尸|";
	_hp = 500;
	_move_speed = 25;
	_after_step_move_speed = 45;
	step_over = true;
	_score = 60;
}
NewspaperZombie::NewspaperZombie()
{
	_name = "读报僵尸□";
	_hp = 150 + 270;
	_read_newspaper = true;
	_after_breaknewspaper_move_speed = 18;
	_score = 60;
}
JackInTheBoxZombie::JackInTheBoxZombie()
{
	_name = "小丑僵尸";
	_hp = 500;
	_move_speed = 22;
	_bomb_rate = 0;
	_score = 60;
}
CatapultZombie::CatapultZombie()
{
	_name = "投石车僵尸";
	_hp = 850;
	_move_speed = 25;
	_atk = 10000;//保证能够一击必杀
	move = true;
	_basketball_number = 20;
	_score = 100;
	_shoot_speed = 14;
	_shoot_count = clock();
}
string Zombies::GetZombieName()
{
	return _name;
}
int Zombies::GetZombieHP()
{
	return _hp;
}
double Zombies::GetGridMove()
{
	return _grid_move;
}
bool Zombies::JugdeMove(bool zstepover)
{
	if (snow && SandGlass(_snow_count, 100))
	{
		snow = false;
		_move_speed /= 2;
		_atk_speed /= 3;
	}//减速计时
	if (move && SandGlass(_move_count, _move_speed))
	{
		_grid_move = 0;
		return true;
	}
	else
	{
		_grid_move += 7.0 / _move_speed;
		return false;
	}
}
bool PoleVaultingZombie::JugdeMove(bool zstepover)
{
	if (snow && SandGlass(_snow_count, 100))
	{
		snow = false;
		_move_speed /= 2;
		_atk_speed /= 3;
	}//减速计时
	if (!move && step_over && SandGlass(_move_count, _move_speed))
	{
		step_over = false;
		_name = "撑杆僵尸";
		_move_speed = _after_step_move_speed;
		if (zstepover)
		{
			_grid_move = 0;			
			move = true;
			return true;
		}
		else
		{
			move = false;
			return false;
		}

	}
	if (move && SandGlass(_move_count, _move_speed))
	{
		_grid_move = 0;
		return true;
	}
	_grid_move += 7.0 / _move_speed;
	return false;
}
bool Zombies::Attack(int& hp, bool b)
{
	move = false;
	if (SandGlass(_atk_count, _atk_speed) && !step_over && !changeroad && !b)//撑杆僵尸在可以越过植物的情况下不能吃植物,处于将要换路的僵尸不能吃植物
	{
		hp -= _atk;
		return true;
	}
	return false;
}
void Zombies::ChangeMove(bool m)
{
	move = m;
}

void ConheadZombie::Function(ZombieAction &za, int x, int lastplant)//实现必须打破路障才能使僵尸本体收到伤害的机制
{
	za = NONE;
	if (_hp <= 270 && _hp > 0 && _conhead)
	{
		_name = "路障僵尸";
		_hp = 270;
		_conhead = false;
	}
}
bool Zombies::BeAttack(int atk, bool effect)
{
	_hp -= atk;
	if (_hp <= 0)
		return true;	
	if (effect)
	{
		snow = true;//打开减速
		_move_speed *= 2;
		_atk_speed *= 2;
		_snow_count = clock();
	}
	return false;
}
bool NewspaperZombie::BeAttack(int atk, bool effect)
{
	_hp -= atk;
	if (_hp <= 0)
		return true;
	if (_hp <= 270 && _read_newspaper)
	{
		_hp = 270;
		_read_newspaper = false;
		_move_speed = _after_breaknewspaper_move_speed;
	}
	if (effect && !_read_newspaper)
	{
		snow = true;//打开减速
		_move_speed *= 2;
		_atk_speed *= 3;
		_snow_count = clock();
	}
	return false;
}
void JackInTheBoxZombie::Function(ZombieAction &za, int x, int lastplant)
{
	static clock_t c = clock();
	if (x >= 5)
		_bomb_rate = 0;
	switch (x)
	{
	case 4:
		_bomb_rate = 20; break;
	case 3:
		_bomb_rate = 40; break;
	case 2:
		_bomb_rate = 60; break;
	case 1:
		_bomb_rate = 80; break;
	case 0:
		_bomb_rate = 100; break;
	}
	if (SandGlass(c, 10))
		if (rand() % 100 < _bomb_rate)
		{
			za = BOMB;
			_hp = 0;
			return;
		}
	za = NONE;
}
//bool CatapultZombie::JugdeMove(bool zstepover)
//{
//	if (move && SandGlass(_move_count, _move_speed))
//	{
//		_grid_move = 0;
//		return true;
//	}
//	return false;
//}
void CatapultZombie::Function(ZombieAction& za, int x, int lastplant)
{
	if (x < 5 && _basketball_number > 0 && lastplant != -1)
	{
		if (move)
			_shoot_count = clock();
		move = false;
		if (SandGlass(_shoot_count, _shoot_speed))
		{			
			--_basketball_number;
			za = SHOOT;
			return;
		}
	}
	if(lastplant == -1 || _basketball_number <= 0)
		move = true;
	za = NONE;
}
bool Zombies::ChangeRoad(bool b)
{
	if (b && !changeroad)
	{
		changeroad = true;
		_changroad_count = clock();
		_move_count = clock();
	}
	if (changeroad && SandGlass(_changroad_count, _move_speed / 2))
	{
		changeroad = false;
		return true;
	}
	else
		return false;
}