#pragma once
#include"Global.h"
#include"Grid.h"
enum ZombieAction;
class Map
{
public:
	Map();
	void Draw();//���Ʋ�ƺ��ͼ
	void MoveCursor(int dx, int dy);//�ƶ���ƺ�Ĺ��
	bool GrowPlant(Plants* &plant, int ID);//��ֲֲ��
	void ChangeDisplayCursor(bool cursor);//�ı�display_cursor��״̬
	void AddZombie(clock_t &time);//�ڵ�ͼ�в�����ʬ
	void Move();//ʵ���ƶ���������ʬ�ƶ����ӵ��ƶ�
	void Update();//���µ�ͼ״̬
	bool GameOver();//��Ϸ�Ƿ����
	void Attack(int& score);//ʵ�ֹ�����������ʬ��ֲ���ֲ�﹥����ʬ
	void Function(int& sunlight, int& score);//��ʬ��ֲ������ض��Ĺ���
private:
	Grid map[5][7];
	deque<Bullets*> bullets[5];//�洢ÿ�е��㶹�ӵ�
	deque<Bullets*> basketball[5];//����ÿ�е������ӵ�
	bool _exist_zombie_lines[5];//��¼ÿ���Ƿ���ڽ�ʬ
	int _last_plant[5];//��¼ÿ��������ֲ�����ڵ�x����
	int _cursor_x;
	int _cursor_y;//��ƺ��������
	bool display_cursor;//�Ƿ���Ҫ��ʾ��ƺ���
};