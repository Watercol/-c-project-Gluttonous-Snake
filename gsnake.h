#ifndef GSNAKE_H
#define GSNAKE_H
#include <graphics.h>  //��������easyx���ڼ��亯��
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
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
};
struct Snake
{
	int longth;//�ߵĳ���
	point body[BODYMAX];//�ߵ�����
	char position;//����
};
void initsnake();//��ʼ����
void drawsnake();//����
void movesnake();//�ƶ���
void keysnake();//��������
void initfood();//��ʼ��ʳ��
int getexist();//��ȡʳ�����������
void drawfood();//��ʳ��
void eatfood();//��ʳ��
int snakedie();//������
void centerwindow(HWND& m);//���ھ���
int menu();//�˵�
int help();//��������
int result();//��������
#endif
