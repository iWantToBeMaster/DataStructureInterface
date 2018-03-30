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
	sqlistptr->length = 0;			//���Ա�ĳ�����0
	sqlistptr->size = 0;			//���Ա��������0
}

int ListLength_sq(const SqList *const sqlistptr)
{//ʱ�临�Ӷ�O(1)
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
	if (index<1 || index>sqlistptr->length)//Ԫ��λ�ò���ȷ����false
		return false;
	*elemptr = *(sqlistptr->elembase + index - 1);
	return true;
}

_Bool ListLocate_sq(const SqList *const sqlistptr, const ElemType elem, _Bool (*compare)(const ElemType, const ElemType), int *const indexptr)
{//ʱ�临�Ӷ�O(n)
	const ElemType *ptr = sqlistptr->elembase;
	int i = 1;
	for (; i <= sqlistptr->length; ++i)
	{
		if ((*compare)(*ptr++, elem))//�Ƚ�Ԫ��
			break;					//����compare�˳�ѭ��
	}
	if (i > sqlistptr->length)//�ж�ѭ���Ƿ��ж�
		return  false;		//δ�ж���δ�ҵ�����Ԫ��
	return true;
}

_Bool ListInsert_sq(SqList *const sqlistptr, const ElemType elem, const int index)
{
	ElemType *insposptr = NULL;

	if (index<1 || index>(sqlistptr->length + 1))//Ԫ��λ�ò���ȷ,����false
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
	insposptr = sqlistptr->elembase + index - 1;						//elemҪ�����λ��
	for (ElemType *p = sqlistptr->elembase + sqlistptr->length; p > insposptr; --p)
		*p = *(p - 1);//��index�������Ԫ������ƶ�һ��λ��
	*insposptr = elem;
	++sqlistptr->length;//���ȼ�1
	return true;
}

_Bool ListDelete_sq(SqList *const sqlistptr, const int index, ElemType *const retptr)
{
	ElemType ret = *(sqlistptr->elembase + index - 1);

	if (0 == sqlistptr->length)//�����Ϊ��,�򷵻�false
		return false;
	if (index<1 || index>sqlistptr->length)//Ԫ��λ�ò���ȷ,����false
		return false;
	for (ElemType *p = sqlistptr->elembase + index - 1; p < sqlistptr->elembase + sqlistptr->length - 1; ++p)
		*p = *(p + 1);//��index+1�������Ԫ��ǰ��һ��λ��
	if (sqlistptr->size - sqlistptr->length >= LIST_INCREMENT_SIZE)
	{
		sqlistptr->elembase = (ElemType *)realloc(sqlistptr->elembase, sizeof(ElemType)*(sqlistptr->size - LIST_INCREMENT_SIZE));//��С��Ŀռ�
		if (NULL == sqlistptr->elembase)//��С�ռ�ʧ��,����false
			return false;
		sqlistptr->size -= LIST_INCREMENT_SIZE;//��������С
	}
	--sqlistptr->length;//���ȼ�1
	*retptr = ret;//��ָ�뷵��Ԫ��
	return true;
}

_Bool ListPriorElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr)
{
	ElemType *ptr = sqlistptr->elembase + 1;

	if (curelem == *sqlistptr->elembase)//��һ��Ԫ����curelem��ȷ���false
		return false;
	for (; ptr <= sqlistptr->elembase + sqlistptr->length - 1; ++ptr)//�����Ա���Ѱ��curelemԪ��
		if (curelem == *ptr)
			break;
	if (ptr > sqlistptr->elembase + sqlistptr->length - 1)//���Ա��в�����curelemԪ��
		return false;
	*retelemptr = *(ptr - 1);//��ָ�뷵��ǰ��
	return true;
}

_Bool ListNextElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr)
{
	ElemType *ptr = sqlistptr->elembase;

	if (curelem == *(sqlistptr->elembase + sqlistptr->length - 1))//���һ��Ԫ����curelem��ȷ���false
		return false;
	for (; ptr <= sqlistptr->elembase + sqlistptr->length - 2; ++ptr)//�����Ա���Ѱ��curelemԪ��
		if (curelem == *ptr)
			break;
	if (ptr > sqlistptr->elembase + sqlistptr->length - 2)//���Ա��в�����curelemԪ��
		return false;
	*retelemptr = *(ptr + 1);//��ָ�뷵�غ��
	return true;
}

_Bool ListMerge_sq(SqList *const sqlistaptr, SqList *const sqlistbptr, SqList *const retlistptr)
{
	int i = 1, j = 1, k = 1;
	while (i <= sqlistaptr->length&&j <= sqlistbptr->length)
	{
		if (*(sqlistaptr->elembase + i - 1) < *(sqlistbptr->elembase + j - 1))
		{
			if (!ListInsert_sq(retlistptr, *(sqlistaptr->elembase + i - 1), k++))
				return false;
			++i;
		}
		else
		{
			if (!ListInsert_sq(retlistptr, *(sqlistbptr->elembase + j - 1), k++))
				return false;
			++j;
		}
	}
	--i, --j;
	while (++i <= sqlistaptr->length)
	{
		if (!ListInsert_sq(retlistptr, *(sqlistaptr->elembase + i - 1), k++))
			return false;
	}
	while (++j <= sqlistbptr->length)
	{
		if (!ListInsert_sq(retlistptr, *(sqlistbptr->elembase + j - 1), k++))
			return false;
	}
	return true;
}

void ListSort_sq(SqList *const sqlistptr)
{
	ElemType *p = sqlistptr->elembase - 1, *q = p + 1, temp;

	while (++p < sqlistptr->elembase + sqlistptr->length - 1)
	{
		q = p;
		while (++q <= sqlistptr->elembase + sqlistptr->length - 1)
			if (*p > *q)
			{
				temp = *p;
				*p = *q;
				*q = temp;
			}
	}
}

_Bool ListCopy_sq(SqList *const sqsrcptr, SqList *const sqdestptr)
{
	if (NULL == (sqdestptr->elembase = (ElemType *)realloc(sqdestptr->elembase, sqsrcptr->size)))//������ͬ�ı�ռ�
		return false;

	ElemType *srcptr = sqsrcptr->elembase, *desptr = sqdestptr->elembase;

	while (srcptr <= sqsrcptr->elembase + sqsrcptr->length - 1)//�������е�����
		*desptr++ = *srcptr++;
	sqdestptr->length = sqsrcptr->length;
	sqdestptr->size = sqsrcptr->size;
	return true;
}

void ListTraverse_sq(SqList *const sqlistptr)
{
	ElemType *lastelemptr = sqlistptr->elembase + sqlistptr->length - 1;//��βԪ�ص�λ��

	for (ElemType *p = sqlistptr->elembase; p <= lastelemptr; ++p)//����������е�����Ԫ��
		printf("%d ", *p);
	printf("\n");
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
