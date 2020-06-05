
#include <iostream>
#include <iomanip>

#include "GraphType.h"
#include "Graph_Methods.h"
#include "Queue.h"

using namespace std;

int visited[MAXV] = { 0 };

//根据邻接矩阵数组，顶点个数和边数创建邻接表
void CreatAdj(AdjGraph*& G, int A[MAXV][MAXV], int n, int e)
{
	int i, j;
	ArcNode* p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));

	//初始化邻接表所有头结点
	for (i = 0; i < n; i++)
	{
		G->adjlist[i].firstarc = NULL;
	}

	// 检查邻接矩阵中的每个元素
	for (i = 0; i < n; i++)
		for (j = n - 1; j >= 0; j--)
			if (A[i][j] != 0 && A[i][j] != INF)			//存在一条边
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));

				//根据临界矩阵信息创建一个边结点
				p->adjvex = j;
				p->weight = A[i][j];

				//使用头插法插入边结点
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
	G->n = n;
	G->e = e;
}

void DispAdj(AdjGraph* G)
{
	ArcNode* p;

	//扫描单链表头结点数组
	for (int i = 0; i < G->n; i++)
	{
		p = G->adjlist[i].firstarc;
		cout << setw(3) << i<<setw(3)<<':';
		while (p != NULL)
		{
			cout << setw(3) << p->adjvex << "[" << setw(3) << p->weight << "]->";
			p = p->nextarc;
		}
		cout << " END" << endl;
	}
}

void DestoryAdj(AdjGraph*& G)
{
	ArcNode* pre, * p;
	for (int i = 0; i < G->n; i++)
	{
		pre = G->adjlist[i].firstarc;
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)
			{
				free(pre);
				pre = p;
				p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);
}


void MatToList(MatGraph g, AdjGraph*& G)
{
	ArcNode* p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (int i = 0; i < g.n; i++)
		G->adjlist[i].firstarc = NULL;
	for (int i = 0; i < g.n; i++)
		for (int j = g.n - 1; j >= 0; j--)
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->weight = g.edges[i][j];
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
	G->n = g.n;
	G->e = g.e;
}

void ListToMat(AdjGraph* G, MatGraph& g)
{
	ArcNode* p;
	for (int i = 0; i < G->n; i++)
	{
		p = G->adjlist[i].firstarc;
		while (p != NULL)
		{
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	g.n = G->n;
	g.e = G->e;
}


void DFS(AdjGraph* G, int v)
{
	ArcNode* p;
	visited[v] = 1;
	cout << setw(3) << v;
	p = G->adjlist[v].firstarc;
	while (p != NULL)
	{
		if (visited[p->adjvex] == 0)
			DFS(G, p->adjvex);
		p = p->nextarc;
	}
}


void BFS(AdjGraph* G, int v)
{
	int w;
	ArcNode* p;
	QuType* qu;
	InitQueue(qu);
	for (int i = 0; i < G->n; i++)
		visited[i] = 0;
	cout << setw(3) << v;
	visited[v] = 1;
	enQueue(qu, v);
	while (!QueueEmpty(qu))
	{
		deQueue(qu, w);
		p = G->adjlist[w].firstarc;
		// 遍历w的所有邻接点
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0)
			{
				cout << setw(3) << p->adjvex;
				visited[p->adjvex] = 1;
				enQueue(qu, p->adjvex);
			}
			p = p->nextarc;
		}
	}
	cout << endl;
}


bool Connect(AdjGraph* G)
{
	bool flag = true;
	for (int i = 0; i < G->n; i++)
		visited[i] = 0;
	DFS(G, 0);
	for(int i=0;i<G->n;i++)
		if (visited[i] == 0)				//如果有顶点未被深度优先遍历到，
		{									//就不连通
			flag = false;
			break;
		}
	return flag;
}


// has表示u到v是否有路径，初始值设为false,使用前保证visited初始化
void ExistPath(AdjGraph* G, int u, int v, bool& has)
{
	int w;
	ArcNode* p;
	visited[u] = 1;						//设置已访问标记
	if (u == v)
	{
		has = true;
		return;
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL)
	{
		w = p->adjvex;
		if (visited[w] == 0)
			ExistPath(G, w, v, has);
		p = p->nextarc;
	}
}

