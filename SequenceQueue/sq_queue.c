#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sq_queue.h"

_Bool QueueInit_sq(SqQueue *const sqqptr)
{
	sqqptr->base = (SqQueueElemType *)malloc(sizeof(SqQueueElemType)*(MAX_QUEUE_SIZE + 1));//为队列分配内存空间
	if (NULL == sqqptr)//如果分配失败返回false
		return false;
	sqqptr->front = 0;//初始化队首指示器
	sqqptr->rear = 0;//初始化队尾指示器
	return true;
}

void QueueDestroy_sq(SqQueue *const sqqptr)
{
	free(sqqptr->base);//释放队列的内存空间
	sqqptr->base = NULL;//内存基址置空
	sqqptr->front = 0;//重置队首指示器
	sqqptr->rear = 0;//重置队尾指示器
}

void QueueClear_sq(SqQueue *const sqqptr)
{
	sqqptr->front = 0;//重置队首指示器
	sqqptr->rear = 0;//重置队尾指示器

}

_Bool QueueIsEmpty_sq(const SqQueue *const sqqptr)
{
	return sqqptr->front == sqqptr->rear;
}

_Bool QueueIsFull_sq(const SqQueue *const sqqptr)
{
	return sqqptr->rear + 1 == sqqptr->front;
}

int QueueLength_sq(const SqQueue *const sqqptr)
{
	return (sqqptr->rear - sqqptr->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

_Bool QueueGetHead_sq(const SqQueue *const sqqptr, SqQueueElemType *const retptr)
{
	if (sqqptr->front == sqqptr->rear)//若队列为空,返回false
		return false;
	*retptr = *(sqqptr->base + sqqptr->front);//指针返回队首元素
	return true;
}

_Bool QueueEnter_sq(SqQueue *const sqqptr, const SqQueueElemType *const elptr)
{
	if (sqqptr->front == (sqqptr->rear + 1))//如果队列为满,返回false
		return false;
	*(sqqptr->base + sqqptr->rear) = *elptr;//队尾赋值
	sqqptr->rear = (sqqptr->rear + 1) % MAX_QUEUE_SIZE;//队尾指示器指向下一位置
	return true;
}

_Bool QueueDelete_sq(SqQueue *const sqqptr, SqQueueElemType *const retptr)
{
	if (sqqptr->front == sqqptr->rear)//若队列为空,返回false
		return false;
	*retptr = *(sqqptr->base + sqqptr->front);//指针返回队首元素
	sqqptr->front = (sqqptr->front + 1) % MAX_QUEUE_SIZE;//队首指示器指向下以位置
	return true;
}

void QueueTraverse_sq(const SqQueue *const sqqptr)
{
	int i = sqqptr->front;
	
	while (i != sqqptr->rear)
	{
		printf("%d ", *(sqqptr->base + i));
		i = (i + 1) % MAX_QUEUE_SIZE;
	}
}