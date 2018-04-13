#ifndef SEQUENCEQUEUE_SQ_QUEUE_H
#define SEQUENCEQUEUE_SQ_QUEUE_H

#include <stdbool.h>

#define MAX_QUEUE_SIZE 20

typedef int SqQueueElemType;

typedef struct
{
	SqQueueElemType *base;		//队列内存空间的基址
	int front;					//对首位置指示器
	int rear;					//对尾位置指示器
}SqQueue;

_Bool QueueInit_sq(SqQueue *const sqqptr);
//操作结果:构造一个空队列

void QueueDestroy_sq(SqQueue *const sqqptr);
//初始条件:队列*sqqptr已经存在
//操作结果:队列*sqqptr被销毁,不再存在

void QueueClear_sq(SqQueue *const sqqptr);
//初始条件:队列*sqqptr已经存在
//操作结果:队列*sqqptr被清空

_Bool QueueIsEmpty_sq(const SqQueue *const sqqptr);
//初始条件:队列*sqqptr已经存在
//操作结果:队列*sqqptr为空队列返回true,否则返回false

_Bool QueueIsFull_sq(const SqQueue *const sqqptr);
//初始条件:队列*sqqptr已经存在
//操作结果:队列*sqqptr为满队列返回true,否则返回false

int QueueLength_sq(const SqQueue *const sqqptr);
//初始条件:队列*sqqptr已经存在
//操作结果:返回队列*sqqptr元素的个数,即队列的长度

_Bool QueueGetHead_sq(const SqQueue *const sqqptr,SqQueueElemType *const retptr);
//初始条件:队列*sqqptr已经存在,且非空
//操作结果:由指针retptr返回队列*sqqptr的队首元素

_Bool QueueEnter_sq(SqQueue *const sqqptr, const SqQueueElemType *const elptr);
//初始条件:队列*sqqptr已经存在,且非满
//操作结果:插入elptr所指元素为队列*sqqptr新的队尾元素

_Bool QueueDelete_sq(SqQueue *const sqqptr, SqQueueElemType *const retptr);
//初始条件:队列*sqqptr已经存在,且非空
//操作结果:删除队列*sqqptr的队首元素,由指针retptr返回其值

void QueueTraverse_sq(const SqQueue *const sqqptr);
//初始条件:队列*sqqptr已经存在
//操作结果:从队首到队尾依次输出队列中元素的值


#endif // !SEQUENCEQUEUE_SQ_QUEUE_H

