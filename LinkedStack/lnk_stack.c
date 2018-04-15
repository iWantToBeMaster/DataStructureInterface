#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lnk_stack.h"

_Bool StackInit_lnk(LnkStack *const lnsptr)
{
	lnsptr->top = (LnkStackNode *)malloc(sizeof(LnkStackNode));//ά�����ڲ����ı�ͷ(ջ��)
	if (NULL == lnsptr->top)
		return false;
	lnsptr->top->next = NULL;
	lnsptr->bottom = lnsptr->top;//��ʼ��ջ��
	lnsptr->stacksize = 0;//��ʼ��ջ��С
	return true;
}

_Bool StackDestroy_lnk(LnkStack *const lnsptr)
{
	LnkStackNode *p = lnsptr->top, *q = NULL;

	if (NULL == p)//ջ�ṹ�����ڷ���false
		return false;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);//�ͷſռ�
	}
	lnsptr->top = lnsptr->bottom = NULL;//ջ����ջ��ָ���ÿ�
	lnsptr->stacksize = 0;//ջ��С��0
	return true;
}

_Bool StackClear_lnk(LnkStack *const lnsptr)
{
	LnkStackNode *p = lnsptr->top->next, *q = NULL;

	while (p)
	{
		q = p;
		p = p->next;
		free(q);//�ͷſռ�
	}
	lnsptr->bottom = lnsptr->top;//����ջ��ָ��
	lnsptr->stacksize = 0;//ջ��С��0
	return true;
}

_Bool StackIsEmpty_lnk(const LnkStack *const lnsptr)
{
	return 0 == lnsptr->stacksize;
}

_Bool StackSize_lnk(const LnkStack *const lnsptr, int *const retsizeptr)
{
	if (lnsptr->top == NULL)//ջ�ṹ�����ڷ���false
		return false;
	*retsizeptr = lnsptr->stacksize;
	return true;
}

_Bool StackGetTop_lnk(const LnkStack *const lnsptr, LnkStackElemType *const retptr)
{
	if (lnsptr->top == lnsptr->bottom)//ջ�շ���false
		return false;
	*retptr = lnsptr->top->elem;//��ָ�뷵��ջ��Ԫ��
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