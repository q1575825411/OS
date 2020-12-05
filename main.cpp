#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MaxNum 100
/*如果小于此值，将不再分割内存*/
#define MINSIZE 20

/*
* 变量定义
*/

typedef struct Process {
	int name;
	int size;
}process;

struct Process p[2 * MaxNum];
int choose = 0;
int b = 0;
int flag = 0;
int RAMSize = 1024;//内存大小
int ProcessNum = 1;//进程数量
int ProcessNumTol = 1;
int ProceessSize[MaxNum];//表示进程大小的数组，数组下标从1开始，下标就是进程号。

void First_Fit();//最先匹配
void Best_Fit();//最佳匹配
void Worst_Fit();//最坏匹配

int menu();//菜单
int SetRAM();//设置内存
int ShouwRAM();//展示内存
void Recycle();//回收内存
void InitMemList();//初始化
void ShowProcess();//展示已有进程
void AddProcess();//新增进程
/*内存分区空间表结构*/
typedef struct _MemoryInfomation
{
	/*起始地址*/
	int start;
	/*大小*/
	int Size;
	/*状态 F:空闲(Free) U:占用(Used) E 结束(End)*/
	char status;
} MEMINFO;

/*内存空间信息表*/
MEMINFO MemList[5000];



int main() {
	b=SetRAM();//设置内存
	system("cls");

	InitMemList();//变量初始化
	ProcessNumTol = ProcessNum;

	while (b)
	{
		choose = menu();
		if (choose != -1) {
			switch (choose)
			{
			case 0:
				AddProcess();
				system("cls");
				break;
			case 1:
				First_Fit();
				break;
			case 2:
				Best_Fit();
				break;
			case 3:
				Worst_Fit();
				break;
			case 4:
				ShouwRAM();
				break;
			case 5:
				Recycle();
				break;
			case 6:
				ShowProcess();
				break;
			case 7:
				system("cls");
				b = 0;
				break;
			default:
				break;
			}
		}
	}

}

void First_Fit()
{
	for (int k = 0; k < ProcessNum; k++)
	{
		int i, j, flag = 0;
		int request;
		request = ProceessSize[k];
		
		//遍历数组
		for (i = 0; i < RAMSize && MemList[i].status != 'e'; i++)
		{
			//满足所需要的大小,且是空闲空间
			if (MemList[i].Size >= request && MemList[i].status == 'f')
			{
				//如果小于规定的最小差则将整个空间分配出去
				if (MemList[i].Size - request <= MINSIZE)
				{
					MemList[i].status = 'u';
				}
				else
				{
					//将i后的信息表元素后移
					for (j = RAMSize - 2; j > i; j--)
					{
						MemList[j + 1] = MemList[j];
					}

					//将i分成两部分，使用低地址部分
					MemList[i + 1].start = MemList[i].start + request;
					MemList[i + 1].Size = MemList[i].Size - request;
					MemList[i + 1].status = 'f';
					MemList[i].Size = request;
					MemList[i].status = 'u';
					flag = 1;
				}
				break;
			}
		}
		//没有找到符合分配的空间
		if (flag != 1 || i == RAMSize || MemList[i].status == 'e')
		{
			printf("空间不足\n");
		}
	}
	ShouwRAM();
}

void Best_Fit()
{
	for (int ll = 0; ll < ProcessNum; ll++)
	{
		int i, j, t, flag, request;
		request = ProceessSize[ll];
		j = 0;
		flag = 0;
		t = RAMSize;
		//保存满足要求的最大空间
		for (i = 0; i < RAMSize && MemList[i].status != 'e'; i++)
		{
			if (MemList[i].Size >= request && MemList[i].status == 'f')
			{
				flag = 1;
				if (MemList[i].Size < t)
				{
					t = MemList[i].Size;
					j = i;
				}
			}
		}
		i = j;
		if (flag == 0)
		{
			printf("空间不足\n");
			j = i;
		}
		else if (MemList[i].Size - request <= MINSIZE)  //如果小于规定的最小差则将整个空间分配出去
		{
			MemList[i].status = 'u';
		}
		else
		{
			//将i后的信息表元素后移
			for (j = RAMSize - 2; j > i; j--)
			{
				MemList[j + 1] = MemList[j];
			}
			//将i分成两部分，使用低地址部分
			MemList[i + 1].start = MemList[i].start + request;
			MemList[i + 1].Size = MemList[i].Size - request;
			MemList[i + 1].status = 'f';
			MemList[i].Size = request;
			MemList[i].status = 'u';
		}

	}
	ShouwRAM();
}

void Worst_Fit()
{
	for (int ll = 0; ll < ProcessNum; ll++)
	{
		int i, j, k, flag, request;
		request = ProceessSize[ll];
		j = 0;
		flag = 0;
		k = 0;
		//保存满足要求的最大空间
		for (i = 0; i < RAMSize - 1 && MemList[i].status != 'e'; i++)
		{
			if (MemList[i].Size >= request && MemList[i].status == 'f')
			{
				flag = 1;
				if (MemList[i].Size > k)
				{
					k = MemList[i].Size;
					j = i;
				}
			}
		}
		i = j;
		if (flag == 0)
		{
			printf("空间不足\n");
			j = i;
		}
		else if (MemList[i].Size - request <= MINSIZE)
		{
			MemList[i].status = 'u';
		}
		else
		{
			for (j = RAMSize - 2; j > i; j--)
			{
				MemList[j + 1] = MemList[j];
			}
			MemList[i + 1].start = MemList[i].start + request;
			MemList[i + 1].Size = MemList[i].Size - request;
			MemList[i + 1].status = 'f';
			MemList[i].Size = request;
			MemList[i].status = 'u';
		}

	}
	ShouwRAM();
}

