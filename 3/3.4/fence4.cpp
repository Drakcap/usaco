/*
ID: drakcap1
PROG: fence4
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

ofstream fout("fence4.out");
ifstream fin("fence4.in");

#define compare(x,y) (fabs(x-y) <= 0.00000001 ? true : false)
#define X 0
#define Y 1
#define NDIV 1000.0

struct Fence {
	double p1[2];
	double p2[2];
	bool visible;
	int ix1, ix2;
	double m, b;
	
	void
	calcMB() {
		m = (p1[Y] - p2[Y]) / (p1[X] - p2[X]);
		b = p1[Y] - m*p1[X];
	}
	
	double
	calcY(double x) {
		/*if (compare(p1[Y], p2[Y])) { //x constante (declive infinito -> recta vertical)
			return p1[Y];
		}*/
		if (fabs(m) <= 0.00000000001) { //y constante (declive 0 -> recta horizontal )  
			return p1[Y];
		}
		return m*x+b;
	}
	
	double
	calcX(double y) {
		/*if (m <= 0.00000000001) { //y constante (declive 0 -> recta horizontal )  
			return p1[X];
		}*/
		if (compare(p1[X], p2[X])) { //x constante (declive infinito -> recta vertical)
			return p1[X];
		}
		return (y-b)/m;
	}
	
	bool operator<(const Fence &f) const {
		if (ix2 != f.ix2) {
			return ix2 < f.ix2;
		}
		return ix1 < f.ix1;
	}
} fences[200];

int N;
double observer[2];
int nvisi;
set<Fence> sol;

bool
sameside(double a[2], double b[2], double c[2], double d[2])
{
	return ( (b[X] - a[X])*(c[Y] - a[Y]) - (b[Y] - a[Y])*(c[X] - a[X])) *
			( (b[X] - a[X])*(d[Y] - a[Y]) - (b[Y] - a[Y])*(d[X] - a[X])) >= 0;
}

bool
cross(Fence &f1, Fence &f2)
{
	return (! sameside(f1.p1, f1.p2, f2.p1, f2.p2) && ! sameside(f2.p1, f2.p2, f1.p1, f1.p2));
}

bool
paralel(Fence &f1, Fence &f2)
{
	double ux = f1.p1[X]-f1.p2[X];
	double uy = f1.p1[Y]-f1.p2[Y];
	double vx = f2.p1[X]-f2.p2[X];
	double vy = f2.p1[Y]-f2.p2[Y];
	return compare((ux*vy-uy*vx),0);
}

bool
processFence(Fence &f, int i)
{
	if (fences[i].visible) {
		return true;
	}
	if (paralel(fences[i], f)) {
		return false;
	}
	
	if(compare(f.p2[X], observer[X]) ||
		compare(f.p2[Y], observer[Y])) {
		return false;
	}

	fences[i].visible = true;
	for (int j = 0; j < N; j++) {
		if (j != i && cross(f, fences[j])) {
			fences[i].visible = false;
			break;
		}
	}
	return false;
}

int
main()
{
	fin >> N >> observer[X] >> observer[Y];
	
	fin >> fences[0].p1[X] >> fences[0].p1[Y];
	fences[0].visible = false;
	fences[0].ix1 = 0;
	fences[0].ix2 = 1;
	
	for (int i = 1; i < N; i++) {
		fin >> fences[i].p1[X] >> fences[i].p1[Y];
		fences[i].visible = false;
		fences[i-1].p2[X] = fences[i].p1[X];
		fences[i-1].p2[Y] = fences[i].p1[Y];
		fences[i].ix1 = i;
		fences[i].ix2 = i+1;
		fences[i-1].calcMB();
	}
	
	swap(fences[N-1].p1[X], fences[N-1].p2[X]);
	swap(fences[N-1].p1[Y], fences[N-1].p2[Y]);
	swap(fences[N-1].ix1, fences[N-1].ix2);
	fences[N-1].ix1 = 0;
	fences[N-1].calcMB();
	
	for (int i = 0; i < N; i++) {
		for (int j = i+2; j < N; j++) {
			if (cross(fences[i], fences[j])) {
				fout << "NOFENCE";
				return 0;
			}
		}
	}
	
	Fence f;
	f.p1[X] = observer[X]; f.p1[Y] = observer[Y];
	double minx, maxx, inc;
	bool y = false;
	int coord = X;
	
	for (int i = 0; i < N; i++) {
		
		//primeiro endpoint da fence
		/*f.p2[X] = fences[i].p1[X];
		f.p2[Y] = fences[i].p1[Y];
		processFence(f, i);
		
		//segundo endpoint da fence
		f.p2[X] = fences[i].p2[X];
		f.p2[Y] = fences[i].p2[Y];
		processFence(f, i);*/
		y = (fences[i].p1[X] == fences[i].p2[X]);
		coord = (y ? Y : X);
		
		minx = (fences[i].p1[coord] > fences[i].p2[coord] ? fences[i].p2[coord] : fences[i].p1[coord]);
		maxx =  (fences[i].p1[coord] < fences[i].p2[coord] ? fences[i].p2[coord] : fences[i].p1[coord]);
		inc = (maxx-minx)/NDIV;
		minx += inc;
		
		for ( ; minx < maxx; minx += inc) {
			f.p2[coord] = minx;
			f.p2[1-coord] = (!y ? fences[i].calcY(minx) : fences[i].calcX(minx));
			/*if(i == 0) {
				//fout << fences[i].p1[X] << " " << fences[i].p1[Y] << " " << fences[i].p2[X] << " " << fences[i].p2[Y] << endl;
				//fout << fences[i].m << endl;
				fout << f.p2[X] << " " << f.p2[Y] << " " << y << " " << minx << " " << fences[i].calcY(minx) << endl;
			}*/
			if (processFence(f, i)) break;
		}

		
		if (fences[i].visible) {
			++nvisi;
			sol.insert(fences[i]);
		}
		
	}
	
	fout << nvisi << endl;
	for (set<Fence>::iterator it = sol.begin(); it != sol.end(); it++) {
		fout << it->p1[X] << " " << it->p1[Y] << " " << it->p2[X] << " " << it->p2[Y] << endl;
	}

	fout.close();
	fin.close();
	return 0;
}
