/*
ID: drakcap1
PROG: shopping
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

ofstream fout("shopping.out");
ifstream fin("shopping.in");

#define QUANT 1
#define PROD 0
#define MAXN 7776
#define INF 2000000000

struct Promocao {
	int prod[5][2]; //produtos e as suas quantidades
	int n;
	int preco;
} promocoes[99];

struct Produto {
	int cod, quant, preco;
	int ix;
} produtos[5];

map<int, int> ix_produtos;
int converter[5];
int s, b;

struct Ligacao {
	int dest, peso;
};

struct No {
	int num;
	Ligacao ligacoes[100];
	int nlig;
	int dist;
	bool visited;
	
	bool operator<(const No& n) const {
		return dist > n.dist;
	}
	
} nos[MAXN];

int
converte()
{
	int res = 0;
	int mult = 1;
	for (int i = 0; i < b; i++) {
		res += converter[i]*mult;
		mult *= 6;
	}
	return res;
}

void
desconverte(int valor)
{
	int ix = 0;
	memset(converter, 0, sizeof(int)*b);
	while (valor > 0) {
		converter[ix++] = valor % 6;
		valor /= 6;
	}

}

void
add_ligacao(int s, int d, int peso)
{
	Ligacao l;
	l.dest = d;
	l.peso = peso;
	nos[s].ligacoes[nos[s].nlig++] = l;
}

bool
valid()
{
	for (int i = 0; i < b; i++) {
		if(converter[i] < 0) {
			return false;
		}
	}
	return true;
}

//ligacoes sem as promocoes
void
add_ligacoes(int prod)
{
	int maxi = 0;
	int mult = 1;
	for (int i = 0; i < b; i++) {
		//fout << ix_produtos.find(i)->second << " " << produtos[ix_produtos.find(i)->second].quant << endl;
		maxi += produtos[i].quant*mult;
		mult *= 6;
	}
	//fout << "maxi: " << maxi << " " << prod << endl;
	
	for (int i = maxi; i >= 0; i--) { //todos os nos
		desconverte(i);
		--converter[prod];
		if(valid()) {
			add_ligacao(converte(), i, produtos[prod].preco);
		} 
	}

}



void
add_lig_prom()
{
	if (s == 0) return;

	int maxi = 0;
	int mult = 1;
	for (int i = 0; i < b; i++) {
		maxi += produtos[i].quant*mult;
		mult *= 6;
	}

	for (int i = maxi; i >= 0; i--) { //todos os nos
		for (int j = 0; j < s; j++) {	//todas as promocoes
			desconverte(i);
			for (int n = 0; n < promocoes[j].n; n++) {
				converter[ix_produtos[promocoes[j].prod[n][PROD]]] -= promocoes[j].prod[n][QUANT];
			}
			if(valid()) {
				add_ligacao(converte(), i, promocoes[j].preco);
			} 
		}
	}
}

int
dijkstra()
{	
	int obj = 0;
	int mult = 1;
	for (int i = 0; i < b; i++) {
		obj  += produtos[i].quant*mult;
		mult *= 6;
	}
	//fout << "objectivo: " << obj << endl;
	for (int i = 0; i <= obj; i++) {
		nos[i].dist = INF;
		nos[i].visited = false;
	}
	
	nos[0].dist = 0;
	//nos[0].visited = true;
	int next = 0;
	int min_dist = INF;
	//priority_queue<No> fila;
	
	//fila.push(nos[0]);
	
	//while (! fila.empty()) {
	while(1) {
		//min_dist = -1;
		min_dist = INF;
		for (int i = 0; i <= obj; i++) {
			if (nos[i].dist < min_dist && ! nos[i].visited) {
				min_dist = nos[i].dist;
				next = i;
			}
		}
		//fout << next << endl;
		nos[next].visited = true;
		//No no = fila.top();
		//fila.pop();
		//if (no.num == obj) {
		if (next == obj) {
			return nos[next].dist;
		}
		
		for (int i = 0; i < nos[next].nlig; i++) {
			if (nos[next].dist + nos[next].ligacoes[i].peso < nos[nos[next].ligacoes[i].dest].dist) {
				nos[nos[next].ligacoes[i].dest].dist = nos[next].dist + nos[next].ligacoes[i].peso;
				//fila.push(nos[no.ligacoes[i].dest]);
			}
			
		}
		//fout << fila.size() << endl;
	}
	return -1;
}


int
main()
{
	for (int i = 0; i < MAXN; i++) {
		nos[i].num = i;
		nos[i].nlig = 0;
	}

	fin >> s;
	
	for (int i = 0; i < s; i++) {
		fin >> promocoes[i].n;
		for (int j = 0; j < promocoes[i].n; j++) {
			fin >> promocoes[i].prod[j][PROD];
			fin >> promocoes[i].prod[j][QUANT];
		}
		fin >> promocoes[i].preco;
	}
	
	fin >> b;
	int t;
	for (int i = 0; i < b; i++) {
		fin >> t;
		ix_produtos[t] = i;
		//produtos[ix_produtos[i]].cod = ix_produtos[i];
		produtos[i].cod = t;
		fin >> produtos[i].quant;
		fin >> produtos[i].preco;
		produtos[i].ix = i;
	}
	
	//ligacoes sem promocoes
	for (int i = 0; i < b; i++) {
		add_ligacoes(i);
	}
	
	add_lig_prom();
	fout << dijkstra() << endl;
	/*for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < nos[i].nlig; j++) {
			fout << i << " -> " << nos[i].ligacoes[j].dest << " " << nos[i].ligacoes[j].peso << endl;
		}
	}*/
	/*desconverte(7560);
	for (int i = 0; i < 5; i++) {
		fout << converter[i] << " ";
	}
	fout << endl;*/
	


	fout.close();
	fin.close();
	return 0;
}
