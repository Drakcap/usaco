/*
ID: drakcap1
PROG: comehome
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

ofstream fout("comehome.out");
ifstream fin("comehome.in");

#define MAXV 52
#define INF 2000000000

struct No {
      map<int, int> ligacoes;
      int dist; 
      //bool naFila;
      
      bool operator<(const No& no) const
      {
           return dist > no.dist;
      }        
};

No nos[MAXV];
int P;

int
ltn(char l)
{
   if (l >= 'A' && l <= 'Z') {
         return l - 'A';
   }
   else
       return l-'a'+26;         
           
}

void
dijkstra()
{
     int source = ltn('Z');
     
     for (int i = 0; i < MAXV; i++) {
         nos[i].dist = INF;
     }
     
     nos[source].dist = 0;
     
     priority_queue<No> fila;
     //nos[source].naFila = true;
     fila.push(nos[source]);
     
     No prox;
     map<int, int>::iterator it;
     
     while (! fila.empty()) {
         prox = fila.top();
         fila.pop();
         
         it = prox.ligacoes.begin();
         
         for (  ; it != prox.ligacoes.end(); it++) {
             if (prox.dist + it->second < nos[it->first].dist) {
                nos[it->first].dist = prox.dist + it->second;
                
                //if (! nos[it->first].naFila) {
                   fila.push(nos[it->first]);      
                //}                                  
             } 
             
             
         }
         //nos[prox].naFila = false;  
           
           
     }          
          
          
}





int
main()
{
      for (int i = 0; i < MAXV; i++) {
          for (int j = 0; j < MAXV; j++) {
           nos[i].ligacoes[j] = INF;
           //nos[i].naFila = false;    
          }
      }
      
      fin >> P;
      
      char l1, l2;
      int peso;
      int v1, v2;
      
      for (int i = 0; i < P; i++) {
          fin >> l1 >> l2 >> peso;
          if (l1 == l2) continue;
          
          v1 = ltn(l1);
          v2 = ltn(l2);
          
          if (nos[v1].ligacoes[v2] == 0 || peso < nos[v1].ligacoes[v2]) {
             nos[v1].ligacoes[v2] = peso;
             nos[v2].ligacoes[v1] = peso;               
          }
            
      }
       
      dijkstra();
      
      int res = INF;
      char r;
      
      for (int i = 0; i < 25; i++) {
          if (nos[i].dist < res) {
               res = nos[i].dist;
               r = 'A' + i;
          }     
          
      }
           
      
      fout << r << " " << res << endl;
       
      
      fout.close();
      fin.close();
      return 0;
}
