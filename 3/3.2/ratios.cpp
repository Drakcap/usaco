/*
ID: drakcap1
PROG: ratios
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
using namespace std;


ofstream fout("ratios.out");
ifstream fin("ratios.in");

struct Mistura {
	int um;
	int dois;
	int tres;
} misturas[3];

int um, dois, tres;


int
main()
{
	fin >> um >> dois >> tres;
	
	for (int i = 0; i < 3; i++) {
		fin >> misturas[i].um >> misturas[i].dois >> misturas[i].tres;
	}
	
	int melhor_soma = -1, quant1 = 0, quant2 = 0, quant3 = 0, ratio = 0;
	int soma, q1, q2, q3, ratio1, ratio2, ratio3;
	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 100; k++) {
				if (i == 0 && j == 0 && k == 0) continue;
			
				soma = i + j + k;
				q1 = misturas[0].um*i + misturas[1].um*j + misturas[2].um*k;
				q2 = misturas[0].dois*i + misturas[1].dois*j + misturas[2].dois*k;
				q3 = misturas[0].tres*i + misturas[1].tres*j + misturas[2].tres*k;
				
				if (um == 0) {
					if (q1 != 0) {
						continue;
					}
					ratio1 = 0;
				} else ratio1 = q1 / um;
				
				if (dois == 0) {
					if (q2 != 0) {
						continue;
					}
					ratio2 = 0;
				} else ratio2 = q2 / dois;
				
				if (tres == 0) {
					if (q3 != 0) {
						continue;
					}
					ratio3 = 0;
				} else ratio3 = q3 / tres;
				
				if ( (soma < melhor_soma || melhor_soma == -1) && (ratio1 == ratio2 || um == 0 || dois == 0) && 
					(ratio2 == ratio3 || dois == 0 || tres == 0) && (ratio1 == ratio3 || um == 0 || tres == 0)
					&& (um == 0 || q1 % um == 0) && (dois == 0 || q2 % dois == 0) && (tres == 0 || q3 % tres == 0)) {
					melhor_soma = soma;
					quant1 = i; quant2 = j; quant3 = k; ratio = ratio1;
				}
			}
		}
	}
	
	if (melhor_soma == -1) {
		fout << "NONE" << endl;
	} else {
		fout << quant1 << " " << quant2 << " " << quant3 << " " << ratio << endl;
	}

	fout.close();
	fin.close();
	return 0;
}
