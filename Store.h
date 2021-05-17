#pragma once
#include"Global.h"
#include"Plants.h"
using namespace std;
struct PlantCard
{
	Plants* _plant;
	int _cost;
	int _CD;
	int _CD_count;
	int ID;
	clock_t c;
};
class Store
{
public:
	Store();
	~Store();
	void Draw();//�����̵�
	void MoveCursor(int dx, int dy);//�ƶ��̵�Ĺ��
	bool BuyPlant(int sunlight, PlantCard& plant);//����ֲ�����ɹ�����true������Ϊfalse
	void CancelBuyPlant(PlantCard& plant);//ȡ������ֲ��
	void SucceedBuy();//�ɹ�����ֲ��
	void Run(int& sunlight, int &score);//�����̵ִ꣬�и���ֲ�ﹺ��CD����������
private:
	PlantCard _plants_in_store[10];//ֲ�￨Ƭ������ֲ���cost��cd
	int _cursor_x;
	int _cursor_y;//�̵��й���λ��
	bool display_cursor;//�Ƿ���Ҫ��ʾ�̵�Ĺ��
};