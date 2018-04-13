#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sq_stack.h"

_Bool StackInit_sq(SqStack *const ssptr)
{
	ssptr->bottom = (StackElemType *)malloc(sizeof(StackElemType)*STACK_INIT_SIZE);//Ϊջ�����ʼ�ڴ�ռ�
	if (NULL == ssptr->bottom)//�������ʧ�ܷ���false
		return false;
	ssptr->top = ssptr->bottom;//��ʼ��ջ��ָ��
	ssptr->stacksize = 0;//��ʼ��ջ�Ĵ�С
	return true;
}

_Bool StackDestroy_sq(SqStack *const ssptr)
{
	if (NULL == ssptr->bottom)//ջ�ṹ������
		return false;
	free(ssptr->bottom);//�ͷ�ջ���ڴ�ռ�
	ssptr->bottom = NULL;//ջ���ÿ�
	ssptr->top = NULL;//ջ���ÿ�
	ssptr->stacksize = 0;//ջ�Ĵ�С��0
	return true;
}

_Bool StackClear_sq(SqStack *const ssptr)
{
	ssptr->bottom = (StackElemType *)realloc(ssptr->bottom, sizeof(StackElemType)*STACK_INIT_SIZE);//����ջ���ڴ�ռ��СΪ��ʼ�ռ��С
	if (NULL == ssptr->bottom)//�ڴ�ռ�����ʧ�ܷ���false
	{
		ssptr->top = NULL;//ջ��ָ������Ϊջ�ṹ�����ڵ�״̬
		ssptr->stacksize = 0;//ջ�Ĵ�С����Ϊջ�ṹ�����ڵ�״̬
		return false;
	}
	ssptr->top = ssptr->bottom;//����ջ��ָ��
	ssptr->stacksize = 0;//ջ�Ĵ�С����Ϊ0
	return true;
}

_Bool StackEmpty_sq(const SqStack *const ssptr)
{
	return ssptr->bottom == ssptr->top;
}

_Bool StackSize_sq(const SqStack *const ssptr, int *const retsizeptr)
{
	if (NULL == ssptr->bottom)//ջ�ṹ������
		return false;
	*retsizeptr = ssptr->top - ssptr->bottom;//��ָ�뷵��ջ�Ĵ�С
	return true;
}

_Bool StackGetTop_sq(const SqStack *const ssptr, StackElemType *const retptr)
{
	if (ssptr->bottom == ssptr->top)//���ջΪ�շ���false
		return false;
	*retptr = *(ssptr->top - 1);//��ָ�뷵��ջ��Ԫ�ص�ֵ
	return true;
}

_Bool StackPush_sq(SqStack *const ssptr, const StackElemType *const elemptr)
{
	int  cursize = ssptr->top - ssptr->bottom;

	if (ssptr->top - ssptr->bottom >= ssptr->stacksize)//���ջ��ǰ���ڴ�ռ��Ѿ���
	{
		ssptr->bottom = (StackElemType *)realloc(ssptr->bottom, sizeof(StackElemType)*(ssptr->stacksize + STACK_INCREMENT_SIZE));
		//׷���ڴ�ռ�
		if (NULL == ssptr->bottom)//׷���ڴ�ռ�ʧ��
		{
			ssptr->top = NULL;//ջ��ָ������Ϊջ�ṹ�����ڵ�״̬
			ssptr->stacksize = 0;//ջ�Ĵ�С����Ϊջ�ṹ�����ڵ�״̬
			return false;
		}
		ssptr->stacksize += STACK_INCREMENT_SIZE;//����ջ�ռ�Ĵ�С
		ssptr->top = ssptr->bottom + cursize;//����ջ��ָ�����¿ռ��λ��
	}
	*ssptr->top++ = *elemptr; //��ջ��ѹ�����ݲ�������ջ��ָ��
	return true;
}

_Bool StackPop_sq(SqStack *const ssptr, StackElemType *const retptr)
{
	if (ssptr->bottom == ssptr->top)//���ջΪ�շ���false;
		return true;
	*retptr = *--ssptr->top;//ջ�е������ݲ�������ջ��ָ��
	return true;
}

void StackTraverse_sq(const SqStack *const ssptr)
{
	const StackElemType *p = ssptr->bottom;

	while (p++ != ssptr->top)
		printf("%d ", *(p - 1));
	printf("\n");
}