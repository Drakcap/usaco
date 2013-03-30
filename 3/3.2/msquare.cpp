/*
ID: drakcap1
PROG: msquare
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

ofstream fout("msquare.out");
ifstream fin("msquare.in");

struct Estado {
	int cima[4];
	int baixo[4];
	string sol;
};

//bool estados[8][8][8][8][8][8][8][8];
Estado objectivo;
//string solucao = "coiso";
set<int> estados;

bool 
isObjectivo(Estado &e) {
	for (int i = 0; i < 4; i++) {
		if (e.cima[i] != objectivo.cima[i] || e.baixo[i] != objectivo.baixo[i]) {
			return false;
		}
	}

	return true;
}

/*void
pesquisa(Estado e, string s)
{
	if (isObjectivo(e)) {
		if (s < solucao || solucao == "coiso") {
			solucao = s;
		}
	}
	if (s.size() >= solucao.size() && solucao != "coiso") {
		return;
	}
	
	
	
	Estado eB;
}*/

/*inline void 
marca_visitado(Estado &e)
{
	estados[e.baixo[0]-1][e.baixo[1]-1][e.baixo[2]-1][e.baixo[3]-1][e.cima[0]-1][e.cima[1]-1][e.cima[2]-1][e.cima[3]-1] = true;
}


inline bool
repetido(Estado &e)
{
	return estados[e.baixo[0]-1][e.baixo[1]-1][e.baixo[2]-1][e.baixo[3]-1][e.cima[0]-1][e.cima[1]-1][e.cima[2]-1][e.cima[3]-1];
}*/

int 
valorEstado(Estado &e)
{
	int valor = 0;
	int mult = 1;
	
	for (int i = 0; i < 4; i++) {
		valor += e.cima[i]*mult;
		mult *= 8;
	}
	
	for (int i = 0; i < 4; i++) {
		valor += e.baixo[i]*mult;
		mult *= 8;
	}
	
	return valor;
}

void
print_estado(Estado &e) 
{
	for (int i = 0; i < 4; i++) {
		fout << e.cima[i] << " ";
	}
	for (int i = 0; i < 4; i++) {
		fout << e.baixo[i] << " ";
	}	
	fout << endl;

}

int
main()
{
	Estado init;
	
	for (int i = 0; i < 4; i++) {
		init.cima[i] = i+1;
		init.baixo[i] = i+5;
		init.sol = "";
	}
	
	for (int i = 0; i < 4; i++) {
		fin >> objectivo.cima[i];
	}
	for (int i = 0; i < 4; i++) {
		fin >> objectivo.baixo[i];
	}
	
	queue<Estado> fila;
	
	fila.push(init);
	int valor;
	
	while (! fila.empty()) {
		
		Estado e = fila.front();
		fila.pop();
		
		valor = valorEstado(e);
		
		if (estados.find(valor) != estados.end()) {
			continue;
		}
		estados.insert(valor);
		
		//if (repetido(e)) {
		//	continue;
		//}
		//marca_visitado(e);
		//print_estado(e);
		
		if (isObjectivo(e)) {
			//fout << "Dasse oblah" << endl;
			fout << e.sol.size() << endl;
			for (unsigned i = 0; i < e.sol.size(); i++) {
				if (i % 60 == 0 && i != 0) fout << endl;
				
				fout << e.sol[i];
			}
			fout << endl;
			break;
		}
		
		Estado eA;
		for (int i = 0; i < 4; i++) {
			eA.cima[i] = e.baixo[3-i];
			eA.baixo[3-i] = e.cima[i];
		}
		eA.sol = e.sol + "A";
		fila.push(eA);
		
		Estado eB;
		eB.cima[0] = e.cima[3];
		eB.baixo[3] = e.baixo[0];
		for (int i = 1; i < 4; i++) {
			eB.cima[i] = e.cima[i-1];
			eB.baixo[3-i] = e.baixo[3-i+1];
		}
		eB.sol = e.sol + "B";
		fila.push(eB);
		
		Estado eC;
		eC.cima[0] = e.cima[0];
		eC.cima[1] = e.baixo[2];
		eC.cima[2] = e.cima[1];
		eC.cima[3] = e.cima[3];
		eC.baixo[0] = e.baixo[0];
		eC.baixo[1] = e.cima[2];
		eC.baixo[2] = e.baixo[1];
		eC.baixo[3] = e.baixo[3];
		eC.sol = e.sol + "C";
		fila.push(eC);
		
		//cout << fila.size() << endl;
	}
	
	//pesquisa(e, "");
	
	//fout << solucao.size() << endl;
	//fout << solucao << endl;

	fout.close();
	fin.close();
	return 0;
}
