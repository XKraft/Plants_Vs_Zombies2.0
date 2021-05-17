#pragma once
#include"Global.h"
using namespace std;
enum PlantAction
{
	_SHOOT,
	_SHOOT_SNOW,
	_BOMP,
	_BOUCE,
	_NONE,
};
class Plants
{
public:
	Plants();
	string GetPlantName();//返回植物的名字
	int& GetPlantHP();
	bool GetStepOver() { return step_over; }
	bool GetInvincibility() { return invincibility; }
	bool BeAttack(int atk);//植物被篮球击中
	virtual bool BeAte() { return false; }//植物被吃
	virtual void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight) { pa = _NONE; }
protected:
	string _name;//植物名字
	int _hp;//植物血量
	int _X;
	int _Y;//植物在map中的位置坐标
	bool step_over;//植物是否可以被撑杆僵尸翻越
	bool invincibility;//是否处于无敌状态，比如窝瓜跳起后
};

class Sunflower :public Plants
{
public:
	Sunflower();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//重写此函数实现增加阳光
private:
	int _function_cd;
	clock_t _function_count;//用于对是否执行Funtion函数计时
};
class PeaShooter : public Plants
{
public:
	PeaShooter();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//重写此函数实现发射豌豆
private:
	int _function_cd;
	clock_t _function_count;//用于对是否执行Funtion函数计时
};

class RepeatPeaShooter :public Plants
{
public:
	RepeatPeaShooter();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//重写此函数实现发射豌豆
private:
	int _function_cd;
	int _function_cd1;
	int _function_cd2;
	clock_t _function_count;//用于对是否执行Funtion函数计时
};

class SnowPeaShooter :public Plants
{
public:
	SnowPeaShooter();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//重写此函数实现发射冷冻豌豆
private:
	int _function_cd;
	clock_t _function_count;//用于对是否执行Funtion函数计时
};

class WallNut : public Plants
{
public:
	WallNut();
};

class TallNut : public Plants
{
public:
	TallNut();
};

class Squash :public Plants
{
public:
	Squash();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//重写此函数实现压瘪僵尸
private:
	int _atk;
	int _function_cd;
	clock_t _function_count;
	bool Bounce;//是否进行压瘪僵尸
};

class CherryBomb :public Plants
{
public:
	CherryBomb();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//重写此函数实现自爆
private:
	int _atk;
	int _function_cd;
	clock_t _function_count;
	bool Bomb;
};

class Garlic :public Plants
{
public:
	Garlic();
	bool BeAte() { return true; }//重写此函数打开僵尸换路开关
};

class Pumpkin :public Plants
{
public:
	Pumpkin();
};