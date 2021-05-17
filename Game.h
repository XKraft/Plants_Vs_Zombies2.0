#pragma once
#include"Global.h"
#include"Map.h"
#include"Store.h"
enum GameState
{
	BUYING,
	SELECT,
	GAMEOVER,
};//�����Ϸ״̬���ֱ����ڹ����С���ѡ��ؿ��С���Ϸ����
class Game
{
public:
	Game();
	void MainLoop();//��Ϸ����ѭ��
	void Draw();//������Ϸ����
	void GetKey();//ʵʱ����û����벢������Ӧ�������ܵ�ʵ��
	void update();//������Ϸ���Զ����״̬��ִ����Ӧ�Ĺ���
	void Gameover();//��Ϸ����
private:
	Store store;
	Map map;
	int _sunlight;//��������
	int _score;//��ǰ����
	PlantCard _plant;//������ʱ���湺���̵����ֲ��ģ��
	GameState _game_state;//��ǰ��Ϸ��״̬
	clock_t _game_time;//��Ϸ����ʱ��
};