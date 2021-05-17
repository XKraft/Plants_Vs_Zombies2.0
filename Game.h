#pragma once
#include"Global.h"
#include"Map.h"
#include"Store.h"
enum GameState
{
	BUYING,
	SELECT,
	GAMEOVER,
};//标记游戏状态，分别是在购买中、在选择地块中、游戏结束
class Game
{
public:
	Game();
	void MainLoop();//游戏的主循环
	void Draw();//绘制游戏界面
	void GetKey();//实时获得用户输入并进行相应按键功能的实现
	void update();//更新游戏所以对象的状态，执行相应的功能
	void Gameover();//游戏结束
private:
	Store store;
	Map map;
	int _sunlight;//阳光总数
	int _score;//当前分数
	PlantCard _plant;//用于临时储存购买商店给的植物模板
	GameState _game_state;//当前游戏的状态
	clock_t _game_time;//游戏运行时间
};