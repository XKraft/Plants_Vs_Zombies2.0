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
	string GetPlantName();//����ֲ�������
	int& GetPlantHP();
	bool GetStepOver() { return step_over; }
	bool GetInvincibility() { return invincibility; }
	bool BeAttack(int atk);//ֲ�ﱻ�������
	virtual bool BeAte() { return false; }//ֲ�ﱻ��
	virtual void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight) { pa = _NONE; }
protected:
	string _name;//ֲ������
	int _hp;//ֲ��Ѫ��
	int _X;
	int _Y;//ֲ����map�е�λ������
	bool step_over;//ֲ���Ƿ���Ա��Ÿ˽�ʬ��Խ
	bool invincibility;//�Ƿ����޵�״̬�������ѹ������
};

class Sunflower :public Plants
{
public:
	Sunflower();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//��д�˺���ʵ����������
private:
	int _function_cd;
	clock_t _function_count;//���ڶ��Ƿ�ִ��Funtion������ʱ
};
class PeaShooter : public Plants
{
public:
	PeaShooter();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//��д�˺���ʵ�ַ����㶹
private:
	int _function_cd;
	clock_t _function_count;//���ڶ��Ƿ�ִ��Funtion������ʱ
};

class RepeatPeaShooter :public Plants
{
public:
	RepeatPeaShooter();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//��д�˺���ʵ�ַ����㶹
private:
	int _function_cd;
	int _function_cd1;
	int _function_cd2;
	clock_t _function_count;//���ڶ��Ƿ�ִ��Funtion������ʱ
};

class SnowPeaShooter :public Plants
{
public:
	SnowPeaShooter();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//��д�˺���ʵ�ַ����䶳�㶹
private:
	int _function_cd;
	clock_t _function_count;//���ڶ��Ƿ�ִ��Funtion������ʱ
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
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//��д�˺���ʵ��ѹ��ʬ
private:
	int _atk;
	int _function_cd;
	clock_t _function_count;
	bool Bounce;//�Ƿ����ѹ��ʬ
};

class CherryBomb :public Plants
{
public:
	CherryBomb();
	void Function(PlantAction& pa, bool existzombie, int zombie_nums, int& sunlight);//��д�˺���ʵ���Ա�
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
	bool BeAte() { return true; }//��д�˺����򿪽�ʬ��·����
};

class Pumpkin :public Plants
{
public:
	Pumpkin();
};