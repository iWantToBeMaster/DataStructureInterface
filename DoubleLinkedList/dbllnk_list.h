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
//构造一个带头节点空的链表*slnklistptr

void ListDestroy_dbllnk(DblLnkList *const slnklistptr);
//销毁链表*slnklistptr,*slnklistptr表结构将不存在

void ListClear_dbllnk(DblLnkList *const slnklistptr);
//将链表*slnklistptr重置为空表,并释放原链表的结点空间,表结构依然存在

_Bool ListInsNodeFirst_dbllnk(DblLnkList *const slnklistptr, const DblLnkPosition inspos);
//将slnkpos所值结点插入在链表*slnklistptr的第一个结点之前

_Bool ListDelNodeFirst_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *const slnkposret);
//删除链表*slnklistptr的第一个结点,并由指针slnkposret返回该结点

void ListAppend_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition slnkposhead);
//将指针slnkposhead所指(彼此以指针相链)的一串结点链接在线性链表*slnklistptr的最后一个结点之后
//并改变链表*slnklistptr的尾指针指向新的尾结点

_Bool ListRemoveRear_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition *slnkposret);
//删除线性链表*slnklistptr中的尾结点并以slnkposret返回,改变链表*slnklistptr中尾指针指向新的尾结点

_Bool ListInsNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos);
//lspos指向线性链表*slnklistptr中的一个结点,将inspos所之结点插在lspos所指结点之前,并且修改指针lspos指向新插入的结点

_Bool ListInsNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition inspos);
//lspos指向线性链表*slnklistptr中的一个结点,将inspos所之结点插在lspos所指结点之后,并且修改指针lspos指向新插入的结点

_Bool ListDelNodeBefore_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition *retpos);
//lspos指向线性链表*slnklistptr中的一个结点,将删除lspos的直接前驱结点,由指针retpos返回删除的结点,如果失败retpos返回NULL

_Bool ListDelNodeAfter_dbllnk(DblLnkList *const slnklistptr, DblLnkPosition lspos, DblLnkPosition *retpos);
//lspos指向线性链表*slnklistptr中的一个结点,将删除lspos的直接后继结点,由指针retpos返回删除的结点,如果失败retpos返回NULL

void ListSetCurElem_dbllnk(DblLnkPosition curpos, const DblLnkElemType elem);
//curpos指向线性链表中的一个结点,用elem更新curpos所指结点中数据元素的值

DblLnkElemType ListGetCurElem_dbllnk(DblLnkPosition curpos);
//curpos指向线性链表中的一个结点,返回curpos所指结点中数据元素的值

_Bool ListIsEmpty_dbllnk(const DblLnkList *const slnklistptr);
//线性链表*slnklistptr为空返回true,否则返回false

int ListLength_dbllnk(const DblLnkList *const slnklistptr);
//返回线性链表*slnklistptr中元素的个数

DblLnkPosition ListGetHead_dbllnk(const DblLnkList *const slnklistptr);
//返回线性链表*slnklistptr中头结点的位置

DblLnkPosition ListGetRear_dbllnk(const DblLnkList *const slnklistptr);
//返回线性链表*slnklistptr最后一个结点的位置

_Bool ListPriorPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos);
//curpos指向线性链表*slnklistptr中的一个结点，由指针retpos返回curpos所指结点的直接前驱的位置,若无前驱指针返回NULL

_Bool ListNextPos_dbllnk(const DblLnkList *const slnklistptr, const DblLnkPosition curpos, DblLnkPosition *retpos);
//curpos指向线性链表*slnklistptr中的一个结点，由指针retpos返回curpos所指结点的直接后继的位置,若无后继指针返回NULL

_Bool ListLocatePos_dbllnk(const DblLnkList *const slnklistptr, const int index, DblLnkPosition *retpos);
//用指针retpos返回线性链表*slnklistptr中第index个结点的位置

_Bool ListLocateElem_dbllnk(const DblLnkList *const slnklistptr, const DblLnkElemType elem, _Bool(*compare)(DblLnkElemType, DblLnkElemType), DblLnkPosition *retpos);
//用指针retpos返回线性链表*slnklistptr中第一个与elem满足compare()判定关系的元素位置,若不存在返回NULL

void ListTraverseAscend_dbllnk(const DblLnkList *const slnklistptr);
//正序依次输出线性链表*slnklistptr中的每一个元素

void ListTraverseDescend_dbllnk(const DblLnkList *const slnklistptr);
//逆序依次输出线性链表*slnklistptr中的每一个元素


_Bool IsGreaterThan_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//如果e1>e2返回true,否则返回false


_Bool IsGreaterThanOrEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//如果e1>=e2返回true,否则返回false


_Bool IsEqual_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//如果e1=e2返回true,否则返回false


_Bool IsLessThan_dbllnk(const DblLnkElemType e1, const DblLnkElemType e2);
//如果e1<e2返回true,否则返回false


_Bool IsLessThanOrEqual(const DblLnkElemType e1, const DblLnkElemType e2);
//如果e1<=e2返回true,否则返回false


#endif // !DOUBLELINKEDLIST_SGLYLNK_LIST_H


