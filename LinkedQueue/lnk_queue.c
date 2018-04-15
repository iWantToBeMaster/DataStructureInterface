#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lnk_queue.h"

_Bool QueueInit_lnk(LnkQueue *const lnkqptr)
{
	lnkqptr->front = (LnkQueueNode *)malloc(sizeof(LnkQueueNode));//带头结点
	if (NULL == lnkqptr->front)
		return false;
	lnkqptr->front->next = NULL;
	lnkqptr->rear = lnkqptr->front;//初始化对尾指针
	lnkqptr->queuesize = 0;//初始化队列大小
	return true;
}

_Bool QueueDestroy_lnk(LnkQueue *const lnkqptr)
{
	LnkQueueNode *p = lnkqptr->front, *q = NULL;

	if (NULL == p)//队列结构不存在返回false
		return false;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);//释放空间
	}
	lnkqptr->front = lnkqptr->rear = NULL;//队首和队尾指针置空
	lnkqptr->queuesize = 0;//队列大小置0
	return true;
}

_Bool QueueClear_lnk(LnkQueue *const lnkqptr)
{
	LnkQueueNode *p = lnkqptr->front->next, *q = NULL;

	if (NULL == p)//队列结构不存在返回false
		return false;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);//释放空间
	}
	lnkqptr->rear = lnkqptr->front;//队首和队尾指针置空
	lnkqptr->queuesize = 0;//队列大小置0
	return true;
}

_Bool QueueIsEmpty_lnk(const LnkQueue *const lnkqptr)
{
	return lnkqptr->front == lnkqptr->rear;
}

_Bool QueueIsFull_lnk(const LnkQueue *const lnkqptr)
{
	return MAX_LNKQUEUE_SIZE == lnkqptr->queuesize;
}

_Bool QueueLength_lnk(const LnkQueue *const lnkqptr, int *const retsize)
{
	if (lnkqptr->front == NULL)//队列结构不存在返回false
		return false;
	*retsize = lnkqptr->queuesize;//由指针返回队列大小
	return true;
}

_Bool QueueGetHead_lnk(const LnkQueue *const lnkqptr, LnkQueueElemType *const retptr)
{
	if (lnkqptr->front == NULL)//队列结构不存在返回false
		return false;
	*retptr = lnkqptr->front->next->elem;//由指针返回队首元素
	return true;
}

_Bool QueueEnter_lnk(LnkQueue *const lnkqptr, const LnkQueueElemType *const elptr)
{
	LnkQueueNode *t = NULL;

	if (MAX_LNKQUEUE_SIZE == lnkqptr->queuesize)//如果队满返回false
		return false;
	t = (LnkQueueNode *)malloc(sizeof(LnkQueueNode));//如果内存分配失败返回false
	if (NULL == t)
		return false;
	t->next = NULL;
	t->elem = *elptr;
	lnkqptr->rear->next = t;
	lnkqptr->rear = lnkqptr->rear->next;
	++lnkqptr->queuesize;
	return true;
}

_Bool QueueDelete_lnk(LnkQueue *const lnkqptr, LnkQueueElemType *const retptr)
{
	LnkQueueNode *t = NULL;

	if (0 == lnkqptr->queuesize)
		return false;
	t = lnkqptr->front->next;
	*retptr = t->elem;
	lnkqptr->front->next = t->next;
	free(t);
	--lnkqptr->queuesize;
	return true;
}

void QueueTraverse_lnk(const LnkQueue *const lnkqptr)
{
	LnkQueueNode *p = lnkqptr->front->next;

	while (p)
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}