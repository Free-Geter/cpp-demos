#include <iostream>
#include <cassert>
#include <cmath>
#include "Rational.h"

int Rational::digits(double d)
{
	char buffer[64];
	sprintf_s(buffer, "%g", d);
	int n = strlen(buffer);
	int i = 0;
	while (buffer[i] != '\0' && buffer[i] != '.')
		++i;
	if (i == n)
		return 0;
	return n - i - 1;
}

int Rational::gcd(int a, int b)
{
	int r;
	while (b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

Rational Rational::normalize()
{
	int n = gcd(this->numerator, this->denominator);
	assert(n != 0);
	this->numerator /= n;
	this->denominator /= n;
	if (this->denominator < 0)
	{
		this->numerator *= -1;
		this->denominator *= -1;
	}
	return *this;
}

Rational::Rational(int a, int b)
{
	this->numerator = a;
	this->denominator = (b == 0 ? 1 : b);
}

Rational::Rational(double d)
{
	int n = Rational::digits(d);
	double e = pow(10.0, n);

	this->numerator = int(d * e);
	this->denominator = int(e);
	this->normalize();
}

Rational::Rational(const Rational& rhs)
{
	this->numerator = rhs.numerator;
	this->denominator = rhs.denominator;
}

Rational& Rational::operator= (const Rational& rhs)
{
	this->numerator = rhs.numerator;
	this->denominator = rhs.denominator;
	return *this;
}

Rational Rational::operator+ (const Rational& rhs) const
{
	Rational r;
	r.numerator = this->numerator * rhs.denominator + this->denominator * rhs.numerator;
	r.denominator = this->denominator * rhs.denominator;
	return r.normalize();
}

Rational Rational::operator-(const Rational& rhs) const
{
	return *this + rhs.operator-();
}

Rational Rational::operator*(const Rational& rhs) const
{
	Rational r;
	r.numerator = this->numerator * rhs.numerator;
	r.denominator = this->denominator * rhs.denominator;
	return r.normalize();
}

Rational Rational::reverse() const
{
	Rational r;
	r.denominator = this->numerator;
	r.numerator = this->denominator;
	return r.normalize();
}

Rational Rational::operator/(const Rational& rhs) const
{
	assert(rhs.numerator != 0);
	return *this * rhs.reverse();
}

Rational& Rational::operator += (const Rational& rhs)
{
	return *this = *this + rhs;
}

Rational& Rational::operator -= (const Rational& rhs)
{
	return *this = *this - rhs;
}

Rational& Rational::operator *= (const Rational& rhs)
{
	return *this = *this * rhs;
}

Rational& Rational::operator /= (const Rational& rhs)
{
	return *this = *this / rhs;
}

Rational operator +(int n, const Rational& rhs)
{
	Rational temp;
	temp.numerator += rhs.numerator + rhs.denominator * n;
	temp.denominator = rhs.denominator;
	return temp.normalize();
}

Rational operator -(int n, const Rational& rhs)
{
	Rational temp;
	temp = n + (-rhs);
	return temp.normalize();
}

Rational operator *(int n, const Rational& rhs)
{
	Rational temp;
	temp.numerator = rhs.numerator * n;
	temp.denominator = rhs.denominator;
	return temp.normalize();
}

Rational operator /(int n, const Rational& rhs)
{
	assert(n != 0);
	Rational temp;
	temp.numerator = rhs.denominator * n;
	return temp.normalize();
}

int& operator += (int& n, const Rational& rhs)
{
	int s;
	return  s = n + int(rhs.numerator / rhs.denominator);
}

int& operator -= (int& n, const Rational& rhs)
{
	int s;
	return  s = n - int(rhs.numerator / rhs.denominator);
}

int& operator *= (int& n, const Rational& rhs)
{
	int s;
	return  s = n * int(rhs.numerator / rhs.denominator);
}

int& operator /= (int& n, const Rational& rhs)
{
	int s;
	return  s = int(n * rhs.denominator / rhs.numerator);
}

Rational operator + (double d, const Rational& rhs)
{
	Rational r(d);
	return r + rhs;
}

Rational operator - (double d, const Rational& rhs)
{
	Rational r(d);
	return r - rhs;
}

Rational operator * (double d, const Rational& rhs)
{
	Rational r(d);
	return r * rhs;
}

Rational operator / (double d, const Rational& rhs)
{
	Rational r(d);
	return r / rhs;
}

double& operator += (double& d, const Rational& rhs)
{
	return d += double(rhs.numerator) / rhs.denominator;
}

double& operator -= (double& d, const Rational& rhs)
{
	return d -= double(rhs.numerator) / rhs.denominator;
}

double& operator *= (double& d, const Rational& rhs)
{
	return d *= double(rhs.numerator) / rhs.denominator;
}

double& operator /= (double& d, const Rational& rhs)
{
	return d /= double(rhs.numerator) / rhs.denominator;
}

bool Rational::operator >(const Rational& rhs)const
{
	if (this->numerator * rhs.denominator > rhs.numerator* this->denominator)
		return true;
	else
		return false;
}

bool Rational::operator ==(const Rational& rhs)const
{
	if (this->numerator * rhs.denominator == rhs.numerator* this->denominator)
		return true;
	else
		return false;
}

bool Rational::operator <(const Rational& rhs)const
{
	if (*this > rhs || *this == rhs)
		return false;
	else
		return true;
}

bool Rational::operator >=(const Rational& rhs)const
{
	if (*this > rhs || *this == rhs)
		return true;
	else
		return false;
}

bool Rational::operator <=(const Rational& rhs)const
{
	if (*this < rhs || *this == rhs)
		return true;
	else
		return false;
}

bool Rational::operator !=(const Rational& rhs)const
{
	if (*this == rhs)
		return false;
	else
		return true;
}

bool operator >(int n, const Rational& rhs)
{
	if (n * rhs.denominator > rhs.numerator)
		return true;
	else
		return false;
}

bool operator ==(int n, const Rational& rhs)
{
	if (n * rhs.denominator == rhs.numerator)
		return true;
	else
		return false;
}

bool operator <(int n, const Rational& rhs)
{
	if (n>rhs||n==rhs)
		return false;
	else
		return true;
}

bool operator >=(int n, const Rational& rhs)
{
	if (n > rhs || n == rhs)
		return true;
	else
		return false;
}

bool operator <=(int n, const Rational& rhs)
{
	if (n < rhs || n == rhs)
		return true;
	else
		return false;
}

bool operator !=(int n, const Rational& rhs)
{
	if (n == rhs)
		return false;
	else
		return true;
}

bool operator > (double n, const Rational& rhs)
{
	if (n * rhs.denominator > rhs.numerator)
		return true;
	else
		return false;
}

bool operator == (double n, const Rational& rhs)
{
	if (n * rhs.denominator == rhs.numerator)
		return true;
	else
		return false;
}

bool operator < (double n, const Rational& rhs)
{
	if (n > rhs || n == rhs)
		return false;
	else
		return true;
}

bool operator >= (double n, const Rational& rhs)
{
	if (n > rhs || n == rhs)
		return true;
	else
		return false;
}

bool operator <= (double n, const Rational& rhs)
{
	if (n < rhs || n == rhs)
		return true;
	else
		return false;
}

bool operator != (double n, const Rational& rhs)
{
	if (n == rhs)
		return false;
	else
		return true;
}

Rational Rational::operator - () const
{
	Rational t;
	t.numerator = -this->numerator;
	t.denominator = this->denominator;
	return t;
}

Rational& Rational::operator ++ ()
{
	return *this = 1 + *this;
}

Rational Rational::operator ++ (int)
{
	return *this = 1 + *this;
}

Rational& Rational::operator -- ()
{
	return *this = 1 - *this;
}

Rational Rational::operator -- (int)
{
	return *this = 1 - *this;
}

Rational::operator int() const
{
	return int(this->numerator / this->denominator);
}

Rational::operator double() const
{
	return double(this->numerator / this->denominator);
}

std::ostream& operator << (std::ostream& os, const Rational& rhs)
{
	os << rhs.numerator << "/" << rhs.denominator;
	return os;
}

std::istream& operator >> (std::istream& is,  Rational& rhs)
{
	char dump;
	is >> rhs.numerator >> dump >> rhs.denominator;
	return is;
}

