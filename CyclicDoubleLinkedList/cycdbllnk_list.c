#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cycdbllnk_list.h"

_Bool CycDblLstNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem);
void CycDblLstNodeFree(CycDblLnkPosition *posptr);

_Bool ListInitial_dbllnk(CycDblLnkList *const slnklistptr)
{
	if (!CycDblLstNodeAllocation(&slnklistptr->head, INT_MAX))//Ϊͷ������ռ�
		return false;
	slnklistptr->head->prev = NULL;//ǰ���ÿ�
	slnklistptr->head->next = NULL;//����ÿ�
	slnklistptr->rear = slnklistptr->head;//��ʼ��βָ��
	slnklistptr->length = 0;//���ȳ�ʼ��Ϊ0
	return true;
}

void ListDestroy_dbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ��㿪ʼ�ͷŽ��ռ�
	while (p!= slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycDblLstNodeFree(&p);
	}
	CycDblLstNodeFree(&slnklistptr->head);//�ͷ�ͷ���
	slnklistptr->head = slnklistptr->rear = NULL;//��ṹ�ÿ�
	slnklistptr->length = 0;//����ֵ0
}

void ListClear_dbllnk(CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ�ڵ����һ����㿪ʼ�ͷŽ��ռ�,�Ա���ͷ���
	while (p != slnklistptr->head)
	{
		q = p;
		p = p->next;
		CycDblLstNodeFree(&p);
	}
	slnklistptr->head->next = NULL;//�ÿ�
	slnklistptr->rear = slnklistptr->head;//����βָ��
	slnklistptr->head->prev = NULL;//ǰ���ÿ�
	slnklistptr->head->next = NULL;//����ÿ�
	slnklistptr->length = 0;//����������
}

_Bool ListInsNodeFirst_dbllnk(CycDblLnkList *const slnklistptr, const CycDblLnkPosition inspos)
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

_Bool ListDelNodeFirst_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *const slnkposret)
{
	if (0 == slnklistptr->length)//�����Ϊ��,����ʧ��
		return false;
	*slnkposret = slnklistptr->head->next;//��ָ��slnkposret���ؽ�ɾ���Ľ��
	if (slnklistptr->rear == slnklistptr->head->next)//���֮ǰ����Ϊ1,������βָ��
		slnklistptr->rear = slnklistptr->head;
	slnklistptr->head->next = slnklistptr->head->next->next;//ͷ���ĺ��Ϊ����һ�����
	slnklistptr->head->next->prev = slnklistptr->head;//ͷ���ĺ�̵�ǰ��Ϊͷ���
	--slnklistptr->length;//�����ȼ�1
	return true;
}

void ListAppend_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition slnkposhead)
{
	CycDblLnkPosition p = slnkposhead;
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

_Bool ListRemoveRear_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *slnkposret)
{
	CycDblLnkPosition p = slnklistptr->head;

	if (slnklistptr->head == slnklistptr->rear)//�����Ϊ��,�򷵻�false
		return false;
	while ((p->next != slnklistptr->rear) && p->next!=slnklistptr->head)//��β����ǰ�� 
		p = p->next;
	*slnkposret = slnklistptr->rear;//��ָ��slnkposret���ؽ�ɾ���Ľ��
	p->next = slnklistptr->head;
	slnklistptr->rear = p;//����βָ��
	--slnklistptr->length;//�����ȼ�1
	return true;
}

_Bool ListInsNodeBefore_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head;
	while ((p->next != lspos) && p->next!=slnklistptr->head)//��lspos��ǰ�����
		p = p->next;
	if (slnklistptr->head == p->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	inspos->next = lspos;//��lspos������Ľ�����ӵ�inspos�ĺ���
	p->next = inspos;//��inspos������Ľ�����ӵ�lsposǰ���ĺ���
	lspos->prev = inspos;//lspos��ǰ��ָ��inspos
	inspos->prev = p;//inspos��ǰ��ָ��p
	++slnklistptr->length;//�����ȼ�1
	return true;
}

_Bool ListInsNodeAfter_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos)
{
	CycDblLnkPosition p = slnklistptr->head;

	while (p!= slnklistptr->head && (p != lspos))//�����Ƿ����lspos���
		p = p->next;
	if (slnklistptr->head == p)//���в�����lspos���,����false
		return false;
	inspos->next = lspos->next;//��lspos����Ľ�����ӵ�inpos���ĺ���
	lspos->next = inspos;//��inspos������Ľ�����ӵ�lspos�ĺ���
	inspos->prev = lspos;
	if (slnklistptr->head != inspos->next)
		inspos->next->prev = inspos;
	if (slnklistptr->rear == p)//���ʱ����β���ĺ���,������β���
		slnklistptr->rear = inspos;
	++slnklistptr->length;//��ĳ��ȼ�1
	return true;
}

