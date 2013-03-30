/*
ID: drakcap1
PROG: holstein
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

ofstream fout("holstein.out");
ifstream fin("holstein.in");

#define MAXV 25
#define MAXF 15

struct Feed {
       int vit[MAXV];     
};

int vitaminas[MAXV];
Feed feeds[MAXF];
int nVit;
int nFeeds;
multiset<int> solucao;

bool
acabado(int* vitaminas)
{
    for (int i = 0; i < nVit; i++) {
        if (vitaminas[i] > 0) {
            return false;
        }    
    }         
    return true;        
}

void
aplicaFeed(int* temp, int* vitaminas, int feed)
{
     for (int i = 0; i < nVit; i++) {
         temp[i] = vitaminas[i] - feeds[feed].vit[i];
         
         if (temp[i] < 0) {
               temp[i] = 0;
         }    
         
     }                    
}

bool
melhor_(int* a, int* b)
{
     int soma1 = 0, soma2 = 0;
     
     for (int i = 0; i < nVit; i++) {
         soma1 += a[i];
         soma2 += b[i];    
     }
     return soma1 < soma2;    
}


/*void
pesquisa()
{
          int melhor[MAXV];
          int temp[MAXV];
          int mFeed;
          
          memcpy(melhor, vitaminas, sizeof(int)*nVit);

          while(!acabado()) {
                            
               for (int i = 0; i < nFeeds; i++) {
                   aplicaFeed(temp, i);
                   if (melhor_(temp, melhor)) {
                      mFeed = i;
                      memcpy(melhor, temp, sizeof(int)*nVit);                
                   }    
               }
               solucao.insert(mFeed); 
                            
               
               memcpy(vitaminas, melhor, sizeof(int)*nVit);             
          }          
               
}*/

void
imprime_sol(multiset<int> &sol)
{
      multiset<int>::iterator it = sol.begin();
      
      if (sol.size() > 0) {
         fout << *it + 1;
         ++it;
      }
      
      
      for ( ; it != sol.end(); it++) {
          fout << " " << *it + 1;
      }
      fout << endl;
}

void
pesquisa(int* vits, multiset<int> &sol, int feed)
{
    //static int cou = 0;
    //fout << cou++ << endl;
    
    
    //imprime_sol(sol);
    /*fout << endl;
    for (int i = 0; i < nVit; i++) {
        fout << vits[i] << " ";
    }
    fout << endl << endl;*/
     
    if (acabado(vits)) {              
       if (sol.size() < solucao.size() || solucao.size() == 0) {          
          solucao = sol;               
       }                   
       else if (sol.size() == solucao.size()) {
            multiset<int>::iterator it = sol.begin(), it2 = solucao.begin();
            
            for ( ; it != sol.end(); it++, it2++) {
                if (*it < *it2) {
                   solucao = sol;
                   break;        
                }    
            }     
       }
       return;                
    }
    else if (feed > nFeeds) {
         return;
    }
    
    int temp[MAXV];
    memcpy(temp, vits, sizeof(int)*nVit);
                  
    aplicaFeed(temp, vits, feed);
    if (melhor_(temp, vits)) {
       multiset<int> nova_sol = sol;               
       nova_sol.insert(feed);               
       pesquisa(temp, nova_sol, feed+1);
    }
    
    memcpy(temp, vits, sizeof(int)*nVit);
    
    multiset<int> nova_sol = sol;
    pesquisa(temp, nova_sol, feed+1);                  
              
              
}


int
main()
{
      fin >> nVit;
      
      for (int i = 0; i < nVit; i++) {
          fin >> vitaminas[i];    
      }
      
      fin >> nFeeds;
      
      for (int i = 0; i < nFeeds; i++) {
          for (int j = 0; j < nVit; j++) {
              fin >> feeds[i].vit[j];    
          }
      }
      
      multiset<int> s;
      
      pesquisa(vitaminas, s, 0);
      
      fout << solucao.size() << " ";
      
      imprime_sol(solucao);
      
      fout.close();
      fin.close();
      return 0;
}
