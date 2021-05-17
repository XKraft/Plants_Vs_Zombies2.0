#pragma once
#include"Global.h"
#include"Plants.h"
#include"Zombies.h"
#include"Bullets.h"
using namespace std;
enum GridState
{
	BLANK,
	PUMPKIN,
	PLANT,
	PLANT_PUMPKIN,
};
enum Target
{
	ZOMBIES,
	PLANTS,
};
enum ZombieAction;
enum PlantAction;
class Grid
{
public:
	Grid();
	GridState GrtGridState() { return _state; }
	void SetGridXY(int x, int y);//设置grid左上角的坐标
	void Draw(bool display_cursor);//绘制grid中的内容
	bool GrowPlant(Plants* plant, int ID);//在该格子中种植植物
	void AddZombie(int ID);//在网格中增加编号为ID的僵尸
	bool ExistZombie();//当前格子是否存在僵尸
	bool MoveZombie(Grid map[][7], int x, int y);//移动格子里的僵尸
	void ZombieEatPlant();//格子里的僵尸攻击植物
	void ZombieFunction(Grid map[][7], int x, int y, int lastplant, deque<Bullets*> &basketball);//格子里的僵尸执行特定的功能
	bool BulletAttack(Bullets* b, Target t, int& score);//子弹打中目标
	void ClearDead(int choice);//清楚格子中已经死亡的僵尸
	void PlantFunction(Grid map[][7], int x, int y, bool exsitzombie, int& sunlight, deque<Bullets*>& bullet, int& score);
private:
	vector<Plants*> _plants;//格子中的植物
	deque<Zombies*> _zombies;//格子中的僵尸
	int _X;
	int _Y;//(_X,_Y)代表各种左上角在命令行中的坐标
	GridState _state;//当前格子的状态
};