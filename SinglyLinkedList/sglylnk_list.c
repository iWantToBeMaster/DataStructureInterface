#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "sglylnk_list.h"

_Bool NodeAllocation(SLnkPosition *posptr, SglyLnkElemType elem);
void NodeFree(SLnkPosition *posptr);

_Bool ListInitial_slnk(SLnkList *const slnklistptr)
{
	if (!NodeAllocation(&slnklistptr->head,INT_MAX))//为头结点分配空间
		return false;
	slnklistptr->rear = slnklistptr->head;//初始化尾指针
	slnklistptr->length = 0;//表长度初始化为0
	return true;
}

void ListDestroy_slnk(SLnkList *const slnklistptr)
{
	SLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head;//从头结点开始释放结点空间
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->head = slnklistptr->rear = NULL;//表结构置空
	slnklistptr->length = 0;//表长度值0
}

void ListClear_slnk(SLnkList *const slnklistptr)
{
	SLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头节点的下一个结点开始释放结点空间,以保留头结点
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->head->next = NULL;//置空
	slnklistptr->rear = slnklistptr->head;//重置尾指针
	slnklistptr->length = 0;//重置链表长度
}

_Bool ListInsNodeFirst_slnk(SLnkList *const slnklistptr, const SLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//头节点之后的结点链接到inspos的后面
	slnklistptr->head->next = inspos;					//inspos及后面的结点链接到头节点的后面
	if (slnklistptr->rear == slnklistptr->head)			//如果之前为空表,则设置尾指针
		slnklistptr->rear = slnklistptr->head->next;
	++slnklistptr->length;								//链表长度加1
	return true;
}

_Bool ListDelNodeFirst_slnk(SLnkList *const slnklistptr, SLnkPosition *const slnkposret)
{
	if (NULL == slnklistptr->head->next)//如果表为空,返回失败
		return false;
	*slnkposret = slnklistptr->head->next;//由指针slnkposret返回将删除的结点
	if (slnklistptr->rear == slnklistptr->head->next)//如果之前表长度为1,则设置尾指针
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;//删除操作
	--slnklistptr->length;//链表长度减1
	return true;
}

void ListAppend_slnk(SLnkList *const slnklistptr, SLnkPosition slnkposhead)
{
	SLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)//计算结点链的长度
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;//将slnkposhead链接到链表的后面
	slnklistptr->rear = p;//重新设置尾指针
	slnklistptr->length += cnt;//重置表长度
}

_Bool ListRemoveRear_slnk(SLnkList *const slnklistptr, SLnkPosition *slnkposret)
{
	SLnkPosition p = slnklistptr->head;
	if (slnklistptr->head == slnklistptr->rear)//如果表为空,则返回false
		return false;
	while ((p->next != slnklistptr->rear) && p->next)//求尾结点的前驱 
		p = p->next;
	*slnkposret = slnklistptr->rear;//由指针slnkposret返回将删除的结点
	p->next = NULL;
	slnklistptr->rear = p;//重置尾指针
	--slnklistptr->length;//链表长度减1
	return true;
}

_Bool ListInsNodeBefore_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos)
{
	SLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next)//求lspos的前驱结点
		p = p->next;
	if (NULL == p->next)//如果没有找到前驱,则返回失败
		return false;
	inspos->next = lspos;//将lspos及后面的结点链接到inspos的后面
	p->next = inspos;//将inspos及后面的结点链接到lspos前驱的后面
	++slnklistptr->length;//链表长度加1
	return true;
}

_Bool ListInsNodeAfter_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos)
{
	SLnkPosition p = slnklistptr->head;
	while (p && (p != lspos))//表中是否存在lspos结点
		p = p->next;
	if (NULL == p)//表中不存在lspos结点,返回false
		return false;
	inspos->next = lspos->next;//将lspos后面的结点链接到inpos结点的后面
	lspos->next = inspos;//将inspos及后面的结点链接到lspos的后面
	if (slnklistptr->rear == p)//如果时插在尾结点的后面,则重置尾结点
		slnklistptr->rear = inspos;
	++slnklistptr->length;//表的长度加1
	return true;
}

void ListSetCurElem_slnk(SLnkPosition curpos, const SglyLnkElemType elem)
{
	curpos->elem = elem;//设置当前结点的元素的值
}

SglyLnkElemType ListGetCurElem_slnk(SLnkPosition curpos)
{
	return curpos->elem;//返回当前结点元素的值
}

_Bool ListIsEmpty_slnk(const SLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//如果表为空,返回true,否则返回false
}

int ListLength_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->length;//返回表的长度
}

SLnkPosition ListGetHead_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->head;//返回表的头结点
}

SLnkPosition ListGetRear_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->rear;//返回表的尾结点
}

_Bool ListPriorPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos)
{
	SLnkPosition p = slnklistptr->head;

	while (p->next && (curpos != p->next))//求curpos结点的前驱
		p = p->next;
	if (NULL == p->next)//如果前驱不存在,返回false
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);//由指针retpos返回前驱
	return true;
}

_Bool ListNextPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);//由retpos返回当前结点的后继
	return true;
}

_Bool ListLocatePos_slnk(const SLnkList *const slnklistptr, const int index, SLnkPosition *retpos)
{
	int i = 0;
	SLnkPosition p = slnklistptr->head;

	if (index<1 || index>slnklistptr->length)//索引不合法,失败处理
	{
		*retpos = NULL;
		return false;
	}
	while (p)//求第index个结点的位置
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	*retpos = p;//由指针retpos返回结点位置
	return true;
}

_Bool ListLocateElem_slnk(const SLnkList *const slnklistptr, const SglyLnkElemType elem, _Bool(*compare)(SglyLnkElemType, SglyLnkElemType), SLnkPosition *retpos)
{
	SLnkPosition p = slnklistptr->head->next;

	while (p)//求第一个与elem满足compare()关系的结点
	{
		if ((*compare)(p->elem, elem))
			break;
		p = p->next;
	}
	if (NULL == p)//如果不存在,失败处理
	{
		*retpos = NULL;
		return false;
	}
	*retpos = p;//由指针返回该结点
	return true;
}

void ListTraverse_slnk(const SLnkList *const slnklistptr)
{
	SLnkPosition p = slnklistptr->head->next;

	while (p)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

_Bool NodeAllocation(SLnkPosition *posptr, SglyLnkElemType elem)
{
	if (NULL == (*posptr = (SLnkPosition)malloc(sizeof(SLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void NodeFree(SLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e2 <= e2;
}
