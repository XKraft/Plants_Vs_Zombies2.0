#pragma once
#include"Global.h"
using namespace std;
class Bullets
{
public:
	Bullets(int x, int y);
	int GetBullex() { return _x; }//得到子弹在map中的x坐标
	int GetBulletAtk() { return _atk; }
	bool GetFreeze() { return freeze; }
	bool Move();//子弹移动
	virtual void Draw();//绘制子弹
protected:
	int _X;//子弹所在X轴（命令行）
	int _Y;//子弹所在y轴（命令行）
	int _x;//子弹所在x轴（map）
	int _y;//子弹所在y轴（map）
	int _atk;//子弹攻击力
	int _speed;//子弹移动速度
	bool move_direction;//子弹移动方向
	bool freeze;//子弹是否具有减速效果
	clock_t _move_count;//子弹移动计时
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
	int _destination;//目的地坐标
};