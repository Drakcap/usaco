/*
ID: drakcap1
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

ofstream fout("frac1.out");
ifstream fin("frac1.in");

#define MAX 160

struct Fraccao {
       int num;
       int denum;
       double valor;
       
       bool operator<(const Fraccao &f) const
       {
            return (valor < f.valor);   
       }
       
};

Fraccao fracs[MAX*MAX];
int nFracs;
int N;

int
gcd(int a, int b)
{
 while(b) swap(a %= b, b);
 
 return a;        
        
}

int
main()
{
      fin >> N;
      
      fracs[0].num = 0;
      fracs[0].denum = 1;
      fracs[0].valor = 0.0;
      
      fracs[1].num = 1;
      fracs[1].denum = 1;
      fracs[1].valor = 1.0;
      
      nFracs = 2;
      
      
      for (int i = 2; i <= N; i++) { //denum
          for (int j = 1; j < i; j++) { //num
              if (gcd(i, j) == 1) {
                 fracs[nFracs].num = j;
                 fracs[nFracs].denum = i;
                 fracs[nFracs].valor = (float)j / (float)i;
                 ++nFracs;           
              } 
              
          }    
          
      }
      
      sort(fracs, fracs + nFracs);
      
      
      for (int i = 0; i < nFracs; i++) {
          fout << fracs[i].num << "/" << fracs[i].denum << endl;   
      }
      
      fout.close();
      fin.close();
      return 0;
}
