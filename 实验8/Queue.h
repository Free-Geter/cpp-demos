#pragma once

#define MaxSize 100
typedef int ElemType;


typedef struct
{
	ElemType data[MaxSize];
	int front, rear;
}QuType;

typedef struct
{
	int data;
	int parent;
}QUERE;

template <typename Qu>
void InitQueue(Qu*& q)
{
	q = (Qu*)malloc(sizeof(Qu));
	q->front = q->rear = -1;
}

template <typename Qu>
void DestroyQueue(Qu*& q)
{
	free(q);
}

template <typename Qu>
bool QueueEmpty(Qu* q)
{
	return (q->front == q->rear);
}

template <typename Qu,typename T>
bool enQueue(Qu*& q, T e)
{
	if (q->rear == MaxSize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

template <typename Qu,typename T>
bool deQueue(Qu*& q, T& e)
{
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}