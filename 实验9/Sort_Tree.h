#pragma once


#include <iostream>
using namespace std;

typedef int KeyType;
typedef char InfoType;

typedef struct node
{
	KeyType key;
	InfoType data;
	node* lchild, * rchild;
}BSTNode;

void Display(BSTNode* bt)
{
	if (bt == NULL)
		return;
	else
	{
		cout << "number " << bt->key << " : " << bt->data << endl;
		Display(bt->lchild);
		Display(bt->rchild);
	}
}

bool InsertBST(BSTNode*& bt,InfoType m, KeyType k)
{
	if (bt == NULL)
	{
		bt = (BSTNode*)malloc(sizeof(BSTNode));
		bt->key = k; bt->data = m; bt->lchild = bt->rchild = NULL;
		return true;
	}
	else if (k == bt->key)
		return false;
	else if (k < bt->key)
		return InsertBST(bt->lchild, m, k);
	else
		return InsertBST(bt->rchild, m, k);
}

BSTNode* CreatSBT(KeyType A[], InfoType M[], int n)
{
	BSTNode* bt = NULL;
	int i = 0;
	while (i < n-1)
	{
		InsertBST(bt, M[i],A[i]);
		i++;
	}
	return bt;
}

BSTNode* SearchBST(BSTNode* bt, KeyType k)
{
	if (bt == NULL || bt->key == k)
		return bt;
	if (k < bt->key)
		return SearchBST(bt->lchild, k);
	else
		return SearchBST(bt->rchild, k);
}

KeyType maxnode(BSTNode* p)
{
	while (p->rchild != NULL)
		p = p->rchild;
	return p->data;
}

KeyType minnode(BSTNode* p)
{
	while (p->lchild != NULL)
		p = p->lchild;
	return p->data;
}


void MaxMinNode(BSTNode* p)
{
	if (p != NULL)
	{
		if (p->lchild != NULL)
			cout << "左子树最大结点为 : " << maxnode(p->lchild) << endl;
		if (p->rchild != NULL)
			cout << "右子树最大结点为 : " << minnode(p->rchild) << endl;
	}
}

void DeleteSp(BSTNode* p, BSTNode*& r)
{
	BSTNode* q;
	if (r->rchild != NULL)
		DeleteSp(p, r->rchild);
	else
	{
		p->key = r->key;
		p->data = r->data;
		q = r;
		r = r->lchild;
		free(q);
	}
}

void Delete(BSTNode*& p)
{
	BSTNode* q;
	if (p->rchild == NULL)
	{
		q = p;
		p = p->lchild;
		free(q);
	}
	else if (p->lchild == NULL)
	{
		q = p;
		p = p->rchild;
		free(q);
	}
	else DeleteSp(p, p->lchild);
}


bool DeleteNode(BSTNode*& bt, KeyType k)
{
	if (bt == NULL)
		return false;
	else 
	{
		if (k < bt->key)
			return DeleteNode(bt->lchild, k);
		else if (k > bt->key)
			return DeleteNode(bt->rchild, k);
		else
		{
			Delete(bt);
			return true;
		}
	}
}

