#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sq_list.h"

_Bool ListInitial_sq(SqList * const sqlistptr)
{//ʱ�临�Ӷ�O(1)
	sqlistptr->elembase = (ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);//�����ڴ�ռ�
	if (NULL == sqlistptr->elembase)		//�������ռ�ʧ��,����false
		return false;
	sqlistptr->length = 0;				//�ձ���Ϊ0
	sqlistptr->size = LIST_INIT_SIZE;	//��ʼ�洢����
	return true;
}

void ListClear_sq(SqList * const sqlistptr)
{//ʱ�临�Ӷ�O(1)
	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	sqlistptr->elembase = (ElemType *)realloc(sqlistptr->elembase, sizeof(ElemType)*LIST_INIT_SIZE);//�洢�ռ�����
	sqlistptr->size = LIST_INIT_SIZE;	//�洢��������
	sqlistptr->length = 0;				//��������Ϊ0
}

void ListDestroy_sq(SqList * const sqlistptr)
{//ʱ�临�Ӷ�O(1)
	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	free(sqlistptr->elembase);		//�ͷ����Ա�Ĵ洢�ռ�
	sqlistptr->elembase = NULL;		//���Ա�Ļ�ַ�ÿ�
	sqlistptr->length = 0;		//���Ա�ĳ�����0
	sqlistptr->size = 0;		//���Ա��������0
}

int ListLength_sq(const SqList *const sqlistptr)
{//ʱ�临�Ӷ�O(1)
	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	return sqlistptr->length;//�������Ա�Ԫ�ظ���
}

_Bool ListIsEmpty_sq(const SqList * const sqlistptr)
{//ʱ�临�Ӷ�O(1)
	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	return 0 == sqlistptr->length;
}

_Bool ListGetElem_sq(const SqList *const sqlistptr, const int index, ElemType *const elemptr)
{//ʱ�临�Ӷ�O(1)
	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	if (index<1 || index>sqlistptr->length)//Ԫ��λ�ò���ȷ����false
		return false;
	*elemptr = *(sqlistptr->elembase + index - 1);
	return true;
}

_Bool ListLocate_sq(const SqList *const sqlistptr, const ElemType elem, _Bool (*compare)(const ElemType, const ElemType), int *const indexptr)
{//ʱ�临�Ӷ�O(n)
	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	const ElemType *ptr = sqlistptr->elembase;
	int i = 1;
	for (; i <= sqlistptr->length; ++i)
	{
		if ((*compare)(elem, *ptr++))//�Ƚ�Ԫ��
			break;					//����compare�˳�ѭ��
	}
	if (i > sqlistptr->length)//�ж�ѭ���Ƿ��ж�
		return  false;		//δ�ж���δ�ҵ�����Ԫ��
	return true;
}

_Bool ListInsert_sq(SqList *const sqlistptr, const ElemType elem, const int index)
{
	ElemType *insposptr = NULL;

	if (NULL == sqlistptr->elembase)//���������,�˳�
		exit(EXIT_FAILURE);
	if (index<1 || index>(sqlistptr->length + 1))
		return false;
	if (sqlistptr->length == sqlistptr->size)//������Ա�ǰ������,���ӱ������
	{
		sqlistptr->elembase = (ElemType *)realloc(sqlistptr->elembase, sizeof(ElemType)*(sqlistptr->size + LIST_INCREMENT_SIZE));//���ӱ������
		if (NULL == sqlistptr->elembase)//��������ʧ��,����false
		{
			sqlistptr->size = 0;
			sqlistptr->length = 0;
			return false;
		}
		sqlistptr->size += LIST_INCREMENT_SIZE;
	}
	insposptr = sqlistptr + index - 1;							//elemҪ�����λ��
	for (ElemType *p = sqlistptr->elembase + sqlistptr->length; p > insposptr; --p)//��index�������Ԫ������ƶ�һ��λ��
		*p = *(p - 1);
	*insposptr = elem;
	++sqlistptr->length;//���ȼ�1
	return true;
}





_Bool IsGreaterThan(const ElemType e1, const ElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual(const ElemType e1, const ElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual(const ElemType e1, const ElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan(const ElemType e1, const ElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual(const ElemType e1, const ElemType e2)
{
	return e2 <= e2;
}