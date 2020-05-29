#include "dependences.h"
#include <string>
#include <iostream>

using namespace std;
int main()
{
	char str[] = "A(B(E,F),C(G(J)),D(H,I(K,L,M)))";
	char pre[]="ABEFDHIKM",in[]="EBFAHDKIM",post[]="EFBHKMIDA";
	BTNode* h = NULL;
	BTNode* temp = NULL;
	//构建一棵二叉树，以某种形式（括号表示法、树形表示法、凹入表示法等）输出二叉树，最后释放二叉树的存储内存。
	CreateBTree(h,str);
	DispBTree(h);
	cout << endl;

	//分别编写程序实现：将二叉树的顺序存储结构转换成链式存储结构；将二叉树的链式存储结构转换为顺序存储结构。
	char a[] = "01234#567";
	CreateBTree(temp, 1, a);
	DispBTree(temp);
	char *b = CreateBTree(temp);
	cout << endl;
	while (*b != '\0') {
		cout << *(b++);
	}cout << endl;

	//实现二叉树的先序、中序、后序和层次序遍历算法。输出二叉树的叶子节点。
	PreOrder(h);
	cout << endl;
	InOrder(h);
	cout << endl;
	PostOrder(h);
	cout << endl;
	DispLeaf(h,a);
	cout << endl;

	//分别计算二叉树的所有节点个数，度为0、1、2的节点个数。
	cout <<"度数为2结点数 : "<< D2Nodes(h) << endl;
	cout << "度数为1结点数 : " << D1Nodes(h) << endl;
	cout << "度数为0结点数 : " << LeafNodes(h) << endl;

	//统计二叉树中值为k的节点个数。计算二叉树中节点最小的值。
	cout << "二叉树中，置为'A'的结点个数为 : " << CountK(h, 'A') << endl;
	cout << "二叉树中最小值" << Min(h)->data << endl;

	//计算二叉树的高度。计算二叉树中节点的层数。
	cout << "二叉树高度为" << BTHeight(h) << endl;
	cout << "二叉树中'D'结点所在层数 : " << Level(h, 'D') << endl;

	//实现两棵二叉树的复制。交换二叉树的左右子树。判断两棵二叉树是否相似。
	BTNode* t;
	Copy(h, t);
	Swap(t);
	cout << "Is two tree liked? result:  " << boolalpha << Like(h, t) << endl;

	//输出二叉树中根节点到每个叶子节点的路径。
	vector<ElemType> path;
	findAllPath(h, path);

	//分别编写程序实现：给定二叉树的中序遍历序列和先序遍历序列，构造该二叉树；给定二叉树的中序遍历序列和后序遍历序列，构造该二叉树。
	DispBTree(CreateBT1(pre, in, NodeCount(h)));
	cout << endl;
	DispBTree(CreateBT2(post, in, NodeCount(h),NodeCount(h)));
}