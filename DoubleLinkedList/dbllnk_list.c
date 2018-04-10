#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "dbllnk_list.h"

_Bool NodeAllocation(DblLnkPosition *posptr, DblLnkElemType elem);
void NodeFree(DblLnkPosition *posptr);

_Bool ListInitial_dbllnk(DblLnkList *const slnklistptr)
{
	if (!NodeAllocation(&slnklistptr->head, INT_MAX))//Ϊͷ������ռ�
		return false;
	slnklistptr->head->prev = NULL;//ǰ���ÿ�
	slnklistptr->head->next = NULL;//����ÿ�
	slnklistptr->rear = slnklistptr->head;//��ʼ��βָ��
	slnklistptr->length = 0;//���ȳ�ʼ��Ϊ0
	return true;
}

void ListDestroy_dbllnk(DblLnkList *const slnklistptr)
{
	DblLnkPosition p = NULL, q = NULL;

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

void ListClear_dbllnk(DblLnkList *const slnklistptr)
{
	DblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ�ڵ����һ����㿪ʼ�ͷŽ��ռ�,�Ա���ͷ���
	while (p)
	{
		q = p;
		p = p->next;
		NodeFree(&p);
	}
	slnklistptr->head->next = NULL;//�ÿ�
	slnklistptr->rear = slnklistptr->head;//����βָ��
	slnklistptr->head->prev = NULL;//ǰ���ÿ�
	slnklistptr->head->next = NULL;//����ÿ�
	slnklistptr->length = 0;//����������
}

_Bool ListInsNodeFirst_dbllnk(DblLnkList *const slnklistptr, const DblLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//ͷ�ڵ�֮��Ľ�����ӵ�inspos�ĺ���
	slnklistptr->head->next = inspos;					//inspos������Ľ�����ӵ�ͷ�ڵ�ĺ���
	inspos->prev = slnklistptr->head;					//inspos��ǰ��ָ��ͷ���
	if (slnklistptr->rear == slnklistptr->head)			//���֮ǰΪ�ձ�,������βָ��
		slnklistptr->rear = slnklistptr->head->next;
	else
		inspos->next->prev = inspos;					//ͷ���ĺ�̵�ǰ��ָ��inspos
	++slnklistptr->length;								//�����ȼ�1
	return true;
}

_Bool ListDelNodeFirst_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *const slnkposret)
{
	if (NULL == slnklistptr->head->next)//�����Ϊ��,����ʧ��
		return false;
	*slnkposret = slnklistptr->head->next;//��ָ��slnkposret���ؽ�ɾ���Ľ��
	if (slnklistptr->rear == slnklistptr->head->next)//���֮ǰ����Ϊ1,������βָ��
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;//ͷ���ĺ��Ϊ����һ�����
	slnklistptr->head->next->prev = slnklistptr->head;//ͷ���ĺ�̵�ǰ��Ϊͷ���
	--slnklistptr->length;//�����ȼ�1
	return true;
}

void ListAppend_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition slnkposhead)
{
	DblLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)//���������ĳ���
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;//��slnkposhead���ӵ�����ĺ���
	slnkposhead->prev = slnklistptr->rear;//slnkposhead��ǰ��ָ���β
	slnklistptr->rear = p;//��������βָ��
	slnklistptr->length += cnt;//���ñ���
}

_Bool ListRemoveRear_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *slnkposret)
{
	DblLnkPosition p = slnklistptr->head;
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

_Bool ListInsNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos)
{
	DblLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next)//��lspos��ǰ�����
		p = p->next;
	if (NULL == p->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	inspos->next = lspos;//��lspos������Ľ�����ӵ�inspos�ĺ���
	p->next = inspos;//��inspos������Ľ�����ӵ�lsposǰ���ĺ���
	lspos->prev = inspos;//lspos��ǰ��ָ��inspos
	inspos->prev = p;//inspos��ǰ��ָ��p
	++slnklistptr->length;//�����ȼ�1
	return true;
}

