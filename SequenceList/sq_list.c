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
	sqlistptr->length = 0;			//线性表的长度置0
	sqlistptr->size = 0;			//线性表的容量置0
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
		if ((*compare)(*ptr++, elem))//比较元素
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
	if (index<1 || index>(sqlistptr->length + 1))//元素位置不正确,返回false
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
	for (ElemType *p = sqlistptr->elembase + sqlistptr->length; p > insposptr; --p)
		*p = *(p - 1);//第index及后面的元素向后移动一个位置
	*insposptr = elem;
	++sqlistptr->length;//表长度加1
	return true;
}

_Bool ListDelete_sq(SqList *const sqlistptr, const int index, ElemType *const retptr)
{
	ElemType ret = *(sqlistptr->elembase + index - 1);

	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	if (0 == sqlistptr->length)//如果表为空,则返回false
		return false;
	if (index<1 || index>sqlistptr->length)//元素位置不正确,返回false
		return false;
	for (ElemType *p = sqlistptr->elembase + index - 1; p < sqlistptr->elembase + sqlistptr->length - 1; ++p)
		*p = *(p + 1);//第index+1及后面的元素前移一个位置
	if (sqlistptr->size - sqlistptr->length >= LIST_INCREMENT_SIZE)
	{
		sqlistptr->elembase = (ElemType *)realloc(sqlistptr->elembase, sizeof(ElemType)*(sqlistptr->size - LIST_INCREMENT_SIZE));//减小表的空间
		if (NULL == sqlistptr->elembase)//减小空间失败,返回false
			return false;
		sqlistptr->size -= LIST_INCREMENT_SIZE;//表容量减小
	}
	--sqlistptr->length;//表长度减1
	*retptr = ret;//由指针返回元素
	return true;
}

_Bool ListPriorElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr)
{
	ElemType *ptr = sqlistptr->elembase + 1;

	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	if (curelem == *sqlistptr->elembase)//第一个元素与curelem相等返回false
		return false;
	for (; ptr <= sqlistptr->elembase + sqlistptr->length - 1; ++ptr)//在线性表中寻找curelem元素
		if (curelem == *ptr)
			break;
	if (ptr > sqlistptr->elembase + sqlistptr->length - 1)//线性表中不存在curelem元素
		return false;
	*retelemptr = *(ptr - 1);//由指针返回前驱
	return true;
}

_Bool ListNextElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr)
{
	ElemType *ptr = sqlistptr->elembase;

	if (NULL == sqlistptr->elembase)//如果表不存在,退出
		exit(EXIT_FAILURE);
	if (curelem == *(sqlistptr->elembase + sqlistptr->length - 1))//最后一个元素与curelem相等返回false
		return false;
	for (; ptr <= sqlistptr->elembase + sqlistptr->length - 2; ++ptr)//在线性表中寻找curelem元素
		if (curelem == *ptr)
			break;
	if (ptr > sqlistptr->elembase + sqlistptr->length - 2)//线性表中不存在curelem元素
		return false;
	*retelemptr = *(ptr + 1);//由指针返回后继
	return true;
}



void ListTraverse_sq(SqList *const sqlistptr)
{
	ElemType *lastelemptr = sqlistptr->elembase + sqlistptr->length - 1;//表尾元素的位置

	for (ElemType *p = sqlistptr->elembase; p <= lastelemptr; ++p)//依次输出表中的数据元素
		printf("%d ", *p);
	printf("\n");
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