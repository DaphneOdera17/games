#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void menu()
{
	printf("*****************************\n");
	printf("****** 1.play 0.exit ********\n");
	printf("*****************************\n");
}

void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	//��ʼ������
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//�������
		PlayerMove(board, ROW, COL);
		//�ж���Ӯ
		ret = IsWin(board, ROW, COL);
		//�����Ϸ����
		if (ret != 'C')
			break;
		DisplayBoard(board, ROW, COL);
		//��������
		ComputerMove(board, ROW, COL);
		//�ж���Ӯ
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
		DisplayBoard(board, ROW, COL);
	}
	if (ret == '*')
		puts("���Ӯ");
	else if (ret == '#')
		puts("����Ӯ");
	else if(ret == 'Q')
		puts("ƽ��");
	DisplayBoard(board, ROW, COL);
	puts("��Ϸ����");
}

int main()
{
	//������������������
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����!\n");
			break;
		}
	} while (input);

	return 0;
}