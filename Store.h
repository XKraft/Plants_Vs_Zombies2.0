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
	void Draw();//绘制商店
	void MoveCursor(int dx, int dy);//移动商店的光标
	bool BuyPlant(int sunlight, PlantCard& plant);//购买植物，购买成功返回true，否则为false
	void CancelBuyPlant(PlantCard& plant);//取消购买植物
	void SucceedBuy();//成功购买植物
	void Run(int& sunlight, int &score);//运行商店，执行更新植物购买CD和增加阳光
private:
	PlantCard _plants_in_store[10];//植物卡片，储存植物的cost，cd
	int _cursor_x;
	int _cursor_y;//商店中光标的位置
	bool display_cursor;//是否需要显示商店的光标
};