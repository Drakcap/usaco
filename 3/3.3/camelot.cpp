/*
ID: drakcap1
PROG: camelot
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

ofstream fout("camelot.out");
ifstream fin("camelot.in");

#define MAXL 30
#define MAXC 26
#define INF 2000000

int r, c, ncav, base;
int cav[MAXL*MAXC][2], king[2]; //posicoes dos cavalos e do rei
int melhores[MAXL+1][MAXC+1][MAXL+1][MAXC+1]; //distancia mais curta entre os diferentes pontos do tabuleiro
int distancias[MAXL*MAXC]; //distancia de cada cavaleiro a um dado ponto de encontro
int visited[MAXL+1][MAXC+1];
int nvisited = 1;


inline bool
dentro(int l, int col) 
{
	return (l > 0 && col > 0 && l <= r && col <= c);
}

struct Pos {
	int l, c, dist;
};

int
distancia(int li, int ci, int lf, int cf)
{
	Pos p1;
	p1.l = li;
	p1.c = ci;
	p1.dist = 0;
	visited[li][ci] = nvisited;
	queue<Pos> fila;
	fila.push(p1);
	//fout << li << " " << ci << " " << lf << " " << cf << endl;
	//fout << "here" << li << " " << ci << " " << lf << " " << cf << endl;
	Pos p, np;
	while (! fila.empty()) {
		p = fila.front();
		fila.pop();
		//fout << linha << " " << coluna << " " << dist << endl;
		//if (li == 1 && ci == 21 && lf == 2 && cf == 1) { fout << p.l << " " << p.c << " " << c << endl;}
		melhores[li][ci][p.l][p.c] = p.dist;
		melhores[p.l][p.c][li][ci] = p.dist;
		
		if (p.l == lf && p.c == cf) {
			++nvisited;
			return p.dist;
		}
		
		np.dist = p.dist+1;
		//fout << nova_dist << endl;
		
		//movimento 1
		np.l = p.l + 2;
		np.c = p.c - 1;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 2
		np.l = p.l + 2;
		np.c = p.c + 1;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 3
		np.l = p.l + 1;
		np.c = p.c + 2;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			//if (li == 1 && ci == 2 && lf == 4 && cf == 1) {
			//	fout << "here" << endl;
			//}
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 4
		np.l = p.l - 1;
		np.c = p.c + 2;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 5
		np.l = p.l - 2;
		np.c = p.c + 1;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 6
		np.l = p.l - 2;
		np.c = p.c - 1;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 7
		np.l = p.l - 1;
		np.c = p.c - 2;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//movimento 8
		np.l = p.l + 1;
		np.c = p.c - 2;
		if(dentro(np.l, np.c) && !(visited[np.l][np.c] == nvisited)) {
			visited[np.l][np.c] = nvisited;
			fila.push(np);
		}
		//if (li == 1 && ci == 21 && lf == 2 && cf == 1) {
		//	fout << fila.size() << endl;
		//}
	}
	//fout << li << " " << ci << " " << lf << " " << cf << endl;
	++nvisited;
	return 1000;
}

int
main()
{
	fin >> r >> c;
	base = max(r, c) + 1;
	
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			for (int k = i; k <= r; k++) {
				for (int l = (k == i ? j + 1 : 1); l <= c; l++) {
					//fout << i << " " << j << " " << k << " " << l << endl;
					if (! melhores[i][j][k][l]) {
						melhores[i][j][k][l] = distancia(i, j, k, l);
						melhores[k][l][i][j] = melhores[i][j][k][l];
					}
				}
			}
		}
	}
	
	//fout << "here" << endl;
	char col;
	
	fin >> col;
	king[1] = col - 'A' + 1;
	fin >> king[0];
	
	while (fin >> col) {
		cav[ncav][1] = col - 'A' + 1;
		fin >> cav[ncav++][0];
	}
	
	int best = -1;
	int distk = 0, distk2 = 0;
	int total, antTotal;
	int minLarea, maxLarea, minCarea, maxCarea;
	minLarea = king[0]-2;
	maxLarea = king[0]+2;
	minCarea = king[1]-2;
	maxCarea = king[1]+2;
	while(minLarea <= 0) ++minLarea;
	while(maxLarea > r) --maxLarea;
	while(minCarea <= 0) ++minCarea;
	while(maxCarea > c) --maxCarea;
	
	
	
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			distk = max(abs(king[0] - i), abs(king[1] - j));
			distk2 = melhores[king[0]][king[1]][i][j];
			total = distk;
			
			for (int k = 0; k < ncav; k++) {
				distancias[k] = melhores[cav[k][0]][cav[k][1]][i][j];
				total += distancias[k];
			}
			if (total < best || best == -1) {
				/*fout << "here " << total << " " << best << endl;
				fout << i << " " << j << endl;
				for (int p = 0; p < ncav; p++) fout << melhores[cav[p][0]][cav[p][1]][i][j] << " " << distancias[p] << endl;
				fout << "done here" << endl;*/
				best = total;
			}
			
			total -= distk;
			antTotal = total;
			//fout << antTotal << endl;
			
			for (int x = minLarea; x <= maxLarea; x++) {
				for (int y = minCarea; y <= maxCarea; y++) {
					for (int k = 0; k < ncav; k++) {
						total -= distancias[k];
						//total += distk2;
						total += melhores[cav[k][0]][cav[k][1]][x][y];
						total += melhores[x][y][i][j];
						total += max(abs(king[0]-x), abs(king[1]-y));
						
						if (total < best || best == -1) {
							/*fout << "here " << total << " " << best << endl;
							fout << x << " " << y << endl;
							//fout << king[0] << " " << king[1] << endl;
							for (int p = 0; p < ncav; p++) fout << melhores[cav[p][0]][cav[p][1]][i][j] << " " << distancias[p] << endl;
							fout << k << " " << distk2 << " " << melhores[cav[k][0]][cav[k][1]][x][y] << " " << (abs(king[0]-x) + abs(king[1]-y)) << endl;
							fout << "done here" << endl;*/
							best = total;
						}
						/*if (i == 2 && j == 3) {
							fout << distancias[0] << " " << distancias[1] << endl;
							fout << x << " " << y << " " << total << endl;
						}*/
						
						total = antTotal;
					}
				}
			}
			
		}
	}
	
	fout << best << endl;
	//fout << melhores[2][3][2][3] << endl;

	fout.close();
	fin.close();
	return 0;
}
