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
	void SetGridXY(int x, int y);//����grid���Ͻǵ�����
	void Draw(bool display_cursor);//����grid�е�����
	bool GrowPlant(Plants* plant, int ID);//�ڸø�������ֲֲ��
	void AddZombie(int ID);//�����������ӱ��ΪID�Ľ�ʬ
	bool ExistZombie();//��ǰ�����Ƿ���ڽ�ʬ
	bool MoveZombie(Grid map[][7], int x, int y);//�ƶ�������Ľ�ʬ
	void ZombieEatPlant();//������Ľ�ʬ����ֲ��
	void ZombieFunction(Grid map[][7], int x, int y, int lastplant, deque<Bullets*> &basketball);//������Ľ�ʬִ���ض��Ĺ���
	bool BulletAttack(Bullets* b, Target t, int& score);//�ӵ�����Ŀ��
	void ClearDead(int choice);//����������Ѿ������Ľ�ʬ
	void PlantFunction(Grid map[][7], int x, int y, bool exsitzombie, int& sunlight, deque<Bullets*>& bullet, int& score);
private:
	vector<Plants*> _plants;//�����е�ֲ��
	deque<Zombies*> _zombies;//�����еĽ�ʬ
	int _X;
	int _Y;//(_X,_Y)����������Ͻ����������е�����
	GridState _state;//��ǰ���ӵ�״̬
};