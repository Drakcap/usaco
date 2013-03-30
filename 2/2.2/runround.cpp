/*
ID: drakcap1
PROG: runround
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

ofstream fout("runround.out");
ifstream fin("runround.in");

unsigned long M;
bool visitas[9];
bool nums[10];

bool
isRun(unsigned long N)
{
    char str[10];
    sprintf(str, "%lu", N);
    
    int tam = strlen(str);
    
    for (int i = 0; i <= 9; i++) {
        nums[i] = false;
    }    
    //numeros todos diferentes e nenhum e' zero
    for (int i = 0; i < tam; i++) {
        if (str[i] == '0') {
           return false;
        }
        else if (nums[str[i]-'0']) {
             return false;
        }
        nums[str[i]-'0'] = true;    
    }
    
    for (int i = 0; i < tam; i++) {
        visitas[i] = false;
    }
    
    int ix = 0;
    
    while (! visitas[ix]) {
          
          visitas[ix] = true;
          
          ix += str[ix] - '0';
          ix %= tam;
          //fout << ix << endl;
    }
    
    if (ix != 0) {
           return false;
    }
    
    
    for (int i = 0; i < tam; i++) {
        if (! visitas[i]) {
              //fout << i << endl;
              return false;
        }    
    }           
    return true;           
               
}

int
main()
{
      
      fin >> M;
      ++M;
      
      while (! isRun(M)) {
         ++M; 
         //fout << M << endl;  
      }
      fout << M << endl;
      //fout << isRun(147) << endl;
      
      fout.close();
      fin.close();
      return 0;
}
