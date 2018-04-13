#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sq_stack.h"

_Bool StackInit_sq(SqStack *const ssptr)
{
	ssptr->bottom = (StackElemType *)malloc(sizeof(StackElemType)*STACK_INIT_SIZE);//为栈分配初始内存空间
	if (NULL == ssptr->bottom)//如果分配失败返回false
		return false;
	ssptr->top = ssptr->bottom;//初始化栈顶指针
	ssptr->stacksize = 0;//初始化栈的大小
	return true;
}

_Bool StackDestroy_sq(SqStack *const ssptr)
{
	if (NULL == ssptr->bottom)//栈结构不存在
		return false;
	free(ssptr->bottom);//释放栈的内存空间
	ssptr->bottom = NULL;//栈底置空
	ssptr->top = NULL;//栈顶置空
	ssptr->stacksize = 0;//栈的大小置0
	return true;
}

_Bool StackClear_sq(SqStack *const ssptr)
{
	ssptr->bottom = (StackElemType *)realloc(ssptr->bottom, sizeof(StackElemType)*STACK_INIT_SIZE);//重置栈的内存空间大小为初始空间大小
	if (NULL == ssptr->bottom)//内存空间重置失败返回false
	{
		ssptr->top = NULL;//栈顶指针重置为栈结构不存在的状态
		ssptr->stacksize = 0;//栈的大小重置为栈结构不存在的状态
		return false;
	}
	ssptr->top = ssptr->bottom;//重置栈顶指针
	ssptr->stacksize = 0;//栈的大小重置为0
	return true;
}

_Bool StackEmpty_sq(const SqStack *const ssptr)
{
	return ssptr->bottom == ssptr->top;
}

_Bool StackSize_sq(const SqStack *const ssptr, int *const retsizeptr)
{
	if (NULL == ssptr->bottom)//栈结构不存在
		return false;
	*retsizeptr = ssptr->top - ssptr->bottom;//由指针返回栈的大小
	return true;
}

_Bool StackGetTop_sq(const SqStack *const ssptr, StackElemType *const retptr)
{
	if (ssptr->bottom == ssptr->top)//如果栈为空返回false
		return false;
	*retptr = *(ssptr->top - 1);//由指针返回栈顶元素的值
	return true;
}

_Bool StackPush_sq(SqStack *const ssptr, const StackElemType *const elemptr)
{
	int  cursize = ssptr->top - ssptr->bottom;

	if (ssptr->top - ssptr->bottom >= ssptr->stacksize)//如果栈当前的内存空间已经满
	{
		ssptr->bottom = (StackElemType *)realloc(ssptr->bottom, sizeof(StackElemType)*(ssptr->stacksize + STACK_INCREMENT_SIZE));
		//追加内存空间
		if (NULL == ssptr->bottom)//追加内存空间失败
		{
			ssptr->top = NULL;//栈顶指针重置为栈结构不存在的状态
			ssptr->stacksize = 0;//栈的大小重置为栈结构不存在的状态
			return false;
		}
		ssptr->stacksize += STACK_INCREMENT_SIZE;//重置栈空间的大小
		ssptr->top = ssptr->bottom + cursize;//重置栈顶指针在新空间的位置
	}
	*ssptr->top++ = *elemptr; //向栈中压入数据并且重置栈顶指针
	return true;
}

_Bool StackPop_sq(SqStack *const ssptr, StackElemType *const retptr)
{
	if (ssptr->bottom == ssptr->top)//如果栈为空返回false;
		return true;
	*retptr = *--ssptr->top;//栈中弹出数据并且重置栈顶指针
	return true;
}

void StackTraverse_sq(const SqStack *const ssptr)
{
	const StackElemType *p = ssptr->bottom;

	while (p++ != ssptr->top)
		printf("%d ", *(p - 1));
	printf("\n");
}