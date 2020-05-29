#pragma once
#pragma once

typedef char ElemType;
#define MaxSize 20
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef struct BTNode
{
	ElemType data;
	struct BTNode* lchild;
	struct BTNode* rchild;
};

typedef struct                 //二叉树结点队列
{
	BTNode* data[MaxSize];
	int front, rear;
}QuType;

void InitQueue(QuType*& q)              //二叉树节点队列配套函数
{
	q = (QuType*)malloc(sizeof(QuType));
	q->front = q->rear = -1;
}

void DestroyQueue(QuType*& q)
{
	free(q);
}

bool QueueEmpty(QuType* q)
{
	return (q->front == q->rear);
}

bool enQueue(QuType*& q, BTNode* e)
{
	if (q->rear == MaxSize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(QuType*& q, BTNode*& e)
{
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

void CreateBTree(BTNode*& b, char* str)       //二叉树构造
{
	BTNode* St[MaxSize], * p = (BTNode*)malloc(sizeof(BTNode));
	int top = -1, k, j = 0;
	char ch;
	b = NULL;
	ch = str[j];
	while (ch != '\0')
	{
		switch (ch)
		{
		case '(':top++; St[top] = p; k = 1; break;
		case ')':top--; break;
		case',':k = 2; break;
		default: p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL)
				b = p;
			else
			{
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}

		}
		ch = str[++j];
	}
}

void CreateBTree(BTNode*& t, int i, char a[])   //顺序存储转换为链式存储
{
	if (i > strlen(a) || a[i - 1] == '#') {
		t = NULL;
	}
	else {
		t = (BTNode*)malloc(sizeof(BTNode));
		t->data = a[i - 1];
		CreateBTree( t->lchild, 2 * i, a);
		CreateBTree (t->rchild, 2 * i + 1, a);
	}
}

char* CreateBTree(BTNode* h)    //链式存储转换为顺序存储
{
	QuType* qu4Btree;
	BTNode* temp;
	char* a = new char[MaxSize];								//new动态分配数组，否则数组会被自动释放，无法传输
	int i = 0;
	InitQueue(qu4Btree);
	enQueue(qu4Btree,h);
	while (!QueueEmpty(qu4Btree))
	{
		deQueue(qu4Btree, temp);
		a[i++] = temp->data;
		if (temp->lchild != NULL && temp->rchild == NULL)    //将二叉树补全为完全二叉树
		{
			BTNode* q = (BTNode*)malloc(sizeof(BTNode));
			q->lchild = q->rchild = NULL;
			q->data = '#';
			temp->rchild = q;
		}
		if (temp->lchild == NULL && temp->rchild != NULL)
		{
			BTNode* q = (BTNode*)malloc(sizeof(BTNode));
			q->lchild = q->rchild = NULL;
			q->data = '#';
			temp->lchild = q;
		}
		if (temp->lchild != NULL)								//层次遍历二叉树
		{
			enQueue(qu4Btree, temp->lchild);
		}
		if (temp->rchild != NULL)
		{
			enQueue(qu4Btree, temp->rchild);
		}
	}
	DestroyQueue(qu4Btree);
	a[i] = '\0';
	return a;
}


void DestoryBTree(BTNode*& b)           //二叉树析构
{
	if (b != NULL)
	{
		DestoryBTree(b->lchild);
		DestoryBTree(b->rchild);
		free(b);
	}
}

void PreOrder(BTNode* b)
{

	if (b != NULL)
	{
		std::cout << b->data;
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

void InOrder(BTNode* b)
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		std::cout << b->data;
		InOrder(b->rchild);
	}
}

void PostOrder(BTNode* b)
{
	if (b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		std::cout << b->data;
	}
}

BTNode* FindNode(BTNode* b, ElemType x)     //先序遍历寻找第一个值为x的结点
{
	BTNode* p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}

int BTHeight(BTNode* b)                   //求树高
{
	int lchildh, rchild;
	if (b == NULL)
		return 0;
	else
	{
		lchildh = BTHeight(b->lchild);
		rchild = BTHeight(b->rchild);
		return (lchildh > rchild) ? (lchildh + 1) : (rchild + 1);
	}
}

void DispBTree(BTNode* b)                  //括号表达式输出二叉树
{
	if (b != NULL)
	{
		std::cout << b->data;
		if (b->lchild != NULL || b->rchild != NULL)
		{
			std::cout << '(';
			DispBTree(b->lchild);
			if (b->rchild != NULL) std::cout << ',';
			DispBTree(b->rchild);
			std::cout << ')';
		}
	}
}

int Nodes(BTNode* b)                   //二叉树结点总数
{
	if (b == NULL)
		return 0;
	else
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

void DispLeaf(BTNode* b,char a[])                  //输出所有叶子结点
{
	int i = 0;
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
		{
			std::cout << b->data;
			a[i++] = b->data;
		}
		else
		{
			DispLeaf(b->lchild,a);
			DispLeaf(b->rchild,a);
		}
	}
}

int Level(BTNode* b, ElemType x, int h = 1)   //先序遍历查找第一个值为x的结点所在层数
{
	if (b == NULL)
		return 0;
	else
	{
		if (b->data == x)
			return h;
		else
		{
			int l = Level(b->lchild, x, h + 1);
			if (l == 0)
				return Level(b->rchild, x, h + 1);
			else
				return l;
		}
	}
}

void Lnodenum(BTNode* b, int k, int& n, int h = 1)   //第k层节点总数
{
	if (b == NULL) return;
	else
	{
		if (h == k) n++;
		else if (h < k)
		{
			Lnodenum(b->lchild, k, n, h + 1);
			Lnodenum(b->rchild, k, n, h + 1);
		}
	}
}

bool Like(BTNode* b1, BTNode* b2)        //判断两棵树是否相似
{
	bool like1, like2;
	if (b1 == NULL && b2 == NULL)
		return  true;
	else if (b1 == NULL || b2 == NULL)
		return false;
	else
	{
		like1 = Like(b1->lchild, b2->lchild);
		like2 = Like(b1->rchild, b2->rchild);
		return like1 && like2;
	}
}

bool DispAncestor(BTNode* b, ElemType x)     //输出结点的所有祖先节点
{
	if (b == NULL)
		return false;
	else if (b->lchild != NULL && b->lchild->data == x
		|| b->rchild != NULL && b->rchild->data == x)
	{
		std::cout << b->data;
		return true;
	}
	else if (DispAncestor(b->lchild, x) || DispAncestor(b->rchild, x))
	{
		std::cout << b->data;
		return true;
	}
	else return false;
}

int NodeCount(BTNode* b)
{
	if (b == NULL)
		return 0;
	else if(b->lchild == NULL && b->rchild == NULL)
	{
		return  1;
	}
	else
	{
		return NodeCount(b->lchild) + NodeCount(b->rchild) + 1;
	}
}

int LeafNodes(BTNode* b)             //求二叉树叶子节点个数
{
	int n1, n2;
	if (b == NULL)
		return 0;
	else
	{
		if (b->lchild == NULL && b->rchild == NULL)
			return 1;
		else
			return LeafNodes(b->lchild) + LeafNodes(b->rchild);
	}
}

int D1Nodes(BTNode* b)                  //度数为1的结点总数
{
	if (b == NULL)
		return 0;
	else if (b->lchild != NULL && b->rchild == NULL)
		return D1Nodes(b->lchild) + 1;
	else if (b->rchild != NULL && b->rchild == NULL)
		return D1Nodes(b->rchild) + 1;
	else
		return D1Nodes(b->lchild) + D1Nodes(b->rchild);
}

int D2Nodes(BTNode* b)               //度数为2的节点总数
{
	if (b == NULL)
		return 0;
	int n = D2Nodes(b->lchild) + D2Nodes(b->rchild);
	if (b->lchild != NULL && b->rchild != NULL)
		return n + 1;
	else
		return n;
}

int CountK(BTNode* b, ElemType k)     //值为k的结点个数
{
	if (b == NULL)
		return 0;
	else if (b->data == k)           //可以换成D2Nodes的写法
		return CountK(b->lchild, k) + CountK(b->rchild, k) + 1;
	else
		return CountK(b->lchild, k) + CountK(b->rchild, k);
}

void Min(BTNode* b, ElemType& x, BTNode*& p)    //求二叉树值最小的结点
{												//功能函数
	if (b != NULL)
	{
		if (b->data < x)
		{
			x = b->data;
			p = b;
		}
		Min(b->lchild, x, p);
		Min(b->rchild, x, p);
	}
}

BTNode* Min(BTNode* t)						//求二叉树值最小的结点
{											//接口函数
	ElemType x = t->data;
	BTNode* p = t;
	Min(t, x, p);
	return p;
}

void Copy(BTNode* b, BTNode*& t)           //辅助二叉树
{
	if (b == NULL)
		t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		t->data = b->data;
		Copy(b->lchild, t->lchild);
		Copy(b->rchild, t->rchild);
	}
}

void Swap(BTNode* b)              //交换二叉树的左右子树
{
	if (b == NULL)
		return;
	else if (b->lchild == NULL && b->rchild != NULL)
	{
		b->lchild = b->rchild;
		b->rchild = NULL;
	}
	else if (b->rchild == NULL && b->lchild != NULL)
	{
		b->rchild = b->lchild;
		b->lchild = NULL;
	}
	else
	{
		BTNode * temp;
		temp = b->lchild;
		b->lchild = b->rchild;
		b->rchild;
	}
}

//打印路径
void printer(vector<ElemType>& path) {
	vector<ElemType>::const_iterator iter = path.begin(); //打印出来
	for (; iter != path.end() - 1; ++iter)
		cout << *iter << "->";
	cout << *iter;
	cout << endl;//换行
}
//找到所有路径
void findAllPath(BTNode* pRoot, vector<ElemType>& path) {
	if (pRoot == NULL)
	{
		return;
	}
	path.push_back(pRoot->data);
	if (pRoot->lchild == NULL && pRoot->rchild == NULL) //达到了叶子节点
	{
		printer(path);//打印路径
	}
	if (pRoot->lchild != NULL)//左子树
	{
		findAllPath(pRoot->lchild, path);
	}
	if (pRoot->rchild != NULL)//右子树
	{
		findAllPath(pRoot->rchild, path);
	}
	path.pop_back();//在返回到父节点之前，在路径上删除当前节点
}


BTNode* CreateBT1(char* pre, char* in, int n)   //根据先序遍历和中序遍历构造二叉树
{
	BTNode* s;
	char* p;
	int k;
	if (n <= 0)return NULL;
	s = (BTNode*)malloc(sizeof(BTNode));
	s->data = *pre;
	for (p = in; p < in + n; p++)
		if (*p == *pre)
			break;
	k = p - in;
	s->lchild = CreateBT1(pre + 1, in, k);			//前半部分递归
	s->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1); //后半部分递归
	return s;
}

BTNode* CreateBT2(char* post, char* in,int n, int m)  //根据中序和后续遍历构造二叉树
{
	BTNode* s;
	char* p=NULL, * q=NULL, * maxp=NULL;
	int k, maxpost, maxin;
	if (n <= 0)return NULL;
	maxpost = -1;
	for (p = in; p < in + n; p++)				//求in中全部字符中，which在post中最右边的字符
		for (q = post; q < post + m; q++)	//在in中用maxp指向这个字符，用maxin标识他在in中的下标
			if (*p == *q)
			{
				k = q - post;
				if (k > maxpost)
				{
					maxpost = k;
					maxp = p;
					maxin = p - in;
				}
			}
	s = (BTNode*)malloc(sizeof(BTNode));
	s->data = post[maxpost];
	s->lchild = CreateBT2(post, in, maxin, m);
	s->rchild = CreateBT2(post, maxp + 1, n - maxin - 1, m);
	return s;
}
