#pragma once
#include"Global.h"
using namespace std;
class Bullets
{
public:
	Bullets(int x, int y);
	int GetBullex() { return _x; }//�õ��ӵ���map�е�x����
	int GetBulletAtk() { return _atk; }
	bool GetFreeze() { return freeze; }
	bool Move();//�ӵ��ƶ�
	virtual void Draw();//�����ӵ�
protected:
	int _X;//�ӵ�����X�ᣨ�����У�
	int _Y;//�ӵ�����y�ᣨ�����У�
	int _x;//�ӵ�����x�ᣨmap��
	int _y;//�ӵ�����y�ᣨmap��
	int _atk;//�ӵ�������
	int _speed;//�ӵ��ƶ��ٶ�
	bool move_direction;//�ӵ��ƶ�����
	bool freeze;//�ӵ��Ƿ���м���Ч��
	clock_t _move_count;//�ӵ��ƶ���ʱ
};

class SnowBullet :public Bullets
{
public:
	SnowBullet(int x, int y);
	void Draw();
};

class BasketballBullet :public Bullets
{
public:
	BasketballBullet(int x, int y, int destination);
	int GetDestination() { return _destination; }
	void Draw();
private:
	int _destination;//Ŀ�ĵ�����
};