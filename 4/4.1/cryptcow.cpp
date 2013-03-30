/*
ID: drakcap1
PROG: cryptcow
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

ofstream fout("cryptcow.out");
ifstream fin("cryptcow.in");

#define NAO -1
#define IGUAL 0
#define SIM 1

char msg[100] = "Begin the Escape execution at the Break of Dawn";
int sizeMsg = strlen(msg);
set<string> visited;

void
swap(const char* actual, char* nova, int C, int O, int W)
{
	for (int i = 0; i < C; i++) {
		nova[i] = actual[i];
	}
	int ixnova = C;
	
	for (int i = O+1; i < W; i++, ixnova++) {
		nova[ixnova] = actual[i];
	}
	
	for (int i = C+1; i < O; i++, ixnova++) {
		nova[ixnova] = actual[i];
	}
	
	for (int i = W+1; actual[i] != 0; i++, ixnova++) {
		nova[ixnova] = actual[i];
	}
	nova[ixnova] = 0;
}

int
valid(const char* m, int size) 
{
	int ix = 0;
	while(m[ix] != 0 && m[ix] != 'C') {
		if(m[ix] != msg[ix]) {
			return NAO;
		}
		++ix;
	}
	if (m[ix] == 0) {
		return IGUAL;
	}
	ix = size-1;
	int ixmsg = sizeMsg-1;
	
	while(ix && ixmsg && m[ix] != 'W') {
		if (m[ix] != msg[ixmsg]) {
			return NAO;
		}
		--ix;
		--ixmsg;
	}
	return SIM;
}

int
pesquisa(const char* m, int size, int count, int ixi, int ixf)
{
	int ret = valid(m, size);
	if (ret == IGUAL) {
		return count;
	} else if (ret == NAO) {
		return -1;
	}
	if (visited.find(string(m)) != visited.end()) {
		return -1;
	}
	
	visited.insert(string(m));
	fout << m << endl;
	
	int C, O, W;
	char novom[100];
	bool inicio = true, fim = true;
	int novosize = size-3;

	for (C = ixi; C < size; C++) {
		if(m[C] != 'C' && inicio) {
			++ixi;
		} else {
			inicio = false;
			for (O = C+1; O < size; O++) {
				if (m[O] == 'O') {
					for (W = ixf; W >= 0; W--) {
						if(m[W] != 'W' && fim) {
							--ixf;
						} else {
							fim = false;
							swap(m, novom, C, O, W);
							if ((ret = pesquisa(novom, novosize, count+1, ixi, ixf)) >= 0) {
								return ret;
							}
						}
					
					}
				}
			}
		}
	
	}
	return -1;

}

int
main()
{

	string in, temp;
	fin >> in;
	
	while (fin >> temp) {
		in += " ";
		in += temp;
	}
	
	char coiso[100];
	unsigned i;
	for (i = 0; i < in.size(); i++) {
		coiso[i] = in[i];
	}
	coiso[i] = 0;
	
	//fout << in << endl;
	int n = pesquisa(in.c_str(), in.size(), 0, 0, in.size());
	
	if (n >= 0) {
		fout << 1 << " " << n << endl;
	} else {
		fout << 0 << " " << 0 << endl;
	}


	fout.close();
	fin.close();
	return 0;
}
