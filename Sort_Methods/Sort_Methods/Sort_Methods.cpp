#include <iostream>
#include "QuickSort.h"
#include "Heap_Sort.h"
using namespace std;

int main()
{
	int info[] = { 1,2,5,7,6,9,4,3,0 };
	int Sinfo[] = { 1,2,5,7,6,9,4,3,0 };
	Quicksort(info,0,8);
	for (int i = 0; i < 9; i++)
		cout << info[i];
	cout << endl;
	Heap_Sort(Sinfo, 9);
	for (int i = 0; i < 9; i++)
		cout << Sinfo[i];
	cout << endl;
}
