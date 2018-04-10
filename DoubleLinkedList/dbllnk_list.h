#ifndef	DOUBLELINKEDLIST_SGLYLNK_LIST_H
#define DOUBLELINKEDLIST_SGLYLNK_LIST_H

#include <stdbool.h>

typedef int DblLnkElemType;

typedef struct DblLnkNode
{
	DblLnkElemType elem;
	struct DblLnkNode *next;
	struct DblLnkNode *prev;
}*DblLnkPosition, DblLnkNode;

typedef struct
{
	DblLnkPosition head, rear;
	int length;
}DblLnkList;


_Bool ListInitial_dbllnk(DblLnkList *const slnklistptr);
//����һ����ͷ�ڵ�յ�����*slnklistptr

void ListDestroy_dbllnk(DblLnkList *const slnklistptr);
//��������*slnklistptr,*slnklistptr��ṹ��������

void ListClear_dbllnk(DblLnkList *const slnklistptr);
//������*slnklistptr����Ϊ�ձ�,���ͷ�ԭ����Ľ��ռ�,��ṹ��Ȼ����

_Bool ListInsNodeFirst_dbllnk(DblLnkList *const slnklistptr, const DblLnkPosition inspos);
//��slnkpos��ֵ������������*slnklistptr�ĵ�һ�����֮ǰ

_Bool ListDelNodeFirst_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *const slnkposret);
//ɾ������*slnklistptr�ĵ�һ�����,����ָ��slnkposret���ظý��

void ListAppend_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition slnkposhead);
//��ָ��slnkposhead��ָ(�˴���ָ������)��һ�������������������*slnklistptr�����һ�����֮��
//���ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListRemoveRear_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *slnkposret);
//ɾ����������*slnklistptr�е�β��㲢��slnkposret����,�ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListInsNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮ǰ,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListInsNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮��,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListDelNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition *retpos);
//lsposָ����������*slnklistptr�е�һ�����,��ɾ��lspos��ֱ��ǰ�����,��ָ��retpos����ɾ���Ľ��,���ʧ��retpos����NULL

_Bool ListDelNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition *retpos);
//lsposָ����������*slnklistptr�е�һ�����,��ɾ��lspos��ֱ�Ӻ�̽��,��ָ��retpos����ɾ���Ľ��,���ʧ��retpos����NULL

void ListSetCurElem_dbllnk(DblLnkPosition curpos, const DblLnkElemType elem);
//curposָ�����������е�һ�����,��elem����curpos��ָ���������Ԫ�ص�ֵ

DblLnkElemType ListGetCurElem_dbllnk(DblLnkPosition curpos);
//curposָ�����������е�һ�����,����curpos��ָ���������Ԫ�ص�ֵ

_Bool ListIsEmpty_dbllnk(const DblLnkList *const slnklistptr);
//��������*slnklistptrΪ�շ���true,���򷵻�false

int ListLength_dbllnk(const DblLnkList *const slnklistptr);
//������������*slnklistptr��Ԫ�صĸ���

DblLnkPosition ListGetHead_dbllnk(const DblLnkList *const slnklistptr);
//������������*slnklistptr��ͷ����λ��

DblLnkPosition ListGetRear_dbllnk(const DblLnkList *const slnklistptr);
//������������*slnklistptr���һ������λ��

_Bool ListPriorPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ��ǰ����λ��,����ǰ��ָ�뷵��NULL

_Bool ListNextPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ�Ӻ�̵�λ��,���޺��ָ�뷵��NULL

_Bool ListLocatePos_dbllnk(const DblLnkList *const slnklistptr, const int index, DblLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�index������λ��

_Bool ListLocateElem_dbllnk(const DblLnkList *const slnklistptr, const DblLnkElemType elem, _Bool(*compare)(DblLnkElemType, DblLnkElemType), DblLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�һ����elem����compare()�ж���ϵ��Ԫ��λ��,�������ڷ���NULL

void ListTraverseAscend_dbllnk(const DblLnkList *const slnklistptr);
//�������������������*slnklistptr�е�ÿһ��Ԫ��

void ListTraverseDescend_dbllnk(const DblLnkList *const slnklistptr);
//�������������������*slnklistptr�е�ÿһ��Ԫ��


_Bool IsGreaterThan_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//���e1>e2����true,���򷵻�false


_Bool IsGreaterThanOrEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//���e1>=e2����true,���򷵻�false


_Bool IsEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//���e1=e2����true,���򷵻�false


_Bool IsLessThan_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//���e1<e2����true,���򷵻�false


_Bool IsLessThanOrEqual(const DblLnkElemType e1, const DblLnkElemType e2);
//���e1<=e2����true,���򷵻�false


#endif // !DOUBLELINKEDLIST_SGLYLNK_LIST_H


