
# 贪吃蛇实验报告

```c
//
//  snake_move_eat.c
//  Created by XinJ Wang, 17309084

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define HEAD 'H'
#define BODY 'X'
#define BLANK ' '
#define FOOD '$'
#define WALL '#'

//WALL -2
//FOOD -1
//HEAD 1
//BODY >1，蛇尾等于snake_length
//BLANK 0
int map[SIZE][SIZE] = {
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
    {-2, 3, 2, 1, 0, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, 0, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, 0, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, 0, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, -1, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, 0, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, 0, 0, 0, 0, 0, -2},
    {-2, 0, 0, 0, 0, 0, 0, 0, 0, -2},
    {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
};

int snake_length = 3;

//pre:输入字符赋值给cmd，cmd是A,D,W,s,a,d,w,s中的一个字符
//post:snake根据cmd移动，若撞墙、撞到自己，则失败返回0
int move(char cmd);

//post:根据map打印界面
void printMap();

int main()
{
    char cmd;
    printMap();
    while (1)
    {
        cmd = getchar();
        if (cmd == '\n')
            continue;

        if (move(cmd))
            printMap();
        else
        {
            printf("Game Over!\n");
            break;
        }
    }

    getchar();
    return 0;
}

int move(char cmd)
{
    cmd = toupper(cmd);
    int row_head, col_head, i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            //tail
            if (map[i][j] == snake_length)
                map[i][j] = 0;
            //body
            else if (map[i][j] > 1)
                map[i][j]++;
            //head
            else if (map[i][j] == 1)
            {
                map[i][j]++;
                switch (cmd)
                {
                case 'A':
                    row_head = i;
                    col_head = j - 1;
                    break;
                case 'D':
                    row_head = i;
                    col_head = j + 1;
                    break;
                case 'W':
                    row_head = i - 1;
                    col_head = j;
                    break;
                case 'S':
                    row_head = i + 1;
                    col_head = j;
                    break;
                default:
                    break;
                }
            }
        }
    }

    //eat food
    if (map[row_head][col_head] == -1)
    {
        map[row_head][col_head] = 1;
        snake_length++;
        //generate new food
        while (1)
        {
            i = rand() % SIZE;
            j = rand() % SIZE;
            if (map[i][j] == 0)
            {
                map[i][j] = -1;
                break;
            }
        }
    }
    //move blank
    else if (map[row_head][col_head] == 0)
    {
        map[row_head][col_head] = 1;
    }
    //run into wall or body, game over
    else
        return 0;

    return 1;
}

void printMap()
{
    int i, j;
    system("cls");
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (map[i][j] == -2)
                printf("%c", WALL);
            else if (map[i][j] == 0)
                printf("%c", BLANK);
            else if (map[i][j] == -1)
                printf("%c", FOOD);
            else if (map[i][j] == 1)
                printf("%c", HEAD);
            else if (map[i][j] > 1)
                printf("%c", BODY);
        }
        printf("\n");
    }
}
```