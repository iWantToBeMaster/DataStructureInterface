#ifndef SEQUENCEQUEUE_SQ_QUEUE_H
#define SEQUENCEQUEUE_SQ_QUEUE_H

#include <stdbool.h>

#define MAX_QUEUE_SIZE 20

typedef int SqQueueElemType;

typedef struct
{
	SqQueueElemType *base;		//�����ڴ�ռ�Ļ�ַ
	int front;					//����λ��ָʾ��
	int rear;					//��βλ��ָʾ��
}SqQueue;

_Bool QueueInit_sq(SqQueue *const sqqptr);
//�������:����һ���ն���

void QueueDestroy_sq(SqQueue *const sqqptr);
//��ʼ����:����*sqqptr�Ѿ�����
//�������:����*sqqptr������,���ٴ���

void QueueClear_sq(SqQueue *const sqqptr);
//��ʼ����:����*sqqptr�Ѿ�����
//�������:����*sqqptr�����

_Bool QueueIsEmpty_sq(const SqQueue *const sqqptr);
//��ʼ����:����*sqqptr�Ѿ�����
//�������:����*sqqptrΪ�ն��з���true,���򷵻�false

_Bool QueueIsFull_sq(const SqQueue *const sqqptr);
//��ʼ����:����*sqqptr�Ѿ�����
//�������:����*sqqptrΪ�����з���true,���򷵻�false

_Bool QueueLength_sq(const SqQueue *const sqqptr, int *const retsizeptr);
//��ʼ����:����*sqqptr�Ѿ�����
//�������:���ض���*sqqptrԪ�صĸ���,�����еĳ���

_Bool QueueGetHead_sq(const SqQueue *const sqqptr,SqQueueElemType *const retptr);
//��ʼ����:����*sqqptr�Ѿ�����,�ҷǿ�
//�������:��ָ��retptr���ض���*sqqptr�Ķ���Ԫ��

_Bool QueueEnter_sq(SqQueue *const sqqptr, const SqQueueElemType *const elptr);
//��ʼ����:����*sqqptr�Ѿ�����,�ҷ���
//�������:����elptr��ָԪ��Ϊ����*sqqptr�µĶ�βԪ��

_Bool QueueDelete_sq(SqQueue *const sqqptr, SqQueueElemType *const retptr);
//��ʼ����:����*sqqptr�Ѿ�����,�ҷǿ�
//�������:ɾ������*sqqptr�Ķ���Ԫ��,��ָ��retptr������ֵ

void QueueTraverse_sq(const SqQueue *const sqqptr);
//��ʼ����:����*sqqptr�Ѿ�����
//�������:�Ӷ��׵���β�������������Ԫ�ص�ֵ


#endif // !SEQUENCEQUEUE_SQ_QUEUE_H

