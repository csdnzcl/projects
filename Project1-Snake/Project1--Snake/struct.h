#pragma once
#include <iostream>
using namespace std;

#define W 60
#define H 30

const int dir[4][2] = { // ���巽������
	{-1, 0}, // ��
	{ 0, 1 }, // ��
	{1, 0}, // ��
	{0, -1}, // ��
};

//ö�����ͱ�ʾ��ͼ�ϵķ�������
enum BlockType {
	EMPTY = 0,
	FOOD = 1,
};

struct Map {
	BlockType data[H][W]; // ��ά�����ʾ��ͼ
	bool hasFood; // �Ƿ���ʳ��
};

struct Point {
	int x;
	int y;
};

struct Snake {
	Point snake[H * W]; // ��������
	int snakeDir;
	int snakeLength; // ������
	int lastMoveTime;
	int moveFrequency;
};
