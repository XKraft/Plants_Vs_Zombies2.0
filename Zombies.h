#pragma once
#include"Global.h"
using namespace std;
enum ZombieAction
{
	BOMB,
	SHOOT,
	NONE,
};
class Zombies
{
public:
	Zombies();
	virtual void Function(ZombieAction& za, int x, int lastplant) { za = NONE; }
	string GetZombieName();
	int GetZombieHP();
	virtual bool ChangeRoad(bool b);//打开僵尸的换路计时
	int GetZombieScore() { return _score; }
	double GetGridMove();
	bool GetSnow() { return snow; }
	virtual bool JugdeMove(bool zstepover);
	bool Attack(int &hp, bool b);//攻击植物
	void ChangeMove(bool m);//改变僵尸的移动状态
	virtual bool BeAttack(int atk, bool effect);//僵尸被攻击
protected:
	string _name;//僵尸名字
	int _hp;//僵尸血量
	int _move_speed;//僵尸的移动速度
	int _atk_speed;//僵尸的攻击速度
	int _atk;//僵尸的攻击力
	int _score;//击杀僵尸所得分数
	bool move;//僵尸是否可以移动
	bool snow;//僵尸是否处于减速状态
	bool changeroad;//僵尸是否处于换路状态
	bool step_over;//僵尸是否可以越过植物
	double _grid_move;//在格子中的移动距离
	clock_t _move_count;//僵尸的移动计时
	clock_t _atk_count;//僵尸的攻击计时
	clock_t _snow_count;//僵尸的减速计时
	clock_t _changroad_count;//僵尸换路计时
};

class ConheadZombie :public Zombies
{
public:
	ConheadZombie();
	void Function(ZombieAction &za, int x, int lastplant);
private:
	bool _conhead;//是否头上还存在路障
};

class PoleVaultingZombie :public Zombies
{
public:
	PoleVaultingZombie();
	bool JugdeMove(bool zstepover);//重写判断能否移动函数实现跨越第一个植物
private:
	int _after_step_move_speed;
};

class NewspaperZombie :public Zombies
{
public:
	NewspaperZombie();
	bool BeAttack(int atk, bool effect);//重写此函数实现报纸可以抵挡减速效果后报纸烂掉之后的狂暴效果
private:
	bool _read_newspaper;//是否在阅读报纸
	int _after_breaknewspaper_move_speed;//报纸没了后的速度
};

class JackInTheBoxZombie :public Zombies
{
public:
	JackInTheBoxZombie();
	void Function(ZombieAction &za, int x, int lastplant);//小丑僵尸执行自爆的功能
private:
	int _bomb_rate;//自爆概率
};
class CatapultZombie :public Zombies
{
public:
	CatapultZombie();
	bool ChangeRoad(bool b) { return false; }//投石车僵尸不受大蒜影响
	void Function(ZombieAction& za, int x, int lastplant);//投石车僵尸执行投石功能
private:
	int _basketball_number;//剩余篮球个数
	int _shoot_speed;//射速
	clock_t _shoot_count;
};