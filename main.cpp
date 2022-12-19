#include <graphics.h>  //便于引入easyx窗口及其函数 
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#define KEYDOWN(VK_NONAME) GetKeyState(VK_NONAME)
#define HIGHT 480//窗口高度
#define WIDTH 640//窗口宽度
#define right 77//方向控制
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
	point foodxy;//食物位置
	int foodexist;//食物存在性
}food;
struct Snake
{
	int longth;//蛇的长度
	point body[BODYMAX];//蛇的身体
	char position;//方向
}snake;
void initsnake();//初始化蛇
void drawsnake();//画蛇
void movesnake();//移动蛇
void keysnake();//按键控制
void initfood();//初始化食物
void drawfood();//画食物
void eatfood();//吃食物
int snakedie();//蛇死亡
int main()
{
	srand((unsigned int)time(NULL));
	HWND hwnd=initgraph(WIDTH, HIGHT, EX_SHOWCONSOLE);//初始化绘图窗口
	setbkcolor(WHITE);//设置窗口颜色
	initsnake();
	while (1)
	{
		BeginBatchDraw();//开始批量绘图，使每一帧被同时绘制
		cleardevice();//刷新绘图窗口
		drawsnake();
		drawfood();
		EndBatchDraw();//结束绘图
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
void initsnake()//初始蛇的长度为3,每段间隔为10
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
void drawsnake()//画蛇
{
	for (int i = 0; i < snake.longth; i++)
	{
		setlinecolor(BLACK);//边框颜色
		setfillcolor(CYAN);//填充颜色
		fillrectangle(snake.body[i].x, snake.body[i].y, snake.body[i].x + 10, snake.body[i].y + 10);
	}
}
void movesnake()//蛇的移动
{
	//先讨论除了蛇头之外的身体，令每一节都等于前一节的坐标即可实现移动
	for (int i = snake.longth - 1; i > 0; i--)
	{
		snake.body[i].x = snake.body[i - 1].x;
		snake.body[i].y = snake.body[i - 1].y;
	}
	//再处理蛇头的移动
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
void keysnake()//利用键盘控制蛇
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
	food.foodexist = 1;//防止反复出现食物
	//如果食物出现在蛇身上
	for (int i = 1; i < snake.longth; i++)
	{
		if (food.foodxy.x == snake.body[i].x && food.foodxy.y == snake.body[i].y)
		{
			food.foodxy.x = rand() % 640;
			food.foodxy.y = rand() % 480;
		}
	}
}
void drawfood()//画食物
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
		MessageBox(NULL, "游戏结束", "撞墙", MB_OK);//弹出一个窗口
		return 1;
	}
	for (int i = 1; i < snake.longth; i++)
	{
		if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
		{
			MessageBox(NULL, "游戏结束", "撞自己", MB_OK);
			return 1;
		}
	}
	return 0;
}