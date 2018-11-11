#include<stdio.h>
#include<windows.h>
#include<time.h>
#define N 2	//�ؿ���Ŀ
#define M N*50	//��ͼ��С	M*M
#define MAX 300//ջ�Ͷ��еĴ�С
#define UPDATETIME 30//ˢ�µ�ʱ����
typedef struct que
{
	int xList[MAX];
	int yList[MAX];
	int front,rear;
}Que;
int level = 0;//��Ϸ�ȼ�
int map[M + 1][M + 1] = { 0 };
int count;//��ͼ��С
int isHaveFind = 0;
//�������飬���ں���Ӽ�
int dir[4][2] = {
	{-1,0},
	{1,0},
	{0,-1},
	{0,1}
};
enum state//����һ��ö�����ͣ��������infoһһ��Ӧ�����������Ժ���չ���򣬲��ð����޸��������ִ���ĺ��壬����ֻ��Ҫ�Ѹ���״̬����Ϣ��Ӧ����
{
	wall,
	empty,
	self,
	end,
	testFlag
};
char info[][3] = {
	"��",//ǽ��
	"  ",//�յ�
	"��",//���
	"��",//�յ�
	"��",//����ͼ��
	"��",//��Ҳ��֪���᲻�����ã��ȷ���
};
int my_x, my_y;//�ҵ�λ��

void Initialize(int count);//��ʼ����ͼ
void Create1(int x,int y);//����������ȱ�������
void Create2(int x,int y);//����������ȱ�������
void Create1Power(int x,int y);//�ݹ�������ȼ�ǿ��
void Create1Power1(int x,int y);//�ǵݹ�������ȼ�ǿ��
void Create2Power1(int x,int y);//������ȼ�ǿ��1
void Create2Power2(int x,int y);//������ȼ�ǿ��2
int InArea(int x,int y);//�ж��Ƿ��ںϷ�λ��
void print(int x,int y);//��ӡ����
int Run();//������Ϸ
int Update(int id);
void menu();//�˵���ѡ���ѶȺʹ�С
void Pos(int x, int y);//���ù��λ�ã�����Ҫ��ʲôλ�����
int Resort(int x,int y);
int IsHaveNeighbor(int x, int y);//�ж��Ƿ����ھ�

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
	for(i = 0;i < 4;++i)//����̽��4������
	{
		if(isHaveFind == 1)//����Ѿ��ҵ�·�ˣ��ҾͲ��ټ��������ˣ�ֱ�ӷ���
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
			map[x + dir[i][0]][y + dir[i][1]] = 7;//���Ϊ��̽������
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
	for(i = 0;i < 4;++i)//����̽��4������
	{
		if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
		{
			map[x + dir[i][0]][y + dir[i][1]] = testFlag;
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] = testFlag;
			//���ӻ�
			print(x + dir[i][0],y + dir[i][1]);
			Sleep(UPDATETIME);
			Create1(x+2 * dir[i][0],y+2 * dir[i][1]);
		}
	}
}

