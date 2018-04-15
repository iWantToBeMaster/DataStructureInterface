#ifndef LINKEDSTACK_LNK_STACK_H
#define LINKEDSTACK_LNK_STACK_H

#include <stdbool.h>

typedef int LnkStackElemType;

typedef struct lnkstacknode
{
	LnkStackElemType elem;				//������
	struct lnkstacknode *next;			//ָ����
}LnkStackNode;

typedef struct
{
	LnkStackNode *bottom;				//ջ��
	LnkStackNode *top;					//ջ��
	int stacksize;						//ջ��С
}LnkStack;

_Bool StackInit_lnk(LnkStack *const lnsptr);
//�������:����һ����ջ

_Bool StackDestroy_lnk(LnkStack *const lnsptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:ջlnsptr������

_Bool StackClear_lnk(LnkStack *const lnsptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:ջlnsptr�����

_Bool StackIsEmpty_lnk(const LnkStack *const lnsptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:���ջlnsptrΪ��ջ,����true,���򷵻�false

_Bool StackSize_lnk(const LnkStack *const lnsptr, int *const retsizeptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:����ջ��Ԫ�صĸ���,��ջ�ĳ���

_Bool StackGetTop_lnk(const LnkStack *const lnsptr, LnkStackElemType *const retptr);
//��ʼ����:ջlnsptr�Ѿ������ҷǿ�
//�������:��ָ��retptr����ջ��Ԫ��

_Bool StackPush_lnk(LnkStack *const lnsptr, const LnkStackElemType *const elemptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:����elemptr��ָ��Ԫ��Ϊջ��Ԫ��

_Bool StackPop_lnk(LnkStack *const lnsptr, LnkStackElemType *const retptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:ɾ��ջ��Ԫ��,����ָ��retptr������ֵ

void StackTraverse_lnk(const LnkStack *const lnsptr);
//��ʼ����:ջlnsptr�Ѿ�����
//�������:��ջ�׵�ջ�����ζ�ssջ�е�Ԫ�ؽ��з���

#endif // !LINKEDSTACK_LNK_STACK_H

