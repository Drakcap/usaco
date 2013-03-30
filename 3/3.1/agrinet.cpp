/*
ID: drakcap1
PROG: agrinet
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <cmath>
#include <iomanip>
#include <queue>
using namespace std;

ofstream fout("agrinet.out");
ifstream fin("agrinet.in");

#define MAXN 100
#define INF 200000

struct No {
       int ligacoes[MAXN];
       bool naMst;     
       int dist;
       int num;
       
       bool operator<(const No &n) const
       {
        return dist > n.dist;     
       }
};

No nos[MAXN];
int N;
int res;

void
prim()
{
      nos[0].dist = 0;
      priority_queue<No> fila;
      
      fila.push(nos[0]);
      No prox;
      
      while (! fila.empty())
      {
              prox = fila.top();
              fila.pop();
              
              //fout << prox.num << " " << prox.dist << endl;
              
              if (nos[prox.num].naMst) continue;
              
              nos[prox.num].naMst = true;
              
              res += prox.dist;
              
              for (int i = 0; i < N; i++) {
                  if (! nos[i].naMst && prox.ligacoes[i] < nos[i].dist) {
                     nos[i].dist = prox.ligacoes[i];
                     fila.push(nos[i]);      
                  }    
              }   
            
      }
      
}


int
main()
{
      fin >> N;
      
      for (int i = 0; i < N; i++) {
          nos[i].naMst = false;
          nos[i].num = i;
          nos[i].dist = INF;
          for (int j = 0; j < N; j++) {
              fin >> nos[i].ligacoes[j];    
          }
      }
      
      prim();
      
      fout << res << endl;
      
      
      fout.close();
      fin.close();
      return 0;      
      
}
