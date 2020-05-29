#pragma once
#include <iostream>
using namespace std;
struct Item
{
	double ceofficient;           //系数
	int exponent;                 //指数
	Item(double a=0, int b=0)
	{
		this->ceofficient = a;
		this->exponent = b;
	}
	Item operator +(const Item rhs)const
	{
		Item p;
		p.ceofficient = this->ceofficient + rhs.ceofficient;
		p.exponent = this->exponent;
		return p;
	}
	Item operator -(const Item rhs)const
	{
		Item p;
		p.ceofficient = this->ceofficient - rhs.ceofficient;
		p.exponent = this->exponent;
		return p;
	}
	Item operator *(const Item rhs)const
	{
		Item p;
		p.ceofficient = this->ceofficient * rhs.ceofficient;
		p.exponent = this->exponent + rhs.exponent;
		return p;
	}
	Item operator /(const Item rhs)const
	{
		Item p;
		p.ceofficient = this->ceofficient / rhs.ceofficient;
		p.exponent = this->exponent - rhs.exponent;
		return p;
	}
	friend ostream& operator <<(ostream& os,Item &a)
	{
		os << a.ceofficient<<"x∧" << a.exponent;
		return os;
	}
	bool operator < (const Item& rhs)
	{
		return this->exponent < rhs.exponent;
	}
	bool operator == (const Item& rhs)
	{
		return this->exponent == rhs.exponent;
	}
	Item operator -()
	{
		Item t;
		t.ceofficient = -(this->ceofficient);
		t.exponent = this->exponent;
		return t;
	}
};


