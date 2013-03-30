/*
ID: drakcap1
PROG: butter
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

ofstream fout("butter.out");
ifstream fin("butter.in");

#define MAXE 1451
#define MAXV 801
#define INF 2000000000
#define MAXN 500
#define MAXP 801

struct No {
	map<int, int> ligacoes;
} nos[MAXP];

struct Par {
	int no, dist;
	bool operator<(const Par &p) const {
		return dist > p.dist;
	}
};

int N, P, C;
int vacas[MAXN+1];
int distancias[MAXP+1];

void
dijkstra(int source, int distancias[])
{
	for (int i = 0; i < P; i++) {
		distancias[i] = INF;
	}
	
	distancias[source] = 0;
	priority_queue<Par> fila;
	Par par;
	par.no = source;
	par.dist = 0;
	
	fila.push(par);
	map<int, int>::iterator it;
	
	while (! fila.empty()) {
		Par p = fila.top();
		fila.pop();
	
		it = nos[p.no].ligacoes.begin();
		
		for ( ; it != nos[p.no].ligacoes.end(); it++) {
			if (p.dist + it->second < distancias[it->first]) {
				distancias[it->first] = p.dist + it->second;
				Par np;
				np.no = it->first;
				np.dist = distancias[it->first];
				fila.push(np);
			}
			
		}
	
	
	}


}


int
main()
{

	fin >> N >> P >> C;
	
	for (int i = 0; i < N; i++) {
		fin >> vacas[i];
		--vacas[i];
	}
	
	int e1, e2, dist;
	for (int i = 0; i < C; i++) {
		fin >> e1 >> e2 >> dist;
		--e1; --e2;
		nos[e1].ligacoes[e2] = dist;
		nos[e2].ligacoes[e1] = dist;
	}
	
	int best = -1;
	int count;
	
	for (int i = 0; i < P; i++) {
		dijkstra(i, distancias);
		count = 0;
		for (int j = 0; j < N; j++) {
			if (vacas[j] != i) {
				count += distancias[vacas[j]];
			}
		}
		if (count < best || best == -1) {
			best = count;
		}
	
	}
	fout << best << endl;

	fout.close();
	fin.close();
	return 0;
}
