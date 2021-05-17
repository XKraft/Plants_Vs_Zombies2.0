#include"Map.h"
Map::Map()
{
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			map[i][j].SetGridXY((GRID_WIDTH - 1) * j, (GRID_HEIGHT - 1) * i);
	for (int i = 0; i < STAGE_LINES; ++i)
	{
		_exist_zombie_lines[i] = false;
		_last_plant[i] = -1;
	}

	_cursor_x = 0;
	_cursor_y = 0;
	display_cursor = false;
}
void Map::Draw()
{
	//绘制网格
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			DrawGridEdge((GRID_WIDTH - 1) * j, (GRID_HEIGHT - 1) * i);
	//绘制格子内信息和光标
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			bool cursor = false;
			if (_cursor_x == j && _cursor_y == i)
				cursor = true;
			map[i][j].Draw(cursor && display_cursor);
		}
	//绘制子弹
	for (int i = 0; i < STAGE_LINES; ++i)
	{
		for (unsigned int j = 0; j < bullets[i].size(); ++j)
			bullets[i][j]->Draw();
		for (unsigned int j = 0; j < basketball[i].size(); ++j)
			basketball[i][j]->Draw();
	}
}
void Map::MoveCursor(int dx, int dy)
{
	if (_cursor_y + dy < 0 || _cursor_y + dy >= STAGE_LINES)
		dy = 0;
	if (_cursor_x + dx < 0 || _cursor_x + dx >= STAGE_COLS)
		dx = 0;
	_cursor_x += dx;
	_cursor_y += dy;
}
bool Map::GrowPlant(Plants* &plant, int ID)
{
	if (map[_cursor_y][_cursor_x].GrowPlant(plant, ID))
		return true;
	else
		return false;
}
void Map::ChangeDisplayCursor(bool cursor)
{
	display_cursor = cursor;
}
void Map::AddZombie(clock_t &time)
{
	static clock_t c = clock();
	time = clock() / CLOCKS_PER_SEC;
	int rand_y = (rand() + rand())% 5;

	/*static bool flag = true;
	if (flag)
	{
		map[rand_y][6].AddZombie(6);
		flag = false;
	}*/

	if (time < 50)
		return;
	else if (time < 90)
	{
		if(SandGlass(c, 100))
			map[rand_y][6].AddZombie(1);
	}
	else if (time < 150)
	{
		if(SandGlass(c, 100))
			map[rand_y][6].AddZombie(2);
	}
	else if (time < 180)
	{
		if (SandGlass(c, 100))
			map[rand_y][6].AddZombie(3);
	}
	else if (time < 210)
	{
		if (SandGlass(c, 100))
			map[rand_y][6].AddZombie(4);
	}
	else if (time < 240)
	{
		if (SandGlass(c, 100))
			map[rand_y][6].AddZombie(5);
	}
	else if (time < 270)
	{
		if (SandGlass(c, 100))
			map[rand_y][6].AddZombie(6);
	}
	else if(time < 300)
	{
		if (SandGlass(c, 100))
			map[rand_y][6].AddZombie(rand() % 6 + 1);
	}
	else
	{
		if (SandGlass(c, 100))
		{
			map[rand_y][6].AddZombie(rand() % 6 + 1);
			map[rand_y][6].AddZombie(rand() % 6 + 1);
		}
	}
}
void Map::Move()
{
	//僵尸移动
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 1; j < STAGE_COLS; ++j)
			map[i][j].MoveZombie(map, j, i);
	//子弹移动
	for (int i = 0; i < STAGE_LINES; ++i)
	{
		for (unsigned int j = 0; j < bullets[i].size(); )
			if (bullets[i][j]->Move())
			{
				delete bullets[i][j];
				bullets[i].erase(bullets[i].begin() + j);
			}
			else
				++j;
		for (unsigned int j = 0; j < basketball[i].size(); )
			if (basketball[i][j]->Move())
			{
				delete basketball[i][j];
				basketball[i].erase(basketball[i].begin() + j);
			}
			else
				++j;
	}
}
void Map::Update()
{
	//更新_exist_zombie_lines
	for (int i = 0; i < STAGE_LINES; ++i)
	{
		_exist_zombie_lines[i] = false;
		for (int j = 0; j < STAGE_COLS; ++j)
			if (map[i][j].ExistZombie())
			{
				_exist_zombie_lines[i] = true;
				break;
			}
	}
	//更新_last_plant
	for (int i = 0; i < STAGE_LINES; ++i)
	{
		_last_plant[i] = -1;
		for (int j = 0; j < STAGE_COLS; ++j)
			if (map[i][j].GrtGridState() != BLANK)
			{
				_last_plant[i] = j;
				break;
			}
	}
	//清除生命值归零的植物和僵尸
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			map[i][j].ClearDead(2);

}
bool Map::GameOver()
{
	for (int i = 0; i < 5; ++i)
		if (map[i][0].MoveZombie(map, 0, i))
			return true;
	return false;
}
void Map::Attack(int& score)
{
	//僵尸攻击植物
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			map[i][j].ZombieEatPlant();
	//植物攻击僵尸
	for (int i = 0; i < STAGE_LINES; ++i)
		for (unsigned int j = 0; j < bullets[i].size(); )
			if (map[i][bullets[i][j]->GetBullex()].BulletAttack(bullets[i][j], ZOMBIES, score))
			{
				delete bullets[i][j];
				bullets[i].erase(bullets[i].begin() + j);
			}
			else
				++j;
	//篮球击中植物
	for (int i = 0; i < STAGE_LINES; ++i)
		for (unsigned int j = 0; j < basketball[i].size(); )
			if (map[i][basketball[i][j]->GetBullex()].BulletAttack(basketball[i][j], PLANTS, score))
			{
				delete basketball[i][j];
				basketball[i].erase(basketball[i].begin() + j);
			}
			else
				++j;
}
void Map::Function(int &sunlight, int& score)
{
	//僵尸执行特定功能
	ZombieAction za = NONE;
	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
		{
			map[i][j].ZombieFunction(map, j, i, _last_plant[i], basketball[i]);
		}
	//植物执行特点功能

	for (int i = 0; i < STAGE_LINES; ++i)
		for (int j = 0; j < STAGE_COLS; ++j)
			map[i][j].PlantFunction(map, j, i, _exist_zombie_lines[i], sunlight, bullets[i], score);
}