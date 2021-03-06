//editor:bysouffle
/**
实验1.1 顺序表的操作
   请编制C程序，利用顺序存储方式来实现下列功能：根据键盘输入数据建立一个线性表，并输出该线性表；
 然后根据屏幕菜单的选择，可以进行数据的插入、删除、查找，并在插入或删除数据后，再输出线性表；最
 后在屏幕菜单中选择0，即可结束程序的运行。
   分析：当我们要在顺序表的第i个位置上插入一个元素时，必须先将线性表的第i个元素之后的所有元素依
 次后移一个位置，以便腾空一个位置，再把新元素插入到该位置。当要删除第i个元素时，也只需将第i个元
 素之后的所有元素前移一个位置。
   算法描述：对每一个算法，都要写出算法的中文描述。本实验中要求分别写出在第i个（从1开始计数）结
 点前插入数据为x的结点、删除指定结点、创建一个线性表、打印线性表等的算法描述。
**/


#include<stdlib.h>
#include<stdio.h>

#define List_int_size 100  //初始分配量
#define Listincrement 10  //增加分配量
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996)


typedef struct
{
	int * elem;		//储存空间基址
	int length;		//当前长度
	int listsize;	//当前分配储存容量
}SqList;


int InitList_Sq(SqList &L)  //构建空线性表
{
	L.elem = (int *)malloc(List_int_size * sizeof(int));   //分配存储空间
	if (!L.elem)		// 分配失败
		exit(OVERFLOW);
	L.length = 0;		//空线性表长度
	L.listsize = List_int_size;
	return OK;
}


int ListInput_Sq(SqList &L, int InputLength)	//输入元素
{
	if (InputLength < 0)	//判断输入长度是否合法
		return ERROR;
	if (InputLength > L.listsize)	//重新分配储存空间
	{
		L.elem = (int *)malloc(Listincrement * sizeof(int));
		if (!L.elem)
			exit(OVERFLOW);
		L.listsize += Listincrement;
	}
	printf("请输入元素:");
	for (int j = 0; j < InputLength; j++)	//插入元素
	{
		scanf("%d", &L.elem[j]);

	}
	printf("\n");
	L.length = InputLength;

	return OK;
}


int display_Sq(SqList &L)		//输出所有元素
{
	printf("线性顺序表为：");
	for (int i = 0; i < L.length; i++)
	{
		printf("%d  ", L.elem[i]);
	}
	printf("\n");
	return OK;
}


int ListInsert_Sq(SqList &L, int i, int e)		//在第i个位置插入元素e
{
	if (i<1 || i>L.length + 1)
		return ERROR;		//判断位置i是否合法
	if (L.length >= L.listsize)		//当前长度大于分配容量时重新分配空间
	{
		L.elem = (int *)realloc(L.elem, (L.listsize + Listincrement) * sizeof(int));
		if (!L.elem)		//分配失败
			exit(OVERFLOW);
		L.listsize += Listincrement;		//增加存储容量
	}
	for (int j = L.length - 1; j >= i - 1; j--)	//插入位置及之后元素往后移动
	{
		L.elem[j + 1] = L.elem[j];
	}
	L.elem[i - 1] = e;		// 插入元素e
	L.length += 1;		//长度+1
	return OK;
}



int ListDelete_Sq(SqList &L, int i, int &e)		//删除第i个元素
{
	if (i<1 || i>L.length)		//判断i是否合法
		return ERROR;
	e = L.elem[i - 1];		//将第i个元素赋值给e
	printf("被删除的元素为：%d", e);
	for (int j = i - 1; j < L.length - 1; j++)		 //删除位置之后元素左移
	{
		L.elem[j] = L.elem[j + 1];

	}
	L.length -= 1;// 长度-1
	return OK;
}


int compare(int a, int b)
{
	if (a == b)
	{
		return true;
	}
	return false;
}
int LocateElem_Sq(SqList L, int e, int(*compare)(int, int))		//查找第一个元素与e满足compare条件的序列
{
	int i = 1;		//第一个元素序列为1
	int * p = L.elem;		//p的初值为elem第一个元素的储存位置
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length)
		return i;
	else return 0;

}


void menu()
{

	printf("\n*******************************\n");
	printf("****  1.创建       2.插入  ****\n");
	printf("****  3.删除       4.查找  ****\n");
	printf("****        0.退出         ****\n");
	printf("*******************************\n");
}
enum op
{
	EXIT,
	CREATE,
	INSERT,
	DEL,
	LOCATE
};		//对应switch


int main()
{

	SqList L;
	InitList_Sq(L);		//初始化线性表
	int i = 1;
	while (i)
	{
		menu();
		printf("请选择：");
		scanf("%d", &i);
		switch (i)
		{
		case CREATE:		//ListInput_Sq
			printf("请输入长度:");
			int n;
			scanf("%d", &n);
			ListInput_Sq(L, n);
			display_Sq(L);
			break;


		case INSERT:		//ListInsert_Sq
			display_Sq(L);
			int i, e;
			printf("插入位数 i = ");
			scanf("%d", &i);
			printf("插入元素 e = ");
			scanf("%d", &e);
			ListInsert_Sq(L, i, e);
			display_Sq(L);
			break;

		case DEL:		//ListDelete_Sq
			display_Sq(L);
			printf("删除元素位数 i = ");
			scanf("%d", &i);
			ListDelete_Sq(L, i, e);
			display_Sq(L);
			break;

		case LOCATE:		//LocateElem_Sq
			display_Sq(L);
			printf("查找元素为: ");
			scanf("%d", &e);
			i = LocateElem_Sq(L, e, compare);
			printf("查找元素 %d 为第 %d 位\n", e, i);
			break;

		case EXIT:		//退出
			exit(0);

		default:
			printf("选择错误");
			break;
		}
	}
}
