#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<iostream>
#include<ctime>
#include <windows.h>
#include <iomanip>
using namespace std; 

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define Row 10 //�Թ����
#define Col 10 //�Թ�����

char maze[Row/2][Col/2]; //�Թ�����
char path[Row-1][Col-1]; //·������

void SetWin(void); //���ÿ���̨����
void Move(int x, int y); //�ƶ����
void Path(int x, int y); //��ͨ·��
void PathU(int *x, int *y); //�Ϲ�·��
void PathD(int *x, int *y); //�¹�·��
void PathL(int *x, int *y); //��·��
void PathR(int *x, int *y); //�ҹ�·��
void Init(void); //��ʼ���Թ�
void Up(int *x,int *y); //�����ƶ�
void Down(int *x,int *y); //�����ƶ�
void Left(int *x,int *y); //�����ƶ�
void Right(int *x,int *y); //�����ƶ�
int Start(void); //��ʼ��Ϸ
int Win(void);//��Ϸ����

int flag,steps=0;
int local_x,local_y;

void main()
{
	SetWin();
	char c=48;
	while(!(c>48&&c<51))
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		cout<<"            ������������������������������������������������������"<<endl;
		cout<<"            ��                  ^ Welcome to ^                  ��"<<endl;
		cout<<"            ��               ^ Maze Wonderland ^                ��"<<endl;
		cout<<"            ������������������������������������������������������"<<endl;
		cout<<"            �� Choose:                                          ��"<<endl;
		cout<<"            ��                                                  ��"<<endl;
		cout<<"            ��   *************** 1.Start Game ****************  ��"<<endl;
		cout<<"            ��   *************** 2.Exit       ****************  ��"<<endl;
		cout<<"            ��                                                  ��"<<endl;
		cout<<"            ������������������������������������������������������"<<endl;
		c=getch();
	}
	int i=c; 
	while(1)
	{
		switch(i)
		{
		case 49:
			system("cls");
			i=Start();
			continue;
		case 50:exit(0);
		}
	}
}

