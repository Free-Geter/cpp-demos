
#include "Sort_Method.h"


void Bubble_Sort(ElemType A[], int N)
{
	for (int P = N - 1; P >= 0; P--)
	{
		int flag = 0;
		for (int i = 0; i < P; i++)
		{
			if (A[i] > A[i + 1])
			{
				Swap(A[i], A[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0)break;
	}
}