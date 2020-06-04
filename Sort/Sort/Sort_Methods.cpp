
#include <iostream>
#include <algorithm>
#include "Sort_Methods.h"
#define  MaxData  999           //哨兵
#define Cutoff 100              //快速排序阈值



void Bubble_Sort(ElemType A[], int N)
{
	for (int P = N - 1; P >= 0; P--)
	{
		int flag = 0;
		for (int i = 0; i < P; i++)
		{
			if (A[i] > A[i + 1])
			{
				std::swap(A[i], A[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0)break;
	}
}


typedef struct HeapStruct* MaxHeap;
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

void Insert_Sort(ElemType A[], int N)
{
    /* 插入排序 */
    int P, i;
    ElemType Tmp;

    for (P = 1; P < N; P++) {
        Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
        for (i = P; i > 0 && A[i - 1] > Tmp; i--)
            A[i] = A[i - 1]; /*依次与已排序序列中元素比较并右移*/
        A[i] = Tmp; /* 放进合适的位置 */
    }
}

/* 归并排序 - 递归实现 */

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(ElemType A[], ElemType TmpA[], int L, int R, int RightEnd)
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1; /* 左边终点位置 */
    Tmp = L;         /* 有序序列的起始位置 */
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
        else
            TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
    }

    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
    while (R <= RightEnd)
        TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */

    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}

void Msort(ElemType A[], ElemType TmpA[], int L, int RightEnd)
{ /* 核心递归排序函数 */
    int Center;

    if (L < RightEnd) {
        Center = (L + RightEnd) / 2;
        Msort(A, TmpA, L, Center);              /* 递归解决左边 */
        Msort(A, TmpA, Center + 1, RightEnd);     /* 递归解决右边 */
        Merge(A, TmpA, L, Center + 1, RightEnd);  /* 合并两段有序序列 */
    }
}

void MergeSort(ElemType A[], int N)
{ /* 归并排序 */
    ElemType* TmpA;
    TmpA = (ElemType*)malloc(N * sizeof(ElemType));

    if (TmpA != NULL) {
        Msort(A, TmpA, 0, N - 1);
        free(TmpA);
    }
    else printf("空间不足");
}


/* 归并排序 - 循环实现 */
/* 这里Merge函数在递归版本中给出 */

/* length = 当前有序子列的长度*/


void Merge_pass(ElemType A[], ElemType TmpA[], int N, int length)
{ /* 两两归并相邻有序子列 */
    int i, j;

    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge(A, TmpA, i, i + length, i + 2 * length - 1);
    if (i + length < N) /* 归并最后2个子列*/
        Merge(A, TmpA, i, i + length, N - 1);
    else /* 最后只剩1个子列*/
        for (j = i; j < N; j++) TmpA[j] = A[j];
}

void Merge_Sort(ElemType A[], int N)
{
    int length;
    ElemType* TmpA;

    length = 1; /* 初始化子序列长度*/
    TmpA = (ElemType*)malloc(N * sizeof(ElemType));
    if (TmpA != NULL) {
        while (length < N) {
            Merge_pass(A, TmpA, N, length);
            length *= 2;
            Merge_pass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else printf("空间不足");
}







ElemType Median3(ElemType A[], int Left, int Right) {
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        std::swap(A[Left], A[Center]);
    if (A[Left] > A[Right])
        std::swap(A[Left], A[Right]);
    if (A[Center] > A[Right])
        std::swap(A[Center], A[Right]);
    /* 此时A[Left] <= A[Center] <= A[Right] */
    std::swap(A[Center], A[Right - 1]); /* 将基准Pivot藏到右边*/
    /* 只需要考虑A[Left+1] … A[Right-2] */
    return  A[Right - 1];  /* 返回基准Pivot */
}

void Quicksort(ElemType A[], int Left, int Right) {

    if (Cutoff <= Right - Left) {
        ElemType Pivot = Median3(A, Left, Right);
        int i = Left; int j = Right - 1;
        while (1) {
            while (A[++i] < Pivot);
            while (A[--j] > Pivot);
            if (i < j)
                std::swap(A[i], A[j]);
            else
                break;
        }
        std::swap(A[i], A[Right - 1]);
        Quicksort(A, Left, i - 1);
        Quicksort(A, i + 1, Right);
    }
    else
        Insert_Sort(A + Left, Right - Left + 1);
}

void Quicksort(ElemType A[], int N)
{
    Quicksort(A, 0, N - 1);
}


int ScanForMin(ElemType A[], int i, int N)
{
    int Min = A[i];
    int MinPosition = i;
    for (int j = i + 1; j < N; j++)
    {
        if (Min > A[i])
        {
            Min = A[i];
            MinPosition = i;
        }
    }
    return MinPosition;
}

void Select_Sort(ElemType A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        int MinPosition = ScanForMin(A, i, N - 1);
        std::swap(A[i], A[MinPosition]);
    }
}

void Shell_Sort(ElemType A[], int N)
{ /* 希尔排序 - 用Sedgewick增量序列 */
    int Si, D, P, i;
    ElemType Tmp;
    /* 这里只列出一小部分增量 */
    int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };

    for (Si = 0; Sedgewick[Si] >= N; Si++)
        ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
        for (P = D; P < N; P++) { /* 插入排序*/
            Tmp = A[P];
            for (i = P; i >= D && A[i - D] > Tmp; i -= D)
                A[i] = A[i - D];
            A[i] = Tmp;
        }
}