#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cycsglylnk_list.h"

_Bool CycListNodeAllocation(CycSLnkPosition *posptr, CycSglyLnkElemType elem);
void CycListNodeFree(CycSLnkPosition *posptr);

_Bool ListInitial_cycslnk(CycSLnkList *const slnklistptr)
{
	if (!CycListNodeAllocation(&slnklistptr->head, INT_MAX))//Ϊͷ������ռ�
		return false;
	slnklistptr->rear = slnklistptr->head;//��ʼ��βָ��
	slnklistptr->rear->next = slnklistptr->head;//��β����
	slnklistptr->length = 0;//���ȳ�ʼ��Ϊ0
	return true;
}

void ListDestroy_cycslnk(CycSLnkList *const slnklistptr)
{
	CycSLnkPosition p = NULL, q = NULL;

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

void ListClear_cycslnk(CycSLnkList *const slnklistptr)
{
	CycSLnkPosition p = NULL, q = NULL;

	p = slnklistptr->head->next;//��ͷ�ڵ����һ����㿪ʼ�ͷŽ��ռ�,�Ա���ͷ���
	while (p)
	{
		q = p;
		p = p->next;
		CycListNodeFree(&p);
	}
	slnklistptr->rear = slnklistptr->head;//����βָ��
	slnklistptr->rear->next = slnklistptr->head;//��β����
	slnklistptr->length = 0;//����������
}

_Bool ListInsNodeFirst_cycslnk(CycSLnkList *const slnklistptr, const CycSLnkPosition inspos)
{
	inspos->next = slnklistptr->head->next;				//ͷ�ڵ�֮��Ľ�����ӵ�inspos�ĺ���
	slnklistptr->head->next = inspos;					//inspos������Ľ�����ӵ�ͷ�ڵ�ĺ���
	if (0 == slnklistptr->length)						//���֮ǰΪ�ձ�,������βָ��
	{
		slnklistptr->rear = inspos;
		slnklistptr->rear->next = slnklistptr->head;	//��β����
	}
	++slnklistptr->length;								//�����ȼ�1
	return true;
}

_Bool ListDelNodeFirst_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition *const slnkposret)
{
	*slnkposret = NULL;
	if (NULL == slnklistptr->head->next)						//�����Ϊ��,����ʧ��
		return false;
	*slnkposret = slnklistptr->head->next;						//��ָ��slnkposret���ؽ�ɾ���Ľ��
	if (1 == slnklistptr->length)								//���֮ǰ����Ϊ1,������βָ��
	{
		slnklistptr->rear = slnklistptr->head;
		slnklistptr->rear->next = slnklistptr->head;			//��β����
	}
	slnklistptr->head->next = slnklistptr->head->next->next;	//ɾ������
	--slnklistptr->length;										//�����ȼ�1
	return true;
}

void ListAppend_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition slnkposhead)
{
	CycSLnkPosition p = slnkposhead;
	int cnt = 1;
	while (p->next)									//���������ĳ���
	{
		++cnt;
		p = p->next;
	}
	slnklistptr->rear->next = slnkposhead;			//��slnkposhead���ӵ�����ĺ���
	slnklistptr->rear = p;							//��������βָ��
	slnklistptr->rear->next = slnklistptr->head;	//��β����
	slnklistptr->length += cnt;						//���ñ���
}

_Bool ListRemoveRear_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition *slnkposret)
{
	CycSLnkPosition p = slnklistptr->head;
	if (0 == slnklistptr->length)						//�����Ϊ��,�򷵻�false
		return false;
	while ((p->next != slnklistptr->rear) && p->next)	//��β����ǰ�� 
		p = p->next;
	*slnkposret = slnklistptr->rear;					//��ָ��slnkposret���ؽ�ɾ���Ľ��
	p->next = NULL;
	slnklistptr->rear = p;								//����βָ��
	slnklistptr->rear->next = slnklistptr->head;		//��β����
	--slnklistptr->length;								//�����ȼ�1
	return true;
}

_Bool ListInsNodeBefore_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition inspos)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p!=slnklistptr->head)	//��lspos��ǰ�����
	{
		if (p->next == lspos)
			break;
		p = p->next;
	}
	if (p == slnklistptr->head)		//���в�����lspos���
		return false;
	inspos->next = lspos;										//��lspos������Ľ�����ӵ�inspos�ĺ���
	p->next = inspos;											//��inspos������Ľ�����ӵ�lsposǰ���ĺ���
	if (p->next == slnklistptr->head)
		slnklistptr->rear = inspos;								//����βָ��
	++slnklistptr->length;										//�����ȼ�1
	return true;
}

_Bool ListInsNodeAfter_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition inspos)
{
	CycSLnkPosition p = slnklistptr->head->next;
	while (p != slnklistptr->head && p != lspos)//�����Ƿ����lspos���
		p = p->next;
	inspos->next = lspos->next;				//��lspos����Ľ�����ӵ�inpos���ĺ���
	lspos->next = inspos;					//��inspos������Ľ�����ӵ�lspos�ĺ���
	if (slnklistptr->rear == p)				//���ʱ����β���ĺ���,������β���
		slnklistptr->rear = inspos;
	++slnklistptr->length;					//��ĳ��ȼ�1
	return true;
}

