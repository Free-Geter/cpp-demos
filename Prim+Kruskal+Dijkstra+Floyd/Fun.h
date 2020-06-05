#pragma once

#include "GraphType.h"

void Prim(MatGraph g, int v);
void Kruskal(MatGraph g);
void Dijkstra(MatGraph g, int v);
void Floyd(MatGraph g);

void ListToMat(AdjGraph* G, MatGraph& g);
void MatToList(MatGraph g, AdjGraph*& G);
void DestoryAdj(AdjGraph*& G);
void DispAdj(AdjGraph* G);
void CreatAdj(AdjGraph*& G, int A[MAXV][MAXV], int n, int e);