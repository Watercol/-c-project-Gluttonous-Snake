#include "gsnake.h"
extern Food food;
extern Snake snake;
void initsnake()//��ʼ�ߵĳ���Ϊ3,ÿ�μ��Ϊ10
{
	snake.body[2].x = 300;
	snake.body[2].y = 240;
	snake.body[1].x = 310;
	snake.body[1].y = 240;
	snake.body[0].x = 320;
	snake.body[0].y = 240;
	snake.longth = 3;
	snake.position = RIGHT;
}
void drawsnake()//����
{
	for (int i = 0; i < snake.longth; i++)
	{
		setlinecolor(BLACK);//�߿���ɫ
		setfillcolor(CYAN);//�����ɫ
		fillrectangle(snake.body[i].x, snake.body[i].y, snake.body[i].x + 10, snake.body[i].y + 10);
	}
}
void movesnake()//�ߵ��ƶ�
{
	//�����۳�����ͷ֮������壬��ÿһ�ڶ�����ǰһ�ڵ����꼴��ʵ���ƶ�
	for (int i = snake.longth - 1; i > 0; i--)
	{
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
	}
	//�ٴ�����ͷ���ƶ�
	switch (snake.position)
	{
	case RIGHT:
		snake.body[0].x += 10;
		break;
	case LEFT:
		snake.body[0].x -= 10;
		break;
	case DOWN:
		snake.body[0].y += 10;
		break;
	case UP:
		snake.body[0].y -= 10;
		break;
	default:
		break;
	}
}
void keysnake()//���ü��̿�����
{
	if (KEYDOWN(38) < 0 || KEYDOWN(87) < 0)
		if (snake.position != DOWN)
			snake.position = UP;
	if (KEYDOWN(40) < 0 || KEYDOWN(83) < 0)
		if (snake.position != UP)
			snake.position = DOWN;
	if (KEYDOWN(37) < 0 || KEYDOWN(65) < 0)
		if (snake.position != RIGHT)
			snake.position = LEFT;
	if (KEYDOWN(39) < 0 || KEYDOWN(68) < 0)
		if (snake.position != LEFT)
			snake.position = RIGHT;
}
void eatfood()
{
	for (int i = 0; i < FOODNUM; i++)
		if (snake.body[0].x == food.foodxy[i].x && snake.body[0].y == food.foodxy[i].y)
		{
			snake.longth++;
			food.foodexist[i] = 0;
		}
}
int snakedie()
{
	if (snake.body[0].x >= WIDTH || snake.body[0].y >= HIGHT || snake.body[0].x < 0 || snake.body[0].y < 0)
	{
		return result();
	}
	for (int i = 1; i < snake.longth; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			return result();
		}
	}
	return 1;
}