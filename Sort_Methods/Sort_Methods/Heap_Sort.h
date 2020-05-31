#pragma once
#pragma once
#include <iostream>


#define  MaxData  999
typedef struct HeapStruct* MaxHeap;
typedef int ElemType;
struct HeapStruct {
    ElemType* Elements;
    int Size;
    int Capacity;
};

MaxHeap Init(int MaxSize) {
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElemType*)malloc((MaxSize + 1) * sizeof(ElemType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxData;                   //哨兵
    return H;
}

bool IsFull(MaxHeap H) {
    return H->Size == H->Capacity;
}

bool IsEmpty(MaxHeap H) {
    return H->Size == 0;
}

void Insert(MaxHeap H, ElemType item) {
    int i;
    if (IsFull(H)) {
        std::cout << "The Heap is full" << std::endl;
        return;
    }
    i = ++H->Size;
    for (; H->Elements[i / 2] < item; i /= 2)        //如果是当前最大的，就会和哨兵比较
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = item;
}


// 可以利用连续的Pop，将整个数组的最小按序输出得到序列
ElemType Pop(MaxHeap H) {
    int Parent, Child;
    ElemType MaxItem, temp;
    if (IsEmpty(H)) {
        std::cout << "The Heap is Empty" << std::endl;
        return 0;
    }
    MaxItem = H->Elements[1];
    temp = H->Elements[H->Size--];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))
            Child++;
        if (temp >= H->Elements[Child]) break;
        else
            H->Elements[Parent] = H->Elements[Child];
    }
    H->Elements[Parent] = temp;
    return MaxItem;
}

/*----------- 建造最大堆 -----------*/
void PercDown(MaxHeap H, int p)                   //堆中数据从下标1开始存储
{ /* 下滤：将H中以H->Elements[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElemType X;

    X = H->Elements[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))
            Child++;  /* Child指向左右子结点的较大者 */
        if (X >= H->Elements[Child]) break; /* 找到了合适位置 */
        else  /* 下滤X */
            H->Elements[Parent] = H->Elements[Child];
    }
    H->Elements[Parent] = X;
}

void BuildHeap(MaxHeap H)
{ /* 调整H->Elements[]中的元素，使满足最大堆的有序性  */
  /* 这里假设所有H->Size个元素已经存在H->Elements[]中 */

    int i;

    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
}

void PercDown(ElemType A[], int p, int N)          //堆中数据从0开始存储
{ /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
  /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElemType X;

    X = A[p]; /* 取出根结点存放的值 */
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            Child++;  /* Child指向左右子结点的较大者 */
        if (X >= A[Child]) break; /* 找到了合适位置 */
        else  /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}



void Heap_Sort(ElemType A[], int N) {
    ElemType temp;
    // 这里不能直接调用Build函数，此处的数组中的信息是从下标0开始存储的
    for (int i = N / 2 - 1; i >= 0; i--)
        PercDown(A, i, N);
    for (int i = N - 1; i > 0; i--) {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        PercDown(A, 0, i);         //将最大的值放到最后，然后将除最后一个之外的所有数字进行堆排序
    }
}