#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "sglylnk_list.h"

_Bool NodeAllocation(SLnkPosition *posptr, ElemType elem);
void NodeFree(SLnkPosition *posptr);

_Bool ListInitial_slnk(SLnkList *const slnklistptr)
{
	if (!NodeAllocation(slnklistptr->head,INT_MAX))//为头结点分配空间
		return false;
	slnklistptr->rear = slnklistptr->head;
	slnklistptr->length = 0;
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
	slnklistptr->head = slnklistptr->rear = NULL;
	slnklistptr->length = 0;
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
	slnklistptr->head->next = NULL;
	slnklistptr->rear = slnklistptr->head;
	slnklistptr->length = 0;
}

_Bool ListInsNodeFirst_slnk(SLnkList *const slnklistptr, SLnkPosition slnkpos)
{
	slnkpos->next = slnklistptr->head->next;
	slnklistptr->head->next = slnkpos;
	if (slnklistptr->rear == slnklistptr->head)
		slnklistptr->rear = slnklistptr->head->next;
	++slnklistptr->length;
	return true;
}

_Bool ListDelNodeFirst_slnk(SLnkList *const slnklistptr, SLnkPosition *const slnkposret)
{
	if (NULL == slnklistptr->head->next)
		return false;
	*slnkposret = slnklistptr->head->next;
	if (slnklistptr->rear == slnklistptr->head->next)
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;
	--slnklistptr->length;
	return true;
}

void ListAppend_slnk(SLnkList *const slnklistptr, SLnkPosition slnkposhead)
{
	SLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;
	slnklistptr->length += cnt;
}

_Bool ListRemoveRear_slnk(SLnkList *const slnklistptr, SLnkPosition *slnkposret)
{
	SLnkPosition p = slnklistptr->head;
	if (slnklistptr->head == slnklistptr->rear)
		return false;
	while (p->next)
		p = p->next;
	*slnkposret = slnklistptr->rear;
	p->next = NULL;
	slnklistptr->rear = p;
	--slnklistptr->length;
	return true;
}

_Bool ListInsNodeBefore_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos)
{
	SLnkPosition p = slnklistptr->head;
	while (p->next)
	{
		if (lspos == p->next)
			break;
		p = p->next;
	}
	if (NULL == p->next)
		return false;
	inspos->next = lspos;
	p->next = inspos;
	++slnklistptr->length;
	return true;
}

_Bool ListInsNodeAfter_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos)
{
	SLnkPosition p = slnklistptr->head;
	while (p)
	{
		if (lspos == p)
			break;
		p = p->next;
	}
	if (NULL == p)
		return false;
	inspos->next = lspos->next;
	lspos->next = inspos;
	++slnklistptr->length;
	return true;
}

void ListSetCurElem_slnk(SLnkPosition curpos, const ElemType elem)
{
	curpos->elem = elem;
}

ElemType ListGetCurElem_slnk(SLnkPosition curpos)
{
	return curpos->elem;
}

_Bool ListIsEmpty_slnk(const SLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;
}

int ListLength_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->length;
}

SLnkPosition ListGetHead_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->head;
}

SLnkPosition ListGetRear_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->rear;
}

_Bool ListPriorPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos)
{
	SLnkPosition p = slnklistptr->head;

	while (p->next)
	{
		if (curpos == p->next)
			break;
		p = p->next;
	}
	if (NULL == p->next)
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);
	return true;
}

_Bool ListNextPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);
	return true;
}

_Bool ListLocatePos_slnk(const SLnkList *const slnklistptr, const int index, SLnkPosition *retpos)
{
	int i = 0;
	SLnkPosition p = slnklistptr->head;

	if (index<1 || index>slnklistptr->length)
	{
		*retpos = NULL;
		return false;
	}
	while (p)
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	if (NULL == p)
	{
		*retpos = NULL;
		return false;
	}
	*retpos = p;
	return true;
}

_Bool ListLocateElem_slnk(const SLnkList *const slnklistptr, const ElemType elem, _Bool(*compare)(ElemType, ElemType), SLnkPosition *retpos)
{
	SLnkPosition p = slnklistptr->head->next;

	while (p)
	{
		if ((*compare)(p->elem, elem))
			break;
		p = p->next;
	}
	if (NULL == p)
	{
		*retpos = NULL;
		return false;
	}
	*retpos = p;
	return true;
}

void ListTraverse_slnk(const SLnkList *const slnklistptr)
{
	SLnkPosition p = slnklistptr->head->next;

	while (p)
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

_Bool NodeAllocation(SLnkPosition *posptr, ElemType elem)
{
	if (NULL == (*posptr = malloc(sizeof(SLnkNode))))
		return false;
	return true;
}

void NodeFree(SLnkPosition *posptr)
{
	free(*posptr);
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
