/*
ID: drakcap1
PROG: preface
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

ofstream fout("preface.out");
ifstream fin("preface.in");

#define I 0
#define V 1
#define X 2
#define L 3
#define C 4
#define D 5
#define M 6

int valores[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
int ocorr[7];

void
usa_valor(int valor)
{
    switch (valor)
    {
           case 1:
                ++ocorr[I];
                break;
           case 4:
                ++ocorr[I];
                ++ocorr[V];
                break;
           case 5:
                ++ocorr[V];
                break;
           case 9:
                ++ocorr[I];
                ++ocorr[X];
                break;
           case 10:
                ++ocorr[X];
                break;
           case 40:
                ++ocorr[X];
                ++ocorr[L];
                break;
           case 50:
                ++ocorr[L];
                break;
           case 90:
                ++ocorr[X];
                ++ocorr[C];
                break;
           case 100:
                ++ocorr[C];
                break;
           case 400:
                ++ocorr[C];
                ++ocorr[D];
                break;
           case 500:
                ++ocorr[D];
                break;
           case 900:
                ++ocorr[C];
                ++ocorr[M];
                break;
           case 1000:
                ++ocorr[M];
                break;
    }                 
              
}

void
processa_numero(int num)
{
    while (num > 0)
    {
        for (int i = 12; i >= 0; i--) {
            if (valores[i] <= num) {
               usa_valor(valores[i]);
               num -= valores[i];
               break;
            }    
        }   
        
    }
                    
                    
}

void
imprime_ocorr(int simb, int oc)
{
     switch(simb)
     {
           case I:
                fout << "I ";
                break;
                
           case V:
                fout << "V ";
                break;
                
           case X:
                fout << "X ";
                break;
                
           case L:
                fout << "L ";
                break;
                
           case C:
                fout << "C ";
                break;
                
           case D:
                fout << "D ";
                break;
                
           case M:
                fout << "M ";
                break;
     }
                
                
           fout << oc << endl;                   
                  
}

int
main()
{
      int N;
      fin >> N;
      
      for (int i = 1; i <= N; i++) {
          processa_numero(i);
      }
      
      for (int i = 0; i < 7; i++) {
          if (ocorr[i] != 0) {
             imprime_ocorr(i, ocorr[i]);
          }             
      }
      
      fout.close();
      fin.close();
      return 0;
}
