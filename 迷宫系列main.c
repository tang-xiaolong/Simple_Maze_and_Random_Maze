#include<stdio.h>
#include<windows.h>
#include<time.h>
#define N 2	//关卡数目
#define M N*50	//地图大小	M*M
#define MAX 300//栈和队列的大小
#define UPDATETIME 30//刷新的时间间隔
typedef struct que
{
	int xList[MAX];
	int yList[MAX];
	int front,rear;
}Que;
int level = 0;//游戏等级
int map[M + 1][M + 1] = { 0 };
int count;//地图大小
int isHaveFind = 0;
//方向数组，便于后面加减
int dir[4][2] = {
	{-1,0},
	{1,0},
	{0,-1},
	{0,1}
};
enum state//定义一个枚举类型，与下面的info一一对应。这有助于以后扩展程序，不用挨个修个各个数字代表的含义，仅仅只需要把各个状态与信息对应即可
{
	wall,
	empty,
	self,
	end,
	testFlag
};
char info[][3] = {
	"■",//墙壁
	"  ",//空地
	"⊙",//玩家
	"☆",//终点
	"◇",//测试图案
	"○",//我也不知道会不会有用，先放着
};
int my_x, my_y;//我的位置

void Initialize(int count);//初始化地图
void Create1(int x,int y);//初级深度优先遍历创造
void Create2(int x,int y);//初级广度优先遍历创造
void Create1Power(int x,int y);//递归深度优先加强版
void Create1Power1(int x,int y);//非递归深度优先加强版
void Create2Power1(int x,int y);//广度优先加强版1
void Create2Power2(int x,int y);//广度优先加强版2
int InArea(int x,int y);//判断是否在合法位置
void print(int x,int y);//打印函数
int Run();//运行游戏
int Update(int id);
void menu();//菜单，选择难度和大小
void Pos(int x, int y);//设置光标位置，决定要在什么位置输出
int Resort(int x,int y);
int IsHaveNeighbor(int x, int y);//判断是否有邻居

int main(void)
{
	int flag = 0;
	srand((unsigned)time(NULL));

	system("mode con cols=200 lines=100");
	system("color 0A");
	menu();
	Initialize(count);
	while (1)
	{
		flag = Run();
		if (flag == 1 || flag == -1)
			return 0;
	}
	return 0;

	system("pause");
	return 0;
}
int InArea(int x,int y)
{
	if(x > 0 && x < count-1 && y > 0 && y < count-1)
		return 1;
	return 0;
}
int Resort(int x,int y)
{
	int i,r = 0;
	for(i = 0;i < 4;++i)//依次探索4个方向
	{
		if(isHaveFind == 1)//如果已经找到路了，我就不再继续回溯了，直接返回
			return 1;
		if(!InArea(x + dir[i][0],y + dir[i][1]) || map[x+dir[i][0]][y+ dir[i][1]] == 7)
			continue;
		if(map[x+dir[i][0]][y+ dir[i][1]] == empty)
		{
			map[x + dir[i][0]][y + dir[i][1]] = testFlag;
			print(x,y);
			Sleep(UPDATETIME);
			if(isHaveFind = Resort(x+dir[i][0],y+dir[i][1]))
				return 1;
			map[x + dir[i][0]][y + dir[i][1]] = 7;//标记为已探索区域
			print(x,y);
		}
		else if(map[x+dir[i][0]][y+dir[i][1]] == end)
			return 1;
	}
	return 0;
}
void Create1(int x,int y)
{
	int i;
	map[x][y] = testFlag;
	for(i = 0;i < 4;++i)//依次探索4个方向
	{
		if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
		{
			map[x + dir[i][0]][y + dir[i][1]] = testFlag;
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] = testFlag;
			//可视化
			print(x + dir[i][0],y + dir[i][1]);
			Sleep(UPDATETIME);
			Create1(x+2 * dir[i][0],y+2 * dir[i][1]);
		}
	}
}

