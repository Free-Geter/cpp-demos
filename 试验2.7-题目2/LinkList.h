#pragma once
#include <iostream>
#include"Item.h"
using namespace std;
template<typename ElemType>
struct LinkNode
{
	ElemType data;
	LinkNode* next;
};

template <typename ElemType>
void CreatList(LinkNode <ElemType>*& L, ElemType a[], int n)
{
	LinkNode<ElemType>* end, *q,*pre,*p;
	L = (LinkNode<ElemType>*)malloc(sizeof(LinkNode<ElemType>));
	L->next = NULL;
	end = L;
	for (int i = 0; i < n; i++)
	{
		q = (LinkNode<ElemType>*)malloc(sizeof(LinkNode<ElemType>));
		q->data = a[i];
		end->next = q;
		end = q;
	}
	end->next = NULL;
	if (L->next != NULL && L->next->next != NULL)
	{
		p = L->next->next;                   //µÝÔöÅÅÐò
		L->next->next = NULL;
		while (p != NULL)
		{
			q = p->next;
			pre = L;
			while (pre->next != NULL && pre->next->data < p->data)
				pre = pre->next;
			p->next = pre->next;
			pre->next = p;
			p = q;
		}
	}
}

template <typename ElemType>
void Display(LinkNode<ElemType>* L)
{
	LinkNode<ElemType>* p = L;
	bool flag = 0;
	while (p->next != NULL)
	{
		p = p->next;
		if (p->data.ceofficient != 0&&p->next!=NULL)
		{
			cout << p->data <<"+";
			flag = 1;
		}
		else if(p->data.ceofficient != 0 && p->next == NULL)
		{
			cout << p->data << endl;
			flag = 1;
		}
	}
	if (!flag)
	{
		cout << 0 << endl;
	}
	cout << endl;
}

template<typename ElemType>
void DestoryList(LinkNode<ElemType>*&L)
{
	LinkNode<ElemType>* pre = L, * p = L->next;
	while (p != NULL)
	{
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}