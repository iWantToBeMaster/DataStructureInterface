#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "dbllnk_list.h"

_Bool NodeAllocation(DblLnkPosition *posptr, DblLnkElemType elem);
void NodeFree(DblLnkPosition *posptr);

_Bool ListInitial_dbllnk(DblLnkList *const slnklistptr)
{
	if (!NodeAllocation(&slnklistptr->head, INT_MAX))//为头结点分配空间
		return false;
	slnklistptr->head->prev = NULL;//前驱置空
	slnklistptr->head->next = NULL;//后继置空
	slnklistptr->rear = slnklistptr->head;//初始化尾指针
	slnklistptr->length = 0;//表长度初始化为0
	return true;
}

void ListDestroy_dbllnk(DblLnkList *const slnklistptr)
{
	DblLnkPosition p = NULL, q = NULL;

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

void ListClear_dbllnk(DblLnkList *const slnklistptr)
{
	DblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头节点的下一个结点开始释放结点空间,以保留头结点
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->head->next = NULL;//置空
	slnklistptr->rear = slnklistptr->head;//重置尾指针
	slnklistptr->head->prev = NULL;//前驱置空
	slnklistptr->head->next = NULL;//后继置空
	slnklistptr->length = 0;//重置链表长度
}

_Bool ListInsNodeFirst_dbllnk(DblLnkList *const slnklistptr, const DblLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//头节点之后的结点链接到inspos的后面
	slnklistptr->head->next = inspos;					//inspos及后面的结点链接到头节点的后面
	inspos->prev = slnklistptr->head;					//inspos的前驱指向头结点
	if (slnklistptr->rear == slnklistptr->head)			//如果之前为空表,则设置尾指针
		slnklistptr->rear = slnklistptr->head->next;
	else
		inspos->next->prev = inspos;					//头结点的后继的前驱指向inspos
	++slnklistptr->length;								//链表长度加1
	return true;
}

_Bool ListDelNodeFirst_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *const slnkposret)
{
	if (NULL == slnklistptr->head->next)//如果表为空,返回失败
		return false;
	*slnkposret = slnklistptr->head->next;//由指针slnkposret返回将删除的结点
	if (slnklistptr->rear == slnklistptr->head->next)//如果之前表长度为1,则设置尾指针
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;//头结点的后继为下下一个结点
	slnklistptr->head->next->prev = slnklistptr->head;//头结点的后继的前驱为头结点
	--slnklistptr->length;//链表长度减1
	return true;
}

void ListAppend_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition slnkposhead)
{
	DblLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)//计算结点链的长度
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;//将slnkposhead链接到链表的后面
	slnkposhead->prev = slnklistptr->rear;//slnkposhead的前驱指向表尾
	slnklistptr->rear = p;//重新设置尾指针
	slnklistptr->length += cnt;//重置表长度
}

_Bool ListRemoveRear_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *slnkposret)
{
	DblLnkPosition p = slnklistptr->head;
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

_Bool ListInsNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos)
{
	DblLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next)//求lspos的前驱结点
		p = p->next;
	if (NULL == p->next)//如果没有找到前驱,则返回失败
		return false;
	inspos->next = lspos;//将lspos及后面的结点链接到inspos的后面
	p->next = inspos;//将inspos及后面的结点链接到lspos前驱的后面
	lspos->prev = inspos;//lspos的前驱指向inspos
	inspos->prev = p;//inspos的前驱指向p
	++slnklistptr->length;//链表长度加1
	return true;
}

_Bool ListInsNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos)
{
	DblLnkPosition p = slnklistptr->head;
	while (p && (p != lspos))//表中是否存在lspos结点
		p = p->next;
	if (NULL == p)//表中不存在lspos结点,返回false
		return false;
	inspos->next = lspos->next;//将lspos后面的结点链接到inpos结点的后面
	lspos->next = inspos;//将inspos及后面的结点链接到lspos的后面
	inspos->prev = lspos;
	if (NULL != inspos->next)
		inspos->next->prev = inspos;
	if (slnklistptr->rear == p)//如果时插在尾结点的后面,则重置尾结点
		slnklistptr->rear = inspos;
	++slnklistptr->length;//表的长度加1
	return true;
}

void ListSetCurElem_dbllnk(DblLnkPosition curpos, const DblLnkElemType elem)
{
	curpos->elem = elem;//设置当前结点的元素的值
}

DblLnkElemType ListGetCurElem_dbllnk(DblLnkPosition curpos)
{
	return curpos->elem;//返回当前结点元素的值
}

_Bool ListIsEmpty_dbllnk(const DblLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//如果表为空,返回true,否则返回false
}

int ListLength_dbllnk(const DblLnkList *const slnklistptr)
{
	return slnklistptr->length;//返回表的长度
}

DblLnkPosition ListGetHead_dbllnk(const DblLnkList *const slnklistptr)
{
	return slnklistptr->head;//返回表的头结点
}

DblLnkPosition ListGetRear_dbllnk(const DblLnkList *const slnklistptr)
{
	return slnklistptr->rear;//返回表的尾结点
}

_Bool ListPriorPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos)
{
	DblLnkPosition p = slnklistptr->head;

	while (p->next && (curpos != p->next))//求curpos结点的前驱
		p = p->next;
	if (NULL == p->next)//如果前驱不存在,返回false
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);//由指针retpos返回前驱
	return true;
}

_Bool ListNextPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);//由retpos返回当前结点的后继
	return true;
}

_Bool ListLocatePos_dbllnk(const DblLnkList *const slnklistptr, const int index, DblLnkPosition *retpos)
{
	int i = 0;
	DblLnkPosition p = slnklistptr->head;

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

_Bool ListLocateElem_dbllnk(const DblLnkList *const slnklistptr, const DblLnkElemType elem, _Bool(*compare)(DblLnkElemType, DblLnkElemType), DblLnkPosition *retpos)
{
	DblLnkPosition p = slnklistptr->head->next;

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

void ListTraverseAscend_dbllnk(const DblLnkList *const slnklistptr)
{
	DblLnkPosition p = slnklistptr->head->next;

	while (p)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void ListTraverseDescend_dbllnk(const DblLnkList *const slnklistptr)
{
	DblLnkPosition p = slnklistptr->rear;

	while (p!=slnklistptr->head)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->prev;
	}
	printf("\n");
}

_Bool NodeAllocation(DblLnkPosition *posptr, DblLnkElemType elem)
{
	if (NULL == (*posptr = (DblLnkPosition)malloc(sizeof(DblLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void NodeFree(DblLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e2 <= e2;
}
