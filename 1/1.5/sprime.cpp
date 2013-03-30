/*
ID: drakcap1
PROG: sprime
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

#define MAX 10000

ofstream fout("sprime.out");
ifstream fin("sprime.in");
int N;
int sol[MAX];
int nSol;

bool is_prime(const unsigned num)
{
     unsigned test_num, test_limit;
     
     if (num == 1)
        return false;
     
     else if (num == 2)
          return true;
     
     if (num % 2 == 0)
        return false;
     
     test_num = 3;
     test_limit = num;
     
     while (test_limit > test_num) {
           
           if (num % test_num == 0)
              return false;
           
           test_limit = num / test_num;
           
           test_num += 2;
     }
     
     return true;
}

void pesquisa(string str, int tam)
{
   int num;
   sscanf(str.c_str(), "%d", &num);
   
   if (!is_prime(num)) {
      return;
   }
   
   if (tam == N && is_prime(num)) {
           sol[nSol++] = num;
           return;
   }
   string temp = " ";
   string nova_str;
   int novo_tam = tam+1;
   
   for (int i = 0; i <= 9; i++) {
       temp[0] = i + '0';
       nova_str = str + temp;
       pesquisa(nova_str, novo_tam);
   } 
     
     
     
}

int main()
{
    fin >> N;
    
    pesquisa("2", 1);
    pesquisa("3", 1);
    pesquisa("5", 1);
    pesquisa("7", 1);
    
    sort(sol, sol + nSol);
    
    for (int i = 0; i < nSol; i++) {
        fout << sol[i] << endl;
    }
    
    fout.close();
    fin.close();
    return 0;
}
