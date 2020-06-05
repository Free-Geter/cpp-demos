#include <iostream>
#include <iomanip>

#include "GraphType.h"
#include "Fun.h"

using namespace std;
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
		cout << setw(3) << i << setw(3) << ':';
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
	g.n = G->n;
	g.e = G->e;
	for (int i = 0; i < g.n; i++)						//将邻接矩阵的权值初始化为INF和0
		for (int j = 0; j < g.n; j++)
		{
			if (i == j)
				g.edges[i][j] = 0;
			else
				g.edges[i][j] = INF;
		}
			
	for (int i = 0; i < G->n; i++)
	{
		p = G->adjlist[i].firstarc;
		while (p != NULL)
		{
			g.edges[i][p->adjvex] = p->weight;
			p = p->nextarc;
		}
	}
	
}

void Prim(MatGraph g, int v)
{
	int k,j;
	int MIN;
	int lowcost[MAXV];
	int closest[MAXV];
	for (int i = 0; i < g.n; i++)				//初始化lowcost、closest数组
	{
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	for (int i = 1; i < g.n; i++)
	{
		MIN = INF;
		for (j = 0; j < g.n; j++)			//在(V-U)中找出离U最近的顶点k
			if (lowcost[j] != 0 && lowcost[j] < MIN)
			{
				MIN = lowcost[j];
				k = j;							//k记录最近顶点的编号
			}
		printf("边(%d,%d)权为: %d\n", closest[k], k, MIN);	//输出最小生成树的一条边
		lowcost[k] = 0;							//标记k已经加入U
		for (j = 0; j < g.n; j++)				//对(V-U)中的顶点j进行调整
			if (lowcost[j] != 0 && g.edges[k][j] < lowcost[j])
			{
				lowcost[j] = g.edges[k][j];
				closest[j] = k;					//修改数组lowcost和closest
			}
	}
}

template <typename T>
void Insert_Sort(T a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; i++)
	{
		//为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
		for (j = i - 1; j >= 0; j--)
			if (a[j] < a[i])
				break;

		//如找到了一个合适的位置
		if (j != (i - 1))
		{
			//将比a[i]大的数据向后移
			T temp = a[i];
			for (k = i - 1; k > j; k--)
				a[k + 1] = a[k];
			//将a[i]放到正确位置上
			a[k + 1] = temp;
		}
	}
}


void Kruskal(MatGraph g)
{
	int u1, v1, sn1, sn2, k,l;
	int vset[MAXV];
	Edge E[MaxSize];							//将图中所有边都存入一个Edge数组
	k = 0;
	for(int i=0;i<g.n;i++)
		for(int j=0;j<=i;j++)
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF)
			{
				E[k].u = i; E[k].v = j; E[k].w = g.edges[i][j];
				k++;
			}
	Insert_Sort(E, g.e);						//将E数组递增排序
	for (int i = 0; i < g.n; i++)				//初始化辅助数组
		vset[i] = i;
	k = 1;										//k表示当前构造生成树的第几条边，初始为1
	l = 0;										//E中边的下标，初始值为0
	while (k < g.n)
	{	
		u1 = E[l].u; v1 = E[l].v;				//取一条边的两个顶点
		sn1 = vset[u1]; sn2 = vset[v1];			//分别得到两个顶点所属的集合编号
		if (sn1 != sn2)							//如果不同，该边就是最小生成树的一条边
		{
			printf("(%d,%d): %d\n", u1, v1, E[l].w);	//输出最小生成树的一条边
			k++;
			for (int i = 0; i < g.n; i++)		//将两个集合统一编号
				if (vset[i] == sn2)
					vset[i] = sn1;
		}
		l++;									//扫描下一条边
	}
}


//输出从顶点v出发的所有最短路径
void Dispath(MatGraph g, int dist[], int path[], int S[], int v)
{
	int k;
	int apath[MAXV], d;
	for(int i=0;i<g.n;i++)
		if (S[i] == 1 && i != v)
		{
			printf("从顶点%d到顶点%d的路径长度为: %d\t路径为: ", v, i, dist[i]);
			d = 0; apath[d] = i;
			k = path[i];
			if (k == -1)
				cout << "无路径" << endl;
			else
			{
				while (k != v)
				{
					d++;	apath[d] = k;
					k = path[k];
				}
				d++;	apath[d] = v;
				cout << apath[d];
				for (int j = d - 1; j >= 0; j--)
					cout << ',' << apath[j];
				cout << endl;
			}
		}
}

void Dijkstra(MatGraph g, int v)
{
	int dist[MAXV], path[MAXV];
	int S[MAXV];							//S[i]=1表示顶点i在S中，0表示在U中
	int MINdis, i, j, u;
	for (int i=0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];			//初始化距离
		S[i] = 0;
		if (g.edges[v][i] < INF)			//初始化路径
			path[i] = v;					//顶点v到顶点i有边，置顶点i的前一个顶点为v
		else
			path[i] = -1;					//顶点v到顶点i没有边，置顶点i的前一个顶点为-1
	}
	S[v] = 1; path[v] = 0;					//源点编号v放入S中
	for (int i = 0; i < g.n - 1; i++)
	{
		MINdis = INF;
		for(int j=0;j<g.n;j++)				//选取U中，具有最小路径长度的顶点u
			if (S[j] == 0 && dist[j] < MINdis)
			{
				u = j;
				MINdis = dist[j];
			}
		S[u] = 1;							//顶点u加入S中
		for(int j=0;j<g.n;j++)
			if(S[j]==0)
				if (g.edges[u][j] < INF && dist[u] + g.edges[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(g, dist, path, S, v);
}




void Dispath4Floyd(MatGraph g, int A[][MAXV], int path[][MAXV])
{
	int k;
	int apath[MAXV], d;
	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++)
		{
			if (A[i][j] != INF && i != j)
			{
				printf("从%d到%d的路径为: ", i, j);
				k = path[i][j];
				d = 0;
				apath[d] = j;						//添加终点
				while (k != -1 && k != i)			//添加中间点
				{
					d++;	apath[d] = k;
					k = path[i][k];
				}
				d++;	apath[d] = i;				//添加起点
				cout << apath[d];
				for (int s = d - 1; s >= 0; s--)
					cout << ',' << apath[s];
				cout << '\t' << "路径长度为: " << A[i][j] << endl;
			}
		}
}


void Floyd(MatGraph g)
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	for(int i=0;i<g.n;i++)
		for (int j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;					//顶点i到j有边
			else
				path[i][j] = -1;				//顶点i到j没有边
		}
	for (int k = 0; k < g.n; k++)
	{
		for(int i=0;i<g.n;i++)
			for(int j=0;j<g.n;j++)
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];		//修改最短路径长度
					path[i][j] = path[k][j];			//修改最短路径
				}
	}
	Dispath4Floyd(g, A, path);
}

