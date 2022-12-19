#include <graphics.h>  //��������easyx���ڼ��亯�� 
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#define KEYDOWN(VK_NONAME) GetKeyState(VK_NONAME)
#define HIGHT 480//���ڸ߶�
#define WIDTH 640//���ڿ��
#define right 77//�������
#define left 75
#define down 80
#define up 72
#define BODYMAX 100
struct point
{
	int x;
	int y;
};
struct Food
{
	point foodxy;//ʳ��λ��
	int foodexist;//ʳ�������
}food;
struct Snake
{
	int longth;//�ߵĳ���
	point body[BODYMAX];//�ߵ�����
	char position;//����
}snake;
void initsnake();//��ʼ����
void drawsnake();//����
void movesnake();//�ƶ���
void keysnake();//��������
void initfood();//��ʼ��ʳ��
void drawfood();//��ʳ��
void eatfood();//��ʳ��
int snakedie();//������
int main()
{
	srand((unsigned int)time(NULL));
	HWND hwnd=initgraph(WIDTH, HIGHT, EX_SHOWCONSOLE);//��ʼ����ͼ����
	setbkcolor(WHITE);//���ô�����ɫ
	initsnake();
	while (1)
	{
		BeginBatchDraw();//��ʼ������ͼ��ʹÿһ֡��ͬʱ����
		cleardevice();//ˢ�»�ͼ����
		drawsnake();
		drawfood();
		EndBatchDraw();//������ͼ
		movesnake();
		if (food.foodexist == 0)
			initfood();
		eatfood();
		if (snakedie())
			break;
		keysnake();
		Sleep(50);
	}
	getchar();
	closegraph();
	return 0;
}
void initsnake()//��ʼ�ߵĳ���Ϊ3,ÿ�μ��Ϊ10
{
	snake.body[2].x = 300;
	snake.body[2].y = 240;
	snake.body[1].x = 310;
	snake.body[1].y = 240;
	snake.body[0].x = 320;
	snake.body[0].y = 240;
	snake.longth = 3;
	snake.position = right;
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
	case right:
		snake.body[0].x += 10;
		break;
	case left:
		snake.body[0].x -= 10;
		break;
	case down:
		snake.body[0].y += 10;
		break;
	case up:
		snake.body[0].y -= 10;
		break;
	default:
		break;
	}
}
void keysnake()//���ü��̿�����
{
	if (KEYDOWN(38)<0 || KEYDOWN(87)<0)
		if (snake.position != down)
			snake.position = up;
	if (KEYDOWN(40)<0 || KEYDOWN(83) < 0)
			if (snake.position != up)
				snake.position = down;
	if (KEYDOWN(37)<0 || KEYDOWN(65) < 0)
			if (snake.position != right)
				snake.position = left;
	if (KEYDOWN(39)<0 || KEYDOWN(68) < 0)
			if (snake.position != left)
				snake.position = right;
}
void initfood()
{
	food.foodxy.x = rand() % 64*10;
	food.foodxy.y = rand() % 48*10;
	food.foodexist = 1;//��ֹ��������ʳ��
	//���ʳ�������������
	for (int i = 1; i < snake.longth; i++)
	{
		if (food.foodxy.x == snake.body[i].x && food.foodxy.y == snake.body[i].y)
		{
			food.foodxy.x = rand() % 640;
			food.foodxy.y = rand() % 480;
		}
	}
}
void drawfood()//��ʳ��
{
	setlinecolor(WHITE);
	setfillcolor(RED);
	fillrectangle(food.foodxy.x, food.foodxy.y, food.foodxy.x + 10, food.foodxy.y + 10);
}
void eatfood()
{
	if (snake.body[0].x == food.foodxy.x && snake.body[0].y == food.foodxy.y)
	{
		snake.longth++;
		food.foodexist = 0;
	}
}
int snakedie()
{
	if (snake.body[0].x >= WIDTH || snake.body[0].y >= HIGHT || snake.body[0].x < 0 || snake.body[0].y < 0)
	{
		MessageBox(NULL, "��Ϸ����", "ײǽ", MB_OK);//����һ������
		return 1;
	}
	for (int i = 1; i < snake.longth; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			MessageBox(NULL, "��Ϸ����", "ײ�Լ�", MB_OK);
			return 1;
		}
	}
	return 0;
}