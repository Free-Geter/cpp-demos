#pragma once
#include "SqStack1.h"
double compvalue(char* postexp)
{
	double a, b, c, d, e;
	SqStack1* Opnd;
	InitStack1(Opnd);
	while (*postexp != '\0')
	{
		switch (*postexp)
		{
		case'+':
		case'-':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			c = (*postexp == '+') ? (b + a) : (b - a);
			Push1(Opnd, c);
			break;
		case'*':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			c = b * a;
			Push1(Opnd, c);
			break;
		case'/':
			Pop1(Opnd, a);
			Pop1(Opnd, b);
			if (a != 0)
			{
				c = b / a;
				Push1(Opnd, c);
				break;
			}
			else {
				std::cout << "除数不能为零" << std::endl;
				exit(0);
			}
			break;
		default:
			d = 0;
			while (*postexp >= '0' && *postexp <= '9')
			{
				d = 10 * d + *postexp - '0';
				postexp++;
			}
			Push1(Opnd, d);
			break;
		}
		postexp++;
	}
	GetTop1(Opnd, e);
	DestroyStack1(Opnd);
	return e;
}