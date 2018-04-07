#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cycsglylnk_list.h"

_Bool NodeAllocation(CycSLnkPosition *posptr, CycSglyLnkElemType elem);
void NodeFree(CycSLnkPosition *posptr);

_Bool ListInitial_cycslnk(CycSLnkList *const slnklistptr)
{
	if (!NodeAllocation(&slnklistptr->head, INT_MAX))//为头结点分配空间
		return false;
	slnklistptr->rear = slnklistptr->head;//初始化尾指针
	slnklistptr->rear->next = slnklistptr->head;//首尾相链
	slnklistptr->length = 0;//表长度初始化为0
	return true;
}

void ListDestroy_cycslnk(CycSLnkList *const slnklistptr)
{
	CycSLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头结点的下一个结点开始释放结点空间
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	NodeFree(&slnklistptr->head);//释放头结点空间
	slnklistptr->head = slnklistptr->rear = NULL;//表结构置空
	slnklistptr->length = 0;//表长度置0
}

void ListClear_cycslnk(CycSLnkList *const slnklistptr)
{
	CycSLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//从头节点的下一个结点开始释放结点空间,以保留头结点
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->rear = slnklistptr->head;//重置尾指针
	slnklistptr->rear->next = slnklistptr->head;//首尾相链
	slnklistptr->length = 0;//重置链表长度
}

_Bool ListInsNodeFirst_cycslnk(CycSLnkList *const slnklistptr, const CycSLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//头节点之后的结点链接到inspos的后面
	slnklistptr->head->next = inspos;					//inspos及后面的结点链接到头节点的后面
	if (0 == slnklistptr->length)			//如果之前为空表,则设置尾指针
	{
		slnklistptr->rear = inspos;
		slnklistptr->rear->next = slnklistptr->head;//首尾相连
	}
	++slnklistptr->length;								//链表长度加1
	return true;
}

_Bool ListDelNodeFirst_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition *const slnkposret)
{
	if (NULL == slnklistptr->head->next)						//如果表为空,返回失败
		return false;
	*slnkposret = slnklistptr->head->next;						//由指针slnkposret返回将删除的结点
	if (1 == slnklistptr->length)								//如果之前表长度为1,则设置尾指针
	{
		slnklistptr->rear = slnklistptr->head;
		slnklistptr->rear->next = slnklistptr->head;			//首尾相链
	}
	slnklistptr->head->next = slnklistptr->head->next->next;	//删除操作
	--slnklistptr->length;										//链表长度减1
	return true;
}

void ListAppend_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition slnkposhead)
{
	CycSLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)									//计算结点链的长度
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;			//将slnkposhead链接到链表的后面
	slnklistptr->rear = p;							//重新设置尾指针
	slnklistptr->rear->next = slnklistptr->head;	//首尾相链
	slnklistptr->length += cnt;						//重置表长度
}

_Bool ListRemoveRear_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition *slnkposret)
{
	CycSLnkPosition p = slnklistptr->head;
	if (0 == slnklistptr->length)						//如果表为空,则返回false
		return false;
	while ((p->next != slnklistptr->rear) && p->next)	//求尾结点的前驱 
		p = p->next;
	*slnkposret = slnklistptr->rear;					//由指针slnkposret返回将删除的结点
	p->next = NULL;
	slnklistptr->rear = p;								//重置尾指针
	slnklistptr->rear->next = slnklistptr->head;		//首尾相链
	--slnklistptr->length;								//链表长度减1
	return true;
}

_Bool ListInsNodeBefore_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition inspos)
{
	CycSLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next != slnklistptr->head)	//求lspos的前驱结点
		p = p->next;
	inspos->next = lspos;										//将lspos及后面的结点链接到inspos的后面
	p->next = inspos;											//将inspos及后面的结点链接到lspos前驱的后面
	if (p->next == slnklistptr->head)
	{
		slnklistptr->rear = inspos;
		slnklistptr->rear->next = slnklistptr->head;			//首尾相链
	}
	++slnklistptr->length;										//链表长度加1
	return true;
}

_Bool ListInsNodeAfter_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition inspos)
{
	CycSLnkPosition p = slnklistptr->head->next;
	while (p != slnklistptr->head && p != lspos)//表中是否存在lspos结点
		p = p->next;
	inspos->next = lspos->next;				//将lspos后面的结点链接到inpos结点的后面
	lspos->next = inspos;					//将inspos及后面的结点链接到lspos的后面
	if (slnklistptr->rear == p)				//如果时插在尾结点的后面,则重置尾结点
	{
		slnklistptr->rear = inspos;
		slnklistptr->rear->next = slnklistptr->head;//首尾相链
	}
	++slnklistptr->length;					//表的长度加1
	return true;
}

void ListSetCurElem_cycslnk(CycSLnkPosition curpos, const CycSglyLnkElemType elem)
{
	curpos->elem = elem;//设置当前结点的元素的值
}

CycSglyLnkElemType ListGetCurElem_cycslnk(CycSLnkPosition curpos)
{
	return curpos->elem;//返回当前结点元素的值
}

_Bool ListIsEmpty_cycslnk(const CycSLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//如果表为空,返回true,否则返回false
}

int ListLength_cycslnk(const CycSLnkList *const slnklistptr)
{
	return slnklistptr->length;//返回表的长度
}

CycSLnkPosition ListGetHead_cycslnk(const CycSLnkList *const slnklistptr)
{
	return slnklistptr->head;//返回表的头结点
}

CycSLnkPosition ListGetRear_cycslnk(const CycSLnkList *const slnklistptr)
{
	return slnklistptr->rear;//返回表的尾结点
}

_Bool ListPriorPos_cycslnk(const CycSLnkList *const slnklistptr, const CycSLnkPosition curpos, CycSLnkPosition *retpos)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p->next != slnklistptr->head && (curpos != p->next))						//求curpos结点的前驱
		p = p->next;
	*retpos = (p == slnklistptr->head->next ? slnklistptr->rear : p);				//由指针retpos返回前驱
	return true;
}

_Bool ListNextPos_cycslnk(const CycSLnkList *const slnklistptr, const CycSLnkPosition curpos, CycSLnkPosition *retpos)
{
	*retpos = (curpos == slnklistptr->rear ? slnklistptr->head->next : curpos->next);//由retpos返回当前结点的后继
	return true;
}

_Bool ListLocatePos_cycslnk(const CycSLnkList *const slnklistptr, const int index, CycSLnkPosition *retpos)
{
	int i = 0;
	CycSLnkPosition p = slnklistptr->head->next;

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

_Bool ListLocateElem_cycslnk(const CycSLnkList *const slnklistptr, const CycSglyLnkElemType elem, _Bool(*compare)(CycSglyLnkElemType, CycSglyLnkElemType), CycSLnkPosition *retpos)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p!=slnklistptr->head)//求第一个与elem满足compare()关系的结点
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

void ListTraverse_cycslnk(const CycSLnkList *const slnklistptr)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p != slnklistptr->head)//依次输出链表中每一个结点的元素的值
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

_Bool NodeAllocation(CycSLnkPosition *posptr, CycSglyLnkElemType elem)
{
	if (NULL == (*posptr = (CycSLnkPosition)malloc(sizeof(CycSLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void NodeFree(CycSLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e2 <= e2;
}
