#pragma once
#include "Item.h"
#include "LinkList.h"

class Polynomial {
private:
	LinkNode<Item>* first, * last;
public:
	Polynomial(LinkNode<Item>*& L , Item a[], int n)
	{
		CreatList(L, a, n);
		LinkNode<Item>* p = L;
		while (p->next != NULL)
			p = p->next;
		first = L;
		last = p;
	}
	Polynomial(const Polynomial& rhs)
	{
		LinkNode<Item>* L, * p, * n, * q;
		L = (LinkNode<Item>*)malloc(sizeof(LinkNode<Item>));
		L->next = NULL;        n = L;
		p = rhs.first->next;
		{
			while (p != NULL)
			{
				q = (LinkNode<Item>*)malloc(sizeof(LinkNode<Item>));
				q->data = p->data;
				n->next = q;
				n = q;
				p = p->next;
			}
			n->next = NULL;
		}
		this->first = L;
		this->last = n;
	}
	Polynomial(LinkNode<Item>* L)
	{
		LinkNode<Item>* p = L;
		while (p->next != NULL)
			p = p->next;
		first = L;
		last = p;
	}
	//~Polynomial()
	//{
	//	DestoryList(this->first);
	//}
	void PolyDisplay()
	{
		Display(this->first);
	}
	Polynomial operator +(const Polynomial rhs)const
	{
		LinkNode<Item>* L, * q, * p, * temp, * n ;
		L = (LinkNode<Item>*)malloc(sizeof(LinkNode<Item>));
		L->next = NULL;
		n = L;
		q = this->first->next;
		p = rhs.first->next;
		while (p != NULL || q != NULL)
		{
			temp = (LinkNode<Item>*)malloc(sizeof(LinkNode<Item>));
			if (p != NULL && q != NULL)
			{
				if (p->data < q->data)
				{
					temp->data = p->data;
					n->next = temp;
					n = temp;
					p = p->next;
				}
				else if (p->data == q->data)
				{
					temp->data.ceofficient = p->data.ceofficient + q->data.ceofficient;
					temp->data.exponent = p->data.exponent;
					p = p->next;
					q = q->next;
					n->next = temp;
					n = temp;
				}
				else
				{
					temp->data = q->data;
					n->next = temp;
					n = temp;
					q = q->next;
				}
			}
			else if (p == NULL && q != NULL)
			{
				temp->data = q->data;
				n->next = temp;
				n = temp;
				q = q->next;
			}
			else if (p != NULL && q == NULL)
			{
				temp->data = p->data;
				n->next = temp;
				n = temp;
				p = p->next;
			}
		}
		n->next = NULL;
		Polynomial t(L);
		return t;
	}
	Polynomial operator -() const
	{
		LinkNode<Item>* p, * q, * n, * L;
		L = (LinkNode<Item>*)malloc(sizeof(LinkNode<Item>));
		L->next = NULL;     n = L;
		p = this->first;
		while (p->next != NULL)
		{
			p = p->next;
			q = (LinkNode<Item>*)malloc(sizeof(LinkNode<Item>));
			q->data = -p->data;
			n->next = q;
			n = q;
		}
		n->next = NULL;
		Polynomial t(L);
		return t;
	}
	Polynomial operator -(const Polynomial& rhs)const
	{
		Polynomial t = *this + (-rhs);
		return t;
	}

	Polynomial operator *(const Polynomial& rhs)const
	{
		LinkNode<Item>* p = this->first->next, * q = rhs.first->next, *t; 
		Polynomial copy(rhs), sum(rhs);
		while (p != NULL)
		{
			Polynomial copy(rhs);
			t = copy.first->next;
			while (t != NULL)
			{
				t->data.ceofficient = t->data.ceofficient * p->data.ceofficient;
				t->data.exponent = t->data.exponent + p->data.exponent;
				t = t->next;
			}
			p = p->next;
			sum = copy + sum;
		}
		sum = sum - copy;
		return sum;
	}
	Polynomial operator /(const Polynomial& rhs)const
	{
		LinkNode<Item>* p = this->first->next, * q = rhs.first->next, * t;
		Polynomial copy(*this), sum(*this);
		while (q != NULL)
		{
			Polynomial copy(*this);
			t = copy.first->next;
			while (t != NULL)
			{
				t->data.ceofficient = t->data.ceofficient / q->data.ceofficient;
				t->data.exponent = t->data.exponent - q->data.exponent;
				t = t->next;
			}
			q = q->next;
			sum = copy + sum;
		}
		sum = sum - copy;
		return sum;
	}

	Polynomial& operator =(const Polynomial& rhs)
	{
		Polynomial copy(rhs);
		Polynomial* q=this;
		this->first = copy.first;
		this->last = copy.last;
		//q->~Polynomial();
		return *this;
	}

	Polynomial diff(int n = 1)const
	{
		LinkNode<Item>* p = this->first->next;
		for (int i = 0; i < n; i++)
		{
			while (p != NULL)
			{
				if (p->data.exponent == 0)
				{
					p->data.ceofficient = 0;
					p = p->next;
				}
				else 
				{
					p->data.ceofficient = p->data.ceofficient * p->data.exponent;
					p->data.exponent--;
					p = p->next;
				}
			}
		}
		return *this;
	}
	Polynomial integral() const
	{
		LinkNode<Item>* p = this->first->next;
		while (p != NULL)
		{
			p->data.ceofficient = p->data.ceofficient / (p->data.exponent + 1);
			p->data.exponent++;
			p = p->next;
		}
		return *this;
	}

	double fun( LinkNode<Item>* L, double x) const               //const 函数只能调用 const函数
	{
		LinkNode<Item>* p = L, *q;
		double sum = 0;
		while (p != NULL && p->data.exponent == 0)
		{
			sum += p->data.ceofficient;
			p = p->next;
			if (p == NULL)
				return sum;
		}
		if (p != NULL&&p->next == NULL && p->data.exponent == 1)
			return x * p->data.ceofficient+sum;
			q = p;
			while (p != NULL)
			{
				p->data.exponent--;
				p = p->next;
			}
			return x * (fun(q, x)+sum);
		
	}

	double value(double x0)const
	{
		Polynomial temp(*this);
		return fun(temp.first->next, x0);                
	}

	friend double nutow_fun(Polynomial fun0,Polynomial fun1,double x)   //牛顿迭代法中设计fun0，fun1避免迭代过程中重复调用diff而导致表达式最终出错
	{
		double result = x - fun0.value(x) / fun1.value(x);
		if (abs(result - x) >= 1e-8)
			return nutow_fun(fun0, fun1, result);
		else
			return result;
	}

	double root_near(double x0)const
	{
		Polynomial fun0(*this);
		Polynomial fun1(this->diff());
		return nutow_fun(fun0, fun1, x0);
	}
};