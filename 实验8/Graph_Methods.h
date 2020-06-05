#pragma once

#include "GraphType.h"

int visited[];							//声明该数组以便不断初始化

void CreatAdj(AdjGraph*& G, int A[MAXV][MAXV], int n, int e);
void DispAdj(AdjGraph* G);
void DestoryAdj(AdjGraph*& G);

void MatToList(MatGraph g, AdjGraph*& G);
void ListToMat(AdjGraph* G, MatGraph& g);

void DFS(AdjGraph* G, int v);
void BFS(AdjGraph* G, int v);

bool Connect(AdjGraph* G);

void ExistPath(AdjGraph* G, int u, int v, bool& has);
void FindPath(AdjGraph* G, int u, int v, int path[], int d);
void FindAllPath(AdjGraph* G, int u, int v, int path[], int d);
void PathlenAll(AdjGraph* G, int u, int v, int l, int path[], int d);
void FindCyclePath(AdjGraph* G, int k);
void ShortPath(AdjGraph* G, int u, int v);

int MaxDist(AdjGraph* G, int v);