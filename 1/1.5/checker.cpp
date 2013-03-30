/*
ID: drakcap1
PROG: checker
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

ofstream fout("checker.out");
ifstream fin("checker.in");

#define MAX 13

int N;

struct Solucao {
       char colunas[MAX];
       bool ocupada[MAX];
       bool operator <(const Solucao &s) const
       {
            for (short i = 0; i < N; i++) {
                if (colunas[i] != s.colunas[i]) {
                   return (colunas[i] < s.colunas[i]);
                }
            }         
            return false;
       }
};

//set<Solucao> solucoes;
int nSol;
Solucao sols[3];
//int nSol;
bool diagonais1[MAX*2];
bool diagonais2[MAX*2];


inline void
imprime_sol(const Solucao &s)
{
     fout << s.colunas[0] + 1;
     for (short i = 1; i < N; i++) {
         fout << " " << s.colunas[i] + 1;
     }
     fout << endl;         
}

/*inline void
espelhamento(int linha, int coluna, int &nLinha, int &nColuna)
{
       nColuna = coluna;                 
       nLinha = N - 1 - linha;          
                 
}*/

inline bool
atacada(Solucao &sol, short linha, short coluna)
{
      
      if (sol.colunas[linha] != -1) {
         return true;
      }

      if (sol.ocupada[coluna]) {
         return true;
      }
      
      return (diagonais1[linha+coluna] || diagonais2[linha-coluna+N-1]);
      
                               
}

inline void
acrescenta_sol(Solucao &sol)
{
   if (sol < sols[0]) {
          sols[2] = sols[1];
          sols[1] = sols[0];
          sols[0] = sol;
          return;
   }
   if (sol < sols[1]) {
           sols[2] = sols[1];
           sols[1] = sol;
           return;
   }
   if (sol < sols[2]) {
           sols[2] = sol;
   }                     
                       
}


inline void
acrescenta_simetrica(Solucao &sol)
{
  Solucao novaSol;
  short nLinha, nColuna;
  
  
  for (short i = 0; i < N; i++) {
      nColuna = sol.colunas[i];                 
      nLinha = N - 1 - i;
      novaSol.colunas[nLinha] = nColuna;
  }
  acrescenta_sol(novaSol);    
  
                        
}



void
pesquisa(Solucao &sol, short coluna)
{
     if (coluna >= N) {
        acrescenta_sol(sol);       
        ++nSol;
        if (N % 2 == 0 || sol.colunas[N/2] != 0) {
           acrescenta_simetrica(sol);
           ++nSol;
        }
        return;
     }
     
     Solucao nova_sol = sol;
     char nova_coluna = coluna + 1;
     
     //int maxL = N;
     char maxL = (coluna == 0 ? (N+1)/2 : N);
     
     //tenta colocar rainha nas diferentes linhas
     for (short i = 0; i < maxL; i++) {
         if (! atacada(sol, i, coluna)) { 
              nova_sol.colunas[i] = coluna;
              nova_sol.ocupada[coluna] = true;
              diagonais1[i+coluna] = true;
              diagonais2[i-coluna+N-1] = true;
              pesquisa(nova_sol, nova_coluna);
              nova_sol.ocupada[coluna] = false;
              nova_sol.colunas[i] = -1;
              diagonais1[i+coluna] = false;
              diagonais2[i-coluna+N-1] = false;
                    
         } 
     }           
                 
}

int
main()
{
      
      fin >> N;
      
      Solucao sol;
      for (short i = 0; i < N; i++) {
          sol.colunas[i] = -1;
          sol.ocupada[i] = false;
      }
      char s = N*2;
      for (short i = 0; i < s; i++) {
          diagonais1[i] = false;
          diagonais2[i] = false;     
      } 
      for (short i = 0; i < N; i++) {
          sols[0].colunas[i] = N;
          sols[1].colunas[i] = N;
          sols[2].colunas[i] = N;
      }
      
      
      pesquisa(sol, 0);
      
      //set<Solucao>::iterator it = solucoes.begin();
      
      //if (solucoes.size() >= 3) {
         //sort(sols, sols +3);
         imprime_sol(sols[0]);
         imprime_sol(sols[1]);
         imprime_sol(sols[2]);
      //}
      
      //fout << solucoes.size() << endl;
      fout << nSol << endl;
      
      fout.close();
      fin.close();
      return 0;
}
