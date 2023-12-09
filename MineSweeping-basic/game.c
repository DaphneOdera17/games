#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	printf("----------------------------扫雷游戏----------------------------\n");
	//打印列号
	for (int j = 0; j <= col; j++)
		printf("%d ", j);
	puts("");
	for (int i = 1; i <= row; i++)
	{
		//打印行号
		printf("%d ", i);
		for (int j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		puts("");
	}
}

void SetMine(char board[ROWS][COLS], int row, int col)
{
	//需要布置的雷的总数
	int count = EASY_COUNT;
	while (count)
	{
		//横坐标范围和纵坐标范围都是 1 ~ 9
		int x = rand() % row + 1;
		int y = rand() % col + 1;

		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

int get_mine_count(char board[ROWS][COLS], int x, int y)
{
	int dx[3] = {-1, 0, 1};
	int dy[3] = { -1, 0, 1 };
	int sum = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(dx[i] != dy[j] && dx[i] != '0')
			sum += board[x + dx[i]][y + dy[j]] - '0';
		}
	}
	return sum;
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0, y = 0;
	//找到非雷的个数
	int win = 0;
	
	while (win < row * col - EASY_COUNT)
	{
		printf("请输入要排查的坐标:>\n");

		scanf("%d %d", &x, &y);

		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] != '*')
			{
				puts("该坐标被排查过了，不能重复排查");
			}
			else
			{
				//如果是雷
				if (mine[x][y] == '1')
				{
					printf("很遗憾，你被炸死了\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
				else //如果不是雷
				{
					win++;
					///统计 mine 数组 (x,y) 坐标周围有多少个雷
					int count = get_mine_count(mine, x, y);
					//将雷的个数转换成数字字符
					show[x][y] = count + '0';
					DisplayBoard(show, ROW, COL);
				}
			}
			
		}
		else
		{
			puts("输入坐标非法，请重新输入");
		}
	}
	
	if (win == row * col - EASY_COUNT)
	{
		puts("恭喜你,排雷成功");
		DisplayBoard(show, ROW, COL);
	}
}