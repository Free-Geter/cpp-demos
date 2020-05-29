#pragma once
#include "SqStack4MG.h"
#include "MG.h"
#include <iostream>
using namespace std;
bool mgpath(int xi, int yi, int xe, int ye)
{
	Box path[MaxSize], e;
	int i, j, di, i1, j1, k;
	bool find;
	StType* st;
	InitStack(st);
	e.i = xi; e.j = yi; e.direction = -1;
	Push(st, e);
	mg[xi][yi] = -1;
	while (!StackEmpty(st))
	{
		GetTop(st, e);
		i = e.i; j = e.j; di = e.direction;
		if (i == xe && j == ye)
		{
			cout << "ÃÔ¹¬Â·¾¶ÈçÏÂ£º" << endl;
			k = 0;
			while (!StackEmpty(st))
			{
				Pop(st, e);
				path[k++] = e;
			}
			int n = 0;
			while (k >= 1)
			{
				k--; n++;
				cout << "\t" << path[k].i << ',' << path[k].j;
				if (n % 5 == 0) cout << endl;
			}
			cout << endl;
			DestroyStack(st);
			return true;
		}
		find = false;
		while (di < 4 && !find)
		{
			di++;
			switch (di)
			{
			case 0:i1 = i - 1; j1 = j; break;
			case 1:i1 = i; j1 = j + 1; break;
			case 2:i1 = i + 1; j1 = j; break;
			case 3:i1 = i; j1 = j - 1; break;
			}
			if (mg[i1][j1] == 0)find = true;
		}
		if (find)
		{
			st->data[st->top].direction = di;
			e.i = i1; e.j = j1; e.direction = -1;
			Push(st, e);
			mg[i1][j1] = -1;
		}
		else
		{
			Pop(st, e);
			mg[e.i][e.j] = 0;
		}
	}
	DestroyStack(st);
	return false;
}