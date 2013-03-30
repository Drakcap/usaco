/*
ID: drakcap1
PROG: kimbits
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


ofstream fout("kimbits.out");
ifstream fin("kimbits.in");

int N, L;
long long I;

string res = "";

long long gcd(long long a, long long b) {
	while(b)  swap(a%=b, b); 
	return a;
}
 
void divbygcd(long long & a,long long & b) 
{
  long long g=gcd(a,b);
  a/=g;
  b/=g;
}
 
long long 
comb(int n,int k)
{
  long long numerator = 1 , denominator = 1 , toMul , toDiv , i ;
 
  if ( k > n/2 ) k = n - k ; /* use smaller k */
 
  for ( i = k ; i ; i-- ) 
  {
    toMul = n - k + i ;
    toDiv = i ;
    /* always divide before multiply */
    divbygcd( toMul , toDiv );
    divbygcd( numerator , toDiv );
    divbygcd( toMul , denominator );
    numerator *= toMul ;
    denominator *= toDiv ;
  }
 
  return numerator / denominator;
}

void
go(int ix, long long conta, int uns) 
{
	if (ix >= N) return;
	
	long long novo_conta = conta;
	
	int sobra = N-ix-1;
	int restoUns = L-uns;
	int k = 0;
	
	while (k <= restoUns && k <= sobra) {
		novo_conta += comb(sobra, k);
		++k;
	}
	
	//fout << ix << " " << novo_conta << endl;
	
	if (novo_conta >= I) {
		res = res + "0";
		go(ix+1, conta, uns);
	}
	else {
		res = res + "1";
		go(ix+1, novo_conta, uns+1);
	}


}

int
main()
{
	fin >> N >> L >> I;
	
	go(0, 0, 0);
	
	fout << res << endl;

	fout.close();
	fin.close();
	return 0;
}
