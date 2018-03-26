#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sq_list.h"

_Bool ListInitial_sq(SqList * const sqlistptr)
{//时间复杂度O(1)
	sqlistptr->elembase = (ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);//分配内存空间
	if (NULL == sqlistptr->elembase)		//如果分配空间失败,返回false
		return false;
	sqlistptr->length = 0;				//空表长度为0
	sqlistptr->size = LIST_INIT_SIZE;	//初始存储容量
	return true;
}

void ListClear_sq(SqList * const sqlistptr)
{//时间复杂度O(1)
	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	sqlistptr->elembase = (ElemType *)realloc(sqlistptr->elembase, sizeof(ElemType)*LIST_INIT_SIZE);//存储空间重置
	sqlistptr->size = LIST_INIT_SIZE;	//存储容量重置
	sqlistptr->length = 0;				//表长度重置为0
}

void ListDestroy_sq(SqList * const sqlistptr)
{//时间复杂度O(1)
	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	free(sqlistptr->elembase);		//释放线性表的存储空间
	sqlistptr->elembase = NULL;		//线性表的基址置空
	sqlistptr->length = 0;		//线性表的长度置0
	sqlistptr->size = 0;		//线性表的容量置0
}

int ListLength_sq(const SqList *const sqlistptr)
{//时间复杂度O(1)
	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	return sqlistptr->length;//返回线性表元素个数
}

_Bool ListIsEmpty_sq(const SqList * const sqlistptr)
{//时间复杂度O(1)
	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	return 0 == sqlistptr->length;
}

_Bool ListGetElem_sq(const SqList *const sqlistptr, const int index, ElemType *const elemptr)
{//时间复杂度O(1)
	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	if (index<1 || index>sqlistptr->length)//元素位置不正确返回false
		return false;
	*elemptr = *(sqlistptr->elembase + index - 1);
	return true;
}

_Bool ListLocate_sq(const SqList *const sqlistptr, const ElemType elem, _Bool (*compare)(const ElemType, const ElemType), int *const indexptr)
{//时间复杂度O(n)
	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	const ElemType *ptr = sqlistptr->elembase;
	int i = 1;
	for (; i <= sqlistptr->length; ++i)
	{
		if ((*compare)(elem, *ptr++))//比较元素
			break;					//满足compare退出循环
	}
	if (i > sqlistptr->length)//判断循环是否中断
		return  false;		//未中断则未找到数据元素
	return true;
}

_Bool ListInsert_sq(SqList *const sqlistptr, const ElemType elem, const int index)
{
	ElemType *insposptr = NULL;

	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	if (index<1 || index>(sqlistptr->length + 1))
		return false;
	if (sqlistptr->length == sqlistptr->size)//如果线性表当前容量满,增加表的容量
	{
		sqlistptr->elembase = (ElemType *)realloc(sqlistptr->elembase, sizeof(ElemType)*(sqlistptr->size + LIST_INCREMENT_SIZE));//增加表的容量
		if (NULL == sqlistptr->elembase)//增加容量失败,返回false
		{
			sqlistptr->size = 0;
			sqlistptr->length = 0;
			return false;
		}
		sqlistptr->size += LIST_INCREMENT_SIZE;
	}
	insposptr = sqlistptr + index - 1;							//elem要插入的位置
	for (ElemType *p = sqlistptr->elembase + sqlistptr->length; p > insposptr; --p)//第index及后面的元素向后移动一个位置
		*p = *(p - 1);
	*insposptr = elem;
	++sqlistptr->length;//表长度加1
	return true;
}





_Bool IsGreaterThan(const ElemType e1, const ElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual(const ElemType e1, const ElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual(const ElemType e1, const ElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan(const ElemType e1, const ElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual(const ElemType e1, const ElemType e2)
{
	return e2 <= e2;
}