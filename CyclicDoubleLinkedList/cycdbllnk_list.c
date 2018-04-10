#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cycdbllnk_list.h"

_Bool CycDblLstNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem);
void CycDblLstNodeFree(CycDblLnkPosition *posptr);

_Bool ListInitial_dbllnk(CycDblLnkList *const slnklistptr)
{
	if (!CycDblLstNodeAllocation(&slnklistptr->head, INT_MAX))//为头结点分配空间
		return false;
	slnklistptr->head->prev = NULL;//前驱置空
	slnklistptr->head->next = NULL;//后继置空
	slnklistptr->rear = slnklistptr->head;//初始化尾指针
	slnklistptr->length = 0;//表长度初始化为0
	return true;
}

void ListDestroy_dbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头结点开始释放结点空间
	while (p!= slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycDblLstNodeFree(&p);
	}
	CycDblLstNodeFree(&slnklistptr->head);//释放头结点
	slnklistptr->head = slnklistptr->rear = NULL;//表结构置空
	slnklistptr->length = 0;//表长度值0
}

void ListClear_dbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头节点的下一个结点开始释放结点空间,以保留头结点
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycDblLstNodeFree(&p);
	}
	slnklistptr->head->next = NULL;//置空
	slnklistptr->rear = slnklistptr->head;//重置尾指针
	slnklistptr->head->prev = NULL;//前驱置空
	slnklistptr->head->next = NULL;//后继置空
	slnklistptr->length = 0;//重置链表长度
}

_Bool ListInsNodeFirst_dbllnk(CycDblLnkList *const slnklistptr, const CycDblLnkPosition inspos)
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

_Bool ListDelNodeFirst_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *const slnkposret)
{
	if (0 == slnklistptr->length)//如果表为空,返回失败
		return false;
	*slnkposret = slnklistptr->head->next;//由指针slnkposret返回将删除的结点
	if (slnklistptr->rear == slnklistptr->head->next)//如果之前表长度为1,则设置尾指针
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;//头结点的后继为下下一个结点
	slnklistptr->head->next->prev = slnklistptr->head;//头结点的后继的前驱为头结点
	--slnklistptr->length;//链表长度减1
	return true;
}

void ListAppend_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition slnkposhead)
{
	CycDblLnkPosition p = slnkposhead;
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

_Bool ListRemoveRear_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *slnkposret)
{
	CycDblLnkPosition p = slnklistptr->head;

	if (slnklistptr->head == slnklistptr->rear)//如果表为空,则返回false
		return false;
	while ((p->next != slnklistptr->rear) && p->next!=slnklistptr->head)//求尾结点的前驱 
		p = p->next;
	*slnkposret = slnklistptr->rear;//由指针slnkposret返回将删除的结点
	p->next = slnklistptr->head;
	slnklistptr->rear = p;//重置尾指针
	--slnklistptr->length;//链表长度减1
	return true;
}

_Bool ListInsNodeBefore_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next!=slnklistptr->head)//求lspos的前驱结点
		p = p->next;
	if (slnklistptr->head == p->next)//如果没有找到前驱,则返回失败
		return false;
	inspos->next = lspos;//将lspos及后面的结点链接到inspos的后面
	p->next = inspos;//将inspos及后面的结点链接到lspos前驱的后面
	lspos->prev = inspos;//lspos的前驱指向inspos
	inspos->prev = p;//inspos的前驱指向p
	++slnklistptr->length;//链表长度加1
	return true;
}

_Bool ListInsNodeAfter_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head;

	while (p!= slnklistptr->head && (p != lspos))//表中是否存在lspos结点
		p = p->next;
	if (slnklistptr->head == p)//表中不存在lspos结点,返回false
		return false;
	inspos->next = lspos->next;//将lspos后面的结点链接到inpos结点的后面
	lspos->next = inspos;//将inspos及后面的结点链接到lspos的后面
	inspos->prev = lspos;
	if (slnklistptr->head != inspos->next)
		inspos->next->prev = inspos;
	if (slnklistptr->rear == p)//如果时插在尾结点的后面,则重置尾结点
		slnklistptr->rear = inspos;
	++slnklistptr->length;//表的长度加1
	return true;
}

_Bool ListDelNodeBefore_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head, q = slnklistptr->head;

	*retpos = NULL;
	while ((p->next != lspos) && p->next!= slnklistptr->head)//求lspos的前驱结点
		p = p->next;
	if (slnklistptr->head == p->next)//如果没有找到前驱,则返回失败
		return false;
	while ((q->next != p) && (q->next!= slnklistptr->head))//求p的前驱结点
		q = q->next;
	if (slnklistptr->head == q->next)//如果没有找到前驱,则返回失败
		return false;
	q->next = p->next;//建立后继关系
	lspos->prev = q;//建立前驱关系
	*retpos = p;//指针返回删除的结点
	--slnklistptr->length;//表长度减1
	return true;

}

_Bool ListDelNodeAfter_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head;

	*retpos = NULL;
	while (p!= slnklistptr->head && (p != lspos))//表中是否存在lspos结点
		p = p->next;
	if (slnklistptr->head == p || slnklistptr->head == p->next)//表中不存在lspos结点,或者lspos没有后继结点,返回false
		return false;
	lspos->next = lspos->next->next;//建立后继关系
	lspos->next->prev = lspos;//建立前驱关系
	*retpos = lspos->next;//指针返回删除的结点
	--slnklistptr->length;//表长度减1
	return true;
}

void ListSetCurElem_dbllnk(CycDblLnkPosition curpos, const CycDblLnkElemType elem)
{
	curpos->elem = elem;//设置当前结点的元素的值
}

CycDblLnkElemType ListGetCurElem_dbllnk(CycDblLnkPosition curpos)
{
	return curpos->elem;//返回当前结点元素的值
}

_Bool ListIsEmpty_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//如果表为空,返回true,否则返回false
}

int ListLength_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->length;//返回表的长度
}

CycDblLnkPosition ListGetHead_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->head;//返回表的头结点
}

CycDblLnkPosition ListGetRear_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->rear;//返回表的尾结点
}

_Bool ListPriorPos_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head;

	while (p->next!= slnklistptr->head && (curpos != p->next))//求curpos结点的前驱
		p = p->next;
	if (slnklistptr->head == p->next)//如果前驱不存在,返回false
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);//由指针retpos返回前驱
	return true;
}

_Bool ListNextPos_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);//由retpos返回当前结点的后继
	return true;
}

_Bool ListLocatePos_dbllnk(const CycDblLnkList *const slnklistptr, const int index, CycDblLnkPosition *retpos)
{
	int i = 0;
	CycDblLnkPosition p = slnklistptr->head;

	if (index<1 || index>slnklistptr->length)//索引不合法,失败处理
	{
		*retpos = NULL;
		return false;
	}
	while (p!= slnklistptr->head)//求第index个结点的位置
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	*retpos = p;//由指针retpos返回结点位置
	return true;
}

_Bool ListLocateElem_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkElemType elem, _Bool(*compare)(CycDblLnkElemType, CycDblLnkElemType), CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p!= slnklistptr->head)//求第一个与elem满足compare()关系的结点
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

void ListTraverseAscend_dbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p!= slnklistptr->head)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void ListTraverseDescend_dbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->rear;

	while (p != slnklistptr->head)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->prev;
	}
	printf("\n");
}

_Bool CycDblLstNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem)
{
	if (NULL == (*posptr = (CycDblLnkPosition)malloc(sizeof(CycDblLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void CycDblLstNodeFree(CycDblLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 <= e2;
}
