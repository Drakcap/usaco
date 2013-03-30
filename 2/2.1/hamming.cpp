/*
ID: drakcap1
PROG: hamming
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

ofstream fout("hamming.out");
ifstream fin("hamming.in");

#define MAXN 64

short solucao[64];
int tamS;

int N, B, D;

short
distancia(short n1, short n2)
{
 short dist = 0;
 short mask = 1;
 
 for (int i = 0; i < B; i++) {
     if ((n1 & mask) != (n2 & mask)) {
        ++dist;       
     }
     mask = mask << 1;
         
 }
 
 return dist;                
                
}

bool
interessa(short num)
{
    for (int i = 0; i < tamS; i++) {
        if (! (distancia(solucao[i], num) >= D)) {
              return false;
        }     
    }                
    return true;            
                
}




int
main()
{
      fin >> N >> B >> D;
      
      short maxLoop = (short)pow(2.0,B);
      bool serve = false;
      
      while (! serve)
      {
            for (int i = 0; i < maxLoop; i++) {
                if (interessa(i)) {
                   solucao[tamS++] = i;                  
                }    
                if (tamS == N) {
                         serve = true;
                         break;
                }
            }      
            
      }
      int i;
      for (i = 1; i <= N; i++) {
          fout << solucao[i-1];
          
          if (i % 10 == 0) {
               fout << endl;
          }
          else if (i != N) {
               fout << " ";
          }
      }
      
      if (! ( (i-1) % 10 == 0))
         fout << endl;
      
      
      fout.close();
      fin.close();
      return 0;
}
