#include <iostream>
#include <cmath>
#include "xr.hpp"

using namespace std;

class Point {
private:
	double x, y;
public:
	Point(double a=0, double b=0) :x(a), y(b)
	{}
	Point(const Point& p) {
		if (this != &p)
		{
			x = p.x;
			y = p.y;
		}
	}
	Point& operator = (const Point& rhs) {
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}
	double Length(const Point& p)const
	{
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}

	double GetX() const { return x; }
	double GetY() const { return y; }
};

class Rectangle {
private:
	Point bottomleft;
	Point upRight;
public:
	Rectangle(const Point& a, const Point& b):
		bottomleft(a),upRight(b)
	{}
	double Area()const
	{
		Point bottomRight(upRight.GetX(), bottomleft.GetY());
		double height = bottomRight.Length(upRight);
		double width = bottomRight.Length(bottomleft);
		return height * width;
	}
	Point CenterPoint() const
	{
		double x = (bottomleft.GetX() + upRight.GetX()) / 2;
		double y = (bottomleft.GetY() + upRight.GetY()) / 2;
		return Point(x, y);
	}
	double GetLX() const { return bottomleft.GetX(); }
	double GetBY() const { return bottomleft.GetY(); }
	double GetRX() const { return upRight.GetX(); }
	double GetUY() const { return upRight.GetY(); }
};

enum Rel {PtOnRect,PtInRect,PtOutRect};

Rel position(const Point& p, const Rectangle r)
{
	if (r.GetLX() < p.GetX() && p.GetX() < r.GetRX() && r.GetBY() < p.GetY() && p.GetY() < r.GetUY())
		return PtInRect;
	else if (r.GetLX() < p.GetX() && p.GetX() < r.GetRX() && (p.GetY() == r.GetBY() || p.GetY() == r.GetUY()) ||
		r.GetBY() < p.GetY() && p.GetY() < r.GetUY() && (p.GetX() == r.GetLX() || p.GetX() == r.GetRX()))
		return PtOnRect;
	else
		return PtOutRect;
}

int main()
{
	Point A(0, 0);
	Point B(5, 5);
	Point po[3];
	po[0] = Point(1, 1);
	po[1] = Point(2, 3);
	po[2] = Point(6, 6);
	Rectangle r(A, B);
	cout << "The area of the rectangle is : " << r.Area() << endl;
	Point s = r.CenterPoint();
	cout << "The CenterPoint of the rectangle is : (" << s.GetX() << ',' << s.GetY() << ')' << endl;
	for(int n=0;n<=2;n++)
	{
		Point p = po[n];
		string str;
		if (position(p, r) == 0)
			str = "PtOnRect";
		else if (position(p, r) == 1)
			str = "PtInRect";
		else
			str = "PtOutRect";
		cout << "The point (" << p.GetX() << ',' << p.GetY() << ')' << "is " << str << endl;
	}
	
	return 0;
}