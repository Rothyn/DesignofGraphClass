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
	int distt;//�������
	char way[50];//��������
	int nodenum;//�����Ķ�����
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


class Mgraph   //�ڽӾ���
{
public:
	int number;//�������Ŀ
	int arcnum;//�ߵ���Ŀ
	CString vexs;
	int arcs[50][50];
	int visited[50];
	primnode closeedge[50];//prim
	adknode dist[50];//���·��
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
	int ctd[50][50];//����������
	void Init5(CString startvex, CString endvex);
	int start5;
	int end5;
};