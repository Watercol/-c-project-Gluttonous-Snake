#include <graphics.h>  //��������easyx���ڼ��亯�� 
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#define KEYDOWN(VK_NONAME) GetKeyState(VK_NONAME)
#define HIGHT 480//���ڸ߶�
#define WIDTH 640//���ڿ��
#define RIGHT 77//�������
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
	point foodxy[FOODNUM];//ʳ��λ��
	int foodexist[FOODNUM];//ÿ��ʳ�������
	int totalexist;//ʳ�����������
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
int getexist();//��ȡʳ�����������
void drawfood();//��ʳ��
void eatfood();//��ʳ��
int snakedie();//������
void centerwindow(HWND &m);//���ھ���
int menu();//�˵�
int help();//��������
int result();//��������
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
		keysnake();//��movesnake����ǰ��ʹ������keysnake��������ֹ©����ʹ����������
		Sleep(60);
	}
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
		food.foodexist[i] = 1;//��ֹ��������ʳ��
		//���ʳ�������������
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
void drawfood()//��ʳ��
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
	x = GetSystemMetrics(SM_CXSCREEN); //��ȡ��Ļ���
	y = GetSystemMetrics(SM_CYSCREEN); //��ȡ��Ļ�߶�
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
	//������������
	int bigtop = HIGHT / 24;
	int bigbottom = HIGHT * 7 / 24;
	int bigleft = WIDTH / 4;
	int bigright = WIDTH * 3 / 4;
	//��һ���˵���������
	int onetop = HIGHT * 3 / 7;
	int onebottom = HIGHT * 11 / 21;
	int oneleft = WIDTH / 3;
	int oneright = WIDTH * 2 / 3;
	//�ڶ����˵���������
	int twotop = HIGHT * 13 / 21;
	int twobottom = HIGHT * 15 / 21;
	int twoleft = WIDTH / 3;
	int tworight = WIDTH * 2 / 3;
	//�������˵���������
	int thrtop = HIGHT * 17 / 21;
	int thrbottom = HIGHT * 19 / 21;
	int thrleft = WIDTH / 3;
	int thrright = WIDTH * 2 / 3;
	setfillcolor(CYAN);//���ò˵�������ɫ
	settextstyle(30, 0, "����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);//ȥ�����ֱ���
	BeginBatchDraw();
	cleardevice();
	fillrectangle(bigleft, bigtop, bigright, bigbottom);
	fillrectangle(oneleft, onetop, oneright, onebottom);
	fillrectangle(twoleft, twotop, tworight, twobottom);
	fillrectangle(thrleft, thrtop, thrright, thrbottom);
	outtextxy(WIDTH / 2-45, HIGHT / 6, "̰����");
	settextstyle(18, 0, "����");//�������ָ�ʽ
	outtextxy(WIDTH / 2 - 30, HIGHT * 10 / 21, "��ʼ��Ϸ");
	outtextxy(WIDTH / 2 - 30, HIGHT * 14 / 21, "�鿴����");
	outtextxy(WIDTH / 2 - 30, HIGHT * 18 / 21, "�˳���Ϸ");
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
	//������������
	int bigtop = HIGHT / 24;
	int bigbottom = HIGHT * 7 / 24;
	int bigleft = WIDTH / 4;
	int bigright = WIDTH * 3 / 4;
	//��һ���˵���������
	int onetop = HIGHT * 3 / 7;
	int onebottom = HIGHT * 11 / 21;
	int oneleft = WIDTH / 3;
	int oneright = WIDTH * 2 / 3;
	//�ڶ����˵���������
	int twotop = HIGHT * 13 / 21;
	int twobottom = HIGHT * 15 / 21;
	int twoleft = WIDTH / 3;
	int tworight = WIDTH * 2 / 3;
	//�������˵���������
	int thrtop = HIGHT * 17 / 21;
	int thrbottom = HIGHT * 19 / 21;
	int thrleft = WIDTH / 3;
	int thrright = WIDTH * 2 / 3;
	setfillcolor(CYAN);//���ò˵�������ɫ
	settextstyle(18, 0, "����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);//ȥ�����ֱ���
	BeginBatchDraw();
	cleardevice();
	fillrectangle(bigleft, bigtop, bigright, bigbottom);
	fillrectangle(oneleft, onetop, oneright, onebottom);
	fillrectangle(thrleft, thrtop, thrright, thrbottom);
	setfillcolor(LIGHTBLUE);
	fillrectangle(twoleft, twotop, tworight, twobottom);
	outtextxy(bigleft+5, HIGHT / 6, "������ƣ�ʹ��W,A,S,D ���߷����");
	outtextxy(WIDTH / 2 - 30, HIGHT * 10 / 21, "��ʼ��Ϸ");
	outtextxy(WIDTH / 2 - 30, HIGHT * 14 / 21, "�鿴����");
	outtextxy(WIDTH / 2 - 30, HIGHT * 18 / 21, "�˳���Ϸ");
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
	//������������
	int bigtop = HIGHT / 24;
	int bigbottom = HIGHT * 7 / 24;
	int bigleft = WIDTH / 4;
	int bigright = WIDTH * 3 / 4;
	//��һ���˵���������
	int onetop = HIGHT * 3 / 7;
	int onebottom = HIGHT * 11 / 21;
	int oneleft = WIDTH / 3;
	int oneright = WIDTH * 2 / 3;
	//�ڶ����˵���������
	int twotop = HIGHT * 13 / 21;
	int twobottom = HIGHT * 15 / 21;
	int twoleft = WIDTH / 3;
	int tworight = WIDTH * 2 / 3;
	//�������˵���������
	int thrtop = HIGHT * 17 / 21;
	int thrbottom = HIGHT * 19 / 21;
	int thrleft = WIDTH / 3;
	int thrright = WIDTH * 2 / 3;
	setfillcolor(CYAN);//���ò˵�������ɫ
	settextstyle(30, 0, "����");//�������ָ�ʽ
	setbkmode(TRANSPARENT);//ȥ�����ֱ���
	BeginBatchDraw();
	cleardevice();
	fillrectangle(bigleft, bigtop, bigright, bigbottom);
	fillrectangle(oneleft, onetop, oneright, onebottom);
	fillrectangle(twoleft, twotop, tworight, twobottom);
	fillrectangle(thrleft, thrtop, thrright, thrbottom);
	outtextxy(WIDTH / 2 - 145, HIGHT / 6, "���ε÷֣�");
	settextstyle(40, 0, "����");
	char score[4] = { 0 };
#pragma warning(suppress : 4996)//���ں���visual studio��������sprintf���������ı�����������������ɾ��
	sprintf(score, "%d", snake.longth-3);
	outtextxy(WIDTH / 2, HIGHT / 6, score);
	settextstyle(18, 0, "����");//�������ָ�ʽ
	outtextxy(WIDTH / 2 - 30, HIGHT * 10 / 21, "���¿�ʼ");
	outtextxy(WIDTH / 2 - 30, HIGHT * 14 / 21, "�鿴����");
	outtextxy(WIDTH / 2 - 30, HIGHT * 18 / 21, "�˳���Ϸ");
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