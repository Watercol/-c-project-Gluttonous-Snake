#include "gsnake.h"
extern Food food;
extern Snake snake;
void centerwindow(HWND& m)
{
	int x, y;
	x = GetSystemMetrics(SM_CXSCREEN); //获取屏幕宽度
	y = GetSystemMetrics(SM_CYSCREEN); //获取屏幕高度
	RECT rect;
	GetWindowRect(m, &rect);
	auto width = rect.right - rect.left;
	auto hight = rect.bottom - rect.top;
	rect.left = x / 2 - width / 2;
	rect.top = y / 2 - hight / 2;
	SetWindowPos(m, HWND_TOP, rect.left, rect.top, width, hight, SWP_SHOWWINDOW);
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
	outtextxy(WIDTH / 2 - 45, HIGHT / 6, "贪吃蛇");
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
	outtextxy(bigleft + 5, HIGHT / 6, "方向控制：使用W,A,S,D 或者方向键");
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
	sprintf(score, "%d", snake.longth - 3);
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