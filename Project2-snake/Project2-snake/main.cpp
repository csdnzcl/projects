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

struct Pos {
	int x;
	int y;
};

struct Snake {
	Pos snake[H * W]; // 蛇身坐标
	int snakeDir; 
	int snakeLength; // 蛇身长度
};

void initSnake(Snake* snake) {
	snake->snakeLength = 1; // 初始化蛇身长度为1
	snake->snakeDir = 1; // 初始化蛇身方向为向右
	snake->snake[0].x = W/2; // 初始化蛇头坐标
	snake->snake[0].y = H/2; // 初始化蛇头坐标
}

void initMap(MAP* map) { // 初始化地图
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			map->data[y][x] = BlockType::EMPTY; // 初始化为空
		}
	}
	map->hasFood = false; // 初始化没有食物
}

void dramUnit(Pos p, const char unit[]) {
	COORD coord; // 定义坐标结构体
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出句柄
	coord.X = p.x + 1; // 设置坐标
	coord.Y = p.y + 1; // 设置坐标
	SetConsoleCursorPosition(hOutput, coord); // 设置光标位置
	cout << unit; // 输出单位
}

void drawSnake(Snake* snake) { // 绘制蛇
	for (int i = 0; i < snake->snakeLength; ++i) {
		Pos p = snake->snake[i]; // 获取蛇身坐标
		dramUnit(p, "■"); // 绘制蛇身
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

void checkSnakeMove(Snake* snake, MAP* map) { // 检查蛇的移动
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
		checkSnakeMove(&snake, &map);
	}
 }