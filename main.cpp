#include "gsnake.h"
#include <windows.h>
Food food;
Snake snake;
int main()
{
	srand((unsigned int)time(NULL));//��ȡ��������ӣ�ʹ��ÿһ����Ϸʳ���λ�ö�����ͬ
	HWND hwnd=initgraph(WIDTH, HIGHT, EX_SHOWCONSOLE);//��ʼ����ͼ����
	setbkcolor(WHITE);//���ô�����ɫ
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
		BeginBatchDraw();//��ʼ������ͼ��ʹÿһ֡��ͬʱ����
		cleardevice();//ˢ�»�ͼ����
		drawsnake();
		drawfood();
		EndBatchDraw();//������ͼ
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