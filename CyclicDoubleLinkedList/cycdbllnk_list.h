#ifndef CYCLICDOUBLELINKEDLIST_CYCDBLLNK_LIST_H
#define CYCLICDOUBLELINKEDLIST_CYCDBLLNK_LIST_H

#ifndef	DOUBLELINKEDLIST_SGLYLNK_LIST_H
#define DOUBLELINKEDLIST_SGLYLNK_LIST_H

#include <stdbool.h>

typedef int CycDblLnkElemType;

typedef struct cycdbllnknode
{
	CycDblLnkElemType elem;
	struct cycdbllnknode *next;
	struct cycdbllnknode *prev;
}*CycDblLnkPosition, CycDblLnkNode;

typedef struct
{
	CycDblLnkPosition head, rear;
	int length;
}CycDblLnkList;


_Bool ListInitial_dbllnk(CycDblLnkList *const slnklistptr);
//����һ����ͷ�ڵ�յ�����*slnklistptr

void ListDestroy_dbllnk(CycDblLnkList *const slnklistptr);
//��������*slnklistptr,*slnklistptr��ṹ��������

void ListClear_dbllnk(CycDblLnkList *const slnklistptr);
//������*slnklistptr����Ϊ�ձ�,���ͷ�ԭ����Ľ��ռ�,��ṹ��Ȼ����

_Bool ListInsNodeFirst_dbllnk(CycDblLnkList *const slnklistptr, const CycDblLnkPosition inspos);
//��slnkpos��ֵ������������*slnklistptr�ĵ�һ�����֮ǰ

_Bool ListDelNodeFirst_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *const slnkposret);
//ɾ������*slnklistptr�ĵ�һ�����,����ָ��slnkposret���ظý��

void ListAppend_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition slnkposhead);
//��ָ��slnkposhead��ָ(�˴���ָ������)��һ�������������������*slnklistptr�����һ�����֮��
//���ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListRemoveRear_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition *slnkposret);
//ɾ����������*slnklistptr�е�β��㲢��slnkposret����,�ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListInsNodeBefore_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮ǰ,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListInsNodeAfter_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮��,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListDelNodeBefore_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos);
//lsposָ����������*slnklistptr�е�һ�����,��ɾ��lspos��ֱ��ǰ�����,��ָ��retpos����ɾ���Ľ��,���ʧ��retpos����NULL

_Bool ListDelNodeAfter_dbllnk(CycDblLnkList *const slnklistptr, CycDblLnkPosition lspos, CycDblLnkPosition *retpos);
//lsposָ����������*slnklistptr�е�һ�����,��ɾ��lspos��ֱ�Ӻ�̽��,��ָ��retpos����ɾ���Ľ��,���ʧ��retpos����NULL

void ListSetCurElem_dbllnk(CycDblLnkPosition curpos, const CycDblLnkElemType elem);
//curposָ�����������е�һ�����,��elem����curpos��ָ���������Ԫ�ص�ֵ

CycDblLnkElemType ListGetCurElem_dbllnk(CycDblLnkPosition curpos);
//curposָ�����������е�һ�����,����curpos��ָ���������Ԫ�ص�ֵ

_Bool ListIsEmpty_dbllnk(const CycDblLnkList *const slnklistptr);
//��������*slnklistptrΪ�շ���true,���򷵻�false

int ListLength_dbllnk(const CycDblLnkList *const slnklistptr);
//������������*slnklistptr��Ԫ�صĸ���

CycDblLnkPosition ListGetHead_dbllnk(const CycDblLnkList *const slnklistptr);
//������������*slnklistptr��ͷ����λ��

CycDblLnkPosition ListGetRear_dbllnk(const CycDblLnkList *const slnklistptr);
//������������*slnklistptr���һ������λ��

_Bool ListPriorPos_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ��ǰ����λ��,����ǰ��ָ�뷵��NULL

_Bool ListNextPos_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkPosition curpos, CycDblLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ�Ӻ�̵�λ��,���޺��ָ�뷵��NULL

_Bool ListLocatePos_dbllnk(const CycDblLnkList *const slnklistptr, const int index, CycDblLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�index������λ��

_Bool ListLocateElem_dbllnk(const CycDblLnkList *const slnklistptr, const CycDblLnkElemType elem, _Bool(*compare)(CycDblLnkElemType, CycDblLnkElemType), CycDblLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�һ����elem����compare()�ж���ϵ��Ԫ��λ��,�������ڷ���NULL

void ListTraverseAscend_dbllnk(const CycDblLnkList *const slnklistptr);
//�������������������*slnklistptr�е�ÿһ��Ԫ��

void ListTraverseDescend_dbllnk(const CycDblLnkList *const slnklistptr);
//�������������������*slnklistptr�е�ÿһ��Ԫ��


_Bool IsGreaterThan_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2);
//���e1>e2����true,���򷵻�false


_Bool IsGreaterThanOrEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2);
//���e1>=e2����true,���򷵻�false


_Bool IsEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2);
//���e1=e2����true,���򷵻�false


_Bool IsLessThan_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2);
//���e1<e2����true,���򷵻�false


_Bool IsLessThanOrEqual_dbllnk(const CycDblLnkElemType e1, const CycDblLnkElemType e2);
//���e1<=e2����true,���򷵻�false


#endif // !DOUBLELINKEDLIST_SGLYLNK_LIST_H




#endif // !CYCLICDOUBLELINKEDLIST_CYCDBLLNK_LIST_H

