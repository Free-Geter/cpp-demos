#pragma once
#include <iostream>

class Rational
{
private:
	int numerator, denominator;
	static int digits(double d);
	static int gcd(int a = 0, int b = 1);
	Rational normalize();
public:
	Rational(int n = 0, int d = 1);
	Rational(double d);
	Rational(const Rational& r);
	//Rational and Rational
	Rational& operator = (const Rational& rhs);
	Rational operator + (const Rational& rhs) const;
	Rational operator - (const Rational& rhs) const;
	Rational operator * (const Rational& rhs) const;
	Rational operator / (const Rational& rhs) const;

	Rational& operator +=(const Rational& rhs);
	Rational& operator -=(const Rational& rhs);
	Rational& operator *=(const Rational& rhs);
	Rational& operator /=(const Rational& rhs);
	//int and Rational
	friend Rational operator +(int n, const Rational& rhs);
	friend Rational operator -(int n, const Rational& rhs);
	friend Rational operator *(int n, const Rational& rhs);
	friend Rational operator /(int n, const Rational& rhs);

	friend int& operator += (int& n, const Rational& rhs);
	friend int& operator -= (int& n, const Rational& rhs);
	friend int& operator *= (int& n, const Rational& rhs);
	friend int& operator /= (int& n, const Rational& rhs);
	//double and Rational
	friend Rational operator + (double d, const Rational& rhs);
	friend Rational operator - (double d, const Rational& rhs);
	friend Rational operator * (double d, const Rational& rhs);
	friend Rational operator / (double d, const Rational& rhs);

	friend double& operator += (double& d, const Rational& rhs);
	friend double& operator -= (double& d, const Rational& rhs);
	friend double& operator *= (double& d, const Rational& rhs);
	friend double& operator /= (double& d, const Rational& rhs);
	//Rational > Rational
	bool operator >(const Rational& rhs)const;
	bool operator == (const Rational& rhs) const;
	bool operator >= (const Rational& rhs) const;
	bool operator < (const Rational& rhs) const;
	bool operator <= (const Rational& rhs) const;
	bool operator != (const Rational& rhs) const;
	//int > Rational 
	friend bool operator >(int n, const Rational& rhs);
	friend bool operator >=(int n, const Rational& rhs);
	friend bool operator <(int n, const Rational& rhs);
	friend bool operator <=(int n, const Rational& rhs);
	friend bool operator ==(int n, const Rational& rhs);
	friend bool operator !=(int n, const Rational& rhs);
	//double > Rational
	friend bool operator > (double n, const Rational& rhs);
	friend bool operator >= (double n, const Rational& rhs);
	friend bool operator < (double n, const Rational& rhs);
	friend bool operator <= (double n, const Rational& rhs);
	friend bool operator == (double n, const Rational& rhs);
	friend bool operator != (double n, const Rational& rhs);
	//求相反数	Rational operator + () const;
	Rational operator - () const;
	//倒数
	Rational reverse() const;
	//++  --
	Rational& operator ++ ();
	Rational operator ++ (int);
	Rational& operator -- ();
	Rational operator -- (int);
	//transformer
	operator int() const;
	operator double() const;
	//<<  >>
	friend std::ostream& operator << (std::ostream& os, const Rational& rhs);
	friend std::istream& operator >> (std::istream& is,  Rational& rhs);
};