void Create1Power(int x,int y)
{
	//�������ǲ�������ѡȡ�ĸ�����̽�������Ǵ�ʣ��ķ�����ѡ��һ������̽��
	int i;
	while(IsHaveNeighbor(x,y))
	{
		i = rand()%4;
		if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
		{
			map[x + dir[i][0]][y + dir[i][1]] = testFlag;
			map[x+2 * dir[i][0]][y+2 * dir[i][1]] = testFlag;
			//���ӻ�
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
		//���в�Ϊ��ʱ�����ǴӶ��׳�һ��Ԫ��
		x = list.xList[list.front];
		y = list.yList[list.front];
		list.front = (list.front + 1)%MAX;
		for(i = 0;i < 4;++i)
			if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && 
				map[x+2 * dir[i][0]][y+2 * dir[i][1]] == empty)
			{
				//�����������ǿ����ߵģ��������뵽������
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				//���ӻ�
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);
				//�������
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
	while(top != -1)//���ջ��Ϊ�գ������
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
				Sleep(UPDATETIME);//��ӡһ��
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
		//���в�Ϊ��ʱ����������Ӷ��׻��βѡȡһ��Ԫ�س�����
		if(rand()%2 == 0)//�Ӷ��׳�һ��Ԫ��
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
				//�����������ǿ����ߵģ��������뵽������
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				//���ӻ�
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);
				//�������
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
		//���в�Ϊ��ʱ����������Ӷ�����ѡȡһ��Ԫ�س�����
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
				//�����������ǿ����ߵģ��������뵽������
				map[x + dir[i][0]][y + dir[i][1]] = testFlag;
				map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] = testFlag;
				//���ӻ�
				print(x + dir[i][0],y + dir[i][1]);
				Sleep(UPDATETIME);
				//�������
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
		if(InArea(x + 2 * dir[i][0],y + 2 * dir[i][1]) && map[x + 2 * dir[i][0]][y + 2 * dir[i][1]] == empty)//�����һ���ھ�Ϊ1����δ����
		{
			flag = 1;
			break;
		}
	return flag;
}
void Initialize(int num)
{
	int i, j;
	my_x = my_y = 1;//��ʼ�����λ��
	if (num % 2 == 0)
		count++;
	for (i = 0;i < count;i++)	//ͨ���󽫵�ͼ��ʼ����ȫ0��
		for (j = 0;j < count;j++)
			map[i][j] = wall;
	//�������ͼ����ĳ�ʼ��Ϊ�հ�,����յغ�ǽ�ڼ��
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

	//����Ƿ���1��,�õ�һ�ַ�������
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
	map[my_x][my_y] = self;//��������λ��
	map[count - 2][count - 2] = end;//�����յ�
	for (i = 0;i < count;++i)
	{
		for (j = 0;j < count;j++)
		{
			print(i,j);
		}
	}
}
void Pos(int x, int y)//���ù��λ��
{//Ҫע�������x��y�����������x��y�Ƿ���
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//���ر�׼�����롢����������豸�ľ����Ҳ���ǻ�����롢���/�������Ļ�������ľ��
	SetConsoleCursorPosition(hOutput, pos);
}
void print(int x,int y)
{
	int i = 0;
	//����xy����Χ����xy����Χ�ĸ�����
	//��Ϊ�����λ���ǰ���Ļ������Ϊԭ�㣬����Ϊx  ����Ϊy  �������Ǵ���Ĳ�����Ҫ����˳�� 
	//�����Ǵ�ӡ���ַ����ǿ��ַ���ռ�����ַ���ȣ��������Ǵ����λ��Ҳ��ż����y*2
	Pos(y*2,x);
	printf("%s",info[map[x][y]]);
	for(i = 0;i < 4;++i)
	{
		if(InArea(x + dir[i][0],y + dir[i][1]))
		{
			Pos(2* (y+ dir[i][1]),x + dir[i][0]);
			if(map[x + dir[i][0]][y + dir[i][1]] < 6)
				printf("%s",info[map[x + dir[i][0]][y + dir[i][1]]]);
			else if(map[x + dir[i][0]][y + dir[i][1]] == 7)//��������Թ��㷨�����Ϊ7�����ɿյش�����
				printf("%s",info[1]);
		}
	}
}
int Update(int id)
{
	//���ж��Ǹ������Ƿ��ǿյ�  �������յ�
	if(map[my_x + dir[id][0]][my_y + dir[id][1]] == empty)//����ǿյأ����¼���
	{
		map[my_x][my_y] = empty;//�Լ�ԭ���ĵط���ɿյ�
		map[my_x + dir[id][0]][my_y + dir[id][1]] = self;//�Լ�ȥ���Ǹ��ط�����Լ�
		my_x += dir[id][0];
		my_y += dir[id][1];
		return 2;
	}
	else if(map[my_x + dir[id][0]][my_y + dir[id][1]] == end)//�յ��� 
	{
		return 1;
	}
	return 0;//�����������
}
int Run()
{
	int id = 0;//�������滹�����Լ���
	int flag = 0;//���ڽ����ƶ����״̬
	if(id == 0)//����������
		Resort(1,1);
	while (id)//������1  �ͱ�ʾ����Լ�����
	{
		flag = 0;
		switch (getch())//���հ�������
		{
		case 'w':flag = Update(0);break;
		case 's':flag = Update(1);break;
		case 'a':flag = Update(2);break;
		case 'd':flag = Update(3);break;
		case 27:return -1;
		}
		if (flag == 2)//���߳ɹ��ˣ�������Ŀǰ��λ�ú���Χ�ĸ�����
			print(my_x,my_y);
		else if (flag == 1)
		{
			//ͨ����
			if (level == N - 1)
			{
				MessageBox(0, "��ϲ������������Ѷȣ��������������","��ϲ", 0);
				return 1;
			}
			else
			{
				MessageBox(0, "��ϲ��ͨ������һ�Ѷȣ����ȷ�������Ϸ�Ѷ�", "��ϲ", 0);
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
	printf("�ֱ���wasd���������ƶ�����Esc�˳���Ϸ\n");
	printf("�������ͼ��С��");
	scanf("%d", &count);
	printf("��������Ϸ�Ѷ�(1��2):");
	while (1)
	{
		scanf("%s", select);
		if (strlen(select)>1)
		{
			printf("�������룬���������룺");
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
				printf("�������룬���������룺");
			}
		}
	}
	system("cls");
}