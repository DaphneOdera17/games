#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void InitBoard(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j < col - 1)
				printf(" %c |", board[i][j]);
			else
				printf(" %c ", board[i][j]);
		}
		puts("");
		if (i < row - 1)
		{
			for (int j = 0; j < col; j++)
			{
				if (j < col - 1)
					printf("---|");
				else
					printf("---");
			}
			puts("");
		}
	}	
}

void PlayerMove(char board[ROW][COL], int row, int col)
{
	printf("玩家下棋:>\n");
	
	int x = 0, y = 0;
	while (1)
	{
		printf("请输入坐标:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//该位置可以下棋
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("坐标被占用，请选择其他位置\n");
			}
		}
		else
		{
			printf("坐标输入不合法,请重新输入\n");
		}
	}
	
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑下棋:>\n");
	
	int x = 0;
	int y = 0;

	while (1)
	{
		x = rand() % row; //0~2
		y = rand() % col; //0~2
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
	
}

//如果满了返回 1，不满的话返回 0
int IsFull(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	
	return 1;
}

char IsWin(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j + 2 < col && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 1] != ' ')
				return board[i][j + 1];
			else if (i + 2 < row && board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 1][j] != ' ')
				return board[i + 1][j];
			else if (i == j && i + 2 < row && j + 2 < col && board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 1][j + 1] != ' ')
				return board[i + 1][j + 1];
			else if (i - 2 >= 0 && j + 2 < col && board[i][j] == board[i - 1][j + 1] && board[i - 1][j + 1] == board[i - 2][j + 2] && board[i - 1][j + 1] != ' ')
				return board[i - 1][j + 1];
		}
	}

	int count = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				count++;
		}
	}
	printf("%d\n", count);

	//没有人赢，平局（如果棋盘满了）
	if(IsFull(board, row, col))
	{
		return 'Q';
	}

	return 'C';

}