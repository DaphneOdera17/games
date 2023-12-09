#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

void menu()
{
	printf("****************************\n");
	printf("*******   1. play   ********\n");
	printf("*******   0. exit   ********\n");
	printf("****************************\n");
}

void game()
{
	//��Ų��úõ��׵���Ϣ
	char mine[ROWS][COLS] = { 0 };
	//����Ų�����׵���Ϣ
	char show[ROWS][COLS] = { 0 };
	//��ʼ�����������Ϊָ��������
	//mine ������û�в����׵�ʱ���� '0'
	InitBoard(mine, ROWS, COLS, '0');
	//show ������û���Ų��׵�ʱ�򣬶��� '*'
	InitBoard(show, ROWS, COLS, '*');

	//DisplayBoard(mine, ROW, COL);
	//������
	SetMine(mine, ROW, COL);

	DisplayBoard(show, ROW, COL);

	//�Ų���
	FindMine(mine, show, ROW, COL);
}

int main()
{
	//������������������
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("ɨ��\n");
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����\n");
			break;
		}
	} while (input);

	return 0;
}