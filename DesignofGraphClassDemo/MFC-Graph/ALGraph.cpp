#include "stdafx.h"
#include "ALGraph.h"
#include <iostream>
#include <stack>
#include <deque>
#include<list>
using namespace std;

//设定无穷值为1000
Mgraph mg;//全局定义


Mgraph::Mgraph()
{ 
}

Mgraph::~Mgraph()
{
}

int Mgraph::LocateVex(char s)
{
	for (int i = 0; i<mg.number; i++)
		if (vexs[i] == s)
			return i;
	return -1;
}

void Mgraph::Init1(CString number, CString arcnum,CString vexss)
{
	this->number = _ttoi(number);
	this->arcnum = _ttoi(arcnum);
	this->vexs = vexss;
}

void Mgraph::Init2(CString vex1,CString vex2,CString weight)
{
	char *v1 = (LPSTR)(LPCTSTR)vex1;
	char *v2 = (LPSTR)(LPCTSTR)vex2;
	int vv1 = LocateVex(*v1);
	int vv2 = LocateVex(*v2);

	int w = _ttoi(weight);
	this->arcs[vv1][vv2] = w;
	this->arcs[vv2][vv1] = w;
}

void Mgraph::Init3()
{
	for (int i = 0; i < this->number; i++)
		for (int j = 0; j < this->number; j++)
			this->arcs[i][j] = 1000;
}


void Mgraph::Init4()
{
	for (int i = 0; i < mg.number; i++)
		mg.visited[i] = 0;
}

void Mgraph::Init5(CString startvex, CString endvex)
{
	char *v1 = (LPSTR)(LPCTSTR)startvex;
	char *v2 = (LPSTR)(LPCTSTR)endvex;
	this->start5 = LocateVex(*v1);
	this->end5 = LocateVex(*v2);
}

void Mgraph::Init6()
{
	int ct = 0;
	for (int i = 0; i < mg.number; i++)
	{
		int flag = 1;
		mg.bnode[ct].x = rand() % 400 + 100;
		mg.bnode[ct].y = rand() % 400 + 100;
		while (flag)
		{
			for (int j = 0; j < ct; j++)
			{
				if (abs(mg.bnode[ct].x - mg.bnode[j].x) < 30 || abs(mg.bnode[ct].y - mg.bnode[j].y) < 30)
				{
					flag = 0; break;
				}
			}
			if (flag)break;
			else
			{
				mg.bnode[ct].x = rand() % 400 + 100;
				mg.bnode[ct].y = rand() % 400 + 100;
				flag = 1;
			}
		}
		ct++;
	}
}

void Mgraph::DFS1(int i)   //递归
{
	int j;
	this->dfs += vexs[i];
	visited[i] = 1;
	for (j = 0; j < number; j++)
	{
		int y = arcs[i][j];
		if (arcs[i][j] != 1000 && !visited[j])
		{
			DFS1(j); 
			int x = j;
		}
	}
}


CString Mgraph::BFS()
{
	int i;
	CString bfs;
	for (i = 0; i < number; i++)
		visited[i] = 0;
	deque<int> de;
	de.push_back(0);
	bfs += vexs[0];
	visited[0] = 1;
	while (!de.empty())
	{
		int k = de.front();
		for (int j = 0; j < number; j++)
		{
			if (arcs[k][j] != 1000 && !visited[j])
			{
				bfs+= vexs[j];
				visited[j] = 1;
				de.push_back(j);
			}
		}
		de.pop_front();
	}
	return bfs;
}

int Mgraph::mini()
{
	int min = 0;    
	static int i;
	for (int j = 0; j < mg.number; j++)
	{
		if (!mg.visited[j])
		{
			if (closeedge[min].lowcost > closeedge[j].lowcost)
			{
				min = j;
			}
		}
	}
	i = min;
	mg.outprim[mg.ctp].beg = closeedge[i].begvex;
	mg.outprim[mg.ctp].end = closeedge[i].endvex;
	return i;
}
void Mgraph::Prim()
{
	int i = mg.LocateVex(vexs[0]);
	mg.visited[i] = 1;
	for (int j = 0; j < mg.number; j++)
	{
		closeedge[j].begvex = mg.vexs[0];
		closeedge[j].endvex = mg.vexs[j];              
		closeedge[j].lowcost = mg.arcs[i][j];
	}
	for (int m = 1; m < mg.number; m++)
	{
		int n = mini(); 
		mg.ctp++;
		mg.visited[n] = 1;
		closeedge[n].lowcost = 1000;
		for (int p = 0; p<mg.number; p++)
		{
			if (!mg.visited[p])
			{
				if (mg.arcs[p][n]<closeedge[p].lowcost)
				{
					closeedge[p].lowcost = mg.arcs[p][n];
					closeedge[p].begvex = mg.vexs[n];
				}
			}
		}
	}
}

