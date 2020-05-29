#include <cmath>
#include "xr.hpp"

class Point {
private:
	double x, y;
public:
	Point(double a, double b) :x(a), y(b) {}
	Point(const Point& p) {
		if (this != &p) {
			x = p.x;
			y = p.y;
		}
	}
	Point& operator = (const Point& rhs)
	{
		if (this != &rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}
	double GetX() const { return x; }
	double GetY() const { return y; }
};

class Line {
private:
	Point start, end;
public:
	Line(double a, double b, double c, double d)
		:start(a, b), end(c, d)
	{}
	Line(const Point& a, const Point& b)
		:start(a), end(b)
	{}
	Line(const Line& l)
		:start(l.start), end(l.end)
	{}
	Line& operator = (const Line& rhs) {
		if (this != &rhs) {
			start = rhs.start;
			end = rhs.end;
		}
		return *this;
	}
	double Length() const {
		double dx = start.GetX() - end.GetX();
		double dy = start.GetY() - end.GetY();
		return sqrt(dx * dx + dy * dy);
	}
	Point MidPoint() const {
		double x = (start.GetX() + end.GetX()) / 2;
		double y = (start.GetY() + end.GetY()) / 2;
		return Point(x, y);
	}
};

int main()
{
	Point a(1, 2), b(1, 4);
	Line la(a, b);
	Line lb(0, 1, 0, 5), lc(lb);

	xr(la.Length());
	xr(lb.Length());
	xr(lc.Length());

	lc = Line(la.MidPoint(), lb.MidPoint());
	xr(lc.Length());
}