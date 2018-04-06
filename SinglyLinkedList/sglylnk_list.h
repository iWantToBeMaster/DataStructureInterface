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
//构造一个带头节点空的链表*slnklistptr

void ListDestroy_slnk(SLnkList *const slnklistptr);
//销毁链表*slnklistptr,*slnklistptr表结构将不存在

void ListClear_slnk(SLnkList *const slnklistptr);
//将链表*slnklistptr重置为空表,并释放原链表的结点空间,表结构依然存在

_Bool ListInsNodeFirst_slnk(SLnkList *const slnklistptr, const SLnkPosition inspos);
//将slnkpos所值结点插入在链表*slnklistptr的第一个结点之前

_Bool ListDelNodeFirst_slnk(SLnkList *const slnklistptr, SLnkPosition *const slnkposret);
//删除链表*slnklistptr的第一个结点,并由指针slnkposret返回该结点

void ListAppend_slnk(SLnkList *const slnklistptr, SLnkPosition slnkposhead);
//将指针slnkposhead所指(彼此以指针相链)的一串结点链接在线性链表*slnklistptr的最后一个结点之后
//并改变链表*slnklistptr的尾指针指向新的尾结点

_Bool ListRemoveRear_slnk(SLnkList *const slnklistptr, SLnkPosition *slnkposret);
//删除线性链表*slnklistptr中的尾结点并以slnkposret返回,改变链表*slnklistptr中尾指针指向新的尾结点

_Bool ListInsNodeBefore_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos);
//lspos指向线性链表*slnklistptr中的一个结点,将inspos所之结点插在lspos所指结点之前,并且修改指针lspos指向新插入的结点

_Bool ListInsNodeAfter_slnk(SLnkList *const slnklistptr, SLnkPosition lspos, SLnkPosition inspos);
//lspos指向线性链表*slnklistptr中的一个结点,将inspos所之结点插在lspos所指结点之后,并且修改指针lspos指向新插入的结点

void ListSetCurElem_slnk(SLnkPosition curpos, const SglyLnkElemType elem);
//curpos指向线性链表中的一个结点,用elem更新curpos所指结点中数据元素的值

SglyLnkElemType ListGetCurElem_slnk(SLnkPosition curpos);
//curpos指向线性链表中的一个结点,返回curpos所指结点中数据元素的值

_Bool ListIsEmpty_slnk(const SLnkList *const slnklistptr);
//线性链表*slnklistptr为空返回true,否则返回false

int ListLength_slnk(const SLnkList *const slnklistptr);
//返回线性链表*slnklistptr中元素的个数

SLnkPosition ListGetHead_slnk(const SLnkList *const slnklistptr);
//返回线性链表*slnklistptr中头结点的位置

SLnkPosition ListGetRear_slnk(const SLnkList *const slnklistptr);
//返回线性链表*slnklistptr最后一个结点的位置

_Bool ListPriorPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos);
//curpos指向线性链表*slnklistptr中的一个结点，由指针retpos返回curpos所指结点的直接前驱的位置,若无前驱指针返回NULL

_Bool ListNextPos_slnk(const SLnkList *const slnklistptr, const SLnkPosition curpos, SLnkPosition *retpos);
//curpos指向线性链表*slnklistptr中的一个结点，由指针retpos返回curpos所指结点的直接后继的位置,若无后继指针返回NULL

_Bool ListLocatePos_slnk(const SLnkList *const slnklistptr, const int index, SLnkPosition *retpos);
//用指针retpos返回线性链表*slnklistptr中第index个结点的位置

_Bool ListLocateElem_slnk(const SLnkList *const slnklistptr, const SglyLnkElemType elem, _Bool(*compare)(SglyLnkElemType, SglyLnkElemType), SLnkPosition *retpos);
//用指针retpos返回线性链表*slnklistptr中第一个与elem满足compare()判定关系的元素位置,若不存在返回NULL

void ListTraverse_slnk(const SLnkList *const slnklistptr);
//依次输出线性链表*slnklistptr中的每一个元素




_Bool IsGreaterThan(const SglyLnkElemType e1, const SglyLnkElemType e2);
//如果e1>e2返回true,否则返回false


_Bool IsGreaterThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2);
//如果e1>=e2返回true,否则返回false


_Bool IsEqual(const SglyLnkElemType e1, const SglyLnkElemType e2);
//如果e1=e2返回true,否则返回false


_Bool IsLessThan(const SglyLnkElemType e1, const SglyLnkElemType e2);
//如果e1<e2返回true,否则返回false


_Bool IsLessThanOrEqual(const SglyLnkElemType e1, const SglyLnkElemType e2);
//如果e1<=e2返回true,否则返回false


#endif // !SINGLYLINKEDLIST_SGLYLNK_LIST_H

