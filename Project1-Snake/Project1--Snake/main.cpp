#include <iostream>
#include "struct.h"
#include "functions.h"

using namespace std;

int main() {
	Map map; // ������ͼ����
	Snake snake; // �����߶���
	hideCursor();
	initGame(&map, &snake); // ��ʼ����Ϸ
	while (1) {
		checkChangeDir(&snake); // ��鷽��仯
		if (checkSnakeMove(&snake, &map) == false) {
			break; // ����ƶ�ʧ�ܣ��˳�ѭ��
		}
		checkFoodGenerate(&snake, &map); // ���ʳ������
	}
	drawUnit({ W / 2 - 4, H / 2 - 4 }, "Game Over!"); // ��Ϸ������ʾ
	while (1);
	return 0;
}