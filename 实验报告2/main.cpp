#include "Complex.h"
#include "xr.hpp"

int main()
{
	xrv(Complex a(14, 2));
	xrv(Complex b(3, 4));
	xrv(Complex c);

	xrv(c = Add(a, b)); xrv(c.Print());
	xrv(c = Sub(a, b)); xrv(c.Print());
	xrv(c = Mul(a, b)); xrv(c.Print());
	xrv(c = Div(a, b)); xrv(c.Print());
}