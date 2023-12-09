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
	printf("----------------------------ɨ����Ϸ----------------------------\n");
	//��ӡ�к�
	for (int j = 0; j <= col; j++)
		printf("%d ", j);
	puts("");
	for (int i = 1; i <= row; i++)
	{
		//��ӡ�к�
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
	//��Ҫ���õ��׵�����
	int count = EASY_COUNT;
	while (count)
	{
		//�����귶Χ�������귶Χ���� 1 ~ 9
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
	//�ҵ����׵ĸ���
	int win = 0;
	
	while (win < row * col - EASY_COUNT)
	{
		printf("������Ҫ�Ų������:>\n");

		scanf("%d %d", &x, &y);

		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] != '*')
			{
				puts("�����걻�Ų���ˣ������ظ��Ų�");
			}
			else
			{
				//�������
				if (mine[x][y] == '1')
				{
					printf("���ź����㱻ը����\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
				else //���������
				{
					win++;
					///ͳ�� mine ���� (x,y) ������Χ�ж��ٸ���
					int count = get_mine_count(mine, x, y);
					//���׵ĸ���ת���������ַ�
					show[x][y] = count + '0';
					DisplayBoard(show, ROW, COL);
				}
			}
			
		}
		else
		{
			puts("��������Ƿ�������������");
		}
	}
	
	if (win == row * col - EASY_COUNT)
	{
		puts("��ϲ��,���׳ɹ�");
		DisplayBoard(show, ROW, COL);
	}
}