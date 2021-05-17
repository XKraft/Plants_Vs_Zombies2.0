#pragma once
#include"Global.h"

//游戏界面设置
const int GRID_WIDTH = 14;//格子宽度
const int GRID_HEIGHT = 6;//格子高度
const int STAGE_COLS = 7;//草坪列数
const int STAGE_LINES = 5;//草坪行数
const int STAGE_WIDTH = (GRID_WIDTH - 1) * STAGE_COLS + 1;//草坪总宽度
const int STAGE_HEIGHT = (GRID_HEIGHT - 1) * STAGE_LINES + 1;//草坪总高度
const int CMD_COLS = STAGE_WIDTH;//命令行宽度
const int CMD_LINES = STAGE_HEIGHT + 9;//命令行高度
const int STORE_LINES = STAGE_HEIGHT + 4;//商店显示位置
//设置命令行字体颜色
const int b_red = BACKGROUND_INTENSITY | BACKGROUND_RED;
const int f_red = FOREGROUND_INTENSITY | FOREGROUND_RED;
const int reset = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
const int f_green = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
const int f_blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
const int f_yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
const int b_yellow = BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
//时间分度值，即100ms
const int TIME = 100;

//功能函数
//更改显示颜色
void SetPrintColor(int color_id);
//移动光标到指定位置
void CursorSetXY(int x, int y);
//设置命令行窗口大小
void SetCMDSize(int cols, int lines);
//隐藏光标
void HideCursor();
//将网格中的二维坐标转化为一维
int CoordTtoO(int x, int y);
//将命令行中的二位坐标转换为网格中的一维
int CoordCMDtoGRID(int x, int y);
//绘制网格的边界
void DrawGridEdge(int x, int y);
//沙漏函数，用于计时
bool SandGlass(clock_t& c, int s);