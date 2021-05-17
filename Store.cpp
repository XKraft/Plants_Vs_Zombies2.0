#include"Store.h"
Store::Store()
{
	Sunflower* p1 = new Sunflower;
	PeaShooter* p2 = new PeaShooter;
	RepeatPeaShooter* p3 = new RepeatPeaShooter;
	SnowPeaShooter* p4 = new SnowPeaShooter;
	WallNut* p5 = new WallNut;
	TallNut* p6 = new TallNut;
	Squash* p7 = new Squash;
	CherryBomb* p8 = new CherryBomb;
	Garlic* p9 = new Garlic;
	Pumpkin* p10 = new Pumpkin;

	_plants_in_store[0] = { p1, 50, 75, 75, 1, clock() };
	_plants_in_store[1] = { p2, 100, 75, 75, 2, clock() };
	_plants_in_store[2] = { p3, 200, 75, 75, 3, clock() };
	_plants_in_store[3] = { p4, 175, 75, 75, 4, clock() };
	_plants_in_store[4] = { p5, 50, 300, 300, 5, clock() };
	_plants_in_store[5] = { p6, 125, 300, 300, 6, clock() };
	_plants_in_store[6] = { p7, 50, 300, 300, 7, clock() };
	_plants_in_store[7] = { p8, 150, 300, 300, 8, clock() };
	_plants_in_store[8] = { p9, 50, 75, 75, 9, clock() };
	_plants_in_store[9] = { p10, 125, 300, 300, 10, clock() };

	_cursor_x = 0;
	_cursor_y = 0;
	display_cursor = true;
}
Store::~Store()
{
	for (int i = 0; i < 10; ++i)
		delete _plants_in_store[i]._plant;
}
void Store::Draw()
{
	CursorSetXY(0, STORE_LINES);
	cout << "ил╣Й";
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 5; ++j)
		{
			if (display_cursor && j == _cursor_x && i == _cursor_y)
				SetPrintColor(f_yellow);
			CursorSetXY((GRID_WIDTH - 1) * j, STORE_LINES + i * 2 + 1);
			cout << _plants_in_store[i * 5 + j]._plant->GetPlantName();
			CursorSetXY((GRID_WIDTH - 1) * j, STORE_LINES + i * 2 + 2);
			cout << _plants_in_store[i * 5 + j]._cost << "  ";
			if (_plants_in_store[i * 5 + j]._CD != _plants_in_store[i * 5 + j]._CD_count)
				cout << _plants_in_store[i * 5 + j]._CD_count * 100 / _plants_in_store[i * 5 + j]._CD << "%";
			else
				cout << "      ";
			SetPrintColor(reset);
		}
}
void Store::MoveCursor(int dx, int dy)
{
	if (_cursor_y + dy < 0 || _cursor_y + dy >= 2)
		dy = 0;
	if (_cursor_x + dx < 0 || _cursor_x + dx >= 5)
		dx = 0;
	_cursor_x += dx;
	_cursor_y += dy;
}
bool Store::BuyPlant(int sunlight, PlantCard& plant)
{
	if (sunlight >= _plants_in_store[_cursor_y * 5 + _cursor_x]._cost && _plants_in_store[_cursor_y * 5 + _cursor_x]._CD == _plants_in_store[_cursor_y * 5 + _cursor_x]._CD_count)
	{
		display_cursor = false;
		int i = _plants_in_store[_cursor_y * 5 + _cursor_x].ID;
		switch (i)
		{
		case 1:
			plant._plant = new Sunflower; break;
		case 2:
			plant._plant = new PeaShooter; break;
		case 3:
			plant._plant = new RepeatPeaShooter; break;
		case 4:
			plant._plant = new SnowPeaShooter; break;
		case 5:
			plant._plant = new WallNut; break;
		case 6:
			plant._plant = new TallNut; break;
		case 7:
			plant._plant = new Squash; break;
		case 8:
			plant._plant = new CherryBomb; break;
		case 9:
			plant._plant = new Garlic; break;
		case 10:
			plant._plant = new Pumpkin; break;
		}
		plant._cost = _plants_in_store[_cursor_y * 5 + _cursor_x]._cost;
		plant.ID = _plants_in_store[_cursor_y * 5 + _cursor_x].ID;
		return true;
	}
	return false;
}
void Store::CancelBuyPlant(PlantCard& plant)
{
	delete plant._plant;
	plant._plant = NULL;
	display_cursor = true;
}
void Store::SucceedBuy()
{
	display_cursor = true;
	_plants_in_store[_cursor_y * 5 + _cursor_x]._CD_count = 0;
}
void Store::Run(int &sunlight, int &score)
{
	static clock_t c1 = clock();
	static clock_t c2 = clock();

	for (int i = 0; i < 10; ++i)
	{
		if (_plants_in_store[i]._CD != _plants_in_store[i]._CD_count)
			if (SandGlass(_plants_in_store[i].c, 1))
				++_plants_in_store[i]._CD_count;
	}

	if (SandGlass(c1, 60))
		sunlight += 25;

	if (SandGlass(c2, 10))
		++score;

}