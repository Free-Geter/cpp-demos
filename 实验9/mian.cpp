#include "Sort_Tree.h"

int main()
{
	int A[10] = { 1,2,3,4,5,6,7,8,9,10 };
	char M[] = "ABCDEFGHIJ";

	BSTNode* h, * q;
	h = CreatSBT(A, M,10);
	Display(h);
	q = SearchBST(h, 5);
	cout << "The result is number " << q->key << " : " << q->data << endl;
	DeleteNode(h, 5);
	cout << "The Tree After Delete is : " << endl;
	Display(h);
}