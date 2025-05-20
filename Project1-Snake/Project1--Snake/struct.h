#pragma once
#include <iostream>
using namespace std;

#define W 60
#define H 30

const int dir[4][2] = { // 定义方向数组
	{-1, 0}, // 上
	{ 0, 1 }, // 右
	{1, 0}, // 下
	{0, -1}, // 左
};

//枚举类型表示地图上的方块类型
enum BlockType {
	EMPTY = 0,
	FOOD = 1,
};

struct Map {
	BlockType data[H][W]; // 二维数组表示地图
	bool hasFood; // 是否有食物
};

struct Point {
	int x;
	int y;
};

struct Snake {
	Point snake[H * W]; // 蛇身坐标
	int snakeDir;
	int snakeLength; // 蛇身长度
	int lastMoveTime;
	int moveFrequency;
};