_Bool ListDelNodeBefore_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head, q = slnklistptr->head;

	*retpos = NULL;
	while ((p->next != lspos) && p->next!= slnklistptr->head)//��lspos��ǰ�����
		p = p->next;
	if (slnklistptr->head == p->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	while ((q->next != p) && (q->next!= slnklistptr->head))//��p��ǰ�����
		q = q->next;
	if (slnklistptr->head == q->next)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	q->next = p->next;//������̹�ϵ
	lspos->prev = q;//����ǰ����ϵ
	*retpos = p;//ָ�뷵��ɾ���Ľ��
	--slnklistptr->length;//���ȼ�1
	return true;

}

_Bool ListDelNodeAfter_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head;

	*retpos = NULL;
	while (p!= slnklistptr->head && (p != lspos))//�����Ƿ����lspos���
		p = p->next;
	if (slnklistptr->head == p || slnklistptr->head == p->next)//���в�����lspos���,����lsposû�к�̽��,����false
		return false;
	lspos->next = lspos->next->next;//������̹�ϵ
	lspos->next->prev = lspos;//����ǰ����ϵ
	*retpos = lspos->next;//ָ�뷵��ɾ���Ľ��
	--slnklistptr->length;//���ȼ�1
	return true;
}

void ListSetCurElem_dbllnk(CycDblLnkPosition curpos, const CycDblLnkElemType elem)
{
	curpos->elem = elem;//���õ�ǰ����Ԫ�ص�ֵ
}

CycDblLnkElemType ListGetCurElem_dbllnk(CycDblLnkPosition curpos)
{
	return curpos->elem;//���ص�ǰ���Ԫ�ص�ֵ
}

_Bool ListIsEmpty_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//�����Ϊ��,����true,���򷵻�false
}

int ListLength_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->length;//���ر�ĳ���
}

CycDblLnkPosition ListGetHead_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->head;//���ر��ͷ���
}

CycDblLnkPosition ListGetRear_dbllnk(const CycDblLnkList *const slnklistptr)
{
	return slnklistptr->rear;//���ر��β���
}

_Bool ListPriorPos_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head;

	while (p->next!= slnklistptr->head && (curpos != p->next))//��curpos����ǰ��
		p = p->next;
	if (slnklistptr->head == p->next)//���ǰ��������,����false
		return false;
	*retpos = (p == slnklistptr->head ? NULL : p);//��ָ��retpos����ǰ��
	return true;
}

_Bool ListNextPos_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos)
{
	*retpos = (curpos->next == NULL ? NULL : curpos->next);//��retpos���ص�ǰ���ĺ��
	return true;
}

_Bool ListLocatePos_dbllnk(const CycDblLnkList *const slnklistptr, const int index, CycDblLnkPosition *retpos)
{
	int i = 0;
	CycDblLnkPosition p = slnklistptr->head;

	if (index<1 || index>slnklistptr->length)//�������Ϸ�,ʧ�ܴ���
	{
		*retpos = NULL;
		return false;
	}
	while (p!= slnklistptr->head)//���index������λ��
	{
		p = p->next;
		++i;
		if (i >= index)
			break;
	}
	*retpos = p;//��ָ��retpos���ؽ��λ��
	return true;
}

_Bool ListLocateElem_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkElemType elem, _Bool(*compare)(CycDblLnkElemType, CycDblLnkElemType), CycDblLnkPosition *retpos)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p!= slnklistptr->head)//���һ����elem����compare()��ϵ�Ľ��
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

void ListTraverseAscend_dbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->head->next;

	while (p!= slnklistptr->head)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

void ListTraverseDescend_dbllnk(const CycDblLnkList *const slnklistptr)
{
	CycDblLnkPosition p = slnklistptr->rear;

	while (p != slnklistptr->head)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->prev;
	}
	printf("\n");
}

_Bool CycDblLstNodeAllocation(CycDblLnkPosition *posptr, CycDblLnkElemType elem)
{
	if (NULL == (*posptr = (CycDblLnkPosition)malloc(sizeof(CycDblLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void CycDblLstNodeFree(CycDblLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2)
{
	return e2 <= e2;
}
