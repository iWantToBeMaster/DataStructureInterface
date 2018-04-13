#ifndef SEQUENCESTACK_SQ_STACK_H
#define SEQUENCESTACK_SQ_STACK_H

#include <stdbool.h>

#define STACK_INIT_SIZE				100
#define STACK_INCREMENT_SIZE		10

typedef int StackElemType;

typedef struct
{
	StackElemType *bottom;		//ջ��ָ��
	StackElemType *top;			//ջ��ָ��  ��Զָ��ջ����һ��Ԫ�ص�λ��
	int stacksize;				//ջ�Ĵ�С
}SqStack;

_Bool StackInit_sq(SqStack *const ssptr);
//�������:����һ����ջ

_Bool StackDestroy_sq(SqStack *const ssptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:ջssptr������

_Bool StackClear_sq(SqStack *const ssptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:ջssptr�����

_Bool StackEmpty_sq(const SqStack *const ssptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:���ջssptrΪ��ջ,����true,���򷵻�false

_Bool StackSize_sq(const SqStack *const ssptr,int *const retsizeptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:����ջ��Ԫ�صĸ���,��ջ�ĳ���

_Bool StackGetTop_sq(const SqStack *const ssptr, StackElemType *const retptr);
//��ʼ����:ջssptr�Ѿ������ҷǿ�
//�������:��ָ��retptr����ջ��Ԫ��

_Bool StackPush_sq(SqStack *const ssptr,const StackElemType *const elemptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:����elemptr��ָ��Ԫ��Ϊջ��Ԫ��

_Bool StackPop_sq(SqStack *const ssptr, StackElemType *const retptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:ɾ��ջ��Ԫ��,����ָ��retptr������ֵ

void StackTraverse_sq(const SqStack *const ssptr);
//��ʼ����:ջssptr�Ѿ�����
//�������:��ջ�׵�ջ�����ζ�ssջ�е�Ԫ�ؽ��з���


#endif // !SEQUENCESTACK_SQ_STACK_H

