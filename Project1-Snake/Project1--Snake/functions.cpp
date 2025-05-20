#include <iostream>
#include <windows.h> // Windows API
#include <conio.h> // ����̨�������
#include "struct.h"
using namespace std;

void initSnake(Snake* snake) {
	snake->snakeLength = 1; // ��ʼ��������Ϊ1
	snake->snakeDir = 1; // ��ʼ��������Ϊ����
	snake->snake[0].x = W / 2; // ��ʼ����ͷ����
	snake->snake[0].y = H / 2; // ��ʼ����ͷ����
	snake->lastMoveTime = 0; // ��ʼ���ϴ��ƶ�ʱ��
	snake->moveFrequency = 300; // ��ʼ���ƶ�Ƶ��
}

void initMap(Map* map) { // ��ʼ����ͼ
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			map->data[y][x] = BlockType::EMPTY; // ��ʼ��Ϊ��
		}
	}
	map->hasFood = false; // ��ʼ��û��ʳ��
}

//��ָ��λ�û��Ƶ�λ
void drawUnit(Point p, const char unit[]) {
	COORD coord; // ��������ṹ��
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��ǰ���ڵľ��
	coord.X = p.x + 1; // ��������
	coord.Y = p.y + 1; // ��������
	SetConsoleCursorPosition(hOutput, coord); // ���ù��λ��
	cout << unit; // �����λ
}

void drawSnake(Snake* snake) { // ������
	for (int i = 0; i < snake->snakeLength; ++i) {
		Point p = snake->snake[i]; // ��ȡ��������
		drawUnit(p, "��"); // ��������
	}
}

void drawMap(Map* map) {
	system("cls"); //��տ���̨
	cout << "��";
	for (int i = 0; i < W; i++) {
		cout << "��";
	}
	cout << "��" << endl;
	for (int y = 0; y < H; y++) {
		cout << "��"; // ��߽�
		for (int x = 0; x < W; x++) {
			if (map->data[y][x] == BlockType::EMPTY) {
				cout << " "; // �ո�
			}
			else if (map->data[y][x] == BlockType::FOOD) {
				cout << "��"; // ʳ��
			}
		}
		cout << "��" << endl; // �ұ߽�
	}
	cout << "��"; // �±߽�
	for (int x = 0; x < W; x++) {
		cout << "��"; // �±߽�
	}
	cout << "��";
}

//���ع�꺯��---------�̶�����----��Ҫ<windows.h>ͷ�ļ�
void hideCursor() {
	GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ���ھ��
	CONSOLE_CURSOR_INFO curInfo = { 1, FALSE }; // ����̨�����Ϣ�Ľṹ��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); // ���ù����Ϣ
}

bool checkOutOfBound(Point p) { // ����Ƿ�Խ��
	if (p.x <= 0 || p.x >= W + 1 || p.y <= 0 || p.y >= H + 1) {
		return true; // Խ��
	}
	return false; // û��Խ��
}

void moveSnake(Snake* snk) {
	for (int i = snk->snakeLength - 1; i > 0; --i) { // ����β��ʼ�ƶ�
		snk->snake[i] = snk->snake[i - 1]; // ��ǰһ�����긳ֵ����ǰ����
	}
	snk->snake[0].y += dir[snk->snakeDir][0]; // ������ͷ����
	snk->snake[0].x += dir[snk->snakeDir][1]; // ������ͷ����
}

void checkEatFood(Snake* snake, Point tail, Map* map) {
	Point head = snake->snake[0];
	if (map->data[head.y][head.x] == BlockType::FOOD) {
		snake->snake[snake->snakeLength++] = tail; // ����β��ӵ�����
		map->data[head.y][head.x] = BlockType::EMPTY; // ���ʳ��
		map->hasFood = false; // ����û��ʳ��
		drawUnit(tail, "��"); // ��������
	}
}

bool doMove(Snake* snk, Map* map) {
	Point tail = snk->snake[snk->snakeLength - 1]; // ��ȡ��β����
	drawUnit(tail, " "); // �����β
	moveSnake(snk); // �ƶ�����
	if (checkOutOfBound(snk->snake[0])) { // �����ͷ�Ƿ�Խ��
		return false; // Խ�磬����ʧ��
	}
	checkEatFood(snk, tail, map); // ����Ƿ�Ե�ʳ��
	drawUnit(snk->snake[0], "��"); // ������ͷ
	return true;
}

bool checkSnakeMove(Snake* snake, Map* map) { // ����ߵ��ƶ�
	int curTime = GetTickCount(); // ��ȡ��ǰʱ��
	if (curTime - snake->lastMoveTime > snake->moveFrequency) { // �ж��Ƿ񵽴��ƶ�Ƶ��
		if (false == doMove(snake, map))
			return false;
		snake->lastMoveTime = curTime; // �����ϴ��ƶ�ʱ��
	}
	return true;
}

void checkChangeDir(Snake* snake) {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (snake->snakeDir != 2)
				snake->snakeDir = 0; // ��
			break;
		case 'd':
			if (snake->snakeDir != 3)
				snake->snakeDir = 1; // ��
			break;
		case 's':
			if (snake->snakeDir != 0)
				snake->snakeDir = 2; // ��
			break;
		case 'a':
			if (snake->snakeDir != 1)
				snake->snakeDir = 3; // ��
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
					break; // ���ʳ��λ���������غϣ�����������
				}
				++i;
			}
			if (i == snake->snakeLength) {
				map->data[y][x] = BlockType::FOOD;
				map->hasFood = true; // ����ʳ��
				drawUnit({ x, y }, "��"); // ����ʳ��
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