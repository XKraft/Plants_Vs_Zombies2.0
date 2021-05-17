#include"UI.h"
#include<iostream>
using namespace std;
//�������������������ɫ
void SetPrintColor(int color_id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_id);
}
//���������й��λ��
void CursorSetXY(int x, int y)
{
	COORD cursor;
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}
//���������д��ڴ�С
void SetCMDSize(int cols, int lines)
{
	char str[40];
	sprintf(str, "mode con cols=%d lines=%d", cols, lines);
	system(str);
}
//���������й��
void HideCursor()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
}
//����ά����ת����һά
int CoordTtoO(int x, int y)
{
	return x + y * STAGE_COLS;
}
//���������еĶ�λ����ת��Ϊ�����е�һά
int CoordCMDtoGRID(int x, int y)
{
	int i = x / GRID_WIDTH;
	int j = y / GRID_HEIGHT;
	return i + j * STAGE_COLS;
}
void DrawGridEdge(int x, int y)
{
	CursorSetXY(x, y);
	cout << "##############";
	for (int i = 1; i < GRID_HEIGHT - 1; ++i)
	{
		CursorSetXY(x, y + i);
		cout << "#";
		CursorSetXY(x + GRID_WIDTH - 1, y + i);
		cout << "#";
	}
	CursorSetXY(x, y + GRID_HEIGHT - 1);
	cout << "##############";
}
//ɳ©���������ڼ�ʱ��һ������Ϊs*100ms
bool SandGlass(clock_t& c, int s)
{
	if (clock() - c >= s * TIME)
	{
		c = clock();
		return true;
	}
	else
		return false;
}