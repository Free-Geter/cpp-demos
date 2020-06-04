#include "Sort_Method.h"


void Swap(ElemType &a,ElemType &b) 
{
	if (a > b)
	{
		ElemType temp;
		temp = a;
		a = b;
		b = temp;
	}
}