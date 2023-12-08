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
	//初始化棋盘
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		//如果游戏结束
		if (ret != 'C')
			break;
		DisplayBoard(board, ROW, COL);
		//电脑下棋
		ComputerMove(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
		DisplayBoard(board, ROW, COL);
	}
	if (ret == '*')
		puts("玩家赢");
	else if (ret == '#')
		puts("电脑赢");
	else if(ret == 'Q')
		puts("平局");
	DisplayBoard(board, ROW, COL);
	puts("游戏结束");
}

int main()
{
	//设置随机数的生成起点
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择\n");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误!\n");
			break;
		}
	} while (input);

	return 0;
}