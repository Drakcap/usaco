/*
ID: drakcap1
PROG: spin
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


ofstream fout("spin.out");
ifstream fin("spin.in");

struct Wedge {
	int i, f;
};

struct Roda {
	int vel;
	vector<Wedge> wedges;
} rodas[5];

struct Estado {
	int pos[5];
	bool operator<(const Estado &e) const
	{
		for (int i = 0; i < 5; i++) {
			if (pos[i] != e.pos[i]) {
				return pos[i] < e.pos[i];
			}
		}
		return false;
	}
};

set<Estado> estados;
int tempo = 0;

void
adiciona_estado()
{
	Estado e;
	for (int i = 0; i < 5; i++) {
		e.pos[i] = rodas[i].wedges[0].i;
	}
	estados.insert(e);
}

bool
estado_repetido()
{
	Estado e;
	for (int i = 0; i < 5; i++) {
		e.pos[i] = rodas[i].wedges[0].i;
	}
	return(estados.find(e) != estados.end());
}

void
reduz(int &angulo)
{
	if (angulo >= 360)
		angulo = angulo % 360;
}

bool
inter_aux(int i1, int f1, int i2, int f2, int &i, int &f)
{

	if (i1 <= i2 && f1 >= f2) {
		i = i2;
		f = f2;
		return true;
	}
	if (i1 >= i2 && f1 <= f2) {
		i = i1;
		f = f1;
		return true;
	}
	if (i1 >= i2 && i1 <= f2 && f1 >= f2) {
		i = i1;
		f = f2;
		return true;
	}
	if (i1 <= i2 && f1 <= f2 && f1 >= i2) {
		i = i2;
		f = f1;
		return true;
	}
	return false;
}

bool
merge(int intervalos[][2], int n_inter, int &inicio, int &fim)
{
	if (n_inter == 0) {
		return false;
	}
	if (n_inter == 1) {
		inicio = intervalos[0][0];
		fim = intervalos[0][1];
		return true;
	}
	
	int ixi = -1;
	bool tem_anterior;
	
	//procura o intervalo inicial
	for (int i = 0; i < n_inter; i++) {
		tem_anterior = false;
		for (int j = 0; j < n_inter; j++) {
			if (j != i) {
				if (intervalos[i][0] == intervalos[j][1]+1 ||
					(intervalos[i][0] == 0 && intervalos[j][1] == 359)) {
					tem_anterior = true;
					break;
				}
			}
		}
		if(! tem_anterior) {
			ixi = i;
			break;
		}
	}
	
	if (ixi == -1) {
		inicio = 0;
		fim = 359;
		return true;
	}
	
	inicio = intervalos[ixi][0];
	
	int ixf = -1;
	bool tem_seguinte;
	
	//procura o intervalo final
	for (int i = 0; i < n_inter; i++) {
		tem_seguinte = false;
		for (int j = 0; j < n_inter; j++) {
			if (j != i) {
				if (intervalos[i][1]+1 == intervalos[j][0] ||
					(intervalos[i][1] == 359 && intervalos[j][0] == 0)) {
					tem_seguinte = true;
					break;
				}
			}
		}
		if(! tem_seguinte) {
			ixf = i;
			break;
		}
	}

	
	fim = intervalos[ixf][1];
	return true;



}

bool
intersecta(Wedge &e, int inicio, int fim, int &novo_inicio, int &novo_fim)
{
	Wedge nova_e = e;
	
	//so um intervalo na wedge que estamos a comparar
	if (e.f >= e.i) {
		//so um intervalo no intervalo a comparar
		if (fim >= inicio) {
			return inter_aux(e.i, e.f, inicio, fim, novo_inicio, novo_fim);
		}
		//dois intervalos no intervalo a comparar
		else {
			int i1, f1, i2, f2;
			i1 = inicio;
			f1 = 359;
			i2 = 0;
			f2 = fim;
			
			int resi1, resf1, resi2, resf2;
			bool teste1, teste2;
			
			teste1 = inter_aux(e.i, e.f, i1, f1, resi1, resf1);
			teste2 = inter_aux(e.i, e.f, i2, f2, resi2, resf2);
			
			if (teste1 && teste2) {
				if (resf1 == 359 && resi2 == 0) {
					novo_inicio = resi1;
					novo_fim = resf2;
				} else {
					novo_inicio = resi2;
					novo_fim = resf1;
				}
			} else if (teste1) {
				novo_inicio = resi1;
				novo_fim = resf1;
				return true;
			} else if (teste2) {
				novo_inicio = resi2;
				novo_fim = resf2;
				return true;
			}
		
		}
	
	}
	//dois intervalos
	else {
		//so um intervalo no intervalo a comparar
		if (fim >= inicio) {
			int ei1 = -1, ef1 = -1, ei2 = -1, ef2 = -1;
			ei1 = e.i;
			ef1 = 359;
			ei2 = 0;
			ef2 = e.f;
			
			int resi1, resf1, resi2, resf2;
			bool teste1, teste2;
			
			teste1 = inter_aux(inicio, fim, ei1, ef1, resi1, resf1);
			teste2 = inter_aux(inicio, fim, ei2, ef2, resi2, resf2);
			
			if (teste1 && teste2) {
				if (resf1 == 359 && resi2 == 0) {
					novo_inicio = resi1;
					novo_fim = resf2;
				} else {
					novo_inicio = resi2;
					novo_fim = resf1;
				}
				return true;
			} else if (teste1) {
				novo_inicio = resi1;
				novo_fim = resf1;
				return true;
			} else if (teste2) {
				novo_inicio = resi2;
				novo_fim = resf2;
				return true;
			}
		}
		//dois intervalos
		else {
			int n_inter = 0;
			int intervalos[4][2];
			
			int i1, f1, i2, f2;
			i1 = inicio;
			f1 = 359;
			i2 = 0;
			f2 = fim;
			
			int ei1 = -1, ef1 = -1, ei2 = -1, ef2 = -1;
			ei1 = e.i;
			ef1 = 359;
			ei2 = 0;
			ef2 = e.f;
			
			//faz as interseccoes entre os 4 intervalos
			int resi, resf;
			
			if (inter_aux(ei1, ef1, i1, f1, resi, resf)) {
				intervalos[n_inter][0] = resi;
				intervalos[n_inter++][1] = resf;
			}
			
			if (inter_aux(ei1, ef1, i2, f2, resi, resf)) {
				intervalos[n_inter][0] = resi;
				intervalos[n_inter++][1] = resf;
			}
			
			if (inter_aux(ei2, ef2, i1, f1, resi, resf)) {
				intervalos[n_inter][0] = resi;
				intervalos[n_inter++][1] = resf;
			}
			
			if (inter_aux(ei2, ef2, i2, f2, resi, resf)) {
				intervalos[n_inter][0] = resi;
				intervalos[n_inter++][1] = resf;
			}
			
			return merge(intervalos, n_inter, novo_inicio, novo_fim);
		
		
		}
	
	}

	return false;
}

bool
alinha(int ix, int inicio, int fim)
{
	if (ix >= 5) {
		return true;
	}
	
	//if (tempo == 1)
	//	fout << ix << " " << inicio << " " << fim << endl;
	
	int novo_inicio, novo_fim;
	
	for (unsigned i = 0; i < rodas[ix].wedges.size(); i++) {
		if (intersecta(rodas[ix].wedges[i], inicio, fim, novo_inicio, novo_fim)) {
			if (alinha(ix+1, novo_inicio, novo_fim)) {
				return true;
			}
		}
	}

	return false;
}

int
main()
{

	int nW, extent;
	for (int i = 0; i < 5; i++) {
		fin >> rodas[i].vel;
		fin >> nW;
		for (int j = 0; j < nW; j++) {
			Wedge e;
			fin >> e.i >> extent;
			e.f = (e.i + extent) % 360;
			rodas[i].wedges.push_back(e);
		}
	}
	
	bool ya = false;
	
	while(1) {
		if(estado_repetido()) {
			//fout << tempo << endl;
			break;
		}
		if(alinha(0, 0, 359)) {
			ya = true;
			break;
		}
		adiciona_estado();
		++tempo;
		for (int i = 0; i < 5; i++) {
			for (unsigned j = 0; j < rodas[i].wedges.size(); j++) {
				rodas[i].wedges[j].i = (rodas[i].wedges[j].i + rodas[i].vel) % 360;
				rodas[i].wedges[j].f = (rodas[i].wedges[j].f + rodas[i].vel) % 360;
			}
		}
		
		/*if (tempo == 1) {
			for (int i = 0; i < 5; i++) {
				for (unsigned j = 0; j < rodas[i].wedges.size(); j++) {
					fout << rodas[i].wedges[j].i << " " << rodas[i].wedges[j].f << endl;
				}
			}
			fout << endl;
		}*/
		
	}
	
	if (! ya) {
		fout << "none" << endl;
	} else {
		fout << tempo << endl;
	}
	
	/*for (int t = 0; t < 9; t++) {
		for (int i = 0; i < 5; i++) {
			for (unsigned j = 0; j < rodas[i].wedges.size(); j++) {
				rodas[i].wedges[j].i = (rodas[i].wedges[j].i + rodas[i].vel) % 360;
				rodas[i].wedges[j].f = (rodas[i].wedges[j].f + rodas[i].vel) % 360;
			}
		}
	}
	
	for (int i = 0; i < 5; i++) {
		for (unsigned j = 0; j < rodas[i].wedges.size(); j++) {
			fout << rodas[i].wedges[j].i << " " << rodas[i].wedges[j].f << endl;
		}
	}*/


	fout.close();
	fin.close();
	return 0;
}
