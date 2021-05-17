#include"Plants.h"
using namespace std;
Plants::Plants()
{
	_name = "";
	_hp = 300;
	_X = -1;
	_Y = -1;
	step_over = true;
	invincibility = false;
}
Sunflower::Sunflower()
{
	_name = "向日葵";
	_function_cd = 80;
	_function_count = clock();
}
PeaShooter::PeaShooter()
{
	_name = "豌豆射手";
	_function_cd = 14;
	_function_count = clock();
}
RepeatPeaShooter::RepeatPeaShooter()
{
	_name = "双发射手";
	_function_cd1 = 14;
	_function_cd2 = 5;
	_function_cd = _function_cd1;
	_function_count = clock();
}
SnowPeaShooter::SnowPeaShooter()
{
	_name = "寒冰射手";
	_function_cd = 14;
	_function_count = clock();
}
WallNut::WallNut()
{
	_name = "坚果墙";
	_hp = 4000;
}
TallNut::TallNut()
{
	_name = "高坚果";
	_hp = 8000;
	step_over = false;
}
Squash::Squash()
{
	_name = "窝瓜";
	Bounce = false;
	_atk = 1800;
	_function_cd = 15;
	_function_count = clock();
}
CherryBomb::CherryBomb()
{
	_name = "樱桃炸弹";
	_atk = 1800;
	_function_cd = 40;
	_function_count = clock();
	Bomb = false;
}
Garlic::Garlic()
{
	_name = "大蒜";
	_hp = 400;
}
Pumpkin::Pumpkin()
{
	_name = "南瓜头";
	_hp = 4000;
}
string Plants::GetPlantName()
{
	return _name;
}
int& Plants::GetPlantHP()
{
	return _hp;
}
bool Plants::BeAttack(int atk)
{
	_hp -= atk;
	if (_hp <= 0)
		return true;
	else
		return false;
}
void Sunflower::Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight)
{
	pa = _NONE;
	if (SandGlass(_function_count, _function_cd))
		sunlight += 25;
}
void PeaShooter::Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight)
{
	if (existzombie && SandGlass(_function_count, _function_cd))
		pa = _SHOOT;
}
void RepeatPeaShooter::Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight)
{
	if (existzombie && SandGlass(_function_count, _function_cd))
	{
		pa = _SHOOT;
		if (_function_cd == _function_cd1)
			_function_cd = _function_cd2;
		else
			_function_cd = _function_cd1;
	}
}
void SnowPeaShooter::Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight)
{
	if (existzombie && SandGlass(_function_count, _function_cd))
		pa = _SHOOT_SNOW;
}
void Squash::Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight)
{
	pa = _NONE;
	if (zombie_nums && !Bounce)
	{
		Bounce = true;
		invincibility = true;
		_function_count = clock();
	}
	if (Bounce)
		if (SandGlass(_function_count, _function_cd))
		{
			_hp = 0;
			pa = _BOUCE;
		}
}
void CherryBomb::Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight)
{
	if (!Bomb)
	{
		Bomb = true;
		_function_count = clock();
	}
	if (Bomb && SandGlass(_function_count, _function_cd))
	{
		_hp = 0;
		pa = _BOMP;
	}
}
