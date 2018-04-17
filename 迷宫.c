#include<stdio.h>
#include<string.h>
#include<windows.h>
#define N 15
#define M 3  //关卡数

//全局变量
int level = 0;
int x,y;
int map[M][N][N] = {
	{		   //
	{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,3,1,1,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,1,0,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,1,0,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,1,1,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,0,1,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,0,4,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
},
{
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,3,1,1,1,1,1,0,0,0,0,0,0},
	{1,1,0,1,1,0,0,0,1,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{1,1,0,1,1,0,0,0,1,1,1,1,1,0,0},
	{1,1,0,1,1,0,0,0,0,0,0,0,1,0,0},
	{1,1,0,1,1,0,0,0,0,0,0,0,1,0,0},
	{1,1,0,1,1,0,0,0,0,0,1,1,1,1,0},
	{1,1,0,1,1,0,0,0,0,0,1,0,0,1,0},
	{1,1,0,1,1,0,0,0,0,0,1,0,0,0,0},
	{1,1,0,1,1,1,1,1,1,0,1,0,1,1,0},
	{1,1,0,1,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,4,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
},
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,3,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
	{0,1,1,0,1,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,1,1,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
}
};


//函数声明
void print();
void menu();
void find();
int move();
int Up();
int Down();
int Right();
int Left();


int main(void)
{
	int flag = 0;
	system("color 0A");
	menu();
	while(1)
	{
		flag = move();
		if(flag == 1 || flag == -1)
			return 0;
	}	
	return 0;
}
//找到自己的位置
void find()
{
	
	int i= 0,j = 0;
	for(i = 0;i < N;i++)
	{
		for(j = 0;j < N;j++)
		{
			if(map[level][i][j] == 3)
			{
				x = i;
				y = j;
				break;
			}
		}
	}
}
int move()
{
	int flag = 0;
	while(1)
	{
		flag = 0;
		find();
		print();
		switch(getch())//接收按键输入
		{
		case 'w':flag = Up();break;
		case 'a':flag = Left();break;
		case 's':flag = Down();break;
		case 'd':flag = Right();break;
		case 27:return -1;
		}
		if(flag == 1)
		{
			//通过了
			if(level == M-1)
			{
				MessageBox(0,TEXT("恭喜你完成了所有关卡，圣诞节快乐"),TEXT("恭喜"),NULL);
				return 1;
			}
			else
			{
				MessageBox(0,TEXT("恭喜你通过了这一关"),TEXT("恭喜"),NULL);
				level ++;
			}
		}
	}
}
int Up()
{
	if(x != 0)
	{
		if(map[level][x-1][y] == 1)//可走
		{
			map[level][x-1][y] = 3;
			map[level][x][y] = 1;
		}
		else if(map[level][x-1][y] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Down()
{
	if(x != N-1)
	{
		if(map[level][x+1][y] == 1)//可走
		{
			map[level][x+1][y] = 3;
			map[level][x][y] = 1;
		}
		else if(map[level][x+1][y] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Right()
{
	if(y != N-1)
	{
		if(map[level][x][y+1] == 1)//可走
		{
			map[level][x][y+1] = 3;
			map[level][x][y] = 1;
		}
		else if(map[level][x][y+1] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Left()
{
	if(y != 0)
	{
		if(map[level][x][y-1] == 1)//可走
		{
			map[level][x][y-1] = 3;
			map[level][x][y] = 1;
		}
		else if(map[level][x][y-1] == 4)
		{
			return 1;
		}
	}
	return 0;
}
void menu()
{
	char select[10];
	printf("分别用wasd控制人物移动，按Esc退出游戏\n");
	printf("请输入游戏难度(1、2、3):");
	while(1)
	{
		scanf("%s",select);
		if(strlen(select)>1)
		{
			printf("错误输入，请重新输入：");
		}
		else
		{
			if('1' == select[0])
			{
				level = 0;
				break;
			}
			else if('2' == select[0])
			{
				level = 1;
				break;
			}
			else if('3' == select[0])
			{
				level = 2;
				break;
			}
			else
			{
				printf("错误输入，请重新输入：");
			}
		}
	}
	printf("%d\n",level);
}
//打印函数
void print()
{
	int i= 0,j = 0;
	system("cls");
	for(i = 0;i < N;i++)
	{
		for(j = 0;j < N;j++)
		{
			if(map[level][i][j] == 0)
				printf("■");
			else if(map[level][i][j] == 1)
				printf("  ");
			else if(map[level][i][j] == 3)
				printf("⊙");
			else if(map[level][i][j] == 4)
				printf("☆");
		}
		printf("\n");
	}
}

