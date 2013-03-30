/*
ID: drakcap1
PROG: fence
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

ofstream fout("fence.out");
ifstream fin("fence.in");

#define MAXE 1025
#define MAXV 501

struct Edge {
	int v1, v2, d;		// d tem o numero de arestas entre os vertices
};

struct Nodo {
	int ind, last_edge, nadj, grau;
	Edge * e[MAXV];
} g[MAXV];

int circuit[MAXE+5] , circuitpos;

void find_circuit(int v)
{
	if (g[v].last_edge >= g[v].nadj)
		circuit[circuitpos++] = v;
	else {
		while ( g[v].last_edge < g[v].nadj ) {
			Edge * e = g[v].e[g[v].last_edge];
			if ( e->d )  {
				e->d--;
				find_circuit( e->v1 == v ? e->v2 : e->v1);
			}
			else
			    g[v].last_edge++;
		}
		circuit[circuitpos++] = v;
	}
}


int
main()
{
	
	int F , i , j , k;
	fin >> F;
	
	for (k=0; k<F ; k++) {			// ler ligacoes entre vertices
		fin >> i >> j;
		if (g[i].e[ j ] == NULL) {
			Edge *e = new Edge;
			e->d = 1;
			e->v1 = i;
			e->v2 = j;
			g[i].e[ j ] = e;
			g[j].e[ i ] = e;
		}
		else
			g[i].e[ j ]->d++;	// incrementar o degree da aresta
		g[i].grau++;
		g[j].grau++;
	}
	
	for (i=1; i<MAXV ; i++) {		// transformar matriz de adjacencias em lista de adjacencias
		g[i].ind = i;
		g[i].last_edge = g[i].nadj = 0;
		for (j=1; j<MAXV ; j++)
			if (g[i].e[j] != NULL)
				g[i].e[ g[i].nadj++ ] = g[i].e[j];
	}
	
	j = 0;				// verificar se existem vertices com grau impar
	for (i=1; i<MAXV && j == 0 ; i++)
		if (g[i].grau & 1)
			j = i;		
	if (j == 0)			// todos os vertices tem grau par
	{					// procurar 1o vertice com arestas
		i = 1;
		while ( g[i].nadj == 0)
			i++;	
	}
	else 				// vertice j tem grau impar, o caminho comeca por ele
		i = j;
	circuitpos = 0;
	find_circuit(i);

	for (i=circuitpos-1 ; i>=0; i--)
		fout << circuit[i] << endl;

	fout.close();
	fin.close();
	return 0;
}
