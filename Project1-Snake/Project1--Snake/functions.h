#pragma once
#include "struct.h"

void initSnake(Snake* snake);
void initMap(Map* map);
void drawUnit(Point p, const char unit[]);
void drawSnake(Snake* snake);
void drawMap(Map* map);
void hideCursor();
bool checkOutOfBound(Point p);
void moveSnake(Snake* snk);
void checkEatFood(Snake* snake, Point tail, Map* map);
bool doMove(Snake* snk, Map* map);
bool checkSnakeMove(Snake* snake, Map* map);
void checkChangeDir(Snake* snake);
void checkFoodGenerate(Snake* snake, Map* map);
void initGame(Map* map, Snake* snake);