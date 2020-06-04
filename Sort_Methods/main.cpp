#include "Sort_Methods/Sort_Method.h"
#include <iostream>
#include <algorithm>
using namespace std;


// 定义测试时间的函数。
#include <stdlib.h>
#include <time.h>

template <class Func, typename T>
double calc_time(Func f, T R[], int n) {
	clock_t start = clock();
	f(R, n);
	clock_t finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	return duration;
}

// 按照下列方式提供三种不同序列的数据进行测试。

template <class Func, typename T>
void test_different_sequence(Func f, T R[], int n) {
	sort(R, R + n);			//Ascending
	double d1 = calc_time(f, R, n);

	reverse(R, R + n);		//Descending
	double d2 = calc_time(f, R, n);

	random_shuffle(R, R + n);	//Random
	double d3 = calc_time(f, R, n);

	cout << d1 << "\t\t" << d2 << "\t\t" << d3 << endl;
}

// 获取初始数据。

int* get_n_data(int n) {
	int* R = new int[n];

	srand((unsigned)time(NULL));
	generate_n(R, n, rand);
	return R;
}

// 用不同的数据量进行测试。

template <class Func>
void test(Func f) {
	static int m[] = { 1, 2, 5, 10, 20, 30 };
	int mn = sizeof(m) / sizeof(*m);
	int N = 1000;

	cout << "\tAscending\tDescending\tRandom" << endl;
	for (int i = 0; i < mn; ++i) {
		cout << m[i] << "\t";
		int n = N * m[i];
		int* R = get_n_data(n);
		test_different_sequence(f, R, n);
		delete[] R;
	}
}

// 在main进行测试。

int main()
{
	cout << "Insert_Sort : " << endl;
	test(Insert_Sort);
	cout << "Bubble_Sort : " << endl;
	test(Bubble_Sort);
	cout << "Select_Sort : " << endl;
	test(Select_Sort);
	cout << "Shell_Sort : " << endl;
	test(Shell_Sort);
	cout << "Merge_Sort : " << endl;
	test(Merge_Sort);
	cout << "Heap_Sort : " << endl;
	test(Heap_Sort);
	cout << "Quicksort : " << endl;
	test(Quicksort);
}