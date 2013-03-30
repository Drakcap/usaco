/*
ID: drakcap1
PROG: fence9
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

ofstream fout("fence9.out");
ifstream fin("fence9.in");

#define compare(x,y) (fabs(x-y) <= 0.00000001 ? true : false)
#define X 0
#define Y 1
#define EPS 0.0000000000001

struct Recta {
	double p1[2], p2[2];
	double m, b;
	
	void
	calcMB() {
		m = (p1[Y] - p2[Y]) / (p1[X] - p2[X]);
		b = p1[Y] - m*p1[X];
	}
	
	double
	calcX(double y) {
		if (compare(p1[X], p2[X])) { //x constante (declive infinito -> recta vertical)
			return p1[X];
		}
		return (y-b)/m;
	}

} rectas[2];

int n, m, p, res;

int
main()
{
	fin >> n >> m >> p;
	rectas[0].p1[X] = 0.0;
	rectas[0].p1[Y] = 0.0;
	rectas[0].p2[X] = rectas[1].p1[X] = n;
	rectas[0].p2[Y] = rectas[1].p1[Y] = m;
	
	rectas[1].p2[X] = p;
	rectas[1].p2[Y] = 0.0;
	
	rectas[0].calcMB();
	rectas[1].calcMB();
	
	int x1, x2;
	double temp;
	for (int i = 1; i < m; i++) {
		x1 = (int)(rectas[0].calcX(i)+EPS);
		
		x2 = (int)(rectas[1].calcX(i)+EPS);
		temp = rectas[1].calcX(i);
		
		if (fabs((temp-x2)<EPS)) {
			--x2;
		}
		
		res += (x2-x1);
	}
	fout << res << endl;

	fout.close();
	fin.close();
	return 0;
}
