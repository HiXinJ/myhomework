
# 智能蛇实验报告


## 一、实验目的

了解 算法 与 “智能” 的关系
通过算法赋予蛇智能
了解 Linux IO 设计的控制

## 二、实验环境
Linux Ubuntu, C99

## 三、编写智能算法
编写人工智能程序，使得 snake 每秒自动走一步。

1、程序要求

1、程序要求

1. 请修改初始化字符矩阵，或者通过文件读入地图。地图中有一些你设定的障碍物（墙）
2. 请实现如下算法决定蛇行走的方向
3. 思考：一个长度为5的障碍物能困死该自动跑的蛇吗？

```
    // Hx,Hy: 头的位置
    // Fx,Fy：食物的位置
	function whereGoNext(Hx,Hy,Fx,Fy) {
	// 用数组movable[3]={“a”,”d”,”w”,”s”} 记录可走的方向
	// 用数组distance[3]={0,0,0,0} 记录离食物的距离
	// 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
	//     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
	//           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
	// 选择distance中存最小距离的下标p，注意最小距离不能是9999
	// 返回 movable[p]
	}
```

2、智能蛇的程序框架
```
	输出字符矩阵
	WHILE not 游戏结束 DO
        wait(time)
		ch＝whereGoNext(Hx,Hy,Fx,Fy)
		CASE ch DO
		‘A’:左前进一步，break 
		‘D’:右前进一步，break    
		‘W’:上前进一步，break    
		‘S’:下前进一步，break    
		END CASE
		输出字符矩阵
	END WHILE
	输出 Game Over!!! 
```

## 四、C语言实现

1、决策函数
```c
char whereGoNext(int Hx, int Hy, int Fx, int Fy)
{
    char movable[4] = {'a', 'd', 'w', 's'};
    int distance[4] = {0, 0, 0, 0};
    distance[0] = map[Hy][Hx - 1] == 0 || map[Hy][Hx - 1] == -1 ? abs(Fx - (Hx - 1)) + abs(Fy - Hy) : 9999;
    distance[1] = map[Hy][Hx + 1] == 0 || map[Hy][Hx + 1] == -1 ? abs(Fx - (Hx + 1)) + abs(Fy - Hy) : 9999;
    distance[2] = map[Hy - 1][Hx] == 0 || map[Hy - 1][Hx] == -1 ? abs(Fx - Hx) + abs(Fy - (Hy - 1)) : 9999;
    distance[3] = map[Hy + 1][Hx] == 0 || map[Hy + 1][Hx] == -1 ? abs(Fx - Hx) + abs(Fy - (Hy + 1)) : 9999;
    int i, min_index = 0;
    for (i = 0; i < 4; i++)
    {
        if (distance[i] < distance[min_index])
            min_index = i;
    }
    return movable[min_index];
}

```

2、移动函数
稍加修改上一版本贪吃蛇中的move，计算新的食物位置。

```c
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
                //计算新的食物位置Fx,Fy
                Fx = j;
                Fy = i;
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
```

3、输出函数
```c
void printMap()
{
    int i, j;
    system("clear");
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





## 完整代码

```c
//
//  snake_move_eat.c
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int Hx = 3, Hy = 1, Fx = 4, Fy = 5;

char whereGoNext(int Hx, int Hy, int Fx, int Fy);

int main()
{
    //srand(time(NULL));
    char cmd;
    printMap();
    while (1)
    {
        cmd = whereGoNext(Hx, Hy, Fx, Fy);

        switch (cmd)
        {
        case 'a':
            Hx--;
            break;
        case 'd':
            Hx++;
            break;
        case 'w':
            Hy--;
            break;
        case 's':
            Hy++;
            break;
        }
        // cmd = getchar();
        if (cmd == '\n')
            continue;

        if (move(cmd))
            printMap();
        else
        {
            printf("Game Over!\n");
            break;
        }
        sleep(1);
    }

    getchar();
    return 0;
}

/* function whereGoNext(Hx,Hy,Fx,Fy) {
	// 用数组movable[3]={“a”,”d”,”w”,”s”} 记录可走的方向
	// 用数组distance[3]={0,0,0,0} 记录离食物的距离
	// 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
	//     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
	//           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
	// 选择distance中存最小距离的下标p，注意最小距离不能是9999
	// 返回 movable[p]
	} */
char whereGoNext(int Hx, int Hy, int Fx, int Fy)
{
    char movable[4] = {'a', 'd', 'w', 's'};
    int distance[4] = {0, 0, 0, 0};
    distance[0] = map[Hy][Hx - 1] == 0 || map[Hy][Hx - 1] == -1 ? abs(Fx - (Hx - 1)) + abs(Fy - Hy) : 9999;
    distance[1] = map[Hy][Hx + 1] == 0 || map[Hy][Hx + 1] == -1 ? abs(Fx - (Hx + 1)) + abs(Fy - Hy) : 9999;
    distance[2] = map[Hy - 1][Hx] == 0 || map[Hy - 1][Hx] == -1 ? abs(Fx - Hx) + abs(Fy - (Hy - 1)) : 9999;
    distance[3] = map[Hy + 1][Hx] == 0 || map[Hy + 1][Hx] == -1 ? abs(Fx - Hx) + abs(Fy - (Hy + 1)) : 9999;
    int i, min_index = 0;
    for (i = 0; i < 4; i++)
    {
        if (distance[i] < distance[min_index])
            min_index = i;
    }
    return movable[min_index];
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
                Fx = j;
                Fy = i;
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
  system("clear");
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