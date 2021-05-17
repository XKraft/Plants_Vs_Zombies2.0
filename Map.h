#pragma once
#include"Global.h"
#include"Grid.h"
enum ZombieAction;
class Map
{
public:
	Map();
	void Draw();//绘制草坪地图
	void MoveCursor(int dx, int dy);//移动草坪的光标
	bool GrowPlant(Plants* &plant, int ID);//种植植物
	void ChangeDisplayCursor(bool cursor);//改变display_cursor的状态
	void AddZombie(clock_t &time);//在地图中产生僵尸
	void Move();//实现移动，包括僵尸移动和子弹移动
	void Update();//更新地图状态
	bool GameOver();//游戏是否结束
	void Attack(int& score);//实现攻击，包括僵尸吃植物和植物攻击僵尸
	void Function(int& sunlight, int& score);//僵尸和植物进行特定的功能
private:
	Grid map[5][7];
	deque<Bullets*> bullets[5];//存储每行的豌豆子弹
	deque<Bullets*> basketball[5];//储存每行的篮球子弹
	bool _exist_zombie_lines[5];//记录每行是否存在僵尸
	int _last_plant[5];//记录每行最后面的植物所在的x坐标
	int _cursor_x;
	int _cursor_y;//草坪光标的坐标
	bool display_cursor;//是否需要显示草坪光标
};