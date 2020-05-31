#pragma once
#pragma once
#define Cutoff 2
typedef int ElemType;

#include "Insert_Sort.h"

void Swap(ElemType &a, ElemType &b) {
    ElemType temp;
    temp = a;
    a = b;
    b = temp;
}

ElemType Median3(ElemType A[], int Left, int Right) {
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(A[Left], A[Center]);
    if (A[Left] > A[Right])
        Swap(A[Left], A[Right]);
    if (A[Center] > A[Right])
        Swap(A[Center], A[Right]);
    /* 此时A[Left] <= A[Center] <= A[Right] */
    Swap(A[Center], A[Right - 1]); /* 将基准Pivot藏到右边*/
    /* 只需要考虑A[Left+1] … A[Right-2] */
    return  A[Right - 1];  /* 返回基准Pivot */
}

void Quicksort(ElemType A[], int Left, int Right) {
    if (Cutoff <= Right - Left) {
        ElemType Pivot = Median3(A, Left, Right);
        int i = Left; int j = Right - 1;
        while (1) {
            while (A[++i] < Pivot) {}
            while (A[--j] > Pivot) {}
            if (i < j)
                Swap(A[i], A[j]);
            else
                break;
        }
        Swap(A[i], A[Right - 1]);
        Quicksort(A, Left, i - 1);
        Quicksort(A, i + 1, Right);
    }
    else
        insert_sort(A, Right - Left);
}