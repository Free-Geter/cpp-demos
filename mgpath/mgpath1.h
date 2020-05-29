#pragma once
#include "QuType.h"
#include "MG.h"
#include <iostream>
using namespace std;


void print(QuType* qu, int front)
{
	int k = front, j, ns = 0;
	cout << endl;
	do
	{
		j = k;
		k = qu->data[k].pre;
		qu->data[j].pre = -1;
	} while (k != 0);
	cout << "ÃÔ¹¬Â·¾¶ÈçÏÂ" << endl;
	k = 0;
	while (k < MaxSize)
	{
		if (qu->data[k].pre == -1)
		{
			ns++;
			cout << "\t" << qu->data[k].i << ',' << qu->data[k].j;
			if (ns % 5 == 0) cout << endl;
		}
		k++;
	}
	cout << endl;
}

bool mgpath(int xi, int yi, int xe, int ye)
{
	Box e;
	int i, j, di, i1, j1;
	QuType* qu;
	InitQueue(qu);
	e.i = xi, e.j = yi, e.pre = -1;
	enQueue(qu, e);
	mg[xi][yi] = -1;
	while (!QueueEmpty(qu))
	{
		deQueue(qu, e);
		i = e.i; j = e.j;
		if (i == xe && j == ye)
		{
			print(qu, qu->front);
			DestroyQueue(qu);
			return true;
		}
		for (di = 0; di < 4; di++)
		{
			switch (di)
			{
			case 0:i1 = i - 1; j1 = j; break;
			case 1:i1 = i; j1 = j + 1; break;
			case 2:i1 = i + 1; j1 = j; break;
			case 3:i1 = i; j1 = j - 1; break;
			}
			if (mg[i1][j1] == 0)
			{
				e.i = i1; e.j = j1;
				e.pre = qu->front;
				enQueue(qu, e);
				mg[i1][j1] = -1;
			}
		}
	}
	DestroyQueue(qu);
	return false;
}


