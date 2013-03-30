/*
ID: drakcap1
PROG: money
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

ofstream fout("money.out");
ifstream fin("money.in");

#define MAXM 25
#define MAXTOTAL 10000

int moedas[MAXM];
int nMoedas;
int total;
long long maneiras[MAXTOTAL+1];


int
main()
{
      fin >> nMoedas;
      fin >> total;
      
      for (int i = 0; i < nMoedas; i++) {
          fin >> moedas[i];
      }
      
      //maneiras[0] = 1;
          
      for (int i = 0; i < nMoedas; i++) {
          if (moedas[i] <= total) {
             ++maneiras[moedas[i]];
          }
          
          for (int j = 1; j <= total; j++) {
              if (maneiras[j] > 0 && (moedas[i] + j) <= total) {
                 maneiras[moedas[i]+j] += maneiras[j];                
              }     
          }
              
              
      }
          
      fout << maneiras[total] << endl;
      
      fout.close();
      fin.close();
      return 0;
}
