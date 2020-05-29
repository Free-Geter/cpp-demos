#pragma once
#pragma once
#include <iostream>
#define MaxSize 100


typedef struct
{
	int i;
	int j;
	int direction;
}Box;

typedef struct
{
	Box data[MaxSize];
	int top;
}StType;


void InitStack(StType*& s)
{
	s = (StType*)malloc(sizeof(StType));
	s->top = -1;
}

void DestroyStack(StType*& s)
{
	free(s);
}

bool StackEmpty(StType* s)
{
	return (s->top == -1);
}

bool Push(StType*& s, Box e)
{
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(StType*& s, Box& e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(StType* s, Box& e)
{
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}