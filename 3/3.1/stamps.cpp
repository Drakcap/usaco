/*
ID: drakcap1
PROG: stamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <stdlib.h>
#include <set>
#include <cmath>
#include <iomanip>
#include <queue>
#include <vector>
using namespace std;

ofstream fout("stamps.out");
ifstream fin("stamps.in");

#define MAXK 200
#define MAXN 50
#define MAXSTAMP 10000
#define MAXTOTAL 2000000

short stamps[MAXN];
int K;
int N;
int dp[MAXTOTAL+1];


int
main()
{

	fin >> K >> N;
	for (int i = 0; i < N; i++) fin >> stamps[i];
	
	for (int i = 0; i < N; i++) {
		dp[stamps[i]] = 1;
	}
	
	for (int i = 1; i <= MAXTOTAL; i++) {
		for (int j = 0; j < N; j++) {
			if (i - stamps[j] > 0 && dp[i-stamps[j]] > 0 && (dp[i-stamps[j]]+1 < dp[i] || dp[i] == 0) && dp[i-stamps[j]] < K) {
				dp[i] = dp[i-stamps[j]] + 1;
			}
		}
		if (! dp[i]) {
			fout << i-1 << endl;
			break;
		}
	}


	fout.close();
	fin.close();
	return 0;
}
