#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cycdbllnk_list.h"

_Bool CycListNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem);
void CycListNodeFree(CycDblLnkPosition *posptr);

_Bool ListInitial_cycdbllnk(CycDblLnkList *const slnklistptr)
{
	if (!CycListNodeAllocation(&slnklistptr->head, INT_MAX))//为头结点分配空间
		return false;
	slnklistptr->rear = slnklistptr->head;//初始化尾指针
	slnklistptr->rear->next = slnklistptr->head;//首尾相链
	slnklistptr->head->prev = slnklistptr->rear;//首尾相链
	slnklistptr->length = 0;//表长度初始化为0
	return true;
}

void ListDestroy_cycdbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头结点的下一个结点开始释放结点空间
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycListNodeFree(&p);
	}
	CycListNodeFree(&slnklistptr->head);//释放头结点空间
	slnklistptr->head = slnklistptr->rear = NULL;//表结构置空
	slnklistptr->length = 0;//表长度置0
}

void ListClear_cycdbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头节点的下一个结点开始释放结点空间,以保留头结点
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycListNodeFree(&p);
	}
	slnklistptr->rear = slnklistptr->head;//重置尾指针
	slnklistptr->rear->next = slnklistptr->head;//首尾相链
	slnklistptr->head->prev = slnklistptr->rear;//首尾相链
	slnklistptr->length = 0;//重置链表长度
}

_Bool ListInsNodeFirst_cycdbllnk(CycDblLnkList *const slnklistptr, const CycDblLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//头节点之后的结点链接到inspos的后面
	inspos->prev = slnklistptr->head;					//inspos结点的前驱置为头结点
	slnklistptr->head->next = inspos;					//inspos及后面的结点链接到头节点的后面
	inspos->next->prev = inspos;						//原来第一个结点的前驱置为inspos
	if (0 == slnklistptr->length)						//如果之前为空表,则设置尾指针
	{
		slnklistptr->rear = inspos;
		slnklistptr->rear->next = slnklistptr->head;	//首尾相连
		slnklistptr->head->prev = slnklistptr->rear;	//首尾相连
	}
	++slnklistptr->length;								//链表长度加1
	return true;
}

_Bool ListDelNodeFirst_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *const slnkposret)
{
	*slnkposret = NULL;
	if (slnklistptr->head == slnklistptr->rear)						//如果表为空,返回失败
		return false;
	*slnkposret = slnklistptr->head->next;						//由指针slnkposret返回将删除的结点
	if (1 == slnklistptr->length)								//如果之前表长度为1,则设置尾指针
	{
		slnklistptr->rear = slnklistptr->head;
		slnklistptr->rear->next = slnklistptr->head;			//首尾相链
		slnklistptr->head->prev = slnklistptr->rear;	//首尾相连
	}
	slnklistptr->head->next = slnklistptr->head->next->next;	//后继指针删除操作
	slnklistptr->head->next->prev = slnklistptr->head;			//前驱指针删除操作
	--slnklistptr->length;										//链表长度减1
	return true;
}

void ListAppend_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition slnkposhead)
{
	CycDblLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)									//计算结点链的长度
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;			//将slnkposhead链接到链表的后面
	slnkposhead->prev = slnklistptr->rear;			
	slnklistptr->rear = p;							//重新设置尾指针
	slnklistptr->rear->next = slnklistptr->head;	//首尾相链
	slnklistptr->head->prev = slnklistptr->rear;	//首尾相连
	slnklistptr->length += cnt;						//重置表长度
}

_Bool ListRemoveRear_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *slnkposret)
{
	CycDblLnkPosition p = NULL;
	if (0 == slnklistptr->length)						//如果表为空,则返回false
		return false;
	*slnkposret = slnklistptr->rear;					//由指针slnkposret返回将删除的结点
	p = slnklistptr->rear;
	slnklistptr->rear = slnklistptr->rear->prev;
	p->prev->next = slnklistptr->head;
	p->next->prev = p->prev;
	--slnklistptr->length;								//链表长度减1
	return true;
}

_Bool ListInsNodeBefore_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//表中是否存在lspos结点
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	p = lspos->prev;
	inspos->next = lspos;										//将lspos及后面的结点链接到inspos的后面
	lspos->prev = inspos;
	p->next = inspos;											//将inspos及后面的结点链接到lspos前驱的后面
	inspos->prev = p;
	if (p->next->next == slnklistptr->head)
		slnklistptr->rear = inspos;								//重置尾指针
	++slnklistptr->length;										//链表长度加1
	return true;
}