void Create1Power(int x,int y)
{
	//这里我们不再依次选取四个方向探索，而是从剩余的方向里选出一个方向探索
	int i;
	while(IsHaveNeighbor(x,y))
	{
		i = rand()%4;
		if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
		{
			map[x + dir[i][0]][y + dir[i][1]] = testFlag;
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] = testFlag;
			//可视化
			print(x + dir[i][0],y + dir[i][1]);
			Sleep(UPDATETIME);
			Create1Power(x+2 * dir[i][0],y+2 * dir[i][1]);
		}
	}
}
void Create2(int x,int y)
{
	int i = 0;
	Que list;
	list.front = list.rear = 0;
	list.xList[list.rear] = x;
	list.yList[list.rear] = y;
	list.rear = (list.rear + 1)%MAX;
	map[x][y] = testFlag;
	while(list.front != list.rear)
	{
		//队列不为空时，我们从队首出一个元素
		x = list.xList[list.front];
		y = list.yList[list.front];
		list.front = (list.front + 1)%MAX;
		for(i = 0;i < 4;++i)
			if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
				map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
			{
				//如果这个方向是可以走的，把它加入到队列中
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				//可视化
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);
				//加入队列
				list.xList[list.rear] = x + 2 * dir[i][0];
				list.yList[list.rear] = y + 2 * dir[i][1];
				list.rear = (list.rear + 1)%MAX;
			}
	}
}
void Create1Power1(int x,int y)
{
	int i;
	int xList[MAX] = {0};
	int yList[MAX] = {0};
	int top = -1;
	++top;
	xList[top] = x;
	yList[top] = y;
	while(top != -1)//如果栈不为空，则继续
	{
		x = xList[top];
		y = yList[top];
		--top;
		while(IsHaveNeighbor(x,y))
		{
			i = rand()%4;
			if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1] && map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] == empty))
			{
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);//打印一下
				++top;
				xList[top] = x + 2 * dir[i][0];
				yList[top] = y + 2 * dir[i][1]; 
			}
		}
	}
}
void Create2Power1(int x,int y)
{
	int i = 0;
	Que list;
	list.front = list.rear = 0;
	list.xList[list.rear] = x;
	list.yList[list.rear] = y;
	list.rear = (list.rear + 1)%MAX;
	map[x][y] = testFlag;
	while(list.front != list.rear)
	{
		//队列不为空时，我们随机从队首或队尾选取一个元素出来。
		if(rand()%2 == 0)//从队首出一个元素
		{
			x = list.xList[list.front];
			y = list.yList[list.front];
			list.front = (list.front + 1)%MAX;
		}
		else
		{
			list.rear = (list.rear - 1 + MAX)%MAX ;
			x = list.xList[list.rear];
			y = list.yList[list.rear];
		}
		for(i = 0;i < 4;++i)
			if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
				map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
			{
				//如果这个方向是可以走的，把它加入到队列中
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				//可视化
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);
				//加入队列
				if(rand()%2 == 0)
				{
					list.xList[list.rear] = x + 2 * dir[i][0];
					list.yList[list.rear] = y + 2 * dir[i][1];
					list.rear = (list.rear + 1)%MAX;
				}
				else
				{
					list.front = (list.front -1 + MAX)%MAX;
					list.xList[list.front] = x + 2 * dir[i][0];
					list.yList[list.front] = y + 2 * dir[i][1];
				}
			}
	}
}
void Create2Power2(int x,int y)
{
	int i = 0;
	Que list;
	list.front = list.rear = 0;
	list.xList[list.rear] = x;
	list.yList[list.rear] = y;
	list.rear = (list.rear + 1)%MAX;
	map[x][y] = testFlag;
	while(list.front != list.rear)
	{
		//队列不为空时，我们随机从队列中选取一个元素出来。
		if(list.front != 0)
			i = rand()%((list.rear + MAX - list.front)%MAX) + list.front;
		else
			i = rand()%list.rear;
		list.rear = (list.rear - 1 + MAX)%MAX ;
		x = list.xList[i];
		y = list.yList[i];
		list.xList[i] = list.xList[list.rear];
		list.yList[i] = list.yList[list.rear];
		for(i = 0;i < 4;++i)
			if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
				map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
			{
				//如果这个方向是可以走的，把它加入到队列中
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				//可视化
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);
				//加入队列
				list.xList[list.rear] = x + 2 * dir[i][0];
				list.yList[list.rear] = y + 2 * dir[i][1];
				list.rear = (list.rear + 1)%MAX;
			}
	}
}
int IsHaveNeighbor(int x, int y)
{
	int i = 0,flag = 0;
	for(i = 0;i < 4;++i)
		if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] == empty)//如果有一个邻居为1，即未访问
		{
			flag = 1;
			break;
		}
	return flag;
}
void Initialize(int num)
{
	int i, j;
	my_x = my_y = 1;//初始化玩家位置
	if (num % 2 == 0)
		count++;
	for (i = 0;i < count;i++)	//通过后将地图初始化成全0的
		for (j = 0;j < count;j++)
			map[i][j] = wall;
	//将所需地图以外的初始化为空白,其余空地和墙壁间隔
	for (i = 1;i < count - 1;i++)
	{
		for (j = 1;j < count - 1;j++)
		{
			if (i % 2 != 0 && j % 2 == 1)
				map[i][j] = empty;
		}
	}
	for (i = 0;i < count;++i)
	{
		for (j = 0;j < count;j++)
		{
			print(i,j);
		}
	}

	//如果是方法1，,用第一种方法生成
	if (level == 0)
		Create1Power1(my_x,my_y);
	else
		Create2Power1(my_x,my_y);
	for (i = 0;i < count;i++)
	{
		for (j = 0;j < count;j++)
			if (map[i][j] == testFlag)
				map[i][j] = empty;
	}
	map[my_x][my_y] = self;//更新自身位置
	map[count - 2][count - 2] = end;//设置终点
	for (i = 0;i < count;++i)
	{
		for (j = 0;j < count;j++)
		{
			print(i,j);
		}
	}
}
void Pos(int x, int y)//设置光标位置
{//要注意这里的x和y与我们数组的x和y是反的
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄
	SetConsoleCursorPosition(hOutput, pos);
}
void print(int x,int y)
{
	int i = 0;
	//跳到xy的周围更新xy和周围四个格子
	//因为这个定位的是把屏幕左上作为原点，左右为x  上下为y  所以我们传入的参数需要调换顺序 
	//而我们打印的字符都是宽字符，占两个字符宽度，所以我们传入的位置也是偶数，y*2
	Pos(y*2,x);
	printf("%s",info[map[x][y]]);
	for(i = 0;i < 4;++i)
	{
		if(InArea(x + dir[i][0],y + dir[i][1]))
		{
			Pos(2* (y+ dir[i][1]),x + dir[i][0]);
			if(map[x + dir[i][0]][y + dir[i][1]] < 6)
				printf("%s",info[map[x + dir[i][0]][y + dir[i][1]]]);
			else if(map[x + dir[i][0]][y + dir[i][1]] == 7)//用于求解迷宫算法，如果为7，当成空地处理即可
				printf("%s",info[1]);
		}
	}
}
int Update(int id)
{
	//先判断那个方向是否是空地  或者是终点
	if(map[my_x + dir[id][0]][my_y + dir[id][1]] == empty)//如果是空地，更新即可
	{
		map[my_x][my_y] = empty;//自己原来的地方变成空地
		map[my_x + dir[id][0]][my_y + dir[id][1]] = self;//自己去的那个地方变成自己
		my_x += dir[id][0];
		my_y += dir[id][1];
		return 2;
	}
	else if(map[my_x + dir[id][0]][my_y + dir[id][1]] == end)//终点了 
	{
		return 1;
	}
	return 0;//这个方向不能走
}
int Run()
{
	int id = 0;//电脑来玩还是我自己玩
	int flag = 0;//用于接收移动后的状态
	if(id == 0)//电脑你来吧
		Resort(1,1);
	while (id)//这里是1  就表示玩家自己来玩
	{
		flag = 0;
		switch (getch())//接收按键输入
		{
		case 'w':flag = Update(0);break;
		case 's':flag = Update(1);break;
		case 'a':flag = Update(2);break;
		case 'd':flag = Update(3);break;
		case 27:return -1;
		}
		if (flag == 2)//行走成功了，更新我目前的位置和周围四个方块
			print(my_x,my_y);
		else if (flag == 1)
		{
			//通过了
			if (level == N - 1)
			{
				MessageBox(0, "恭喜你解锁了所有难度，今天你剁手了吗？","恭喜", 0);
				return 1;
			}
			else
			{
				MessageBox(0, "恭喜你通过了这一难度，点击确定提高游戏难度", "恭喜", 0);
				level++;
				Initialize(count);
			}
		}

	}
	return 0;
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
			else
			{
				printf("错误输入，请重新输入：");
			}
		}
	}
	system("cls");
}