/*
ID: drakcap1
PROG: range
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

ofstream fout("range.out");
ifstream fin("range.in");

int N;
int mapa[250][250];
int pos[250][250];
int areas[251];

int
main()
{
	fin >> N;
	string temp;
	
	for (int i = 0; i < N; i++) {
		fin >> temp;
		for (int j = 0; j < N; j++) {
			mapa[i][j] = temp[j] - '0';
		}
	}
	
	//primeira linha
	for (int j = 0; j < N; j++) {
		pos[0][j] = mapa[0][j];
	}
	
	//primeira coluna
	for (int i = 0; i < N; i++) {
		pos[i][0] = mapa[i][0];
	}
	
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			if (mapa[i][j]) {
				if (pos[i][j-1] && pos[i-1][j-1] && pos[i-1][j]) {
					pos[i][j] = min(min(pos[i][j-1], pos[i-1][j-1]), pos[i-1][j]) + 1;
					for (int k = 2; k <= pos[i][j]; k++) {
						++areas[k];
					}

				} else {
					pos[i][j] = 1;
				}
			
			}
		}
	}
	
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fout << pos[i][j] << " ";
		}
		fout << endl;
	}*/
	
	for (int i = 0; i <= 250; i++) {
		if (areas[i]) {
			fout << i << " " << areas[i] << endl;
		}
	}

	fout.close();
	fin.close();
	return 0;
}