_Bool ListDelNodeBefore_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition *retpos)
{
	CycSLnkPosition p = slnklistptr->head, q = slnklistptr->head;

	*retpos = NULL;
	while (p != slnklistptr->head)	//��lspos��ǰ�����
	{
		if (p->next == lspos)
			break;
		p = p->next;
	}
	if (p == slnklistptr->head)		//���в�����lspos���
		return false;
	while (q != slnklistptr->head)//��p��ǰ�����
	{
		if (q->next == p)
			break;
		q = q->next;
	}
	if (q = slnklistptr->head)//���û���ҵ�ǰ��,�򷵻�ʧ��
		return false;
	q->next = p->next;//ɾ������
	*retpos = p;//ָ�뷵��ɾ���Ľ��
	--slnklistptr->length;//���ȼ�1
	return true;
}

_Bool ListDelNodeAfter_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition *retpos)
{
	CycSLnkPosition p = slnklistptr->head->next;

	*retpos = NULL;
	while (p != slnklistptr->head&&p != lspos)//�����Ƿ����lspos���
		p = p->next;
	if (slnklistptr->head == p || slnklistptr->head == p->next)//���в�����lspos���,����lsposû�к�̽��,����false
		return false;
	lspos->next = lspos->next->next;//ɾ������
	*retpos = lspos->next;//ָ�뷵��ɾ���Ľ��
	--slnklistptr->length;
	return true;
}

void ListSetCurElem_cycslnk(CycSLnkPosition curpos, const CycSglyLnkElemType elem)
{
	curpos->elem = elem;//���õ�ǰ����Ԫ�ص�ֵ
}

CycSglyLnkElemType ListGetCurElem_cycslnk(CycSLnkPosition curpos)
{
	return curpos->elem;//���ص�ǰ���Ԫ�ص�ֵ
}

_Bool ListIsEmpty_cycslnk(const CycSLnkList *const slnklistptr)
{
	return 0 == slnklistptr->length;//�����Ϊ��,����true,���򷵻�false
}

int ListLength_cycslnk(const CycSLnkList *const slnklistptr)
{
	return slnklistptr->length;//���ر�ĳ���
}

CycSLnkPosition ListGetHead_cycslnk(const CycSLnkList *const slnklistptr)
{
	return slnklistptr->head;//���ر��ͷ���
}

CycSLnkPosition ListGetRear_cycslnk(const CycSLnkList *const slnklistptr)
{
	return slnklistptr->rear;//���ر��β���
}

_Bool ListPriorPos_cycslnk(const CycSLnkList *const slnklistptr, const CycSLnkPosition curpos, CycSLnkPosition *retpos)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p->next != slnklistptr->head && (curpos != p->next))						//��curpos����ǰ��
		p = p->next;
	*retpos = (p == slnklistptr->head->next ? slnklistptr->rear : p);				//��ָ��retpos����ǰ��
	return true;
}

_Bool ListNextPos_cycslnk(const CycSLnkList *const slnklistptr, const CycSLnkPosition curpos, CycSLnkPosition *retpos)
{
	*retpos = (curpos == slnklistptr->rear ? slnklistptr->head->next : curpos->next);//��retpos���ص�ǰ���ĺ��
	return true;
}

_Bool ListLocatePos_cycslnk(const CycSLnkList *const slnklistptr, const int index, CycSLnkPosition *retpos)
{
	int i = 0;
	CycSLnkPosition p = slnklistptr->head->next;

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

_Bool ListLocateElem_cycslnk(const CycSLnkList *const slnklistptr, const CycSglyLnkElemType elem, _Bool(*compare)(CycSglyLnkElemType, CycSglyLnkElemType), CycSLnkPosition *retpos)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p!=slnklistptr->head)//���һ����elem����compare()��ϵ�Ľ��
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

void ListTraverse_cycslnk(const CycSLnkList *const slnklistptr)
{
	CycSLnkPosition p = slnklistptr->head->next;

	while (p != slnklistptr->head)//�������������ÿһ������Ԫ�ص�ֵ
	{
		printf("%d ", p->elem);
		p = p->next;
	}
	printf("\n");
}

_Bool CycListNodeAllocation(CycSLnkPosition *posptr, CycSglyLnkElemType elem)
{
	if (NULL == (*posptr = (CycSLnkPosition)malloc(sizeof(CycSLnkNode))))
		return false;
	(*posptr)->elem = elem;
	(*posptr)->next = NULL;
	return true;
}

void CycListNodeFree(CycSLnkPosition *posptr)
{
	free(*posptr);
}

_Bool IsGreaterThan_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e1 > e2;
}

_Bool IsGreaterThanOrEqual_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e1 >= e2;
}

_Bool IsEqual_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e1 == e2;
}

_Bool IsLessThan_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e2 < e2;
}

_Bool IsLessThanOrEqual_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2)
{
	return e2 <= e2;
}
