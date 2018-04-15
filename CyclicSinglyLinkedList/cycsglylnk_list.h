#ifndef CYCLICSINGLYLINKEDLIST_SGLYLNK_LIST_H
#define CYCLICSINGLYLINKEDLIST_SGLYLNK_LIST_H

#include <stdbool.h>

typedef int CycSglyLnkElemType;

typedef struct slnknode
{
	CycSglyLnkElemType elem;
	struct slnknode *next;
}*CycSLnkPosition, CycSLnkNode;

typedef struct
{
	CycSLnkPosition head, rear;
	int length;
}CycSLnkList;


_Bool ListInitial_cycslnk(CycSLnkList *const slnklistptr);
//����һ����ͷ�ڵ�յ�����*slnklistptr

void ListDestroy_cycslnk(CycSLnkList *const slnklistptr);
//��������*slnklistptr,*slnklistptr��ṹ��������

void ListClear_cycslnk(CycSLnkList *const slnklistptr);
//������*slnklistptr����Ϊ�ձ�,���ͷ�ԭ����Ľ��ռ�,��ṹ��Ȼ����

_Bool ListInsNodeFirst_cycslnk(CycSLnkList *const slnklistptr, const CycSLnkPosition inspos);
//��slnkpos��ֵ������������*slnklistptr�ĵ�һ�����֮ǰ

_Bool ListDelNodeFirst_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition *const slnkposret);
//ɾ������*slnklistptr�ĵ�һ�����,����ָ��slnkposret���ظý��

void ListAppend_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition slnkposhead);
//��ָ��slnkposhead��ָ(�˴���ָ������)��һ�������������������*slnklistptr�����һ�����֮��
//���ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListRemoveRear_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition *slnkposret);
//ɾ����������*slnklistptr�е�β��㲢��slnkposret����,�ı�����*slnklistptr��βָ��ָ���µ�β���

_Bool ListInsNodeBefore_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮ǰ,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListInsNodeAfter_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition inspos);
//lsposָ����������*slnklistptr�е�һ�����,��inspos��֮������lspos��ָ���֮��,�����޸�ָ��lsposָ���²���Ľ��

_Bool ListDelNodeBefore_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition *retpos);
//lsposָ����������*slnklistptr�е�һ�����,��ɾ��lspos��ֱ��ǰ�����,��ָ��retpos����ɾ���Ľ��,���ʧ��retpos����NULL

_Bool ListDelNodeAfter_cycslnk(CycSLnkList *const slnklistptr, CycSLnkPosition lspos, CycSLnkPosition *retpos);
//lsposָ����������*slnklistptr�е�һ�����,��ɾ��lspos��ֱ�Ӻ�̽��,��ָ��retpos����ɾ���Ľ��,���ʧ��retpos����NULL

void ListSetCurElem_cycslnk(CycSLnkPosition curpos, const CycSglyLnkElemType elem);
//curposָ�����������е�һ�����,��elem����curpos��ָ���������Ԫ�ص�ֵ

CycSglyLnkElemType ListGetCurElem_cycslnk(CycSLnkPosition curpos);
//curposָ�����������е�һ�����,����curpos��ָ���������Ԫ�ص�ֵ

_Bool ListIsEmpty_cycslnk(const CycSLnkList *const slnklistptr);
//��������*slnklistptrΪ�շ���true,���򷵻�false

int ListLength_cycslnk(const CycSLnkList *const slnklistptr);
//������������*slnklistptr��Ԫ�صĸ���

CycSLnkPosition ListGetHead_cycslnk(const CycSLnkList *const slnklistptr);
//������������*slnklistptr��ͷ����λ��

CycSLnkPosition ListGetRear_cycslnk(const CycSLnkList *const slnklistptr);
//������������*slnklistptr���һ������λ��

_Bool ListPriorPos_cycslnk(const CycSLnkList *const slnklistptr, const CycSLnkPosition curpos, CycSLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ��ǰ����λ��,����ǰ��ָ�뷵��NULL

_Bool ListNextPos_cycslnk(const CycSLnkList *const slnklistptr, const CycSLnkPosition curpos, CycSLnkPosition *retpos);
//curposָ����������*slnklistptr�е�һ����㣬��ָ��retpos����curpos��ָ����ֱ�Ӻ�̵�λ��,���޺��ָ�뷵��NULL

_Bool ListLocatePos_cycslnk(const CycSLnkList *const slnklistptr, const int index, CycSLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�index������λ��

_Bool ListLocateElem_cycslnk(const CycSLnkList *const slnklistptr, const CycSglyLnkElemType elem, _Bool(*compare)(CycSglyLnkElemType, CycSglyLnkElemType), CycSLnkPosition *retpos);
//��ָ��retpos������������*slnklistptr�е�һ����elem����compare()�ж���ϵ��Ԫ��λ��,�������ڷ���NULL

void ListTraverse_cycslnk(const CycSLnkList *const slnklistptr);
//���������������*slnklistptr�е�ÿһ��Ԫ��

_Bool IsGreaterThan_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2);
//���e1>e2����true,���򷵻�false


_Bool IsGreaterThanOrEqual_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2);
//���e1>=e2����true,���򷵻�false


_Bool IsEqual_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2);
//���e1=e2����true,���򷵻�false


_Bool IsLessThan_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2);
//���e1<e2����true,���򷵻�false


_Bool IsLessThanOrEqual_cycslnk(const CycSglyLnkElemType e1, const CycSglyLnkElemType e2);
//���e1<=e2����true,���򷵻�false


#endif // !CYCLICSINGLYLINKEDLIST_SGLYLNK_LIST_H