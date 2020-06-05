#pragma once

#define INF 32767
#define MAXV 5



typedef char InfoType;


typedef struct
{
	int no;						//顶点编号
	InfoType info;				//顶点的其他信息
}VertexType;					//顶点类型

typedef struct
{
	int edges[MAXV][MAXV];		//邻接矩阵数组
	int n, e;					//顶点数n，边数e
	VertexType vexs[MAXV];		//顶点信息数组
}MatGraph;						//完整的图邻接矩阵类型




typedef struct ANode
{
	int adjvex;					//该边的邻接点编号
	ANode* nextarc;				//指向下一条边得指针
	int weight;					//该边得相关信息，如权值（这里用整形表示）
}ArcNode;						//边结点类型

typedef struct Vnode
{
	InfoType info;				//顶点得其他星系
	ArcNode* firstarc;			//指向第一个边结点
}VNode;							//头结点类型

typedef struct
{
	VNode adjlist[MAXV];		//头结点数组
	int n, e;					//顶点数n，边数e
}AdjGraph;						//完整的图邻接表类型