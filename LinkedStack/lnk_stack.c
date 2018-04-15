#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lnk_stack.h"

_Bool StackInit_lnk(LnkStack *const lnsptr)
{
	lnsptr->top = (LnkStackNode *)malloc(sizeof(LnkStackNode));//维护易于操作的表头(栈顶)
	if (NULL == lnsptr->top)
		return false;
	lnsptr->top->next = NULL;
	lnsptr->bottom = lnsptr->top;//初始化栈底
	lnsptr->stacksize = 0;//初始化栈大小
	return true;
}

_Bool StackDestroy_lnk(LnkStack *const lnsptr)
{
	LnkStackNode *p = lnsptr->top, *q = NULL;

	if (NULL == p)//栈结构不存在返回false
		return false;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);//释放空间
	}
	lnsptr->top = lnsptr->bottom = NULL;//栈顶和栈底指针置空
	lnsptr->stacksize = 0;//栈大小置0
	return true;
}

_Bool StackClear_lnk(LnkStack *const lnsptr)
{
	LnkStackNode *p = lnsptr->top->next, *q = NULL;

	while (p)
	{
		q = p;
		p = p->next;
		free(q);//释放空间
	}
	lnsptr->bottom = lnsptr->top;//重置栈底指针
	lnsptr->stacksize = 0;//栈大小置0
	return true;
}

_Bool StackIsEmpty_lnk(const LnkStack *const lnsptr)
{
	return 0 == lnsptr->stacksize;
}

_Bool StackSize_lnk(const LnkStack *const lnsptr, int *const retsizeptr)
{
	if (lnsptr->top == NULL)//栈结构不存在返回false
		return false;
	*retsizeptr = lnsptr->stacksize;
	return true;
}

_Bool StackGetTop_lnk(const LnkStack *const lnsptr, LnkStackElemType *const retptr)
{
	if (lnsptr->top == lnsptr->bottom)//栈空返回false
		return false;
	*retptr = lnsptr->top->elem;//由指针返回栈顶元素
	return true;
}

_Bool StackPush_lnk(LnkStack *const lnsptr, const LnkStackElemType *const elemptr)
{
	LnkStackNode *t = NULL;

	t = (LnkStackNode *)malloc(sizeof(LnkStackNode));
	if (NULL == t)
		return false;
	t->elem = *elemptr;
	t->next = lnsptr->top->next;
	lnsptr->top->next = t;
	if (0 == lnsptr->stacksize)
		lnsptr->bottom = t;
	++lnsptr->stacksize;
	return true;
}

_Bool StackPop_lnk(LnkStack *const lnsptr, LnkStackElemType *const retptr)
{
	LnkStackNode *t = NULL;

	if (lnsptr->bottom == lnsptr->top)
		return false;
	*retptr = lnsptr->top->next->elem;
	t = lnsptr->top;
	lnsptr->top = lnsptr->top->next;
	free(t);
	--lnsptr->stacksize;
	return true;
}

void StackTraverse_lnk(const LnkStack *const lnsptr)
{
	LnkStackNode *p = lnsptr->top->next;

	while (p)
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}