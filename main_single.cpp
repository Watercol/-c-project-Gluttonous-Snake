#include <graphics.h>  //便于引入easyx窗口及其函数 
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#define KEYDOWN(VK_NONAME) GetKeyState(VK_NONAME)
#define HIGHT 480//窗口高度
#define WIDTH 640//窗口宽度
#define RIGHT 77//方向控制
#define LEFT 75
#define DOWN 80
#define UP 72
#define BODYMAX 100
#define FOODNUM 5
struct point
{
	int x;
	int y;
};
struct Food
{
	point foodxy[FOODNUM];//食物位置
	int foodexist[FOODNUM];//每个食物存在性
	int totalexist;//食物整体存在性
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
int getexist();//获取食物整体存在性
void drawfood();//画食物
void eatfood();//吃食物
int snakedie();//蛇死亡
void centerwindow(HWND &m);//窗口居中
int menu();//菜单
int help();//帮助界面
int result();//结束界面
int main()
{
	srand((unsigned int)time(NULL));//获取随机数种子，使得每一局游戏食物的位置都不相同
	HWND hwnd=initgraph(WIDTH, HIGHT, EX_SHOWCONSOLE);//初始化绘图窗口
	setbkcolor(WHITE);//设置窗口颜色
	centerwindow(hwnd);
	switch (menu())
	{
	case 1:
		break;
	case 0:
		return 0;
	}
	initsnake();
	initfood();
	while (1)
	{
		BeginBatchDraw();//开始批量绘图，使每一帧被同时绘制
		cleardevice();//刷新绘图窗口
		drawsnake();
		drawfood();
		EndBatchDraw();//结束绘图
		if (!getexist())
			initfood();
		eatfood();
		keysnake();
		movesnake();
		if (!snakedie())
			break;
		keysnake();//在movesnake（）前后使用两次keysnake（）来防止漏键，使操作更连贯
		Sleep(60);
	}
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
	snake.position = RIGHT;
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
void keysnake()//利用键盘控制蛇
{
	if (KEYDOWN(38)<0 || KEYDOWN(87)<0)
		if (snake.position != DOWN)
			snake.position = UP;
	if (KEYDOWN(40)<0 || KEYDOWN(83) < 0)
			if (snake.position != UP)
				snake.position = DOWN;
	if (KEYDOWN(37)<0 || KEYDOWN(65) < 0)
			if (snake.position != RIGHT)
				snake.position = LEFT;
	if (KEYDOWN(39)<0 || KEYDOWN(68) < 0)
			if (snake.position != LEFT)
				snake.position = RIGHT;
}
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
void eatfood()
{
	for(int i=0;i<FOODNUM;i++)
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
void centerwindow(HWND &m)
{
	int x, y;
	x = GetSystemMetrics(SM_CXSCREEN); //获取屏幕宽度
	y = GetSystemMetrics(SM_CYSCREEN); //获取屏幕高度
	RECT rect;
	GetWindowRect(m,&rect);
	auto width = rect.right - rect.left;
	auto hight = rect.bottom - rect.top;
	rect.left = x / 2 - width / 2;
	rect.top = y / 2 - hight / 2;
	SetWindowPos(m, HWND_TOP, rect.left, rect.top, width, hight, SWP_SHOWWINDOW);
}
int getexist()
{
	for (int i = 0; i < FOODNUM; i++)
		if (food.foodexist[i] == 1)
			return 1;
	return 0;
}
int menu()
{
	//标题栏的坐标
	int bigtop = HIGHT / 24;
	int bigbottom = HIGHT * 7 / 24;
	int bigleft = WIDTH / 4;
	int bigright = WIDTH * 3 / 4;
	//第一个菜单栏的坐标
	int onetop = HIGHT * 3 / 7;
	int onebottom = HIGHT * 11 / 21;
	int oneleft = WIDTH / 3;
	int oneright = WIDTH * 2 / 3;
	//第二个菜单栏的坐标
	int twotop = HIGHT * 13 / 21;
	int twobottom = HIGHT * 15 / 21;
	int twoleft = WIDTH / 3;
	int tworight = WIDTH * 2 / 3;
	//第三个菜单栏的坐标
	int thrtop = HIGHT * 17 / 21;
	int thrbottom = HIGHT * 19 / 21;
	int thrleft = WIDTH / 3;
	int thrright = WIDTH * 2 / 3;
	setfillcolor(CYAN);//设置菜单栏背景色
	settextstyle(30, 0, "楷体");//设置文字格式
	setbkmode(TRANSPARENT);//去掉文字背景
	BeginBatchDraw();
	cleardevice();
	fillrectangle(bigleft, bigtop, bigright, bigbottom);
	fillrectangle(oneleft, onetop, oneright, onebottom);
	fillrectangle(twoleft, twotop, tworight, twobottom);
	fillrectangle(thrleft, thrtop, thrright, thrbottom);
	outtextxy(WIDTH / 2-45, HIGHT / 6, "贪吃蛇");
	settextstyle(18, 0, "楷体");//设置文字格式
	outtextxy(WIDTH / 2 - 30, HIGHT * 10 / 21, "开始游戏");
	outtextxy(WIDTH / 2 - 30, HIGHT * 14 / 21, "查看帮助");
	outtextxy(WIDTH / 2 - 30, HIGHT * 18 / 21, "退出游戏");
	EndBatchDraw();
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.x > oneleft && m.x<oneright && m.y>onetop && m.y < onebottom)
		{
			setlinecolor(RED);
			rectangle(oneleft, onetop, oneright, onebottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				return 1;
			}
		}
		else if (m.x > twoleft && m.x < tworight && m.y > twotop && m.y < twobottom)
		{
			setlinecolor(RED);
			rectangle(twoleft, twotop, tworight, twobottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				return help();
			}
		}
		else if (m.x > thrleft && m.x < thrright && m.y > thrtop && m.y < thrbottom)
		{
			setlinecolor(RED);
			rectangle(thrleft, thrtop, thrright, thrbottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				return 0;
			}
		}
	}
}
int help()
{
	//标题栏的坐标
	int bigtop = HIGHT / 24;
	int bigbottom = HIGHT * 7 / 24;
	int bigleft = WIDTH / 4;
	int bigright = WIDTH * 3 / 4;
	//第一个菜单栏的坐标
	int onetop = HIGHT * 3 / 7;
	int onebottom = HIGHT * 11 / 21;
	int oneleft = WIDTH / 3;
	int oneright = WIDTH * 2 / 3;
	//第二个菜单栏的坐标
	int twotop = HIGHT * 13 / 21;
	int twobottom = HIGHT * 15 / 21;
	int twoleft = WIDTH / 3;
	int tworight = WIDTH * 2 / 3;
	//第三个菜单栏的坐标
	int thrtop = HIGHT * 17 / 21;
	int thrbottom = HIGHT * 19 / 21;
	int thrleft = WIDTH / 3;
	int thrright = WIDTH * 2 / 3;
	setfillcolor(CYAN);//设置菜单栏背景色
	settextstyle(18, 0, "楷体");//设置文字格式
	setbkmode(TRANSPARENT);//去掉文字背景
	BeginBatchDraw();
	cleardevice();
	fillrectangle(bigleft, bigtop, bigright, bigbottom);
	fillrectangle(oneleft, onetop, oneright, onebottom);
	fillrectangle(thrleft, thrtop, thrright, thrbottom);
	setfillcolor(LIGHTBLUE);
	fillrectangle(twoleft, twotop, tworight, twobottom);
	outtextxy(bigleft+5, HIGHT / 6, "方向控制：使用W,A,S,D 或者方向键");
	outtextxy(WIDTH / 2 - 30, HIGHT * 10 / 21, "开始游戏");
	outtextxy(WIDTH / 2 - 30, HIGHT * 14 / 21, "查看帮助");
	outtextxy(WIDTH / 2 - 30, HIGHT * 18 / 21, "退出游戏");
	EndBatchDraw();
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.x > oneleft && m.x<oneright && m.y>onetop && m.y < onebottom)
		{
			setlinecolor(RED);
			rectangle(oneleft, onetop, oneright, onebottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				return 1;
			}
		}
		else if (m.x > thrleft && m.x < thrright && m.y > thrtop && m.y < thrbottom)
		{
			setlinecolor(RED);
			rectangle(thrleft, thrtop, thrright, thrbottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				return 0;
			}
		}
	}
}
int result()
{
	//标题栏的坐标
	int bigtop = HIGHT / 24;
	int bigbottom = HIGHT * 7 / 24;
	int bigleft = WIDTH / 4;
	int bigright = WIDTH * 3 / 4;
	//第一个菜单栏的坐标
	int onetop = HIGHT * 3 / 7;
	int onebottom = HIGHT * 11 / 21;
	int oneleft = WIDTH / 3;
	int oneright = WIDTH * 2 / 3;
	//第二个菜单栏的坐标
	int twotop = HIGHT * 13 / 21;
	int twobottom = HIGHT * 15 / 21;
	int twoleft = WIDTH / 3;
	int tworight = WIDTH * 2 / 3;
	//第三个菜单栏的坐标
	int thrtop = HIGHT * 17 / 21;
	int thrbottom = HIGHT * 19 / 21;
	int thrleft = WIDTH / 3;
	int thrright = WIDTH * 2 / 3;
	setfillcolor(CYAN);//设置菜单栏背景色
	settextstyle(30, 0, "楷体");//设置文字格式
	setbkmode(TRANSPARENT);//去掉文字背景
	BeginBatchDraw();
	cleardevice();
	fillrectangle(bigleft, bigtop, bigright, bigbottom);
	fillrectangle(oneleft, onetop, oneright, onebottom);
	fillrectangle(twoleft, twotop, tworight, twobottom);
	fillrectangle(thrleft, thrtop, thrright, thrbottom);
	outtextxy(WIDTH / 2 - 145, HIGHT / 6, "本次得分：");
	settextstyle(40, 0, "楷体");
	char score[4] = { 0 };
#pragma warning(suppress : 4996)//用于忽视visual studio编译器对sprintf（）函数的报警，其他编译器可删除
	sprintf(score, "%d", snake.longth-3);
	outtextxy(WIDTH / 2, HIGHT / 6, score);
	settextstyle(18, 0, "楷体");//设置文字格式
	outtextxy(WIDTH / 2 - 30, HIGHT * 10 / 21, "重新开始");
	outtextxy(WIDTH / 2 - 30, HIGHT * 14 / 21, "查看帮助");
	outtextxy(WIDTH / 2 - 30, HIGHT * 18 / 21, "退出游戏");
	EndBatchDraw();
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.x > oneleft && m.x<oneright && m.y>onetop && m.y < onebottom)
		{
			setlinecolor(RED);
			rectangle(oneleft, onetop, oneright, onebottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				initsnake();
				initfood();
				return 1;
			}
		}
		else if (m.x > twoleft && m.x < tworight && m.y > twotop && m.y < twobottom)
		{
			setlinecolor(RED);
			rectangle(twoleft, twotop, tworight, twobottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				initsnake();
				initfood();
				return help();
			}
		}
		else if (m.x > thrleft && m.x < thrright && m.y > thrtop && m.y < thrbottom)
		{
			setlinecolor(RED);
			rectangle(thrleft, thrtop, thrright, thrbottom);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				return 0;
			}
		}
	}
}