#include <iostream>
#include "Fun.h"

using namespace std;

int main()
{
	int A[MAXV][MAXV] = { {0,8,INF,5,INF},{8,0,3,INF,INF},{INF,3,0,9,6},
		{5,INF,9,0,INF},{INF,INF,6,INF,0} };

	AdjGraph* G;
	MatGraph g;
	int n = 5, e = 5;
	CreatAdj(G, A, n, e);
	cout << "图G: " << endl << endl;
	DispAdj(G);
	ListToMat(G, g);
	cout << "Prim 构造最小生成树" << endl << endl;
	Prim(g,0);
	cout << "Kruskal 构造最小生成树" << endl << endl;
	Kruskal(g);
	cout << "Dijkstra 输出0到其他结点的最小路径" << endl << endl;
	Dijkstra(g, 0);
	cout << "Floyd 输出所有结点到其他结点的最小路径" << endl << endl;
	Floyd(g);
	
}