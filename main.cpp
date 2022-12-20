#include "gsnake.h"
#include <windows.h>
Food food;
Snake snake;
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
		Sleep(60);
	}
	closegraph();
	return 0;
}