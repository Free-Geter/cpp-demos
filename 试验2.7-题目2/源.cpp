#include "Item.h"
#include "LinkList.h"
#include "polynomial.h"


int main()
{
	Item a[5] = { {1,1}, {6,6}, {3,3}, {4,4}, {5,5} };
	Item b[5] = { {1,1},{2,2},{3,3},{4,4},{5,5} };
	Item c[2] = { {1,1} ,{2,2} };
	LinkNode<Item>* L, * M,*Q;
	Polynomial plus(Q, c, 2),temp(plus);
	Polynomial s(L, a, 5);
	Polynomial t(M, b, 5);
	s.PolyDisplay();
	plus = plus + plus;
	plus.PolyDisplay();
	plus = temp;
	plus = plus - plus;
	plus.PolyDisplay();
	plus = temp;
	plus = plus * plus;
	plus.PolyDisplay();
	plus = temp;
	plus = plus / plus;
	plus.PolyDisplay();
	plus = temp;
	plus = plus.diff();
	plus.PolyDisplay();
	plus = plus.integral();
	plus.PolyDisplay();
	cout << plus.value(2) << endl;
	cout << plus.diff().root_near(2);
}