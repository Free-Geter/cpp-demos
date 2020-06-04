
#include"Sort_Method.h"



int ScanForMin(ElemType A[], int i, int N)
{
	int Min = A[i];
	int MinPosition = i;
	for (int j = i+1; j < N; j++)
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
		Swap(A[i], A[MinPosition]);
	}
}

