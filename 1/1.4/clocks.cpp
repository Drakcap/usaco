/*
ID: drakcap1
PROG: clocks
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <map>
#include <stdio.h>
using namespace std;

ofstream fout("clocks.out");
ifstream fin("clocks.in");

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8

#define MAX_MOVS 27



typedef enum Hora {Tres = 1, Seis, Nove, Doze};

struct Relogio {
       Hora horas[9];
};

struct Solucao {
       int movimentos[MAX_MOVS];
       int n_movimentos;
       
       bool operator<(Solucao &s)
       {
        if (n_movimentos != s.n_movimentos) return n_movimentos < s.n_movimentos;
        
        
        for (int i = 0; i < n_movimentos; i++) {
            if (movimentos[i] != s.movimentos[i]) {
               return (movimentos[i] < s.movimentos[i]); 
            }
        }
        return false;
       }
       
};
       

bool 
relogio_satisfaz(Relogio &r)
{
     for (int i = 0; i < 9; i++) {
         if (r.horas[i] != Doze) {
                       return false;
         }
     }
     return true;     
     
}

inline Hora 
intToHora(int valor)
{
     return (Hora)(valor / 3);          
}

inline void
rodaPonteiro(Hora &h)
{
    if (h == Doze) h = Tres;
    else h = (Hora) (h+1);                  
}

void
move1(Relogio &r)
{
    rodaPonteiro(r.horas[A]);
    rodaPonteiro(r.horas[B]);
    rodaPonteiro(r.horas[D]);
    rodaPonteiro(r.horas[E]);
}

void
move2(Relogio &r)
{
    rodaPonteiro(r.horas[A]);
    rodaPonteiro(r.horas[B]);
    rodaPonteiro(r.horas[C]);
}

void
move3(Relogio &r)
{
    rodaPonteiro(r.horas[B]);
    rodaPonteiro(r.horas[C]);
    rodaPonteiro(r.horas[E]);
    rodaPonteiro(r.horas[F]);
}

void
move4(Relogio &r)
{
    rodaPonteiro(r.horas[A]);
    rodaPonteiro(r.horas[D]);
    rodaPonteiro(r.horas[G]);
}

void
move5(Relogio &r)
{
    rodaPonteiro(r.horas[B]);
    rodaPonteiro(r.horas[D]);
    rodaPonteiro(r.horas[E]);
    rodaPonteiro(r.horas[F]);
    rodaPonteiro(r.horas[H]);
}

void
move6(Relogio &r)
{
    rodaPonteiro(r.horas[C]);
    rodaPonteiro(r.horas[F]);
    rodaPonteiro(r.horas[I]);
}

void
move7(Relogio &r)
{
    rodaPonteiro(r.horas[D]);
    rodaPonteiro(r.horas[E]);
    rodaPonteiro(r.horas[G]);
    rodaPonteiro(r.horas[H]);
}

void
move8(Relogio &r)
{
    rodaPonteiro(r.horas[G]);
    rodaPonteiro(r.horas[H]);
    rodaPonteiro(r.horas[I]);
}

void
move9(Relogio &r)
{
    rodaPonteiro(r.horas[E]);
    rodaPonteiro(r.horas[F]);
    rodaPonteiro(r.horas[H]);
    rodaPonteiro(r.horas[I]);
}

void
movimento(Relogio &r, Solucao &s, int mov)
{
  switch (mov) {
         case 1:
              move1(r);
              break;
         case 2:
              move2(r);
              break;
         case 3:
              move3(r);
              break;
         case 4:
              move4(r);
              break;
         case 5:
              move5(r);
              break;
         case 6:
              move6(r);
              break;
         case 7:
              move7(r);
              break;
         case 8:
              move8(r);
              break;
         case 9:
              move9(r);
              break;
  }
  
  s.movimentos[s.n_movimentos++] = mov;                
}

Solucao sol_f;

void
imprime_solucao(Solucao &s)
{
   if (s.n_movimentos == 50000) {fout << endl; return;}
   
   for (int i = 0; i < s.n_movimentos; i++) {
            if (i != 0) fout << " ";
            fout << s.movimentos[i];
    }
    fout << endl;
}

void
imprime_relogio(Relogio &r)
{
 for (int i = 0; i < 9; i++) {
     fout << r.horas[i] << " ";
 }
 fout << endl;                        
                        
}


void
pesquisa(Relogio r, Solucao s, int mov_actual)
{
   //fout << mov_actual << endl;
   //imprime_solucao(s);
   //imprime_relogio(r);
   //fout << endl;
                

    if (relogio_satisfaz(r)) {
       //fout << mov_actual << endl;
       if (s < sol_f) {
          sol_f = s;
       }
       return;
    }
    if (mov_actual > 9) {
                 return;
    }   
    
    else if (! (s < sol_f)) {
         return;
    }
    
    int prox_mov = mov_actual + 1;             
    
    //nao aplica o movimento actual
    pesquisa(r, s, prox_mov);
    
    //aplica uma vez
    Relogio r1 = r;
    Solucao s1 = s;
    
    movimento(r1, s1, mov_actual);
    pesquisa(r1, s1, prox_mov);
    
    //aplica duas vezes
    Relogio r2 = r;
    Solucao s2 = s;
    
    movimento(r2, s2, mov_actual);
    movimento(r2, s2, mov_actual);
    pesquisa(r2, s2, prox_mov);
    
    //aplica tres vezes
    Relogio r3 = r;
    Solucao s3 = s;
    
    movimento(r3, s3, mov_actual);
    movimento(r3, s3, mov_actual);
    movimento(r3, s3, mov_actual);
    pesquisa(r3, s3, prox_mov);
                 
                 
                 
}




int main()
{
    
    Relogio r;
    Solucao s;
    s.n_movimentos = 0;
    sol_f.n_movimentos = 50000;
    
    int temp;
    
    for (int i = 0; i < 9; i++) {
        fin >> temp;    
        r.horas[i] = (Hora) (temp / 3);
    }
    
    pesquisa(r, s, 1);
    /*move4(r);
    move5(r);
    move8(r);
    move9(r);
    
    imprime_relogio(r);*/
    
    imprime_solucao(sol_f);
    
    fout.close();
    fin.close();
    return 0;
       
}
