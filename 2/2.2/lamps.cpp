/*
ID: drakcap1
PROG: lamps
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

ofstream fout("lamps.out");
ifstream fin("lamps.in");

#define MAXL 101

int N;
int C;

struct Solucao {
      bool lampadas[MAXL];
      int op[4];
      
      bool operator<(const Solucao &s) const
      {
          for (int i = 0; i < N; i++) {
              if (lampadas[i] != s.lampadas[i]) {
                  return s.lampadas[i];
              }    
          }     
          return false; 
      }
}; 

set<Solucao> sols;
bool acesas[MAXL];
bool apagadas[MAXL];

bool
satisfaz(Solucao &s)
{                
     for (int i = 0; i < N; i++) {
         if (acesas[i] && (!s.lampadas[i])) {
             return false;
         }
         if (apagadas[i] && s.lampadas[i]) {
             return false;
         }    
         
     }
     int soma = s.op[0] + s.op[1] + s.op[2] + s.op[3];
     //fout << soma << endl;
     
     if (soma > C) {
       return false;
     }
     
     return ( (soma % 2) == (C % 2) );
     return true;         
}

void
imprime_sol(Solucao &s)
{
   for (int i = 0; i < N; i++) {
       fout << s.lampadas[i];
   }                    
   fout << endl;                 
}

void
aplica_op(Solucao &s, int op)
{
    s.op[op] = 1;
    
    if (op == 0) {
       for (int i = 0; i < N; i++) {
           s.lampadas[i] = !s.lampadas[i];
       }       
    }
    
    //odd numbered
    else if (op == 1) {
         for (int i = 0; i < N; i += 2) {
             s.lampadas[i] = !s.lampadas[i];
         }          
    }
    //even numbered
    else if (op == 2) {
         for (int i = 1; i < N; i += 2) {
             s.lampadas[i] = !s.lampadas[i];
         }
    }
    else {
         for (int i = 0; i < N; i += 3) {
             s.lampadas[i] = !s.lampadas[i];
         }      
    }                  
                  
}

void
pesquisa(Solucao s, int op)
{
      //fout << op << endl;           
      if (op == 4) {
         //imprime_sol(s);
             
         if (satisfaz(s)) {          
             sols.insert(s); 
         }
         //fout << endl;
         return;                                   
      }
      
      Solucao nova_sol = s;                 
      
      //aplica uma vez a operacao
      aplica_op(nova_sol, op);
      pesquisa(nova_sol, op+1);
      
      //nao aplica op
      s.op[op] = 0;
      pesquisa(s, op+1);           
                 
}


int
main()
{
      fin >> N >> C;
      
      int temp;
      
      fin >> temp;
      
      while (temp != -1) {
            acesas[temp-1] = true;
            fin >> temp;      
      }
      fin >> temp;
      
      while (temp != -1) {
            apagadas[temp-1] = true;
            fin >> temp;      
      }
      
      Solucao s;
      
      for (int i = 0; i < N; i++) {
          s.lampadas[i] = true;
      }
      
      pesquisa(s, 0);
      
      //fout << "end search" << endl;
      
      if (sols.size() == 0) {
            fout << "IMPOSSIBLE" << endl;
      }          
      
      set<Solucao>::iterator it = sols.begin();
      
      for ( ; it != sols.end(); it++) {
          for (int i = 0; i < N; i++) {
              fout << it->lampadas[i];    
          }
          fout << endl;   
      }
      
      
      fout.close();
      fin.close();
      return 0;
}
