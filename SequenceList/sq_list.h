#ifndef SEQUENCELIST_SQ_LIST_H
#define SEQUENCELIST_SQ_LIST_H

#include <stdbool.h>
#include <stdarg.h>

#define LIST_INIT_SIZE				20	//���Ա�洢�ռ�ĳ�ʼ������
#define LIST_INCREMENT_SIZE			5	//���Ա�洢�ռ�ķ�������

typedef int ElemType;

typedef struct
{
	ElemType *elembase;	//�洢�ռ��ַ
	int length;		//��ǰ����
	int size;		//��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ)
}SqList;

_Bool ListInitial_sq(SqList *const sqlistptr);
//�������:����һ���յ����Ա�*sqlistptr


void ListClear_sq(SqList *const sqlistptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����
//�������:��*sqlistptr����Ϊ�ձ�


void ListDestroy_sq(SqList *const sqlistptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����
//�������:�������Ա�*sqlistptr


int ListLength_sq(const SqList *const sqlistptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����
//�������:�������Ա�*sqlistptr������Ԫ�صĸ���


_Bool ListIsEmpty_sq(const SqList *const sqlistptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����
//�������:�����Ա�*sqlistptrΪ�ձ�,�򷵻�true,���򷵻�false;


_Bool ListGetElem_sq(const SqList *const sqlistptr, const int index, ElemType *const elemptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����,1<=i<=ListLength_sq(sqlistptr)
//�������:��elemptr����*sqlistptr�е�index��Ԫ�ص�ֵ


_Bool ListLocate_sq(const SqList *const sqlistptr, const ElemType elem, _Bool (*compare)(const ElemType, const ElemType), int *const indexptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����,Compare(const ElemType, const ElemType)������Ԫ���ж�����
//�������:��indexptrָ�뷵�����Ա�*sqlistptr�е�һ����elem�����ϵCompare(const ElemType, const ElemType)������Ԫ�ص�λ��,
//		  �������Ԫ�ش��ڷ���true,���򷵻�false


_Bool ListInsert_sq(SqList *const sqlistptr, const ElemType elem, const int index);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����,1<=i<=ListLength_sq(sqlistptr)+1
//�������:�����Ա�*sqlistptr��index��λ��֮ǰ�����µ�Ԫ��elem,*sqlistptr��������1


_Bool ListDelete_sq(SqList *const sqlistptr, const int index, ElemType *const retptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ������ҷǿ�,1<=i<=ListLength_sq(sqlistptr)
//�������:ɾ��*sqlistptr�ĵ�index��Ԫ��,����ָ��retptr������ֵ,���Ա�*sqlistptr�ĳ��ȼ�1


_Bool ListPriorElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ���
//�������:��curelem�����Ա�*sqlistptr�е�Ԫ��,�Ҳ��ǵ�һ��,����ָ��retelemptr��������ǰ��,�������ʧ��


_Bool ListNextElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ���
//�������:��curelem�����Ա�*sqlistptr�е�Ԫ��,�Ҳ������һ��,����ָ��retelemptr�������ĺ��,�������ʧ��


_Bool ListMerge_sq(SqList *const sqlistaptr, SqList *const sqlistbptr, SqList *const retlistptr);
//��ʼ����:���Ա�*sqlistaptr��*sqlistbptr�Ѿ���,������,˳����ͬ.*retlistptrΪ�ձ�
//�������:���Ա�*sqlistaptr�����Ա�*sqlistbptr�鲢�������±���Ȼ����,��ָ��retlistptr����


void ListSort_sq(SqList *const sqlistptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����
//�������:���е�Ԫ�شӴ�С����


_Bool ListCopy_sq(SqList *const sqsrcptr, SqList *const sqdestptr);
//��ʼ����:���Ա�*sqsrcptr�Ѿ�����
//�������:*sqsrcptr���Ƹ�*sqdestptr


void ListTraverse_sq(SqList *const sqlistptr);
//��ʼ����:���Ա�*sqlistptr�Ѿ�����
//�������:���ζ�*sqlist��ÿ������Ԫ�ؽ������



_Bool IsGreaterThan(const ElemType e1, const ElemType e2);
//���e1>e2����true,���򷵻�false


_Bool IsGreaterThanOrEqual(const ElemType e1, const ElemType e2);
//���e1>=e2����true,���򷵻�false


_Bool IsEqual(const ElemType e1, const ElemType e2);
//���e1=e2����true,���򷵻�false


_Bool IsLessThan(const ElemType e1, const ElemType e2);
//���e1<e2����true,���򷵻�false


_Bool IsLessThanOrEqual(const ElemType e1, const ElemType e2);
//���e1<=e2����true,���򷵻�false

#endif // !SEQUENCELIST_SQ_LIST_H

