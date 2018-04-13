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
//�������:����һ���ն���

void QueueDestroy_lnk(LnkQueue *const lnkqptr);
//��ʼ����:����*lnkqptr�Ѿ�����
//�������:����*lnkqptr������,���ٴ���

void QueueClear_lnk(LnkQueue *const lnkqptr);
//��ʼ����:����*lnkqptr�Ѿ�����
//�������:����*lnkqptr�����

_Bool QueueIsEmpty_lnk(const LnkQueue *const lnkqptr);
//��ʼ����:����*lnkqptr�Ѿ�����
//�������:����*lnkqptrΪ�ն��з���true,���򷵻�false

_Bool QueueIsFull_lnk(const LnkQueue *const lnkqptr);
//��ʼ����:����*lnkqptr�Ѿ�����
//�������:����*lnkqptrΪ�����з���true,���򷵻�false

_Bool QueueLength_lnk(const LnkQueue *const lnkqptr, int *const retsize);
//��ʼ����:����*lnkqptr�Ѿ�����
//�������:���ض���*lnkqptrԪ�صĸ���,�����еĳ���

_Bool QueueGetHead_lnk(const LnkQueue *const lnkqptr, LnkQueueElemType *const retptr);
//��ʼ����:����*lnkqptr�Ѿ�����,�ҷǿ�
//�������:��ָ��retptr���ض���*lnkqptr�Ķ���Ԫ��

_Bool QueueEnter_lnk(LnkQueue *const lnkqptr, const LnkQueueElemType *const elptr);
//��ʼ����:����*lnkqptr�Ѿ�����,�ҷ���
//�������:����elptr��ָԪ��Ϊ����*lnkqptr�µĶ�βԪ��

_Bool QueueDelete_lnk(LnkQueue *const lnkqptr, LnkQueueElemType *const retptr);
//��ʼ����:����*lnkqptr�Ѿ�����,�ҷǿ�
//�������:ɾ������*lnkqptr�Ķ���Ԫ��,��ָ��retptr������ֵ

void QueueTraverse_lnk(const LnkQueue *const lnkqptr);
//��ʼ����:����*lnkqptr�Ѿ�����
//�������:�Ӷ��׵���β�������������Ԫ�ص�ֵ




#endif // !LNKEDQUEUE_LNK_QUEUE_H

