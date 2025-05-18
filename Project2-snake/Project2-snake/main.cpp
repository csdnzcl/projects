#include <iostream>
#include <windows.h> // Windows API
#include <conio.h> // 控制台输入输出
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

void initSnake(Snake* snake) {
	snake->snakeLength = 1; // 初始化蛇身长度为1
	snake->snakeDir = 1; // 初始化蛇身方向为向右
	snake->snake[0].x = W/2; // 初始化蛇头坐标
	snake->snake[0].y = H/2; // 初始化蛇头坐标
	snake->lastMoveTime = 0; // 初始化上次移动时间
	snake->moveFrequency = 300; // 初始化移动频率
}

void initMap(Map* map) { // 初始化地图
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			map->data[y][x] = BlockType::EMPTY; // 初始化为空
		}
	}
	map->hasFood = false; // 初始化没有食物
}

//在指定位置绘制单位
void drawUnit(Point p, const char unit[]) {
	COORD coord; // 定义坐标结构体
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取当前窗口的句柄
	coord.X = p.x + 1; // 设置坐标
	coord.Y = p.y + 1; // 设置坐标
	SetConsoleCursorPosition(hOutput, coord); // 设置光标位置
	cout << unit; // 输出单位
}

void drawSnake(Snake* snake) { // 绘制蛇
	for (int i = 0; i < snake->snakeLength; ++i) {
		Point p = snake->snake[i]; // 获取蛇身坐标
		drawUnit(p, "■"); // 绘制蛇身
	}
}

void drawMap(Map* map) {
	system("cls"); //清空控制台
	cout << "┏";
	for (int i = 0; i < W; i++) {
		cout << "━"; 
	}
	cout << "┓" << endl;
	for (int y = 0; y < H; y++) {
		cout << "┃"; // 左边界
		for (int x = 0; x < W; x++) {
			if (map->data[y][x] == BlockType::EMPTY) {
				cout << " "; // 空格
			}
			else if (map->data[y][x] == BlockType::FOOD) {
				cout << "●"; // 食物
			}
		}
		cout << "┃" << endl; // 右边界
	}
	cout << "┗"; // 下边界
	for (int x = 0; x < W; x++) {
		cout << "━"; // 下边界
	}
	cout << "┛" ;
}

//隐藏光标函数---------固定代码----需要<windows.h>头文件
void hideCursor() {
	GetStdHandle(STD_OUTPUT_HANDLE);// 获取窗口句柄
	CONSOLE_CURSOR_INFO curInfo = { 1, FALSE }; // 控制台光标信息的结构体
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); // 设置光标信息
}

bool checkOutOfBound(Point p) { // 检查是否越界
	if (p.x <= 0 || p.x >= W + 1 || p.y <= 0 || p.y >= H + 1) {
		return true; // 越界
	}
	return false; // 没有越界
}

void moveSnake(Snake* snk) {
	for (int i = snk->snakeLength - 1; i > 0; --i) { // 从蛇尾开始移动
		snk->snake[i] = snk->snake[i - 1]; // 将前一个坐标赋值给当前坐标
	}
	snk->snake[0].y += dir[snk->snakeDir][0]; // 更新蛇头坐标
	snk->snake[0].x += dir[snk->snakeDir][1]; // 更新蛇头坐标
}

void checkEatFood(Snake* snake, Point tail, Map* map) {
	Point head = snake->snake[0];
	if (map->data[head.y][head.x] == BlockType::FOOD) {
		snake->snake[snake->snakeLength++] = tail; // 将蛇尾添加到蛇身
		map->data[head.y][head.x] = BlockType::EMPTY; // 清除食物
		map->hasFood = false; // 设置没有食物
		drawUnit(tail, "■"); // 绘制蛇身
	}
}

bool doMove(Snake* snk, Map* map) {
	Point tail = snk->snake[snk->snakeLength - 1]; // 获取蛇尾坐标
	drawUnit(tail, " "); // 清除蛇尾
	moveSnake(snk); // 移动蛇身
	if (checkOutOfBound(snk->snake[0])) { // 检查蛇头是否越界
		return false; // 越界，返回失败
	}
	checkEatFood(snk, tail, map); // 检查是否吃到食物
	drawUnit(snk->snake[0], "■"); // 绘制蛇头
	return true;
}

bool checkSnakeMove(Snake* snake, Map* map) { // 检查蛇的移动
	int curTime = GetTickCount(); // 获取当前时间
	if (curTime - snake->lastMoveTime > snake->moveFrequency) { // 判断是否到达移动频率
		if (false == doMove(snake, map))
			return false;
		snake->lastMoveTime = curTime; // 更新上次移动时间
	}
	return true;
}

void checkChangeDir(Snake* snake) {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (snake->snakeDir != 2) 
				snake->snakeDir = 0; // 上
			break;
		case 'd':
			if (snake->snakeDir != 3)
				snake->snakeDir = 1; // 右
			break;
		case 's':
			if (snake->snakeDir != 0)
				snake->snakeDir = 2; // 下
			break;
		case 'a':
			if (snake->snakeDir != 1)
				snake->snakeDir = 3; // 左
			break;
		}
	}
}

void checkFoodGenerate(Snake* snake, Map* map) {
	if (false == map->hasFood) {
		while (1) {
			int x = rand() % W;
			int y = rand() % H;
			int i = 0;
			while (i < snake->snakeLength) {
				if (snake->snake[i].x == x && snake->snake[i].y == y) {
					break; // 如果食物位置与蛇身重合，则重新生成
				}
				++i;
			}
			if (i == snake->snakeLength) {
				map->data[y][x] = BlockType::FOOD;
				map->hasFood = true; // 生成食物
				drawUnit({ x, y }, "●"); // 绘制食物
				return;
			}
		}
	}
}

void initGame(Map* map, Snake* snake) {
	hideCursor();
	initMap(map); 
	initSnake(snake);
	drawMap(map); 
	drawSnake(snake); 
}

int main() {
	Map map; // 创建地图对象
	Snake snake; // 创建蛇对象
	hideCursor();
	initGame(&map, &snake); // 初始化游戏
	while (1) {
		checkChangeDir(&snake); // 检查方向变化
		if (checkSnakeMove(&snake, &map) == false) {
			break; // 如果移动失败，退出循环
		}
		checkFoodGenerate(&snake, &map); // 检查食物生成
	}
	drawUnit({ W / 2 - 4, H / 2 - 4 }, "Game Over!"); // 游戏结束提示
	while (1);
	return 0;
 }