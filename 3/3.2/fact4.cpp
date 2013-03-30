/*
ID: drakcap1
PROG: fact4
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


ofstream fout("fact4.out");
ifstream fin("fact4.in");



int N;

int
main()
{

	fin >> N;
	int fact = 1;
	
	
	for (int i = 2; i <= N; i++) {
		fact *= i;
		while (fact % 10 == 0) {
			fact = fact / 10;
		}
		if (fact > 1000000) {
			fact = fact % 1000000;
		}
		//fout << fact << endl;
	}
	fout << fact % 10 << endl;

	fout.close();
	fin.close();
	return 0;
}
