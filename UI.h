#pragma once
#include"Global.h"

//��Ϸ��������
const int GRID_WIDTH = 14;//���ӿ��
const int GRID_HEIGHT = 6;//���Ӹ߶�
const int STAGE_COLS = 7;//��ƺ����
const int STAGE_LINES = 5;//��ƺ����
const int STAGE_WIDTH = (GRID_WIDTH - 1) * STAGE_COLS + 1;//��ƺ�ܿ��
const int STAGE_HEIGHT = (GRID_HEIGHT - 1) * STAGE_LINES + 1;//��ƺ�ܸ߶�
const int CMD_COLS = STAGE_WIDTH;//�����п��
const int CMD_LINES = STAGE_HEIGHT + 9;//�����и߶�
const int STORE_LINES = STAGE_HEIGHT + 4;//�̵���ʾλ��
//����������������ɫ
const int b_red = BACKGROUND_INTENSITY | BACKGROUND_RED;
const int f_red = FOREGROUND_INTENSITY | FOREGROUND_RED;
const int reset = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
const int f_green = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
const int f_blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE;
const int f_yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
const int b_yellow = BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
//ʱ��ֶ�ֵ����100ms
const int TIME = 100;

//���ܺ���
//������ʾ��ɫ
void SetPrintColor(int color_id);
//�ƶ���굽ָ��λ��
void CursorSetXY(int x, int y);
//���������д��ڴ�С
void SetCMDSize(int cols, int lines);
//���ع��
void HideCursor();
//�������еĶ�ά����ת��Ϊһά
int CoordTtoO(int x, int y);
//���������еĶ�λ����ת��Ϊ�����е�һά
int CoordCMDtoGRID(int x, int y);
//��������ı߽�
void DrawGridEdge(int x, int y);
//ɳ©���������ڼ�ʱ
bool SandGlass(clock_t& c, int s);