/*
ID: drakcap1
PROG: cowtour
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
using namespace std;

ofstream fout("cowtour.out");
ifstream fin("cowtour.in");

#define MAXN 150
#define INF -1.0

struct No {
       int locX, locY;
       int ligacoes[MAXN];
       int nLigacoes;
       int grupo;
       bool visited;
};

No nos[MAXN];
int nNos;

char linha[MAXN+1];

//para o floyd
double pesos[MAXN][MAXN];
double dist[MAXN][MAXN];

inline double
calc_dist(int x1, int y1, int x2, int y2)
{          
    return sqrt ( (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));                                         
}

void
le_input()
{
    fin >> nNos;
          
    for (int i = 0; i < nNos; i++) {
          fin >> nos[i].locX;
          fin >> nos[i].locY;
          nos[i].nLigacoes = 0;
          nos[i].visited = false;   
      }
      
      double dist;
      
      for (int i = 0; i < nNos; i++) {
          fin >> linha;
          for (int j = 0; j < nNos; j++) {
              if (linha[j] == '1') {
                 dist = calc_dist(nos[i].locX, nos[i].locY, nos[j].locX, nos[j].locY);
                 pesos[i][j] = dist;
                 pesos[j][i] = dist;          
                 nos[i].ligacoes[nos[i].nLigacoes++] = j;
                 nos[j].ligacoes[nos[j].nLigacoes++] = i;             
              }    
          }        
      }      
               
}

void
floyd()
{
      for (int i = 0; i < nNos; i++) {
          for (int j = 0; j < nNos; j++) {
              dist[i][j] = INF;
              
              if (i == j) dist[i][j] = 0.0;    
          }
      }
      
      for (int i = 0; i < nNos; i++) {
          for (int j = 0; j < nNos; j++) {
              if (pesos[i][j] != 0) {
                 dist[i][j] = pesos[i][j];                
              }    
          }
      }
      
      for (int k = 0; k < nNos; k++) {
          for (int i = 0; i < nNos; i++) {
              for (int j = 0; j < nNos; j++) {
                  if (dist[i][k] != INF && dist[k][j] != INF && (dist[i][k] + dist[k][j] < dist[i][j] || dist[i][j] == INF)) {
                     dist[i][j] = dist[i][k] + dist[k][j];
                     dist[j][i] = dist[i][k] + dist[k][j];               
                  }
              }
          }
      }        
       
}

void
print_dist()
{
     for (int i = 0; i < nNos; i++) {
         for (int j = 0; j < nNos; j++) {
             fout << dist[i][j] << " ";    
         }
         fout << endl;    
     }             
     fout << endl;
             
}


void
print_pesos()
{
   for (int i = 0; i < nNos; i++) {
         for (int j = 0; j < nNos; j++) {
             fout << pesos[i][j] << " ";    
         }
         fout << endl;    
     }
     fout << endl;          
             
}


int
main()
{
      
      le_input();
      
      //print_pesos();
      
      floyd();
      
      double maxD = 0.0;
      
      for (int i = 0; i < nNos; i++) {
          for (int j = 0; j < nNos; j++) {
              if (dist[i][j] > maxD) maxD = dist[i][j];
          }
      }
      
      
      double res = 1000000000.0;
      double d;
      double max_; // temp = 0.0,
       
      
      
      //tenta unir o no i com o no j
      for (int i = 0; i < nNos; i++) {
          double m = 0.0;
          
          //ve o no que esta mais afastado do no i
          for (int k = 0; k < nNos; k++) {
              if (k != i && dist[k][i] > m) {
                 m = dist[k][i];
                 //fout << k << " " << m << " " << grupos[0].nos[i] << endl;     
              }    
          }
          
          for (int j = 0; j < nNos; j++) {
              
              //i e j nao podem estar ligados
              if (dist[i][j] == INF) {
                  d = calc_dist(nos[i].locX, nos[i].locY,
                                nos[j].locX, nos[j].locY);
              }
              else continue;
                            
              //fout << d << endl;
              
              //if (d == 0.0) fout << i << " " << j << endl;
                            
              max_ = 0.0;
              
              //ve qual o no mais afastado de j
              for (int k = 0; k < nNos; k++) {
                  if (k != j && dist[j][k] > max_) {
                        max_ = dist[j][k];                              
                  }
                  //fout << temp << endl;
     
              }
              if (max_ + m + d < res) {
                      res = max_ + m + d;
                      //fout << max_ << " " << m << " " << d << endl;
                      //fout << i << " " << grupos[1].nos[j] << endl;
                      //fout << max_ << " " << m << " " << d << endl;
              }    
              
          }
          
      }
      fout.setf(ios::fixed);
      fout << setprecision(6) << (maxD > res ? maxD : res) << endl;
      
      //fout << calc_dist(30, 15, 25, 10) << endl;
      //fout << calc_dist(10, 10, 20, 10);
      // + calc_dist(20, 10, 10, 10) << endl;
      //print_dist();
      
      /*double m = 0.0;
      int i1, j1;
      
      for (int i = 0; i < nNos; i++) {
          for (int j = 0; j < nNos; j++) {
              if (dist[i][j] > m) {
                    m = dist[i][j];
                    i1 = i;
                    j1 = j;
              }
          }
      }
      fout << m << " " << i1 << " " << j1 << endl;*/ 
      
      fout.close();
      fin.close();
      return 0;
}