_Bool ListInsNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos)
{
	DblLnkPosition p = slnklistptr->head;
	while (p && (p != lspos))//�����Ƿ����lspos���
		p = p->next;
	if (NULL == p)//���в�����lspos���,����false
		return false;
	inspos->next = lspos->next;//��lspos����Ľ�����ӵ�inpos���ĺ���
	lspos->next = inspos;//��inspos������Ľ�����ӵ�lspos�ĺ���
	inspos->prev = lspos;
	if (NULL != inspos->next)
		inspos->next->prev = inspos;
	if (slnklistptr->rear == p)//���ʱ����β���ĺ���,������β���
		slnklistptr->rear = inspos;
	++slnklistptr->length;//��ĳ��ȼ�1
	return true;
}

_Bool ListDelNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition *retpos)
{
	DblLnkPosition p = slnklistptr->head, q = slnklistptr->head;

	*retpos = NULL;
	while ((p->next != lspos) && p->next)//��lspos��ǰ�����
		p = p->next;
	if (NULL == p->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	while ((q->next != p) && (q->next))//��p��ǰ�����
		q = q->next;
	if (NULL == q->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	q->next = p->next;//������̹�ϵ
	lspos->prev = q;//����ǰ����ϵ
	*retpos = p;//ָ�뷵��ɾ���Ľ��
	--slnklistptr->length;//���ȼ�1
	return true;

}

_Bool ListDelNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition *retpos)
{
	DblLnkPosition p = slnklistptr->head;

	*retpos = NULL;
	while (p && (p != lspos))//�����Ƿ����lspos���
		p = p->next;
	if (NULL == p || NULL == p->next)//���в�����lspos���,����lsposû�к�̽��,����false
		return false;
	lspos->next = lspos->next->next;//������̹�ϵ
	lspos->next->prev = lspos;//����ǰ����ϵ
	*retpos = lspos->next;//ָ�뷵��ɾ���Ľ��
	--slnklistptr->length;//���ȼ�1
	return true;
}

void ListSetCurElem_dbllnk(DblLnkPosition curpos, const DblLnkElemType elem)
{
	curpos->elem = elem;//���õ�ǰ����Ԫ�ص�ֵ
}

DblLnkElemType ListGetCurElem_dbllnk(DblLnkPosition curpos)
{
	return curpos->elem;//���ص�ǰ���Ԫ�ص�ֵ
}

_Bool ListIsEmpty_dbllnk(const DblLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//�����Ϊ��,����true,���򷵻�false
}

int ListLength_dbllnk(const DblLnkList *const slnklistptr)
{
	return slnklistptr->length;//���ر�ĳ���
}

DblLnkPosition ListGetHead_dbllnk(const DblLnkList *const slnklistptr)
{
	return slnklistptr->head;//���ر��ͷ���
}

DblLnkPosition ListGetRear_dbllnk(const DblLnkList *const slnklistptr)
{
	return slnklistptr->rear;//���ر��β���
}

_Bool ListPriorPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos)
{
	DblLnkPosition p = slnklistptr->head;

	while (p->next && (curpos != p->next))//��curpos����ǰ��
		p = p->next;
	if (NULL == p->next)//���ǰ��������,����false
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);//��ָ��retpos����ǰ��
	return true;
}

_Bool ListNextPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);//��retpos���ص�ǰ���ĺ��
	return true;
}

_Bool ListLocatePos_dbllnk(const DblLnkList *const slnklistptr, const int index, DblLnkPosition *retpos)
{
	int i = 0;
	DblLnkPosition p = slnklistptr->head;

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

_Bool ListLocateElem_dbllnk(const DblLnkList *const slnklistptr, const DblLnkElemType elem, _Bool(*compare)(DblLnkElemType, DblLnkElemType), DblLnkPosition *retpos)
{
	DblLnkPosition p = slnklistptr->head->next;

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

void ListTraverseAscend_dbllnk(const DblLnkList *const slnklistptr)
{
	DblLnkPosition p = slnklistptr->head->next;

	while (p)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void ListTraverseDescend_dbllnk(const DblLnkList *const slnklistptr)
{
	DblLnkPosition p = slnklistptr->rear;

	while (p!=slnklistptr->head)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->prev;
	}
	printf("\n");
}

_Bool NodeAllocation(DblLnkPosition *posptr, DblLnkElemType elem)
{
	if (NULL == (*posptr = (DblLnkPosition)malloc(sizeof(DblLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void NodeFree(DblLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2)
{
	return e2 <= e2;
}
