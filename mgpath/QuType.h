#pragma 
#define MaxSize 100
#include <iostream>

typedef struct
{
	int i, j;
	int pre;
}Box;
typedef struct
{
	Box data[MaxSize];
	int front, rear;
}QuType;

void InitQueue(QuType*& q)
{
	q = (QuType*)malloc(sizeof(QuType));
	q->front = q->rear = -1;
}

void DestroyQueue(QuType*& q)
{
	free(q);
}

bool QueueEmpty(QuType* q)
{
	return (q->front == q->rear);
}

bool enQueue(QuType*& q, Box e)
{
	if (q->rear == MaxSize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(QuType*& q,Box& e)
{
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}