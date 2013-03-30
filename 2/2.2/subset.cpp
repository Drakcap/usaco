/*
ID: drakcap1
PROG: subset
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

ofstream fout("subset.out");
ifstream fin("subset.in");

#define MAX 391

int N;
//int nManeiras;
long long nManeiras[MAX];
int metade;

void
pesquisa()
{
          long long temp[MAX];
          
          for (int i = 1; i <= N; i++) {
              memcpy(temp, nManeiras, sizeof(long long)*(metade+1));
              ++temp[i]; 
              for (int j = 1; j <= metade; j++) {
                  if (nManeiras[j] > 0 && i+j <= metade) {
                       //fout << i << " " << j << endl;
                       //fout << nManeiras[j] << endl;
                       //fout << temp[i+j] << endl << endl;            
                                     
                       temp[i+j] += nManeiras[j];     
                  }
                  
              
              }
              /*fout << "num " << i << ": ";
              for (int k = 0; k <= metade; k++) {
                  fout << temp[k] << " ";
              }fout << endl;*/
                  
              memcpy(nManeiras, temp, sizeof(long long)*(metade+1));
          }
      
             
}

int
main()
{
      
      fin >> N;
      
      int soma_total = N * (N+1) / 2;
      
      if (soma_total % 2 != 0) {
         fout << 0 << endl;
         fout.close();
         fin.close();
         return 0;               
      }
      
      metade = soma_total / 2;
      
      pesquisa();
          
      fout << nManeiras[metade] / 2 << endl;
      
      fout.close();
      fin.close();
      return 0;
}
