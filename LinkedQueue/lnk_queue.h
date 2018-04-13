#ifndef LNKEDQUEUE_LNK_QUEUE_H
#define LNKEDQUEUE_LNK_QUEUE_H

#include <stdbool.h>

#define MAX_LNKQUEUE_SIZE   20

typedef int LnkQueueElemType;

typedef struct lnkqueuenode
{
	LnkQueueElemType elem;
	struct lnkqueuenode *next;
}LnkQueueNode;


typedef struct
{
	LnkQueueNode *front;
	LnkQueueNode *rear;
	int queuesize;
}LnkQueue;

_Bool QueueInit_lnk(LnkQueue *const lnkqptr);
//操作结果:构造一个空队列

void QueueDestroy_lnk(LnkQueue *const lnkqptr);
//初始条件:队列*lnkqptr已经存在
//操作结果:队列*lnkqptr被销毁,不再存在

void QueueClear_lnk(LnkQueue *const lnkqptr);
//初始条件:队列*lnkqptr已经存在
//操作结果:队列*lnkqptr被清空

_Bool QueueIsEmpty_lnk(const LnkQueue *const lnkqptr);
//初始条件:队列*lnkqptr已经存在
//操作结果:队列*lnkqptr为空队列返回true,否则返回false

_Bool QueueIsFull_lnk(const LnkQueue *const lnkqptr);
//初始条件:队列*lnkqptr已经存在
//操作结果:队列*lnkqptr为满队列返回true,否则返回false

_Bool QueueLength_lnk(const LnkQueue *const lnkqptr, int *const retsize);
//初始条件:队列*lnkqptr已经存在
//操作结果:返回队列*lnkqptr元素的个数,即队列的长度

_Bool QueueGetHead_lnk(const LnkQueue *const lnkqptr, LnkQueueElemType *const retptr);
//初始条件:队列*lnkqptr已经存在,且非空
//操作结果:由指针retptr返回队列*lnkqptr的队首元素

_Bool QueueEnter_lnk(LnkQueue *const lnkqptr, const LnkQueueElemType *const elptr);
//初始条件:队列*lnkqptr已经存在,且非满
//操作结果:插入elptr所指元素为队列*lnkqptr新的队尾元素

_Bool QueueDelete_lnk(LnkQueue *const lnkqptr, LnkQueueElemType *const retptr);
//初始条件:队列*lnkqptr已经存在,且非空
//操作结果:删除队列*lnkqptr的队首元素,由指针retptr返回其值

void QueueTraverse_lnk(const LnkQueue *const lnkqptr);
//初始条件:队列*lnkqptr已经存在
//操作结果:从队首到队尾依次输出队列中元素的值




#endif // !LNKEDQUEUE_LNK_QUEUE_H

