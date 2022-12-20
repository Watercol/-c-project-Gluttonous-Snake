#include "gsnake.h"
extern Food food;
extern Snake snake;
void initfood()
{
	for (int i = 0; i < FOODNUM; i++)
	{
		food.foodxy[i].x = rand() % 64 * 10;
		food.foodxy[i].y = rand() % 48 * 10;
		food.foodexist[i] = 1;//防止反复出现食物
		//如果食物出现在蛇身上
		for (int i = 1; i < snake.longth; i++)
		{
			if (food.foodxy[i].x == snake.body[i].x && food.foodxy[i].y == snake.body[i].y)
			{
				food.foodxy[i].x = rand() % 64 * 10;
				food.foodxy[i].y = rand() % 48 * 10;
			}
		}
	}
}
void drawfood()//画食物
{
	setlinecolor(WHITE);
	setfillcolor(RED);
	for (int i = 0; i < FOODNUM; i++)
		if (food.foodexist[i] == 1)
			fillrectangle(food.foodxy[i].x, food.foodxy[i].y, food.foodxy[i].x + 10, food.foodxy[i].y + 10);
}
int getexist()
{
	for (int i = 0; i < FOODNUM; i++)
		if (food.foodexist[i] == 1)
			return 1;
	return 0;
}