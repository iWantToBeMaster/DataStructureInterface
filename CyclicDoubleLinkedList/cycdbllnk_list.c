#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cycdbllnk_list.h"

_Bool CycListNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem);
void CycListNodeFree(CycDblLnkPosition *posptr);

_Bool ListInitial_cycdbllnk(CycDblLnkList *const slnklistptr)
{
	if (!CycListNodeAllocation(&slnklistptr->head, INT_MAX))//Ϊͷ������ռ�
		return false;
	slnklistptr->rear = slnklistptr->head;//��ʼ��βָ��
	slnklistptr->rear->next = slnklistptr->head;//��β����
	slnklistptr->head->prev = slnklistptr->rear;//��β����
	slnklistptr->length = 0;//���ȳ�ʼ��Ϊ0
	return true;
}

void ListDestroy_cycdbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ������һ����㿪ʼ�ͷŽ��ռ�
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycListNodeFree(&p);
	}
	CycListNodeFree(&slnklistptr->head);//�ͷ�ͷ���ռ�
	slnklistptr->head = slnklistptr->rear = NULL;//��ṹ�ÿ�
	slnklistptr->length = 0;//������0
}

void ListClear_cycdbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ�ڵ����һ����㿪ʼ�ͷŽ��ռ�,�Ա���ͷ���
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycListNodeFree(&p);
	}
	slnklistptr->rear = slnklistptr->head;//����βָ��
	slnklistptr->rear->next = slnklistptr->head;//��β����
	slnklistptr->head->prev = slnklistptr->rear;//��β����
	slnklistptr->length = 0;//����������
}

_Bool ListInsNodeFirst_cycdbllnk(CycDblLnkList *const slnklistptr, const CycDblLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//ͷ�ڵ�֮��Ľ�����ӵ�inspos�ĺ���
	inspos->prev = slnklistptr->head;					//inspos����ǰ����Ϊͷ���
	slnklistptr->head->next = inspos;					//inspos������Ľ�����ӵ�ͷ�ڵ�ĺ���
	inspos->next->prev = inspos;						//ԭ����һ������ǰ����Ϊinspos
	if (0 == slnklistptr->length)						//���֮ǰΪ�ձ�,������βָ��
	{
		slnklistptr->rear = inspos;
		slnklistptr->rear->next = slnklistptr->head;	//��β����
		slnklistptr->head->prev = slnklistptr->rear;	//��β����
	}
	++slnklistptr->length;								//�����ȼ�1
	return true;
}

_Bool ListDelNodeFirst_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *const slnkposret)
{
	*slnkposret = NULL;
	if (slnklistptr->head == slnklistptr->rear)						//�����Ϊ��,����ʧ��
		return false;
	*slnkposret = slnklistptr->head->next;						//��ָ��slnkposret���ؽ�ɾ���Ľ��
	if (1 == slnklistptr->length)								//���֮ǰ����Ϊ1,������βָ��
	{
		slnklistptr->rear = slnklistptr->head;
		slnklistptr->rear->next = slnklistptr->head;			//��β����
		slnklistptr->head->prev = slnklistptr->rear;	//��β����
	}
	slnklistptr->head->next = slnklistptr->head->next->next;	//���ָ��ɾ������
	slnklistptr->head->next->prev = slnklistptr->head;			//ǰ��ָ��ɾ������
	--slnklistptr->length;										//�����ȼ�1
	return true;
}

void ListAppend_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition slnkposhead)
{
	CycDblLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)									//���������ĳ���
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;			//��slnkposhead���ӵ�����ĺ���
	slnkposhead->prev = slnklistptr->rear;			
	slnklistptr->rear = p;							//��������βָ��
	slnklistptr->rear->next = slnklistptr->head;	//��β����
	slnklistptr->head->prev = slnklistptr->rear;	//��β����
	slnklistptr->length += cnt;						//���ñ���
}

_Bool ListRemoveRear_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *slnkposret)
{
	CycDblLnkPosition p = NULL;
	if (0 == slnklistptr->length)						//�����Ϊ��,�򷵻�false
		return false;
	*slnkposret = slnklistptr->rear;					//��ָ��slnkposret���ؽ�ɾ���Ľ��
	p = slnklistptr->rear;
	slnklistptr->rear = slnklistptr->rear->prev;
	p->prev->next = slnklistptr->head;
	p->next->prev = p->prev;
	--slnklistptr->length;								//�����ȼ�1
	return true;
}

_Bool ListInsNodeBefore_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//�����Ƿ����lspos���
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	p = lspos->prev;
	inspos->next = lspos;										//��lspos������Ľ�����ӵ�inspos�ĺ���
	lspos->prev = inspos;
	p->next = inspos;											//��inspos������Ľ�����ӵ�lsposǰ���ĺ���
	inspos->prev = p;
	if (p->next->next == slnklistptr->head)
		slnklistptr->rear = inspos;								//����βָ��
	++slnklistptr->length;										//�����ȼ�1
	return true;
}

