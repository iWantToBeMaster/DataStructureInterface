#ifndef SEQUENCELIST_SQ_LIST_H
#define SEQUENCELIST_SQ_LIST_H

#include <stdbool.h>
#include <stdarg.h>

#define LIST_INIT_SIZE				100	//线性表存储空间的初始分配量
#define LIST_INCREMENT_SIZE			10	//线性表存储空间的分配增量

typedef int ElemType;

typedef struct
{
	ElemType *elembase;	//存储空间基址
	int length;		//当前长度
	int size;		//当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;

_Bool ListInitial_sq(SqList *const sqlistptr);
//操作结果:构造一个空的线性表*sqlistptr


void ListClear_sq(SqList *const sqlistptr);
//初始条件:线性表*sqlistptr已经存在
//操作结果:将*sqlistptr重置为空表


void ListDestroy_sq(SqList *const sqlistptr);
//初始条件:线性表*sqlistptr已经存在
//操作结果:销毁线性表*sqlistptr


int ListLength_sq(const SqList *const sqlistptr);
//初始条件:线性表*sqlistptr已经存在
//操作结果:返回线性表*sqlistptr中数据元素的个数


_Bool ListIsEmpty_sq(const SqList *const sqlistptr);
//初始条件:线性表*sqlistptr已经存在
//操作结果:若线性表*sqlistptr为空表,则返回true,否则返回false;


_Bool ListGetElem_sq(const SqList *const sqlistptr, const int index, ElemType *const elemptr);
//初始条件:线性表*sqlistptr已经存在,1<=i<=ListLength_sq(sqlistptr)
//操作结果:用elemptr返回*sqlistptr中第index个元素的值


_Bool ListLocate_sq(const SqList *const sqlistptr, const ElemType elem, _Bool (*compare)(const ElemType, const ElemType), int *const indexptr);
//初始条件:线性表*sqlistptr已经存在,Compare(const ElemType, const ElemType)是数据元素判定函数
//操作结果:由indexptr指针返回线性表*sqlistptr中第一个与elem满足关系Compare(const ElemType, const ElemType)的数据元素的位序,
//		  如果数据元素存在返回true,否则返回false


_Bool ListInsert_sq(SqList *const sqlistptr, const ElemType elem, const int index);
//初始条件:线性表*sqlistptr已经存在,1<=i<=ListLength_sq(sqlistptr)+1
//操作结果:在线性表*sqlistptr第index个位置之前插入新的元素elem,*sqlistptr长度增加1


_Bool ListDelete_sq(SqList *const sqlistptr, const int index, ElemType *const retptr);
//初始条件:线性表*sqlistptr已经存在且非空,1<=i<=ListLength_sq(sqlistptr)
//操作结果:删除*sqlistptr的第index个元素,并用指针retptr返回其值,线性表*sqlistptr的长度减1


_Bool ListPriorElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr);
//初始条件:线性表*sqlistptr已经存
//操作结果:若curelem是线性表*sqlistptr中的元素,且不是第一个,则用指针retelemptr返回它的前驱,否则操作失败


_Bool ListNextElem_sq(SqList *const sqlistptr, const ElemType curelem, ElemType *const retelemptr);
//初始条件:线性表*sqlistptr已经存
//操作结果:若curelem是线性表*sqlistptr中的元素,且不是最后一个,则用指针retelemptr返回它的后继,否则操作失败


_Bool ListMerge_sq(SqList *const sqlistaptr, SqList *const sqlistbptr, SqList *const retlistptr);
//初始条件:线性表*sqlistaptr和*sqlistbptr已经存,且有序,顺序相同.*retlistptr为空表
//操作结果:线性表*sqlistaptr和线性表*sqlistbptr归并产生的新表仍然有序,由指针retlistptr返回


void ListSort_sq(SqList *const sqlistptr);
//初始条件:线性表*sqlistptr已经存在
//操作结果:表中的元素从大到小排序


_Bool ListCopy_sq(SqList *const sqsrcptr, SqList *const sqdestptr);
//初始条件:线性表*sqsrcptr已经存在
//操作结果:*sqsrcptr复制给*sqdestptr


void ListTraverse_sq(SqList *const sqlistptr);
//初始条件:线性表*sqlistptr已经存在
//操作结果:依次对*sqlist的每个数据元素进行输出



_Bool IsGreaterThan(const ElemType e1, const ElemType e2);
//如果e1>e2返回true,否则返回false


_Bool IsGreaterThanOrEqual(const ElemType e1, const ElemType e2);
//如果e1>=e2返回true,否则返回false


_Bool IsEqual(const ElemType e1, const ElemType e2);
//如果e1=e2返回true,否则返回false


_Bool IsLessThan(const ElemType e1, const ElemType e2);
//如果e1<e2返回true,否则返回false


_Bool IsLessThanOrEqual(const ElemType e1, const ElemType e2);
//如果e1<=e2返回true,否则返回false

#endif // !SEQUENCELIST_SQ_LIST_H

