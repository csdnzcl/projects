#include <iostream>
#include "struct.h"
#include "functions.h"

using namespace std;

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