void Mgraph::Kruskal()                   
{
	int a, b, k = 0;
	mg.ctk = 0;
	int min = 1000;
	int arcs1[50][50];
	for (int m = 0; m<mg.number; m++)
		mg.visited[m] = m;//每一个顶点属于一颗树
	int arcs2[50][50];
	for (int i = 0; i<mg.number; i++)
		for (int j = 0; j<mg.number; j++)
			arcs2[i][j] = arcs[i][j];
	for (int i = 0; i<mg.number; i++)
		for (int j = 0; j<mg.number; j++)
			arcs1[i][j] = arcs2[i][j];
	while (k<mg.number - 1)
	{
		min = 1000; int fk = 0;
		for (int i = 0; i < mg.number; i++)
		{
			for (int j = 0; j < mg.number; j++)
			{
				if (arcs1[i][j]<min)
				{
					fk = 1;
					a = i;
					b = j;
					min = arcs1[i][j];
				}
			}
		}
		if (fk == 0)break;//避免死循环
		if (visited[a] != visited[b])
		{
			mg.outkruskal[mg.ctk].beg = mg.vexs[a];
			mg.outkruskal[mg.ctk].end = mg.vexs[b];
			mg.ctk++;
			k++;
			for (int n = 0; n<mg.number; n++)
			{
				if (visited[n] == visited[b])
					visited[n] = visited[a];
			}
		}
		else
			arcs1[a][b] = arcs2[b][a] = 1000;//不能改arc数组里的值
	}
}

void Mgraph::Dijkstra()
{
	for (int m = 0; m < 50; m++)
		for (int n = 0; n < 50; n++)
			mg.ctd[m][n] = 0;
	for (int i = 0; i < mg.number; i++)
	{
		for (int m = 0; m < mg.number; m++)
			mg.visited[m] = 0;
		mg.visited[i] = 1;
		for (int j = 0; j < mg.number; j++)
		{
			mg.dist[j].distt = mg.arcs[i][j];
			mg.dist[j].nodenum = 0;
		}
		for (int j = 1; j < number; j++)
		{
			int distance = 1000;
			int min = 0;
			for (int n = 0; n<mg.number; n++)
			{
				if (!mg.visited[n])
				{
					if (distance>mg.dist[n].distt)
					{
						distance = mg.dist[n].distt;
						min = n;
					}
				}
			}
			int m = min;
			mg.visited[m] = 1;
			for (int n = 0; n < mg.number; n++)
			{
				if (!mg.visited[n])
				{
					if ((mg.dist[m].distt + mg.arcs[m][n]) < mg.dist[n].distt)
					{
						mg.dist[n].distt = mg.dist[m].distt + mg.arcs[m][n];
						mg.dist[n].nodenum = 0;
						for (int x = 0; x < mg.dist[m].nodenum; x++)
						{
							mg.dist[n].way[x] = mg.dist[m].way[x];
							mg.dist[n].nodenum++;
						}
						mg.dist[n].way[dist[n].nodenum++] = mg.vexs[m];
					}
				}
			}
		}
		for (int n = 0; n < mg.number; n++)
		{
			if (n != i)
			{
				if (mg.dist[n].distt < 1000)
				{
					mg.outdijkstra[i][n][0] = mg.vexs[i]; 
					mg.ctd[i][n]++;
					for (int p = 0; p < mg.dist[n].nodenum; p++)
					{
						mg.outdijkstra[i][n][ctd[i][n]++] = mg.dist[n].way[p];//三维数组表示i->n记下的路径，ctd记录i->n的路径长
					}
					mg.outdijkstra[i][n][mg.ctd[i][n]++] = mg.vexs[n];
				}
			}
		}
	}
}