// d表示path的长度，初始值设为-1,使用前保证visited初始化
void FindPath(AdjGraph* G, int u, int v, int path[], int d)
{
	int w;
	ArcNode* p;
	visited[u] = 1;
	d++;	path[d] = u;			//路径长度加1，并将走过的路径放入数组
	if (u == v)
	{
		for (int i = 0; i <= d; i++)
			cout << setw(3) << path[i];
		cout << endl;
		return;
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL)
	{
		w = p->adjvex;
		if (visited[w] == 0)
			FindPath(G, w, v, path, d);
		p = p->nextarc;
	}
}


// d表示path的长度，初始值设为-1,使用前保证visited初始化
void FindAllPath(AdjGraph* G, int u, int v, int path[], int d)
{
	int w;
	ArcNode* p;
	d++;	path[d] = u;
	visited[u] = 1;
	if (u == v && d >= 0)
	{
		for (int i = 0; i <= d; i++)
			cout << setw(3) << path[i];
		cout << endl;
	}
	p = G->adjlist[u].firstarc;
	while (p!= NULL)
	{
		w = p->adjvex;
		if (visited[w] == 0)
			FindAllPath(G, w, v, path, d);
		p = p->nextarc;
	}
	visited[u] = 0;
}


//d表示path中的路径长度，初始值为-1
void PathlenAll(AdjGraph* G, int u, int v,int l ,int path[], int d)
{
	int w;
	ArcNode* p;
	visited[u] = 1;
	d++;	path[d] = u;
	if (u == v && d == l)
	{
		cout << " ";
		for (int i = 0; i <= d; i++)
			cout << path[i];
		cout << endl;
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL)
	{
		w = p->adjvex;
		if (visited[w] == 0)
			PathlenAll(G, w, v, l, path, d);
		p = p->nextarc;
	}
	visited[u] = 0;
}


//d表示path中的路径长度，初始为-1
void DFSPath(AdjGraph* G, int u, int v, int path[], int d)
{
	int w;
	ArcNode* p;
	visited[u] = 1;
	d++;	path[d] = u;
	p = G->adjlist[u].firstarc;
	while (p!= NULL)
	{
		w = p->adjvex;
		if (w == v && d > 0)
		{
			cout << " ";
			for (int i = 0; i <= d; i++)
				cout << path[i];
			cout << v << endl;
		}
		if (visited[w] == 0)
			DFSPath(G, w, v, path, d);
		p = p->nextarc;
	}
	visited[u] = 0;
}

void FindCyclePath(AdjGraph* G, int k)
{
	int path[MAXV];
	DFSPath(G, k, k, path, -1);
}


//逆向输出从顶点u到顶点v的最短路径
void ShortPath(AdjGraph* G, int u, int v)
{
	int w,i;
	ArcNode* p;
	QUERE qu[MAXV];
	int front = -1, rear = -1;
	for (i = 0; i < G->n; i++)
		visited[i] = 0;
	rear++;
	qu[rear].data = u;
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear)
	{
		front++;
		w = qu[front].data;
		if (w == v)
		{						//通过队列输出逆路径
			i = front;
			while (qu[i].parent != -1)
			{
				cout << setw(3) << qu[i].data;
				i = qu[i].parent;
			}
			cout << setw(3) << qu[i].data;
			break;
		}
		p = G->adjlist[w].firstarc;
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0)
			{
				visited[p->adjvex] = 1;
				rear++;
				qu[rear].data = p->adjvex;
				qu[rear].parent = front;
			}
			p = p->nextarc;
		}
	}
}

int MaxDist(AdjGraph* G, int v)
{
	ArcNode* p;
	int k;
	int Qu[MAXV];							//环形队列数组
	int front = 0, rear = 0;
	for (int i = 0; i < G->n; i++)
		visited[i] = 0;
	rear++;
	Qu[rear] = v;
	visited[v] = 1;
	while (rear != front)
	{
		front = (front + 1) % MAXV;
		k = Qu[front];
		p = G->adjlist[k].firstarc;
		while (p != NULL)
		{
			int j = p->adjvex;
			if (visited[j] == 0)
			{
				visited[j] = 1;
				rear = (rear + 1) % MAXV;
				Qu[rear] = j;
			}
			p = p->nextarc;
		}
	}
	return k;
}