_Bool ListInsNodeAfter_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head->next;
	
	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//表中是否存在lspos结点
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	inspos->next = lspos->next;				//将lspos后面的结点链接到inpos结点的后面
	lspos->next->prev = inspos;
	lspos->next = inspos;					//将inspos及后面的结点链接到lspos的后面
	inspos->prev = lspos;
	if (slnklistptr->rear == p)				//如果时插在尾结点的后面,则重置尾结点
		slnklistptr->rear = inspos;
	++slnklistptr->length;					//表的长度加1
	return true;
}

_Bool ListDelNodeBefore_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next, q = NULL;

	*retpos = NULL;
	if (0 == slnklistptr->length)
		return false;
	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//表中是否存在lspos结点
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	p = lspos->prev->prev;
	q = lspos;
	if (lspos == slnklistptr->head->next)
	{
		p = slnklistptr->rear->prev;
		q = slnklistptr->head;
	}
	*retpos = p->next;
	p->next = q;
	q->prev = p;
	if (lspos == slnklistptr->head->next || lspos == slnklistptr->head)
		slnklistptr->rear = p;
	--slnklistptr->length;//表长度减1
	return true;
}

_Bool ListDelNodeAfter_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	*retpos = NULL;
	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//表中是否存在lspos结点
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	if (lspos->next == slnklistptr->head)
		p = slnklistptr->head;
	else
		p = lspos;
	*retpos = p->next;//指针返回删除的结点
	p->next = p->next->next;
	p->next->prev = p;
	--slnklistptr->length;
	return true;
}

void ListSetCurElem_cycdbllnk(CycDblLnkPosition curpos, const CycDblLnkElemType elem)
{
	curpos->elem = elem;//设置当前结点的元素的值
}

CycDblLnkElemType ListGetCurElem_cycdbllnk(CycDblLnkPosition curpos)
{
	return curpos->elem;//返回当前结点元素的值
}

_Bool ListIsEmpty_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//如果表为空,返回true,否则返回false
}

int ListLength_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->length;//返回表的长度
}

CycDblLnkPosition ListGetHead_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->head;//返回表的头结点
}

CycDblLnkPosition ListGetRear_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->rear;//返回表的尾结点
}

_Bool ListPriorPos_cycdbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	if (curpos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != curpos)//表中是否存在lspos结点
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	*retpos = (p == slnklistptr->head->next ? slnklistptr->rear : p);				//由指针retpos返回前驱
	return true;
}

_Bool ListNextPos_cycdbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;
	
	if (curpos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != curpos)//表中是否存在lspos结点
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	*retpos = (curpos == slnklistptr->rear ? slnklistptr->head->next : curpos->next);//由retpos返回当前结点的后继
	return true;
}

_Bool ListLocatePos_cycdbllnk(const CycDblLnkList *const slnklistptr, const int index, CycDblLnkPosition *retpos)
{
	int i = 0;
	CycDblLnkPosition p = slnklistptr->head->next;

	if (index<1 || index>slnklistptr->length)//索引不合法,失败处理
	{
		*retpos = NULL;
		return false;
	}
	while (p != slnklistptr->head)//求第index个结点的位置
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	*retpos = p;//由指针retpos返回结点位置
	return true;
}

_Bool ListLocateElem_cycdbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkElemType elem, _Bool(*compare)(CycDblLnkElemType, CycDblLnkElemType), CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p != slnklistptr->head)//求第一个与elem满足compare()关系的结点
	{
		if ((*compare)(p->elem, elem))
			break;
		p = p->next;
	}
	if (slnklistptr->head == p)//如果不存在,失败处理
	{
		*retpos = NULL;
		return false;
	}
	*retpos = p;//由指针返回该结点
	return true;
}

void ListTraverseAscend_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p != slnklistptr->head)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void ListTraverseDescend_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->rear;

	while (p != slnklistptr->head)
	{
		printf("%d ", p->elem);
		p = p->prev;
	}
	printf("\n");
}

_Bool CycListNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem)
{
	if (NULL == (*posptr = (CycDblLnkPosition)malloc(sizeof(CycDblLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void CycListNodeFree(CycDblLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 <= e2;
}