void SetWin()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ������
	COORD size = {Col*2+157, Row*2+43};
	SetConsoleScreenBufferSize(hOut,size); //���ô��ڴ�С
	SMALL_RECT rc = {0,0,157,43};
	SetConsoleWindowInfo(hOut,true ,&rc); //���ô���λ��
	SetConsoleTitle("MAZE WONDERLAND"); //���ô��ڱ���
	//���ع��
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Move(int x, int y)
{
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void Path(int x, int y)
{
	Move(4*y+2,2*x+2);
	cout<<" ";
	path[2*x][2*y]=path[0][0];
	flag++;
}

void PathU(int *x, int *y)
{
	maze[--(*x)][*y]=maze[0][0];
	path[2*(*x+1)-1][2*(*y)]=path[0][0];
	Path(*x,*y);
	Move(4*(*y)+2,2*(*x)+3);
	cout<<" ";
}

void PathD(int *x, int *y)
{
	maze[++(*x)][*y]=maze[0][0];
	path[2*(*x-1)+1][2*(*y)]=path[0][0];
	Path(*x,*y);
	Move(4*(*y)+2,2*(*x)+1);
	cout<<" ";
}

void PathL(int *x, int *y)
{
	maze[*x][--(*y)]=maze[0][0];
	path[2*(*x)][2*(*y+1)-1]=path[0][0];
	Path(*x,*y);
	Move(4*(*y)+4,2*(*x)+2);
	cout<<" ";
}

void PathR(int *x, int *y)
{
	maze[*x][++(*y)]=maze[0][0];
	path[2*(*x)][2*(*y-1)+1]=path[0][0];
	Path(*x,*y);
	Move(4*(*y),2*(*x)+2);
	cout<<" ";
}

void Init()
{
	int i,j;
	int T=1,F=1;
	int m=0,n=0;
	int x=0;
	flag=0;
	srand((unsigned)time(NULL));
	//��ʼ���Թ�����
	for(i=0;i<Row/2;i++) 
	{
		for(j=0;j<Col/2;j++)
			maze[i][j]='f';
	}
	//��ʼ��·������
	for(i=0;i<Row-1;i++) 
	{
		for(j=0;j<Col-1;j++)
			path[i][j]='f';
	}
	path[0][0]='t';
	//�߿�
	for(i=0;i<Col+1;i++) 
		cout<<"**";
	cout<<endl;
	for(i=0;i<Row+1;i++)
	{
		for(j=0;j<Col+1;j++)
			cout<<"��";
		cout<<endl;
	}
	for(i=0;i<Col+1;i++)
		cout<<"**";
	//�����Թ�
	while(F)
	{
		if(T==0)
		{
			for(j=0;j<Col/2;j++)
			{
				for(i=0;i<Row/2;i++)
				{
					if(maze[i][j]=='f')
					{
						m=i;n=j;
						maze[m][n]='t';
						Path(m,n);
						if(maze[m-1][n]==maze[0][0]) //������δ��ͨ·��
						{
							PathU(&m,&n);
							m=i;n=j;
							flag--;
							break;
						}
						if(maze[m+1][n]==maze[0][0]) //������δ��ͨ·��
						{
							PathD(&m,&n);
							m=i;n=j;
							flag--;
							break;
						}
						if(maze[m][n-1]==maze[0][0]) //������δ��ͨ·��
						{
							PathL(&m,&n);
							m=i;n=j;
							flag--;
							break;
						}
						if(maze[m][n+1]==maze[0][0]) //������δ��ͨ·��
						{
							PathR(&m,&n);
							m=i;n=j;
							flag--;
							break;
						}
					}
				}
				if(m==i&&n==j)//m,n����ֵ������δ�����ʵĵ�Ԫ������ѭ�����Ե�ǰλ�ÿ�ʼ��һѭ��
					break;
			}
		}
		T=1;
		while(T)
		{
			x++;
			if(m==0&&n==0)//��λ����ʼλ��
			{
				maze[m][n]='t';
				Path(m,n);
				switch(rand()%2)//�����������
				{
				case 0://����
					PathD(&m,&n);
					break;
				case 1://����
					PathR(&m,&n);
				}
			}
			switch(rand()%4)
			{
			case 0://����
				if(m==0) continue;//�ڱ߽��޷�����
				if(maze[m-1][n]==maze[0][0]) break; //�ѷ���
				PathU(&m,&n);break;
			case 1://����
				if(m==Row/2-1) continue;
				if(maze[m+1][n]==maze[0][0]) break;
				PathD(&m,&n);break;
			case 2://����
				if(n==0) continue;
				if(maze[m][n-1]==maze[0][0]) break;
				PathL(&m,&n);break;
			case 3://����
				if(n==Col/2-1) continue;
				if(maze[m][n+1]==maze[0][0]) break;
				PathR(&m,&n);
			}
			if(x>Row*Col/4)//�ߵ���·
			{
				x=0;T=0;
			}
		}
		if(flag==Row*Col/4)//ȫ����ͨ������Թ�
			F=0;
	}
}

void Up(int *x,int *y)
{
	int i,j;
	i=2*(*y)+2;
	j=(*x)+2;
	Move(i,j);
	cout<<" ";
	j-=1;
	Move(i,j);
	cout<<"��";
	(*x)--;
	path[*x][*y]='o';
	steps++;
	Move(0,0);
	cout<<"Steps:"<<setw(3) << setfill('0') << steps;
}
void Down(int *x,int *y)
{
	int i,j;
	i=2*(*y)+2;
	j=(*x)+2;
	Move(i,j);
	cout<<" ";
	j+=1;
	Move(i,j);
	cout<<"��";
	(*x)++;
	path[*x][*y]='o';
	steps++;
	Move(0,0);
	cout<<"Steps:"<<setw(3) << setfill('0') << steps;
}
void Left(int *x,int *y)
{
	int i,j;
	i=2*(*y)+2;
	j=(*x)+2;
	Move(i,j);
	cout<<" ";
	i-=2;
	Move(i,j);
	cout<<"��";
	(*y)--;
	path[*x][*y]='o';
	steps++;
	Move(0,0);
	cout<<"Steps:"<<setw(3) << setfill('0') << steps;
}
void Right(int *x,int *y)
{
	int i,j;
	i=2*(*y)+2;
	j=(*x)+2;
	Move(i,j);
	cout<<" ";
	i+=2;
	Move(i,j);
	cout<<"��";
	(*y)++;
	path[*x][*y]='o';
	steps++;
	Move(0,0);
	cout<<"Steps:"<<setw(3) << setfill('0') << steps;
}

int  Start()            
{
	char key;
	local_x=0;
	local_y=0;
	system("cls");
	Init();
	Move(2,2);//��ʼλ��
	cout<<"��";//���ͼ��
	while(path[Row-2][Col-2]!='o')
	{
		key=getch();
		if(key==-32)
		{
			key=getch();
			switch(key)
			{
			case UP:
				if(path[local_x-1][local_y]='f'||local_x-1<0) break; //·����ͨ��Խ��
				Up(&local_x,&local_y);
				break;
			case DOWN:
				if(path[local_x+1][local_y]!='t'&&path[local_x+1][local_y]!='o'||local_x+1>Row-2) break;
				Down(&local_x,&local_y);
				break;
			case LEFT:
				if(path[local_x][local_y-1]!='t'&&path[local_x][local_y-1]!='o'||local_y-1<0) break;
				Left(&local_x,&local_y);
				break;
			case RIGHT:
				if(path[local_x][local_y+1]!='t'&&path[local_x][local_y+1]!='o'||local_y+1>Col-2) break;
				Right(&local_x,&local_y);
				break;
			}
		}
	}
	system("cls");
	char c=Win();
	return c;
}

int Win()
{
	printf("\n\n\n\n\n\n\n\n");
	cout<<"            ������������������������������������������������������"<<endl;
	cout<<"            ��                                                  ��"<<endl;
	cout<<"            ��               �� Congratulations ��              ��"<<endl;
	cout<<"            ��            �� Finished in "<<setw(3) << setfill('0') << steps<<" Steps ��           ��"<<endl;//����λ����ʾ����
	cout<<"            ��                                                  ��"<<endl;
	cout<<"            ������������������������������������������������������"<<endl;
	cout<<"            �� Choose:                                          ��"<<endl;
	cout<<"            ��                                                  ��"<<endl;
	cout<<"            ��   **************** 1.New Game  ****************  ��"<<endl;
	cout<<"            ��   **************** 2.Exit      ****************  ��"<<endl;
	cout<<"            ��                                                  ��"<<endl;
	cout<<"            ������������������������������������������������������"<<endl;
	char c=getch();
	return c;
}