/*
ID: drakcap1
PROG: rockers
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

ofstream fout("rockers.out");
ifstream fin("rockers.in");

int N, M, T;
int anteriores[20][20];
int best[20][21][20];
int musicas[20];
int res;

void
dp()
{
	for (int i = 0; i < M; i++) { //disco
		for (int j = 0; j <= T; j++) { //minuto
			for (int k = 0; k < N; k++) { //musica
				if (i && j == 0) {	//inicio de um disco que nao é o primeiro
					best[i][j][k] = anteriores[i-1][k];
				} else {
					if (j - musicas[k] >= 0) {
						best[i][j][k] = (k == 0 ? 1 : best[i][j-musicas[k]][k-1] + 1);
						if (best[i][j][k] > anteriores[i][k]) {
							anteriores[i][k] = best[i][j][k];
						}
						if (best[i][j][k] > res) {
							res = best[i][j][k];
						}
					} else if (k != 0) {
						best[i][j][k] = best[i][j][k-1];
					}
				}
			}
		}
	}
}

void
printdp()
{
	for (int i = 0; i < M; i++) { //disco
		for (int j = 0; j <= T; j++) { //minuto
			for (int k = 0; k < N; k++) { //musica
				fout << "disco " << i << " " << " minuto " << j << " musica " << k << " :" << best[i][j][k] << " ";
				fout << endl;
			}
			fout << endl;
		}
		fout << endl;
	}
}

int
main()
{

	fin >> N >> T >> M;
	
	for (int i = 0; i < N; i++) {
		fin >> musicas[i];
	}
	
	dp();
	//printdp();
	
	fout << res << endl;

	fout.close();
	fin.close();
	return 0;
}
