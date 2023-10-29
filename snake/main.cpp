#include <iostream>
#include "easyx/include/easyx.h"
#include "easyx/include/graphics.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

#define SNAKE_NUM 500 //蛇的最大节数

int sum;

enum DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

//蛇的结构
struct Snake
{
    int size; //蛇的节数
    int dir; //蛇的方向
    int speed; //蛇的移动速度
    POINT coor[SNAKE_NUM]; //坐标
}snake;

struct Food
{
    int x;
    int y;
    int r; //食物大小
    bool flag; //食物是否被吃
    DWORD color; //食物颜色
}food;

//数据的初始化
void GameInit()
{

    //init 初始化 graph 图形窗口 SHOWCONSOLE 显示控制台
    initgraph(640, 480/*, SHOWCONSOLE*/);

    //设置随机数种子
    srand(GetTickCount());

    //初始化蛇 一开始有三节蛇
    snake.size = 3;
    snake.speed = 10;
    snake.dir = RIGHT;
    for(int i = snake.size - 1; i >= 0; i --)
    {
        snake.coor[i].x = 10 * (snake.size - 1 - i) + 20;
        snake.coor[i].y = 10;
    }

    //初始化食物
    //rand() 随机产生一个整数，如果没有设置随机数种子，每次产生的都是固定的整数
    food.x = rand() % 640;
    food.y = rand() % 480;
    food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
    food.r = rand() % 10 + 5;
    food.flag = true;
}

void GameDraw()
{
    //防止闪屏 双缓冲绘图
    BeginBatchDraw();

    //设置背景颜色
    setbkcolor(RGB(28, 115, 119));
    cleardevice(); //清空绘图设备才可以

    //设置蛇的颜色
    setfillcolor(GREEN);
    //绘制蛇
    for(int i = 0; i < snake.size; i ++)
        solidcircle(snake.coor[i].x, snake.coor[i].y, 5);

    //绘制食物
    if(food.flag)
        solidcircle(food.x, food.y, food.r);
    EndBatchDraw();
}

//移动蛇
void snakeMove()
{
    for(int i = snake.size - 1; i > 0; i --)
    {
        snake.coor[i] = snake.coor[i - 1];
    }
    //移动会让坐标进行改变
    switch(snake.dir)
    {
        case UP: snake.coor[0].y -= snake.speed;
            //超出了上面的边界
            if(snake.coor[0].y - 5 <= 0)
                snake.coor[0].y = 480;
            break;
        case DOWN: snake.coor[0].y += snake.speed;
            if(snake.coor[0].y + 5 >= 480)
                snake.coor[0].y = 0;
            break;
        case LEFT: snake.coor[0].x -= snake.speed;
            if(snake.coor[0].x - 5 <= 0)
                snake.coor[0].x = 640;
            break;
        case RIGHT: snake.coor[0].x += snake.speed;
            if(snake.coor[0].x + 5 >= 640)
                snake.coor[0].x = 0;
            break;
    }
}

//通过按键改变蛇的移动方向
void keyControl()
{
    //判断有没有按键
    //如果有按键就返回 真
    if(_kbhit())
    {
        switch(_getch())
        {
            //72 80 75 77 上下左右键值
            case 'w': case 'W': case 72:
                if(snake.dir != DOWN)
                    snake.dir = UP;
                break;
            case 's': case 'S': case 80:
                if(snake.dir != UP)
                    snake.dir = DOWN;
                break;
            case 'a': case 'A': case 75:
                if(snake.dir != RIGHT)
                snake.dir = LEFT; break;
            case 'd': case 'D': case 77:
                if(snake.dir != LEFT)
                    snake.dir = RIGHT;
                break;
            default: break;
        }
    }
}

//游戏暂停
void stop()
{
    if(_kbhit())
    {
        if(_getch() == ' ')
        {
            while(1)
            {
                if(_getch() == ' ')
                    break;
            }
        }
    }
}

void EatFood()
{
    if(food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
    {
        food.flag = false;
        snake.size ++;
    }

    //如果食物消失，则重新生成一个
    if(!food.flag)
    {
        food.x = rand() % 640;
        food.y = rand() % 480;
        food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
        food.r = rand() % 10 + 5;
        food.flag = true;
    }

    //吃一个食物，分数增加
    sum += 5;
}

int main()
{
    GameInit();

    while(1)
    {
        GameDraw();
        snakeMove();
        stop();
        keyControl();
        EatFood();
        Sleep(50);
    }
    return 0;
}