int menu()
{
	printf_s("\n\t请选择想要使用的算法\n");
	printf_s("\t0. 新增进程\n");
	printf_s("\t1. 最先匹配法\n");
	printf_s("\t2. 最佳匹配法\n");
	printf_s("\t3. 最坏匹配法\n");
	printf_s("\t4. 显示内存使用\n");
	printf_s("\t5. 回收已分配的空间\n");
	printf_s("\t6. 展示已有进程\n");
	printf_s("\t7. 退出程序\n");
	printf_s("输入对应编号进行选择：");
	scanf_s("%d", &choose);
	return choose;
}

int SetRAM()
{
	int pname;
	if (!flag) {
		printf_s("\n\t请输入想要给定的内存大小：");
		scanf_s("%d", &RAMSize);
		printf_s("\n\t请输入想要给定的进程数量： ");
		scanf_s("%d", &ProcessNum);
		printf_s("\n\t请输入进程号和对应进程所需内存空间大小： ");
		
		for (int i = 0; i < ProcessNum; i++)
		{
			printf_s("\n\t第%d个进程的名称为：", i + 1);
			scanf_s("%d", &pname);
			p[i].name = pname;
			printf_s("\n\t第%d个进程的大小为：", i + 1);
			scanf_s("%d", &ProceessSize[i]);
			p[i].size = ProceessSize[i];
		}
		flag = 1;
		
	}

	return flag;
}

int ShouwRAM()
{
	int i, used = 0;//记录可以使用的总空间量
	printf("\n---------------------------------------------------\n");
	printf("%5s%15s%15s%15s", "号码", "起始地址", "大小", "状态");
	printf("\n---------------------------------------------------\n");
	for (i = 0; i < RAMSize && MemList[i].status != 'e'; i++)
	{
		if (MemList[i].status == 'u')
		{
			used += MemList[i].Size;
		}
		printf("%5d%15d%15d%15s\n", i, MemList[i].start, MemList[i].Size, MemList[i].status == 'u' ? "使用中" : "空闲中");
	}
	printf("\n----------------------------------------------\n");
	printf("总大小:%-10d 已使用:%-10d 空余大小:%-10d\n", RAMSize, used, RAMSize - used);
	return 0;
}

void Recycle()
{
	int i, number;
	printf("\n请输入您要回收的进程号:\n");
	scanf_s("%d", &number);
	//输入的空间是使用的
	if (MemList[number].status == 'u')
	{
		MemList[number].status = 'f';//标志为空闲
		if (MemList[number + 1].status == 'f')//右侧空间为空则合并
		{
			MemList[number].Size += MemList[number].Size;//大小合并
			for (i = number + 1; i < RAMSize - 1 && MemList[i].status != 'e'; i++) //i后面的空间信息表元素后移
			{
				if (i > 0)
				{
					MemList[i] = MemList[i + 1];
				}
			}
		}
		//左测空间空闲则合并
		if (number > 0 && MemList[number - 1].status == 'f')
		{
			MemList[number - 1].Size += MemList[number].Size;
			for (i = number; i < RAMSize - 1 && MemList[i].status != 'e'; i++)
			{
				MemList[i] = MemList[i + 1];
			}
		}
	}
	else
	{
		printf_s("此进程不存在或已经释放\n");
	}
	ShouwRAM();
}

void InitMemList()
{
	int i;
	MEMINFO temp = { 0,0,'e' };
	//初始化空间信息表
	for (i = 0; i < RAMSize; i++)
	{
		MemList[i] = temp;
	}
	//起始地址为0
	MemList[0].start = 0;
	//空间初始为最大
	MemList[0].Size = RAMSize;
	//状态为空闲
	MemList[0].status = 'f';
}

void ShowProcess()
{
	printf_s("\n-----------------------------\n");
	printf_s("%5s%15s", "进程号", "进程大小");
	printf_s("\n-----------------------------\n");
	for (int i = 0; i < ProcessNumTol; i++)
	{
		printf_s("%5d%15d\n", p[i].name, p[i].size);
	}
	printf("\n------------------------------\n");
}

void AddProcess()
{
	char name;
	ProcessNumTol++;
	printf_s("请输入新增进程内存编号");
	scanf_s("%d",&p[ProcessNumTol-1].name);
	printf_s("请输入新增进程内存大小");
	for (int i = 0; i < ProcessNum; i++)
	{
		ProceessSize[i] = 0;
	}
	ProcessNum = 1;
	scanf_s("%d",&ProceessSize[0]);
	p[ProcessNumTol - 1].size = ProceessSize[0];
}

