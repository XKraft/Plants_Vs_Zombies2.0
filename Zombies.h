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
	virtual bool ChangeRoad(bool b);//�򿪽�ʬ�Ļ�·��ʱ
	int GetZombieScore() { return _score; }
	double GetGridMove();
	bool GetSnow() { return snow; }
	virtual bool JugdeMove(bool zstepover);
	bool Attack(int &hp, bool b);//����ֲ��
	void ChangeMove(bool m);//�ı佩ʬ���ƶ�״̬
	virtual bool BeAttack(int atk, bool effect);//��ʬ������
protected:
	string _name;//��ʬ����
	int _hp;//��ʬѪ��
	int _move_speed;//��ʬ���ƶ��ٶ�
	int _atk_speed;//��ʬ�Ĺ����ٶ�
	int _atk;//��ʬ�Ĺ�����
	int _score;//��ɱ��ʬ���÷���
	bool move;//��ʬ�Ƿ�����ƶ�
	bool snow;//��ʬ�Ƿ��ڼ���״̬
	bool changeroad;//��ʬ�Ƿ��ڻ�·״̬
	bool step_over;//��ʬ�Ƿ����Խ��ֲ��
	double _grid_move;//�ڸ����е��ƶ�����
	clock_t _move_count;//��ʬ���ƶ���ʱ
	clock_t _atk_count;//��ʬ�Ĺ�����ʱ
	clock_t _snow_count;//��ʬ�ļ��ټ�ʱ
	clock_t _changroad_count;//��ʬ��·��ʱ
};

class ConheadZombie :public Zombies
{
public:
	ConheadZombie();
	void Function(ZombieAction &za, int x, int lastplant);
private:
	bool _conhead;//�Ƿ�ͷ�ϻ�����·��
};

class PoleVaultingZombie :public Zombies
{
public:
	PoleVaultingZombie();
	bool JugdeMove(bool zstepover);//��д�ж��ܷ��ƶ�����ʵ�ֿ�Խ��һ��ֲ��
private:
	int _after_step_move_speed;
};

class NewspaperZombie :public Zombies
{
public:
	NewspaperZombie();
	bool BeAttack(int atk, bool effect);//��д�˺���ʵ�ֱ�ֽ���Եֵ�����Ч����ֽ�õ�֮��Ŀ�Ч��
private:
	bool _read_newspaper;//�Ƿ����Ķ���ֽ
	int _after_breaknewspaper_move_speed;//��ֽû�˺���ٶ�
};

class JackInTheBoxZombie :public Zombies
{
public:
	JackInTheBoxZombie();
	void Function(ZombieAction &za, int x, int lastplant);//С��ʬִ���Ա��Ĺ���
private:
	int _bomb_rate;//�Ա�����
};
class CatapultZombie :public Zombies
{
public:
	CatapultZombie();
	bool ChangeRoad(bool b) { return false; }//Ͷʯ����ʬ���ܴ���Ӱ��
	void Function(ZombieAction& za, int x, int lastplant);//Ͷʯ����ʬִ��Ͷʯ����
private:
	int _basketball_number;//ʣ���������
	int _shoot_speed;//����
	clock_t _shoot_count;
};