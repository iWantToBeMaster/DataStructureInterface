#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "sglylnk_list.h"

_Bool NodeAllocation(SLnkPosition *posptr, SglyLnkElemType elem);
void NodeFree(SLnkPosition *posptr);

_Bool ListInitial_slnk(SLnkList *const slnklistptr)
{
	if (!NodeAllocation(&slnklistptr->head,INT_MAX))//Ϊͷ������ռ�
		return false;
	slnklistptr->rear = slnklistptr->head;//��ʼ��βָ��
	slnklistptr->length = 0;//���ȳ�ʼ��Ϊ0
	return true;
}

void ListDestroy_slnk(SLnkList *const slnklistptr)
{
	SLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head;//��ͷ��㿪ʼ�ͷŽ��ռ�
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->head = slnklistptr->rear = NULL;//��ṹ�ÿ�
	slnklistptr->length = 0;//����ֵ0
}

void ListClear_slnk(SLnkList *const slnklistptr)
{
	SLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ�ڵ����һ����㿪ʼ�ͷŽ��ռ�,�Ա���ͷ���
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->head->next = NULL;//�ÿ�
	slnklistptr->rear = slnklistptr->head;//����βָ��
	slnklistptr->length = 0;//����������
}

_Bool ListInsNodeFirst_slnk(SLnkList *const slnklistptr, const SLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//ͷ�ڵ�֮��Ľ�����ӵ�inspos�ĺ���
	slnklistptr->head->next = inspos;					//inspos������Ľ�����ӵ�ͷ�ڵ�ĺ���
	if (slnklistptr->rear == slnklistptr->head)			//���֮ǰΪ�ձ�,������βָ��
		slnklistptr->rear = slnklistptr->head->next;
	++slnklistptr->length;								//�����ȼ�1
	return true;
}

_Bool ListDelNodeFirst_slnk(SLnkList *const slnklistptr, SLnkPosition *const slnkposret)
{
	if (NULL == slnklistptr->head->next)//�����Ϊ��,����ʧ��
		return false;
	*slnkposret = slnklistptr->head->next;//��ָ��slnkposret���ؽ�ɾ���Ľ��
	if (slnklistptr->rear == slnklistptr->head->next)//���֮ǰ����Ϊ1,������βָ��
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;//ɾ������
	--slnklistptr->length;//�����ȼ�1
	return true;
}

void ListAppend_slnk(SLnkList *const slnklistptr, SLnkPosition slnkposhead)
{
	SLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)//���������ĳ���
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;//��slnkposhead���ӵ�����ĺ���
	slnklistptr->rear = p;//��������βָ��
	slnklistptr->length += cnt;//���ñ���
}

_Bool ListRemoveRear_slnk(SLnkList *const slnklistptr, SLnkPosition *slnkposret)
{
	SLnkPosition p = slnklistptr->head;
	if (slnklistptr->head == slnklistptr->rear)//�����Ϊ��,�򷵻�false
		return false;
	while ((p->next != slnklistptr->rear) && p->next)//��β����ǰ�� 
		p = p->next;
	*slnkposret = slnklistptr->rear;//��ָ��slnkposret���ؽ�ɾ���Ľ��
	p->next = NULL;
	slnklistptr->rear = p;//����βָ��
	--slnklistptr->length;//�����ȼ�1
	return true;
}

_Bool ListInsNodeBefore_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos)
{
	SLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next)//��lspos��ǰ�����
		p = p->next;
	if (NULL == p->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	inspos->next = lspos;//��lspos������Ľ�����ӵ�inspos�ĺ���
	p->next = inspos;//��inspos������Ľ�����ӵ�lsposǰ���ĺ���
	++slnklistptr->length;//�����ȼ�1
	return true;
}

_Bool ListInsNodeAfter_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos)
{
	SLnkPosition p = slnklistptr->head;
	while (p && (p != lspos))//�����Ƿ����lspos���
		p = p->next;
	if (NULL == p)//���в�����lspos���,����false
		return false;
	inspos->next = lspos->next;//��lspos����Ľ�����ӵ�inpos���ĺ���
	lspos->next = inspos;//��inspos������Ľ�����ӵ�lspos�ĺ���
	if (slnklistptr->rear == p)//���ʱ����β���ĺ���,������β���
		slnklistptr->rear = inspos;
	++slnklistptr->length;//��ĳ��ȼ�1
	return true;
}

void ListSetCurElem_slnk(SLnkPosition curpos, const SglyLnkElemType elem)
{
	curpos->elem = elem;//���õ�ǰ����Ԫ�ص�ֵ
}

SglyLnkElemType ListGetCurElem_slnk(SLnkPosition curpos)
{
	return curpos->elem;//���ص�ǰ���Ԫ�ص�ֵ
}

_Bool ListIsEmpty_slnk(const SLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//�����Ϊ��,����true,���򷵻�false
}

int ListLength_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->length;//���ر�ĳ���
}

SLnkPosition ListGetHead_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->head;//���ر��ͷ���
}

SLnkPosition ListGetRear_slnk(const SLnkList *const slnklistptr)
{
	return slnklistptr->rear;//���ر��β���
}

_Bool ListPriorPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos)
{
	SLnkPosition p = slnklistptr->head;

	while (p->next && (curpos != p->next))//��curpos����ǰ��
		p = p->next;
	if (NULL == p->next)//���ǰ��������,����false
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);//��ָ��retpos����ǰ��
	return true;
}

_Bool ListNextPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);//��retpos���ص�ǰ���ĺ��
	return true;
}

_Bool ListLocatePos_slnk(const SLnkList *const slnklistptr, const int index, SLnkPosition *retpos)
{
	int i = 0;
	SLnkPosition p = slnklistptr->head;

	if (index<1 || index>slnklistptr->length)//�������Ϸ�,ʧ�ܴ���
	{
		*retpos = NULL;
		return false;
	}
	while (p)//���index������λ��
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	*retpos = p;//��ָ��retpos���ؽ��λ��
	return true;
}

_Bool ListLocateElem_slnk(const SLnkList *const slnklistptr, const SglyLnkElemType elem, _Bool(*compare)(SglyLnkElemType, SglyLnkElemType), SLnkPosition *retpos)
{
	SLnkPosition p = slnklistptr->head->next;

	while (p)//���һ����elem����compare()��ϵ�Ľ��
	{
		if ((*compare)(p->elem, elem))
			break;
		p = p->next;
	}
	if (NULL == p)//���������,ʧ�ܴ���
	{
		*retpos = NULL;
		return false;
	}
	*retpos = p;//��ָ�뷵�ظý��
	return true;
}

void ListTraverse_slnk(const SLnkList *const slnklistptr)
{
	SLnkPosition p = slnklistptr->head->next;

	while (p)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

_Bool NodeAllocation(SLnkPosition *posptr, SglyLnkElemType elem)
{
	if (NULL == (*posptr = (SLnkPosition)malloc(sizeof(SLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void NodeFree(SLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2)
{
	return e2 <= e2;
}
