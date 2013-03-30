/*
ID: drakcap1
PROG: game1
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

ofstream fout("game1.out");
ifstream fin("game1.in");

int tabuleiro[100];
int best[100][100];
int somas[100][100];
int N;

void
dp()
{
	for (int i = 0; i < N; i++) {
		best[i][i] = tabuleiro[i];
	}
	for (int i = 0; i < N; i++) {
		best[i][i+1] = max(tabuleiro[i], tabuleiro[i+1]);
	}
	for (int i = 0; i < N; i++) {
		somas[i][i] = tabuleiro[i];
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			somas[i][j] = somas[i][j-1] + tabuleiro[j];
		}
	}
	
	for (int i = N-2; i >= 0; i--) {
		for (int j = i+2; j < N; j++) {
			best[i][j] = somas[i][j] - min(best[i+1][j], best[i][j-1]);
		}
	}
	

	
}


int
main()
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> tabuleiro[i];
	}
	
	dp();
	
	fout << best[0][N-1] << " " << somas[0][N-1] - best[0][N-1] << endl;

	fout.close();
	fin.close();
	return 0;
}
