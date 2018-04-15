#ifndef LINKEDSTACK_LNK_STACK_H
#define LINKEDSTACK_LNK_STACK_H

#include <stdbool.h>

typedef int LnkStackElemType;

typedef struct lnkstacknode
{
	LnkStackElemType elem;				//数据域
	struct lnkstacknode *next;			//指针域
}LnkStackNode;

typedef struct
{
	LnkStackNode *bottom;				//栈底
	LnkStackNode *top;					//栈顶
	int stacksize;						//栈大小
}LnkStack;

_Bool StackInit_lnk(LnkStack *const lnsptr);
//操作结果:构造一个空栈

_Bool StackDestroy_lnk(LnkStack *const lnsptr);
//初始条件:栈lnsptr已经存在
//操作结果:栈lnsptr被销毁

_Bool StackClear_lnk(LnkStack *const lnsptr);
//初始条件:栈lnsptr已经存在
//操作结果:栈lnsptr被清空

_Bool StackIsEmpty_lnk(const LnkStack *const lnsptr);
//初始条件:栈lnsptr已经存在
//操作结果:如果栈lnsptr为空栈,返回true,否则返回false

_Bool StackSize_lnk(const LnkStack *const lnsptr, int *const retsizeptr);
//初始条件:栈lnsptr已经存在
//操作结果:返回栈中元素的个数,即栈的长度

_Bool StackGetTop_lnk(const LnkStack *const lnsptr, LnkStackElemType *const retptr);
//初始条件:栈lnsptr已经存在且非空
//操作结果:由指针retptr返回栈顶元素

_Bool StackPush_lnk(LnkStack *const lnsptr, const LnkStackElemType *const elemptr);
//初始条件:栈lnsptr已经存在
//操作结果:插入elemptr所指的元素为栈顶元素

_Bool StackPop_lnk(LnkStack *const lnsptr, LnkStackElemType *const retptr);
//初始条件:栈lnsptr已经存在
//操作结果:删除栈顶元素,并由指针retptr返回其值

void StackTraverse_lnk(const LnkStack *const lnsptr);
//初始条件:栈lnsptr已经存在
//操作结果:从栈底到栈顶依次对ss栈中的元素进行访问

#endif // !LINKEDSTACK_LNK_STACK_H

