#include "GraphType.h"
#include "Graph_Methods.h"

#include<iostream>
using namespace std;

void InitVisited(int a[],int n)
{
	for (int i = 0; i < n; i++)
		a[i] = 0;
}


int main()
{
	int A[MAXV][MAXV] = { {0,8,INF,5,INF},{INF,0,3,INF,INF},{INF,INF,0,INF,6},
		{INF,INF,9,0,INF},{INF,INF,INF,INF,0} };
	int B[MAXV][MAXV] = { {0,1,0,1,1},{1,0,1,1,0},
		{0,1,0,1,1},{1,1,1,0,1},{1,0,1,1,0} };
	int C[MAXV][MAXV] = { {0,1,1,0,0},{0,0,1,0,0},{0,0,0,1,1},
		{0,0,0,0,1},{1,0,0,0,0} };
	int n = 5;
	int e = 10;
	
	AdjGraph* G, * H,*I;
	
	CreatAdj(I, C, 5, 7);
	CreatAdj(H, B, 5, 8);
	CreatAdj(G, A, n, e);
	cout << "图G: " << endl;
	DispAdj(G);
	cout << "图G的DFS遍历: " << endl;
	DFS(G, 0);
	cout << "图G的BFS遍历: " << endl;
	BFS(G, 0);

	cout << "图G的所有简单路径: " << endl;
	for(int i = 0;i<G->n;i++)
		for (int j = 0; j < G->n ; j++)
		{
			if (j == i && j + 1 < G->n)
				j++;
			else if (j == i && j + 1 >= G->n)
				break;
			//flag初始为false
			bool flag = false;
			int Path[10] = { 0 };
			// d初始为-1
			int d = -1;
			ExistPath(G, i, j, flag);
			InitVisited(visited, MAXV);
			if (flag)
			{
				FindAllPath(G, i, j, Path, d);
			}
				
		}
	int path[10] = { 0 };
	int d = -1;
	cout << "图H: " << endl;
	DispAdj(H);
	cout << "图H中从1到4，距离为3的简单路径: " << endl;
	PathlenAll(H, 1, 4, 3, path, d);
	cout << "图H中从1到4，逆向输出距离最短的简单路径: " << endl;
	ShortPath(H, 1, 4);
	cout << endl;
	cout << "图H中距离1最远的结点: " << endl;
	cout << MaxDist(H, 1) << endl;

	cout << "图I: " << endl;
	DispAdj(I);
	cout << "图I中0开始的简单回路: " << endl;
	InitVisited(visited, MAXV);
	FindCyclePath(I, 0);

	
}

