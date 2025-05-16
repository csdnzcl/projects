#include <iostream>
#include <windows.h> // Windows API
using namespace std;

#define H 30
#define W 50

const int dir[4][2] = { // 定义方向数组
	{0, 1}, // 右
	{1, 0}, // 下
	{0, -1}, // 左
	{-1, 0} // 上
};

//枚举类型表示地图上的方块类型
enum BlockType {
	EMPTY = 0,
	FOOD = 1,
 }; 

struct MAP {
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
	snake->moveFrequency = 200; // 初始化移动频率
}

void initMap(MAP* map) { // 初始化地图
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			map->data[y][x] = BlockType::EMPTY; // 初始化为空
		}
	}
	map->hasFood = false; // 初始化没有食物
}

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

void drawMap(MAP* map) {
	system("cls"); //清空控制台
	cout << "┏";              // ┏┓┗┛
	for (int i = 0; i < W; i++) {
		cout << "─"; 
	}
	cout << "┓" << endl;
	for (int y = 0; y < H; y++) {
		cout << "│"; // 左边界
		for (int x = 0; x < W; x++) {
			if (map->hasFood == false) {
				cout << " "; // 空格
			}
		}
		cout << "│" << endl; // 右边界
	}
	cout << "┗"; // 下边界
	for (int i = 0; i < W; i++) {
		cout << "─"; // 下边界
	}
	cout << "┛" ;
}

//隐藏光标函数
void hideCursor() {
	GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出句柄（编号）
	CONSOLE_CURSOR_INFO curInfo = { 1, FALSE }; // 控制台光标信息的结构体
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); // 设置光标信息
}

bool checkOutOfBound(Point p) { // 检查是否越界
	if (p.x == 0 || p.x == W + 1 || p.y == 0 || p.y == H + 1) {
		return true; // 越界
	}
	return false; // 没有越界
}

void moveSnake(Snake* snk) {
	for (int i = snk->snakeLength - 1; i > 0; --i) { // 从蛇尾开始移动
		snk->snake[i] = snk->snake[i - 1]; // 将前一个坐标赋值给当前坐标
	}
	snk->snake[0].x += dir[snk->snakeDir][0]; // 更新蛇头坐标
	snk->snake[0].y += dir[snk->snakeDir][1]; // 更新蛇头坐标
}

bool doMove(Snake* snk, MAP* map) {
	Point tail = snk->snake[snk->snakeLength - 1]; // 获取蛇尾坐标
	drawUnit(tail, " "); // 清除蛇尾
	moveSnake(snk); // 移动蛇身
	if (checkOutOfBound(snk->snake[0])) { // 检查蛇头是否越界
		return false; // 越界，返回失败
	}
	drawUnit(snk->snake[0], "■"); // 绘制蛇头
	return true;
}

bool checkSnakeMove(Snake* snake, MAP* map) { // 检查蛇的移动
	int curTime = GetTickCount(); // 获取当前时间
	if (curTime - snake->lastMoveTime > snake->moveFrequency) { // 判断是否到达移动频率
		if (false == doMove(snake, map))
			return false;
		snake->lastMoveTime = curTime; // 更新上次移动时间
	}
	return true;
}

int main() {
	MAP map; // 创建地图对象
	Snake snake; // 创建蛇对象
	hideCursor();
	initMap(&map); // 初始化地图
	initSnake(&snake); // 初始化蛇
	drawMap(&map); // 绘制地图
	drawSnake(&snake); // 绘制蛇
	while (1) {
		if (checkSnakeMove(&snake, &map) == false) {
			break; // 如果移动失败，退出循环
		}
	}
	drawUnit({ W / 2 - 4, H / 2 }, "Game Over!"); // 游戏结束提示
	return 0;
 }