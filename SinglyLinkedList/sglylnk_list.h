#ifndef SINGLYLINKEDLIST_SGLYLNK_LIST_H
#define SINGLYLINKEDLIST_SGLYLNK_LIST_H

#include <stdbool.h>

typedef int SglyLnkElemType;

typedef struct slnknode
{
	SglyLnkElemType elem;
	struct slnknode *next;
}*SLnkPosition,SLnkNode;

typedef struct
{
	SLnkPosition head, rear;
	int length;
}SLnkList;


_Bool ListInitial_slnk(SLnkList *const slnklistptr);
//����һ����ͷ�ڵ�յ�����*slnklistptr

void ListDestroy_slnk(SLnkList *const slnklistptr);
//��������*slnklistptr,*slnklistptr��ṹ��������

void ListClear_slnk(SLnkList *const slnklistptr);
//������*slnklistptr����Ϊ�ձ�,���ͷ�ԭ����Ľ��ռ�,��ṹ��Ȼ����

_Bool ListInsNodeFirst_slnk(SLnkList *const slnklistptr, const SLnkPosition inspos);
//��slnkpos��ֵ������������*slnklistptr�ĵ�һ�����֮ǰ

_Bool ListDelNodeFirst_slnk(SLnkList *const slnklistptr, SLnkPosition *const slnkposret);
//ɾ������*slnklistptr�ĵ�һ�����,����ָ��slnkposret���ظý��

void ListAppend_slnk(SLnkList *const slnklistptr, SLnkPosition slnkposhead);
//��ָ��slnkposhead��ָ(�˴���ָ������)��һ�������������������*slnklistptr�����һ�����֮��
//���ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListRemoveRear_slnk(SLnkList *const slnklistptr, SLnkPosition *slnkposret);
//ɾ����������*slnklistptr�е�β��㲢��slnkposret����,�ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListInsNodeBefore_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮ǰ,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListInsNodeAfter_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮��,�����޸�ָ��lsposָ���²���Ľ��

void ListSetCurElem_slnk(SLnkPosition curpos, const SglyLnkElemType elem);
//curposָ�����������е�һ�����,��elem����curpos��ָ���������Ԫ�ص�ֵ

SglyLnkElemType ListGetCurElem_slnk(SLnkPosition curpos);
//curposָ�����������е�һ�����,����curpos��ָ���������Ԫ�ص�ֵ

_Bool ListIsEmpty_slnk(const SLnkList *const slnklistptr);
//��������*slnklistptrΪ�շ���true,���򷵻�false

int ListLength_slnk(const SLnkList *const slnklistptr);
//������������*slnklistptr��Ԫ�صĸ���

SLnkPosition ListGetHead_slnk(const SLnkList *const slnklistptr);
//������������*slnklistptr��ͷ����λ��

SLnkPosition ListGetRear_slnk(const SLnkList *const slnklistptr);
//������������*slnklistptr���һ������λ��

_Bool ListPriorPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ��ǰ����λ��,����ǰ��ָ�뷵��NULL

_Bool ListNextPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ�Ӻ�̵�λ��,���޺��ָ�뷵��NULL

_Bool ListLocatePos_slnk(const SLnkList *const slnklistptr, const int index, SLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�index������λ��

_Bool ListLocateElem_slnk(const SLnkList *const slnklistptr, const SglyLnkElemType elem, _Bool(*compare)(SglyLnkElemType, SglyLnkElemType), SLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�һ����elem����compare()�ж���ϵ��Ԫ��λ��,�������ڷ���NULL

void ListTraverse_slnk(const SLnkList *const slnklistptr);
//���������������*slnklistptr�е�ÿһ��Ԫ��




_Bool IsGreaterThan(const SglyLnkElemType e1, const SglyLnkElemType e2);
//���e1>e2����true,���򷵻�false


_Bool IsGreaterThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2);
//���e1>=e2����true,���򷵻�false


_Bool IsEqual(const SglyLnkElemType e1, const SglyLnkElemType e2);
//���e1=e2����true,���򷵻�false


_Bool IsLessThan(const SglyLnkElemType e1, const SglyLnkElemType e2);
//���e1<e2����true,���򷵻�false


_Bool IsLessThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2);
//���e1<=e2����true,���򷵻�false


#endif // !SINGLYLINKEDLIST_SGLYLNK_LIST_H

