/*
ID: drakcap1
PROG: ariprog
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
using namespace std;

#define MAX 125000
#define NBISQUARES 21046

int incrementos[26] = {0, 0, 0, 1, 4, 4, 12, 12, 12, 12, 12, 12, 12, 12, 84, 84, 84, 84, 84, 84, 84, 84, 2772, 0, 0, 0};
int maximos[26] = {0, 0, 0, 62500, 41568, 30876, 24648, 20280, 17328, 14784, 12444, 11100, 9240, 9240, 8400, 8400, 5880, 5880, 5880, 3696, 2772, 2772, 2772, 0, 0, 0}; 

ofstream fout("ariprog.out");
ifstream fin("ariprog.in");

struct Solucao {
       
       int inicio;
       int dist;
       
       bool operator < (const Solucao &s) const
       {
            if (dist < s.dist) {
               return true;
            }
            if (dist > s.dist) {
                       return false;
            }
            else {
                 return (inicio < s.inicio);
            }
            
       }       
       
};

bool is_bisquare[MAX+10];
int bisquares[NBISQUARES];
int tamanhos[MAX+10];
int N,M;
int max_bisquare;
int n_bisquares = 0;
Solucao solucoes[10001];
int n_solucoes = 0;
//set<Solucao> solucoes;
set<int> bes;

void
calcula_bisquares()
{
    int maximo = M*M + M*M;
    int mult, num;
                   
    for (int i = 0; i <= maximo; i++) {
        is_bisquare[i] = false;
    }
                   
    //calculo dos bisquares
    for (int q = 0; q <= M; q++) {
        mult = q*q;
        for (int p = 0; p <= M; p++) {
            num = mult + p*p;
            is_bisquare[num] = true;
        }
    }
    
    //condensa bisquares num unico array
    for (int i = 0; i <= maximo; i++) {
        if (is_bisquare[i]) {
           //fout << i << endl;
           bisquares[n_bisquares++] = i;
        }
    }
    //fout << n_bisquares << endl;
    max_bisquare = bisquares[--n_bisquares];              
                   
                   
}

void
pesquisa()
{
    int b, soma, a, k;
    
    //fout << "max_bisquare: " << max_bisquare << endl;
    
    for (int i = 0; i < n_bisquares; i++) {
        a = bisquares[i];
                
        for (int j = i+1; j < n_bisquares; j++) {
            k = N;
            b = bisquares[j] - a;
        
            soma = bisquares[j] + (N-2)*b;
            
            for ( ; k > 1; k--, soma -= b) {
                if (soma > max_bisquare || !is_bisquare[soma]) {
                   break;
                }
            }
            
            if (k == 1) {
               Solucao s;
               s.inicio = a;
               s.dist = b;
               solucoes[n_solucoes++] = s;
               //bes.insert(b);     
            }
            
        }
        
    }          
          
          
}

void pesquisa2()
{
     int k;
     int soma;
     
     for (int i = 0; i < n_bisquares; i++) {
         for (int b = incrementos[N]; b <= maximos[N]; b+= incrementos[N]) {
               if (b == 0) break;
             
               k = N;
               soma = bisquares[i] + (N-1)*b;     
             
               for ( ; k > 1; k--, soma -= b) {
                    if (soma > max_bisquare || !is_bisquare[soma]) {
                       break;
                    }
               }
                
                if (k == 1) {
                   Solucao s;
                   s.inicio = bisquares[i];
                   s.dist = b;
                   solucoes[n_solucoes++] = s;
                   //bes.insert(b);     
                }
          }
     }
     
     
     
}


int main()
{
    
    fin >> N >> M;
    //M = 250;
    
    calcula_bisquares();
    
    //fout << is_bisquare[16193] << endl;
    //fout << is_bisquare[18965] << endl;
    
    if (N == 3) {
          pesquisa();
    }
    else {
         pesquisa2();
    }
    
    //pesquisa2();
    
    /*for (N =4; N <= 25; N++) {
       pesquisa();
       
       fout << "N: " << N << endl;
       
       set<int>::iterator it = bes.begin();
    
       for ( ; it != bes.end(); it++)
           fout << *it << endl;
           
       bes.clear();
    }*/
       
    //fout << "tamanho: " << bes.size() << endl;
    
   
    
    
    if (n_solucoes == 0) fout << "NONE" << endl;
    
    sort(solucoes, solucoes + n_solucoes);
    
    for (int i = 0; i < n_solucoes; i++) {
        fout << solucoes[i].inicio << " " << solucoes[i].dist << endl;
    }


    
    
    fout.close();
    fin.close();
    return 0;
}