_Bool ListInsNodeAfter_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head->next;
	
	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//�����Ƿ����lspos���
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	inspos->next = lspos->next;				//��lspos����Ľ�����ӵ�inpos���ĺ���
	lspos->next->prev = inspos;
	lspos->next = inspos;					//��inspos������Ľ�����ӵ�lspos�ĺ���
	inspos->prev = lspos;
	if (slnklistptr->rear == p)				//���ʱ����β���ĺ���,������β���
		slnklistptr->rear = inspos;
	++slnklistptr->length;					//��ĳ��ȼ�1
	return true;
}

_Bool ListDelNodeBefore_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next, q = NULL;

	*retpos = NULL;
	if (0 == slnklistptr->length)
		return false;
	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//�����Ƿ����lspos���
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	p = lspos->prev->prev;
	q = lspos;
	if (lspos == slnklistptr->head->next)
	{
		p = slnklistptr->rear->prev;
		q = slnklistptr->head;
	}
	*retpos = p->next;
	p->next = q;
	q->prev = p;
	if (lspos == slnklistptr->head->next || lspos == slnklistptr->head)
		slnklistptr->rear = p;
	--slnklistptr->length;//���ȼ�1
	return true;
}

_Bool ListDelNodeAfter_cycdbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	*retpos = NULL;
	if (lspos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != lspos)//�����Ƿ����lspos���
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	if (lspos->next == slnklistptr->head)
		p = slnklistptr->head;
	else
		p = lspos;
	*retpos = p->next;//ָ�뷵��ɾ���Ľ��
	p->next = p->next->next;
	p->next->prev = p;
	--slnklistptr->length;
	return true;
}

void ListSetCurElem_cycdbllnk(CycDblLnkPosition curpos, const CycDblLnkElemType elem)
{
	curpos->elem = elem;//���õ�ǰ����Ԫ�ص�ֵ
}

CycDblLnkElemType ListGetCurElem_cycdbllnk(CycDblLnkPosition curpos)
{
	return curpos->elem;//���ص�ǰ���Ԫ�ص�ֵ
}

_Bool ListIsEmpty_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//�����Ϊ��,����true,���򷵻�false
}

int ListLength_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->length;//���ر�ĳ���
}

CycDblLnkPosition ListGetHead_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->head;//���ر��ͷ���
}

CycDblLnkPosition ListGetRear_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->rear;//���ر��β���
}

_Bool ListPriorPos_cycdbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	if (curpos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != curpos)//�����Ƿ����lspos���
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	*retpos = (p == slnklistptr->head->next ? slnklistptr->rear : p);				//��ָ��retpos����ǰ��
	return true;
}

_Bool ListNextPos_cycdbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;
	
	if (curpos != slnklistptr->head)
	{
		while (p != slnklistptr->head && p != curpos)//�����Ƿ����lspos���
			p = p->next;
		if (p == slnklistptr->head)
			return false;
	}
	*retpos = (curpos == slnklistptr->rear ? slnklistptr->head->next : curpos->next);//��retpos���ص�ǰ���ĺ��
	return true;
}

_Bool ListLocatePos_cycdbllnk(const CycDblLnkList *const slnklistptr, const int index, CycDblLnkPosition *retpos)
{
	int i = 0;
	CycDblLnkPosition p = slnklistptr->head->next;

	if (index<1 || index>slnklistptr->length)//�������Ϸ�,ʧ�ܴ���
	{
		*retpos = NULL;
		return false;
	}
	while (p != slnklistptr->head)//���index������λ��
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	*retpos = p;//��ָ��retpos���ؽ��λ��
	return true;
}

_Bool ListLocateElem_cycdbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkElemType elem, _Bool(*compare)(CycDblLnkElemType, CycDblLnkElemType), CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p != slnklistptr->head)//���һ����elem����compare()��ϵ�Ľ��
	{
		if ((*compare)(p->elem, elem))
			break;
		p = p->next;
	}
	if (slnklistptr->head == p)//���������,ʧ�ܴ���
	{
		*retpos = NULL;
		return false;
	}
	*retpos = p;//��ָ�뷵�ظý��
	return true;
}

void ListTraverseAscend_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p != slnklistptr->head)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void ListTraverseDescend_cycdbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->rear;

	while (p != slnklistptr->head)
	{
		printf("%d ", p->elem);
		p = p->prev;
	}
	printf("\n");
}

_Bool CycListNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem)
{
	if (NULL == (*posptr = (CycDblLnkPosition)malloc(sizeof(CycDblLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void CycListNodeFree(CycDblLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual_cycdbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 <= e2;
}
