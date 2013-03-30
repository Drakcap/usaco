/*
ID: drakcap1
PROG: fence6
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
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <sstream>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;

#define FOR(i,a,b) for(int i = a, n = b; i < n; i++)
#define SET(a, v) memset(a, v, sizeof(a))
#define EPS 0.000000001
#define FIND(s, v) ((s).find(v) != (s).end())

ofstream fout("fence6.out");
ifstream fin("fence6.in");

struct Seg {
    int num, len;
    int no1, no2;
    set<int> side1, side2;
} segs[110];

struct No {
    int ligacoes[210];
    int tamLig[210];
    int nLig;
    char visited;
} nos[210];


int N;
int best = -1;
int nNos;


void read_input()
{
    int num, side1, side2, temp1, temp2;

    fin >> N;
    
    FOR(i, 0, N) {
        fin >> num;
        --num;
        segs[num].num = num;
        fin >> segs[num].len >> side1 >> side2;
        segs[num].no1 = segs[num].no2 = -1;
        FOR(j, 0, side1) {
            fin >> temp1;
            segs[num].side1.insert(temp1-1);
        }
        
        FOR(j, 0, side2) {
            fin >> temp2;
            segs[num].side2.insert(temp2-1);
        }
    }
    
}

void remove_lig(int seg, int lig, int nNos)
{
    if (FIND(segs[seg].side1, lig)) {
        segs[seg].no1 = nNos;
    } else {
        segs[seg].no2 = nNos;
    }
}

void build_graph()
{
    set<int>::iterator it;
    FOR(i, 0, N) {
        //this side isn't still a node
        if (segs[i].no1 == -1) {
            nos[nNos].nLig = 0;
            nos[nNos].visited = 0;
            segs[i].no1 = nNos;
            it = segs[i].side1.begin();
            for ( ; it != segs[i].side1.end(); it++) {
                remove_lig(*it, i, nNos);
            }
            ++nNos;
        }
        //this side isn't still a node
        if (segs[i].no2 == -1) {
            nos[nNos].nLig = 0;
            nos[nNos].visited = 0;
            segs[i].no2 = nNos;
            it = segs[i].side2.begin();
            for ( ; it != segs[i].side2.end(); it++) {
                remove_lig(*it, i, nNos);
            }
            ++nNos;
        }

        //connects the two nodes
        
        if (nos[segs[i].no1].nLig || ! binary_search(nos[segs[i].no1].ligacoes, nos[segs[i].no1].ligacoes+nos[segs[i].no1].nLig, segs[i].no2)) {
            //fout << nos[segs[i].no1].nLig << endl;
            nos[segs[i].no1].tamLig[nos[segs[i].no1].nLig] = segs[i].len;
            nos[segs[i].no2].tamLig[nos[segs[i].no2].nLig] = segs[i].len;
            nos[segs[i].no1].ligacoes[nos[segs[i].no1].nLig++] = segs[i].no2;
            nos[segs[i].no2].ligacoes[nos[segs[i].no2].nLig++] = segs[i].no1;
        }
        
    }

}

void print_graph()
{
    FOR(i, 0, nNos) {
        fout << "node: " << i << " has the following connections: " << endl;
        
        FOR(j, 0, nos[i].nLig) {
            fout << nos[i].ligacoes[j] << " with weight " << nos[i].tamLig[j] << endl;
        }
        fout << endl;
    }
}

void solveAux(int no, int size, int prev, int inicial)
{
    //fout << "visiting " << no << " " << size << " " << inicial << endl;
    if (best != -1 && size > best) {
        return;
    }
    
    //loop that matters
    if (size != 0 && no == inicial) {
        if (size < best || best == -1) {
            //fout << "inicial: " << inicial << " size: " << size << endl;
            best = size;
            return;
        }
    }
    
    
    FOR(i, 0, nos[no].nLig) {
        if ((nos[nos[no].ligacoes[i]].visited  > 0 && nos[no].ligacoes[i] != inicial) || nos[no].ligacoes[i] == prev) continue;
        nos[nos[no].ligacoes[i]].visited = 2;
        solveAux(nos[no].ligacoes[i], size+nos[no].tamLig[i], no, inicial);
        nos[nos[no].ligacoes[i]].visited = 0;
    }
    
}

void solve()
{
    FOR(i, 0, nNos) {
        nos[i].visited = 1;
        solveAux(i, 0, -1, i);        
    }
}

int
main()
{
    read_input();
    build_graph();
    solve();
    
    fout << best << endl;

	fout.close();
	fin.close();
	return 0;
}
