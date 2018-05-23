#pragma once

struct primnode
{
public:
	char begvex;
	char endvex;
	int lowcost;
};

struct adknode
{
	int distt;//最近距离
	char way[50];//顶点数组
	int nodenum;//经过的顶点数
};

struct gpnode
{
	int x;
	int y;
};

struct xnode
{
	char beg;
	char end;
};


class Mgraph   //邻接矩阵
{
public:
	int number;//顶点的数目
	int arcnum;//边的数目
	CString vexs;
	int arcs[50][50];
	int visited[50];
	primnode closeedge[50];//prim
	adknode dist[50];//最短路径
public:
	Mgraph();
	~Mgraph();
	void Init6();
	void Init1(CString number, CString arcnum, CString vexss);
	void Init2(CString vex1, CString vex2, CString weight);
	void Init3();
	void Init4();
	int  LocateVex(char s);
	void DFS1(int i);
	CString dfs;
	CString BFS();
	int mini();
	int ctp = 0;
	int ctk = 0;
	void Prim();
	void Kruskal();
	CString dijk;
	void Dijkstra();
	gpnode bnode[50];
	xnode outprim[50];
	xnode outkruskal[50];
	char outdijkstra[50][50][50];
	int ctd[50][50];//经过顶点数
	void Init5(CString startvex, CString endvex);
	int start5;
	int end5;
};