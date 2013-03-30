/*
ID: drakcap1
PROG: nocows
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

ofstream fout("nocows.out");
ifstream fin("nocows.in");

int N, K;

int maneiras[200][100];  //maneiras[N][K] -> maneiras de construir uma arvore de altura ate' K com N nos



int
main()
{
      
      fin >> N >> K;
      
      //com um no so ha uma maneira de construir a arvore
      for (int i = 1; i <= K; i++) {
          maneiras[1][i] = 1;
      }
      
      for (int k = 2; k <= K; k++) {
          for (int n = 2; n <= N; n ++) {
              for (int i = 1; i < n; i++) {
                  //long long unsigned temp = maneiras[i][k-1] * maneiras[n-i-1][k-1];
                  
                  //if (k == K)
                     //fout << temp << " " << maneiras[i][k-1] << " " << maneiras[n-i-1][k-1] << endl;
                     
                  maneiras[n][k] += maneiras[i][k-1] * maneiras[n-i-1][k-1];
                  maneiras[n][k] %= 9901;
                  //fout << "n k i: " << n << " " << k << " " << i << " " <<  maneiras[i][k-1] << " " << maneiras[n-i][k-1] << endl;    
              } 
              
          }
      }
      
      //fout << maneiras[N][K] << endl;
      //fout << maneiras[N][K-1] << endl;
      
      if (maneiras[N][K] - maneiras[N][K-1] < 0) {
         fout << 9901 + maneiras[N][K] - maneiras[N][K-1] << endl;
      }
      else
          fout << maneiras[N][K] - maneiras[N][K-1] << endl;
      
      fout.close();
      fin.close();      
      return 0;
}
