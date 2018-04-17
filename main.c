#include<stdio.h>
#include<windows.h>
#include<time.h>
#define N 2	//关卡数目
#define M N*50	//地图大小	M*M
int level = 0;//游戏等级
int map[M + 1][M + 1] = { 0 };
int count;//地图大小
int my_x, my_y;//我的位置
char str[2 * (M + 1)*(M + 1)] = { '\0' };

void Initialize(int count);//初始化地图
void print();//打印函数
void find();//找到自己
int move();//控制移动
int Up();//上移
int Down();//下移
int Right();//右移
int Left();//左移
void menu();//菜单，选择难度和大小
int IsHaveNeighbor(int X_index, int Y_index);//判断当前方块处是否有邻居
void Creat_01(int X_index, int Y_index);//第一种创建方法，主干较明显，难度低
void Creat_02(int X_index, int Y_index);//

int main(void)
{
	int flag = 0;
	int s[100][100] = { 0 };
	srand((unsigned)time(NULL));

	system("mode con cols=220 lines=100");
	system("color 0A");
	menu();
	Initialize(count);
	while (1)
	{
		flag = move();
		if (flag == 1 || flag == -1)
			return 0;
	}
	return 0;

	system("pause");
	return 0;
}
int IsHaveNeighbor(int X_index, int Y_index)
{
	int i, j, flag = 0;
	if (level == 0)
	{
		if ((X_index >= 3 && map[X_index - 2][Y_index] == 1) || (X_index < count - 3 && map[X_index + 2][Y_index] == 1) || (Y_index >= 3 && map[X_index][Y_index - 2] == 1) || (Y_index < count - 3 && map[X_index][Y_index + 2] == 1))
			return 1;
		return 0;
	}
	else if (level == 1)
	{
		for (i = 0;i < count;i++)
		{
			for (j = 0;j < count;j++)
			{
				if (map[i][j] == 6)//还存在蓝色方块
				{
					flag++;
				}

			}
		}
		return flag;
	}
}
void Creat_01(int X_index, int Y_index)
{
	int rand_position, x, y, flag = 0;
	x = X_index;
	y = Y_index;
	//如果四个方向都没有了，返回上一步，否则，继续
	while (1)
	{
		flag = 0;
		flag = IsHaveNeighbor(X_index, Y_index);
		if (flag == 0)
		{
			return;
		}
		else
		{
			map[X_index][Y_index] = 5;
			x = X_index;
			y = Y_index;
			while (1)
			{
				rand_position = rand() % 4;
				if (rand_position == 0 && X_index >= 3 && map[X_index - 2][Y_index] == 1)//上
				{
					X_index = X_index - 2;
				}
				else if (rand_position == 1 && X_index < count - 3 && map[X_index + 2][Y_index] == 1)//下
				{
					X_index = X_index + 2;
				}
				else if (rand_position == 2 && Y_index >= 3 && map[X_index][Y_index - 2] == 1)//左
				{
					Y_index -= 2;
				}
				else if (rand_position == 3 && Y_index < count - 3 && map[X_index][Y_index + 2] == 1)//右
				{
					Y_index += 2;
				}
				map[(x + X_index) / 2][(y + Y_index) / 2] = 5;
				map[X_index][Y_index] = 5;
				Creat_01(X_index, Y_index);
				break;
			}
		}
	}
}
void Creat_02_Change(int X_index, int Y_index)
{
	if (X_index > 1 && map[X_index - 1][Y_index] == 0)
		map[X_index - 1][Y_index] = 6;
	if (Y_index > 1 && map[X_index][Y_index - 1] == 0)
		map[X_index][Y_index - 1] = 6;
	if (X_index < count - 2 && map[X_index + 1][Y_index] == 0)
		map[X_index + 1][Y_index] = 6;
	if (Y_index < count - 2 && map[X_index][Y_index + 1] == 0)
		map[X_index][Y_index + 1] = 6;

}
void Creat_02(int X_index, int Y_index)
{
	int rand_point, x = 1, y = 2, flag = 0, i, j;
	while (1)
	{
		flag = IsHaveNeighbor(X_index, Y_index);
		if (flag == 0)
			return;
		else
		{
			while (1)
			{
				//如果目前剩余1个蓝色方块
				if (flag == 1)
					rand_point = 0;
				else
					rand_point = rand() % flag;//2个   0  1	随机一个小于flag的数，用于随机选取蓝色方块
											   //print();
				for (i = 0;i < count;i++)
				{
					for (j = 0;j < count;j++)
					{
						if (map[i][j] == 6 && rand_point == 0)
						{
							x = i;
							y = j;
							break;
						}
						else if (map[i][j] == 6)
							rand_point--;
					}
					if (map[i][j] == 6 && rand_point == 0)
						break;
				}
				if (map[x + 1][y] == 5)//往上
				{
					if (map[x - 1][y] == 1)
					{
						map[x - 1][y] = 5;
						map[x][y] = 5;
						x = x - 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				else if (map[x - 1][y] == 5)//向下
				{
					if (map[x + 1][y] == 1)
					{
						map[x + 1][y] = 5;
						map[x][y] = 5;
						x = x + 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				else if (map[x][y + 1] == 5)//向左
				{
					if (map[x][y - 1] == 1)
					{
						map[x][y - 1] = 5;
						map[x][y] = 5;
						y = y - 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				else if (map[x][y - 1] == 5)//向右
				{
					if (map[x][y + 1] == 1)
					{
						map[x][y + 1] = 5;
						map[x][y] = 5;
						y = y + 1;
					}
					else
					{
						map[x][y] = 0;
						break;
					}
				}
				Creat_02_Change(x, y);
				X_index = x;
				Y_index = y;
				break;
			}
		}
	}
}
void Initialize(int num)
{
	int i, j;
	if (num % 2 == 0)
		count++;
	for (i = 0;i < count;i++)	//通过后将地图初始化成全0的
		for (j = 0;j < count;j++)
			map[i][j] = 0;
	//将所需地图以外的初始化为空白,其余空地和墙壁间隔
	for (i = 0;i < M;i++)
	{
		for (j = 0;j < M;j++)
		{
			if (i >= count || j >= count)
				map[i][j] = -1;
			else if (i != 0 && j != 0 && i != count - 1 && j != count - 1)
			{
				if (i % 2 != 0)
					if (j % 2 == 1)
						map[i][j] = 1;
			}
		}
	}
	//如果是等级1，,用第一种方法生成
	if (level == 0)
		Creat_01(1, 1);
	else if (level == 1)
	{
		map[1][1] = 5;
		map[1][2] = 6;
		map[2][1] = 6;
		Creat_02(1, 1);
	}
	for (i = 0;i < count;i++)
	{
		for (j = 0;j < count;j++)
			if (map[i][j] == 5)
				map[i][j] = 1;
	}
	map[1][1] = 3;
	map[count - 2][count - 2] = 4;
}
//打印函数
void print()
{
	int i = 0, j = 0;
	str[0] = '\0';
	system("cls");
	for (i = 0;i < M;i++)
	{
		for (j = 0;j < M;j++)
		{
			if (map[i][j] == 0)
			{
				strcat(str, "■");
			}
			//printf("■");
			else if (map[i][j] == -1)
				break;
			else if (map[i][j] == 1)
			{
				strcat(str, "  ");
			}
			//printf("  ");
			else if (map[i][j] == 3)
			{
				strcat(str, "⊙");
			}
			//	printf("⊙");
			else if (map[i][j] == 4)
			{
				strcat(str, "☆");
			}
			//	printf("☆");
			else if (map[i][j] == 5)
			{
				strcat(str, "◇");
			}
			//	printf("◇");
			else if (map[i][j] == 6)
			{
				strcat(str, "○");
			}
			//	printf("○");
		}
		if (map[i][0] != -1)
			strcat(str, "\n");
		//printf("\n");
	}
	printf("%s", str);
}
int move()
{
	int flag = 0;
	print();
	while (1)
	{
		flag = 0;
		find();

		switch (getch())//接收按键输入
		{
		case 'w':flag = Up();break;
		case 'a':flag = Left();break;
		case 's':flag = Down();break;
		case 'd':flag = Right();break;
		case 27:return -1;
		}
		if (flag == 2)
			print();
		else if (flag == 1)
		{
			//通过了
			if (level == N - 1)
			{
				MessageBox(0, TEXT("恭喜你解锁了所有难度，圣诞节快乐"), TEXT("恭喜"), NULL);
				return 1;
			}
			else
			{
				MessageBox(0, TEXT("恭喜你通过了这一难度，点击确定提高游戏难度"), TEXT("恭喜"), NULL);
				level++;
				Initialize(count);
				print();
			}
		}

	}
}
int Up()
{
	if (my_x != 0)
	{
		if (map[my_x - 1][my_y] == 1)//可走
		{
			map[my_x - 1][my_y] = 3;
			map[my_x][my_y] = 1;
			return 2;//行走成功
		}
		else if (map[my_x - 1][my_y] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Down()
{
	if (my_x != count - 1)
	{
		if (map[my_x + 1][my_y] == 1)//可走
		{
			map[my_x + 1][my_y] = 3;
			map[my_x][my_y] = 1;
			return 2;//行走成功
		}
		else if (map[my_x + 1][my_y] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Right()
{
	if (my_y != count - 1)
	{
		if (map[my_x][my_y + 1] == 1)//可走
		{
			map[my_x][my_y + 1] = 3;
			map[my_x][my_y] = 1;
			return 2;//行走成功
		}
		else if (map[my_x][my_y + 1] == 4)
		{
			return 1;
		}
	}
	return 0;
}
int Left()
{
	if (my_y != 0)
	{
		if (map[my_x][my_y - 1] == 1)//可走
		{
			map[my_x][my_y - 1] = 3;
			map[my_x][my_y] = 1;
			return 2;//行走成功
		}
		else if (map[my_x][my_y - 1] == 4)
		{
			return 1;
		}
	}
	return 0;
}
void find()
{
	int i, j;
	for (i = 0;i < count;i++)
		for (j = 0;j < count;j++)
		{
			if (map[i][j] == 3)
			{
				my_x = i;
				my_y = j;
			}
		}
}

void menu()
{
	char select[10];
	printf("分别用wasd控制人物移动，按Esc退出游戏\n");
	printf("请输入地图大小：");
	scanf("%d", &count);
	printf("请输入游戏难度(1、2):");
	while (1)
	{
		scanf("%s", select);
		if (strlen(select)>1)
		{
			printf("错误输入，请重新输入：");
		}
		else
		{
			if ('1' == select[0])
			{
				level = 0;
				break;
			}
			else if ('2' == select[0])
			{
				level = 1;
				break;
			}
			/*else if ('3' == select[0])
			{
			level = 2;
			break;
			}*/
			else
			{
				printf("错误输入，请重新输入：");
			}
		}
	}

}