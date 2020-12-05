#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MaxNum 100
/*���С�ڴ�ֵ�������ٷָ��ڴ�*/
#define MINSIZE 20

/*
* ��������
*/

typedef struct Process {
	int name;
	int size;
}process;

struct Process p[2 * MaxNum];
int choose = 0;
int b = 0;
int flag = 0;
int RAMSize = 1024;//�ڴ��С
int ProcessNum = 1;//��������
int ProcessNumTol = 1;
int ProceessSize[MaxNum];//��ʾ���̴�С�����飬�����±��1��ʼ���±���ǽ��̺š�

void First_Fit();//����ƥ��
void Best_Fit();//���ƥ��
void Worst_Fit();//�ƥ��

int menu();//�˵�
int SetRAM();//�����ڴ�
int ShouwRAM();//չʾ�ڴ�
void Recycle();//�����ڴ�
void InitMemList();//��ʼ��
void ShowProcess();//չʾ���н���
void AddProcess();//��������
/*�ڴ�����ռ��ṹ*/
typedef struct _MemoryInfomation
{
	/*��ʼ��ַ*/
	int start;
	/*��С*/
	int Size;
	/*״̬ F:����(Free) U:ռ��(Used) E ����(End)*/
	char status;
} MEMINFO;

/*�ڴ�ռ���Ϣ��*/
MEMINFO MemList[5000];



int main() {
	b=SetRAM();//�����ڴ�
	system("cls");

	InitMemList();//������ʼ��
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
		
		//��������
		for (i = 0; i < RAMSize && MemList[i].status != 'e'; i++)
		{
			//��������Ҫ�Ĵ�С,���ǿ��пռ�
			if (MemList[i].Size >= request && MemList[i].status == 'f')
			{
				//���С�ڹ涨����С���������ռ�����ȥ
				if (MemList[i].Size - request <= MINSIZE)
				{
					MemList[i].status = 'u';
				}
				else
				{
					//��i�����Ϣ��Ԫ�غ���
					for (j = RAMSize - 2; j > i; j--)
					{
						MemList[j + 1] = MemList[j];
					}

					//��i�ֳ������֣�ʹ�õ͵�ַ����
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
		//û���ҵ����Ϸ���Ŀռ�
		if (flag != 1 || i == RAMSize || MemList[i].status == 'e')
		{
			printf("�ռ䲻��\n");
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
		//��������Ҫ������ռ�
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
			printf("�ռ䲻��\n");
			j = i;
		}
		else if (MemList[i].Size - request <= MINSIZE)  //���С�ڹ涨����С���������ռ�����ȥ
		{
			MemList[i].status = 'u';
		}
		else
		{
			//��i�����Ϣ��Ԫ�غ���
			for (j = RAMSize - 2; j > i; j--)
			{
				MemList[j + 1] = MemList[j];
			}
			//��i�ֳ������֣�ʹ�õ͵�ַ����
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
		//��������Ҫ������ռ�
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
			printf("�ռ䲻��\n");
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
	printf_s("\n\t��ѡ����Ҫʹ�õ��㷨\n");
	printf_s("\t0. ��������\n");
	printf_s("\t1. ����ƥ�䷨\n");
	printf_s("\t2. ���ƥ�䷨\n");
	printf_s("\t3. �ƥ�䷨\n");
	printf_s("\t4. ��ʾ�ڴ�ʹ��\n");
	printf_s("\t5. �����ѷ���Ŀռ�\n");
	printf_s("\t6. չʾ���н���\n");
	printf_s("\t7. �˳�����\n");
	printf_s("�����Ӧ��Ž���ѡ��");
	scanf_s("%d", &choose);
	return choose;
}

int SetRAM()
{
	int pname;
	if (!flag) {
		printf_s("\n\t��������Ҫ�������ڴ��С��");
		scanf_s("%d", &RAMSize);
		printf_s("\n\t��������Ҫ�����Ľ��������� ");
		scanf_s("%d", &ProcessNum);
		printf_s("\n\t��������̺źͶ�Ӧ���������ڴ�ռ��С�� ");
		
		for (int i = 0; i < ProcessNum; i++)
		{
			printf_s("\n\t��%d�����̵�����Ϊ��", i + 1);
			scanf_s("%d", &pname);
			p[i].name = pname;
			printf_s("\n\t��%d�����̵Ĵ�СΪ��", i + 1);
			scanf_s("%d", &ProceessSize[i]);
			p[i].size = ProceessSize[i];
		}
		flag = 1;
		
	}

	return flag;
}

int ShouwRAM()
{
	int i, used = 0;//��¼����ʹ�õ��ܿռ���
	printf("\n---------------------------------------------------\n");
	printf("%5s%15s%15s%15s", "����", "��ʼ��ַ", "��С", "״̬");
	printf("\n---------------------------------------------------\n");
	for (i = 0; i < RAMSize && MemList[i].status != 'e'; i++)
	{
		if (MemList[i].status == 'u')
		{
			used += MemList[i].Size;
		}
		printf("%5d%15d%15d%15s\n", i, MemList[i].start, MemList[i].Size, MemList[i].status == 'u' ? "ʹ����" : "������");
	}
	printf("\n----------------------------------------------\n");
	printf("�ܴ�С:%-10d ��ʹ��:%-10d �����С:%-10d\n", RAMSize, used, RAMSize - used);
	return 0;
}

void Recycle()
{
	int i, number;
	printf("\n��������Ҫ���յĽ��̺�:\n");
	scanf_s("%d", &number);
	//����Ŀռ���ʹ�õ�
	if (MemList[number].status == 'u')
	{
		MemList[number].status = 'f';//��־Ϊ����
		if (MemList[number + 1].status == 'f')//�Ҳ�ռ�Ϊ����ϲ�
		{
			MemList[number].Size += MemList[number].Size;//��С�ϲ�
			for (i = number + 1; i < RAMSize - 1 && MemList[i].status != 'e'; i++) //i����Ŀռ���Ϣ��Ԫ�غ���
			{
				if (i > 0)
				{
					MemList[i] = MemList[i + 1];
				}
			}
		}
		//���ռ������ϲ�
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
		printf_s("�˽��̲����ڻ��Ѿ��ͷ�\n");
	}
	ShouwRAM();
}

void InitMemList()
{
	int i;
	MEMINFO temp = { 0,0,'e' };
	//��ʼ���ռ���Ϣ��
	for (i = 0; i < RAMSize; i++)
	{
		MemList[i] = temp;
	}
	//��ʼ��ַΪ0
	MemList[0].start = 0;
	//�ռ��ʼΪ���
	MemList[0].Size = RAMSize;
	//״̬Ϊ����
	MemList[0].status = 'f';
}

void ShowProcess()
{
	printf_s("\n-----------------------------\n");
	printf_s("%5s%15s", "���̺�", "���̴�С");
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
	printf_s("���������������ڴ���");
	scanf_s("%d",&p[ProcessNumTol-1].name);
	printf_s("���������������ڴ��С");
	for (int i = 0; i < ProcessNum; i++)
	{
		ProceessSize[i] = 0;
	}
	ProcessNum = 1;
	scanf_s("%d",&ProceessSize[0]);
	p[ProcessNumTol - 1].size = ProceessSize[0];
}

