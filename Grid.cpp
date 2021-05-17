#include"Grid.h"
using namespace std;
Grid::Grid()
{
	_X = -1;
	_Y = -1;
	_state = BLANK;
}
void Grid::SetGridXY(int x, int y)
{
	_X = x;
	_Y = y;
}
void Grid::Draw(bool display_cursor)
{
	for (int i = 1; i <= 4; ++i)
	{
		CursorSetXY(_X + 1, _Y + i);
		cout << "            ";
	}
	if (display_cursor)
	{
		SetPrintColor(b_yellow);
		DrawGridEdge(_X, _Y);
		SetPrintColor(reset);
	}
	if (_state == BLANK)
	{

		if (_zombies.size() == 1)
		{
			if (_zombies.front()->GetSnow())
				SetPrintColor(f_blue);
			CursorSetXY(_X + 3, _Y + 2);
			cout << _zombies.front()->GetZombieName();
			CursorSetXY(_X + 3, _Y + 3);
			cout << "HP:" << _zombies.front()->GetZombieHP();
			SetPrintColor(reset);
		}
		if (_zombies.size() > 1 && _zombies.size() <= 3)
		{
			for (int i = 0; i < _zombies.size(); ++i)
			{
				if (_zombies[i]->GetSnow())
					SetPrintColor(f_blue);
				CursorSetXY(_X + 3, _Y + i + 1);
				cout << _zombies[i]->GetZombieName();
				SetPrintColor(reset);
			}
		}
		if (_zombies.size() > 3)
		{
			for (int i = 0; i < 3; ++i)
			{
				if (_zombies[i]->GetSnow())
					SetPrintColor(f_blue);
				CursorSetXY(_X + 3, _Y + i + 1);
				cout << _zombies[i]->GetZombieName();
				SetPrintColor(reset);
			}
			CursorSetXY(_X + 1, _Y + 4);
			cout << "僵尸 ×" << _zombies.size();
		}
	}
	else
	{
		if (_zombies.size())
		{
			if (_state == PLANT_PUMPKIN)
			{
				CursorSetXY(_X + 1, _Y + 1);
				cout << _plants[0]->GetPlantName();
				CursorSetXY(_X + 1, _Y + 2);
				cout << _plants[1]->GetPlantName();
				CursorSetXY(_X + 1, _Y + 3);
				if (_zombies.front()->GetSnow())
					SetPrintColor(f_blue);
				cout << _zombies.front()->GetZombieName();
				SetPrintColor(reset);
				CursorSetXY(_X + 1, _Y + 4);
				cout << "僵尸 ×" << _zombies.size();
			}
			else
			{
				CursorSetXY(_X + 1, _Y + 1);
				cout << "HP:" << _plants[0]->GetPlantHP();
				CursorSetXY(_X + 1, _Y + 2);
				cout << _plants[0]->GetPlantName();
				CursorSetXY(_X + 1, _Y + 3);
				if (_zombies.front()->GetSnow())
					SetPrintColor(f_blue);
				cout << _zombies.front()->GetZombieName();
				SetPrintColor(reset);
				CursorSetXY(_X + 1, _Y + 4);
				cout << "僵尸 ×" << _zombies.size();
			}
		}
		else
		{
			if (_state == PLANT_PUMPKIN)
			{
				CursorSetXY(_X + 1, _Y + 1);
				cout << "HP:" << _plants[0]->GetPlantHP();
				CursorSetXY(_X + 1, _Y + 2);
				cout << _plants[0]->GetPlantName();
				CursorSetXY(_X + 1, _Y + 3);
				cout << _plants[1]->GetPlantName();
				CursorSetXY(_X + 1, _Y + 4);
				cout << "HP:" << _plants[1]->GetPlantHP();
			}
			else
			{
				CursorSetXY(_X + 1, _Y + 2);
				cout << _plants[0]->GetPlantName();
				CursorSetXY(_X + 1, _Y + 3);
				cout << "HP:" << _plants[0]->GetPlantHP();
			}
		}
	}
}
bool Grid::GrowPlant(Plants* plant, int ID)
{
	if (_state == BLANK)
	{
		_plants.push_back(plant);
		if (ID != 10)
			_state = PLANT;
		else
			_state = PUMPKIN;
		return true;
	}
	if (_state == PLANT_PUMPKIN)
		return false;
	if (_state == PLANT)
	{
		if (ID == 10)
		{
			_plants.push_back(plant);
			_state = PLANT_PUMPKIN;
			return true;
		}
		else
			return false;
	}
	if (_state == PUMPKIN)
	{
		if (ID != 10)
		{
			_plants.insert(_plants.begin(), plant);
			_state = PLANT_PUMPKIN;
			return true;
		}
		else
			return false;
	}
}
void Grid::AddZombie(int ID)
{
	Zombies* zombie = NULL;
	switch (ID)
	{
	case 1:
		zombie = new Zombies; break;
	case 2:
		zombie = new ConheadZombie; break;
	case 3:
		zombie = new PoleVaultingZombie; break;
	case 4:
		zombie = new NewspaperZombie; break;
	case 5:
		zombie = new JackInTheBoxZombie; break;
	case 6:
		zombie = new CatapultZombie; break;
	}
	_zombies.push_back(zombie);
}
bool Grid::ExistZombie()
{
	if (_zombies.size() != 0)
		return true;
	else
		return false;
}
bool Grid::MoveZombie(Grid map[][7], int x, int y)
{
	bool zstepover = true;
	if (_plants.size() == 0)
		zstepover = true;
	else
		zstepover = _plants[0]->GetStepOver();
	for (unsigned int i = 0; i < _zombies.size(); )
	{
		if (_zombies[i]->ChangeRoad(false))
		{
			int dy = 0;
			if (y == 0 ) 
				dy = 1;
			else if (y == 4 ) 
				dy = -1;
			else
			{
				int i = rand() % 2;
				if (i == 0)
					dy = 1;
				else
					dy = -1;
			}
					_zombies[i]->ChangeMove(true);
			map[y + dy][x]._zombies.push_back(_zombies[i]);
			_zombies.erase(_zombies.begin() + i);
		}
		else if ((_zombies[i])->JugdeMove(zstepover))
		{
			if (x == 0)
				return true;
			map[y][x - 1]._zombies.push_back(_zombies[i]);
			_zombies.erase(_zombies.begin() + i);
		}
		else
			++i;
	}
	return false;
}
void Grid::ZombieEatPlant()
{
	if (_state != BLANK && _zombies.size() != 0)
		for (unsigned int i = 0; i < _zombies.size(); ++i)
		{
			if (_zombies[i]->Attack(_plants.back()->GetPlantHP(), _plants.back()->GetInvincibility()))
			{
				_zombies[i]->ChangeRoad(_plants.back()->BeAte());
				if (_plants.back()->GetPlantHP() == 0)
				{
					Plants* p = _plants.back();
					_plants.pop_back();
					delete p;
					if (_plants.size() == 1)
					{
						_state = PLANT;
						continue;
					}
					else
					{
						_state = BLANK;
						for (int j = 0; j < _zombies.size(); ++j)
							_zombies[j]->ChangeMove(true);
						break;
					}
				}
			}
		}
}
void Grid::ZombieFunction(Grid map[][7], int x, int y, int lastplant, deque<Bullets*>& basketball)
{
	ZombieAction za = NONE;
	for (unsigned int i = 0; i < _zombies.size(); )
	{
		_zombies[i]->Function(za, x, lastplant);
		if (za == BOMB)
		{
			SetPrintColor(b_red);
			for (int k = -1; k <= 1; ++k)
				for (int j = -1; j <= 1; ++j)
				{
					if (x + j < 7 && x + j >= 0 && y + k < 5 && y + k >= 0)
					{
						DrawGridEdge(map[y + k][x + j]._X, map[y + k][x + j]._Y);//绘制爆炸特效
						map[y + k][x + j].ClearDead(3);
					}
				}
			ClearDead(1);
			SetPrintColor(reset);
		}
		if (za == SHOOT)
		{
			BasketballBullet* p = new BasketballBullet(_X, _Y + 1, lastplant);
			basketball.push_back(p);
			++i;
		}
		if (za == NONE)
			++i;
	}
}
bool Grid::BulletAttack(Bullets* b, Target t, int &score)
{
	if (t == ZOMBIES)
	{
		if (_zombies.size() != 0)
		{
			auto max = _zombies.begin();
			for (auto i = _zombies.begin(); i < _zombies.end(); ++i)
				if ((*i)->GetGridMove() > (*max)->GetGridMove())
					max = i;
			if ((*max)->BeAttack(b->GetBulletAtk(), b->GetFreeze()))
			{
				score += (*max)->GetZombieScore();
				delete (*max);
				_zombies.erase(max);
			}
			return true;
		}
		return false;
	}
	if (t == PLANTS)
	{
		BasketballBullet* p = (BasketballBullet*)b;
		if (p->GetDestination() == _X / 13)
		{
			if (_plants.size() == 0)
				return true;
			if (_plants[0]->BeAttack(p->GetBulletAtk()))
			{
				delete _plants[0];
				_plants.erase(_plants.begin());
				if (_plants.size() == 1)
					_state = PUMPKIN;
				else
					_state = BLANK;
			}
			return true;
		}
		return false;
	}
}
void Grid::ClearDead(int choice)
{
	if (choice == 0 || choice == 2)//清除格子中HP为0的植物
		for (unsigned int i = 0; i < _plants.size(); )
			if (_plants[i]->GetPlantHP() <= 0)
			{
				delete _plants[i];
				_plants.erase(_plants.begin() + i);
				if (_plants.size() == 0)
					_state = BLANK;
				if (_plants.size() == 1 && i == 0)
					_state = PUMPKIN;
				if (_plants.size() == 1 && i == 1)
					_state = PLANT;
			}
			else
				++i;
	if (choice == 1 || choice == 2)//清除格子中HP为0的僵尸
		for (unsigned int i = 0; i < _zombies.size(); )
			if (_zombies[i]->GetZombieHP() <= 0)
			{
				delete _zombies[i];
				_zombies.erase(_zombies.begin() + i);
			}
			else
				++i;
	if (choice == 3 || choice == 5)//清除格子中所有植物
	{
		while (!_plants.empty())
		{
			delete _plants.front();
			_plants.erase(_plants.begin());
		}
		_state = BLANK;
	}
	if (choice == 4 || choice == 5)//清除格子中所有僵尸
	{
		while (!_zombies.empty())
		{
			delete _zombies.front();
			_zombies.erase(_zombies.begin());
		}
	}
}
void Grid::PlantFunction(Grid map[][7], int x, int y, bool exsitzombie, int& sunlight, deque<Bullets*> &bullet, int& score)
{
	PlantAction pa = _NONE;
	for (unsigned int i = 0; i < _plants.size(); )
	{
		unsigned int zombie_nums = 0;
		for (int j = -1; j <= 1; ++j)
			if (x + j >= 0 && x + j < 7)
				zombie_nums += map[y][x + j]._zombies.size();
		_plants[i]->Function(pa, exsitzombie, zombie_nums, sunlight);
		if (pa == _SHOOT)
		{
			Bullets* p = new Bullets(_X + 13, _Y + 2);
			bullet.push_back(p);
			pa = _NONE;
		}
		if (pa == _SHOOT_SNOW)
		{
			Bullets* p = new SnowBullet(_X + 13, _Y + 2);
			bullet.push_back(p);
			pa = _NONE;
		}
		if (pa == _BOMP)
		{
			SetPrintColor(b_red);
			for (int k = -1; k <= 1; ++k)
				for (int j = -1; j <= 1; ++j)
				{
					if (x + j < 7 && x + j >= 0 && y + k < 5 && y + k >= 0)
					{
						DrawGridEdge(map[y + k][x + j]._X, map[y + k][x + j]._Y);//绘制爆炸特效
						for (auto m = map[y + k][x + j]._zombies.begin(); m < map[y + k][x + j]._zombies.end(); ++m)
							score += (*m)->GetZombieScore();
						map[y + k][x + j].ClearDead(4);
					}
				}
			ClearDead(0);
			SetPrintColor(reset);
		}
		if (pa == _BOUCE)
		{
			int _x = x;
			/*if (map[x][y]._zombies.size() == 0 && zombie_nums)
			{
				if (x - 1 < 0)
					_x = x + 1;
				else if (x + 1 >= 7)
					_x = x - 1;
				else if (map[x - 1][y]._zombies.size() == 0)
					_x = x + 1;
				else if (map[x + 1][y]._zombies.size() == 0)
					_x = x - 1;
				else
				{
					if (map[x - 1][y]._zombies.size() > map[x - 1][y]._zombies.size())
						_x = x - 1;
					else
						_x = x + 1;
				}
			}*/
			/*if (x - 1 >= 0)
			{
				if (map[x - 1][y]._zombies.size() != 0)
					_x = x - 1;
			}
			else if (map[x][y]._zombies.size() != 0)
				_x = x;
			else if (x + 1 < 7)
			{
				if (map[x + 1][y]._zombies.size() != 0)
					_x = x + 1;
			}*/
			if (x + 1 < 7)
				if (!map[y][x + 1]._zombies.empty())
					_x = x + 1;
			if (!map[y][x]._zombies.empty())
				_x = x;
			if (x - 1 >= 0)
				if (!map[y][x - 1]._zombies.empty())
					_x = x - 1;
			SetPrintColor(b_red);
			DrawGridEdge(map[y][_x]._X, map[y][_x]._Y);//绘制特效
			SetPrintColor(reset);
			map[y][_x].ClearDead(4);
			ClearDead(0);
		}
		if (pa == _NONE)
			++i;
	}
}