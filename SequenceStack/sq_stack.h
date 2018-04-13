#ifndef SEQUENCESTACK_SQ_STACK_H
#define SEQUENCESTACK_SQ_STACK_H

#include <stdbool.h>

#define STACK_INIT_SIZE				100
#define STACK_INCREMENT_SIZE		10

typedef int StackElemType;

typedef struct
{
	StackElemType *bottom;		//栈底指针
	StackElemType *top;			//栈顶指针  永远指向栈顶下一个元素的位置
	int stacksize;				//栈的大小
}SqStack;

_Bool StackInit_sq(SqStack *const ssptr);
//操作结果:构造一个空栈

_Bool StackDestroy_sq(SqStack *const ssptr);
//初始条件:栈ssptr已经存在
//操作结果:栈ssptr被销毁

_Bool StackClear_sq(SqStack *const ssptr);
//初始条件:栈ssptr已经存在
//操作结果:栈ssptr被清空

_Bool StackEmpty_sq(const SqStack *const ssptr);
//初始条件:栈ssptr已经存在
//操作结果:如果栈ssptr为空栈,返回true,否则返回false

_Bool StackSize_sq(const SqStack *const ssptr,int *const retsizeptr);
//初始条件:栈ssptr已经存在
//操作结果:返回栈中元素的个数,即栈的长度

_Bool StackGetTop_sq(const SqStack *const ssptr, StackElemType *const retptr);
//初始条件:栈ssptr已经存在且非空
//操作结果:由指针retptr返回栈顶元素

_Bool StackPush_sq(SqStack *const ssptr,const StackElemType *const elemptr);
//初始条件:栈ssptr已经存在
//操作结果:插入elemptr所指的元素为栈顶元素

_Bool StackPop_sq(SqStack *const ssptr, StackElemType *const retptr);
//初始条件:栈ssptr已经存在
//操作结果:删除栈顶元素,并由指针retptr返回其值

void StackTraverse_sq(const SqStack *const ssptr);
//初始条件:栈ssptr已经存在
//操作结果:从栈底到栈顶依次对ss栈中的元素进行访问


#endif // !SEQUENCESTACK_SQ_STACK_H

