#ifndef GSNAKE_H
#define GSNAKE_H
#include <graphics.h>  //便于引入easyx窗口及其函数
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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
};
struct Snake
{
	int longth;//蛇的长度
	point body[BODYMAX];//蛇的身体
	char position;//方向
};
void initsnake();//初始化蛇
void drawsnake();//画蛇
void movesnake();//移动蛇
void keysnake();//按键控制
void initfood();//初始化食物
int getexist();//获取食物整体存在性
void drawfood();//画食物
void eatfood();//吃食物
int snakedie();//蛇死亡
void centerwindow(HWND& m);//窗口居中
int menu();//菜单
int help();//帮助界面
int result();//结束界面
#endif
