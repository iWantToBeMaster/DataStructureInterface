#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sq_queue.h"

_Bool QueueInit_sq(SqQueue *const sqqptr)
{
	sqqptr->base = (SqQueueElemType *)malloc(sizeof(SqQueueElemType)*(MAX_QUEUE_SIZE + 1));//Ϊ���з����ڴ�ռ�
	if (NULL == sqqptr)//�������ʧ�ܷ���false
		return false;
	sqqptr->front = 0;//��ʼ������ָʾ��
	sqqptr->rear = 0;//��ʼ����βָʾ��
	return true;
}

void QueueDestroy_sq(SqQueue *const sqqptr)
{
	free(sqqptr->base);//�ͷŶ��е��ڴ�ռ�
	sqqptr->base = NULL;//�ڴ��ַ�ÿ�
	sqqptr->front = 0;//���ö���ָʾ��
	sqqptr->rear = 0;//���ö�βָʾ��
}

void QueueClear_sq(SqQueue *const sqqptr)
{
	sqqptr->front = 0;//���ö���ָʾ��
	sqqptr->rear = 0;//���ö�βָʾ��

}

_Bool QueueIsEmpty_sq(const SqQueue *const sqqptr)
{
	return sqqptr->front == sqqptr->rear;
}

_Bool QueueIsFull_sq(const SqQueue *const sqqptr)
{
	return sqqptr->rear + 1 == sqqptr->front;
}

_Bool QueueLength_sq(const SqQueue *const sqqptr,int *const retsizeptr)
{
	if (NULL == sqqptr->base)
		return false;
	*retsizeptr = (sqqptr->rear - sqqptr->front + (MAX_QUEUE_SIZE + 1)) % (MAX_QUEUE_SIZE + 1);
	return true;
}

_Bool QueueGetHead_sq(const SqQueue *const sqqptr, SqQueueElemType *const retptr)
{
	if (sqqptr->front == sqqptr->rear)//������Ϊ��,����false
		return false;
	*retptr = *(sqqptr->base + sqqptr->front);//ָ�뷵�ض���Ԫ��
	return true;
}

_Bool QueueEnter_sq(SqQueue *const sqqptr, const SqQueueElemType *const elptr)
{
	if (sqqptr->front == (sqqptr->rear + 1))//�������Ϊ��,����false
		return false;
	*(sqqptr->base + sqqptr->rear) = *elptr;//��β��ֵ
	sqqptr->rear = (sqqptr->rear + 1) % (MAX_QUEUE_SIZE + 1);//��βָʾ��ָ����һλ��
	return true;
}

_Bool QueueDelete_sq(SqQueue *const sqqptr, SqQueueElemType *const retptr)
{
	if (sqqptr->front == sqqptr->rear)//������Ϊ��,����false
		return false;
	*retptr = *(sqqptr->base + sqqptr->front);//ָ�뷵�ض���Ԫ��
	sqqptr->front = (sqqptr->front + 1) % (MAX_QUEUE_SIZE + 1);//����ָʾ��ָ������λ��
	return true;
}

void QueueTraverse_sq(const SqQueue *const sqqptr)
{
	int i = sqqptr->front;
	
	while (i != sqqptr->rear)
	{
		printf("%d ", *(sqqptr->base + i));
		i = (i + 1) % (MAX_QUEUE_SIZE + 1);
	}
	printf("\n");
}