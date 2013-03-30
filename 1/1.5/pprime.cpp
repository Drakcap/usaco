/*
ID: drakcap1
PROG: pprime
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

ofstream fout("pprime.out");
ifstream fin("pprime.in");

#define MAX 1000

int maxS;
int sol[MAX];
int nSol;
int a, b;

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

void geraPal(string s, int tamanho)
{
     int num = 0;
     
     if (s.size() != 0) {
        sscanf(s.c_str(), "%d", &num);
     }
     
     //fout << tamanho << " " << s << " " << num << endl;
     
     if (num > b) {
        return;
     }
     
     if (num >= a && is_prime(num)) {
        sol[nSol++] = num;        
     }
     
     if (tamanho >= maxS) {
        return;
     }
     
     
     
     string nova_str, s1 = " ";
     int novoTam = tamanho + 2;
     
     for (int i = 0; i <= 9; i++) {
        s1[0] = '0' + i;
        nova_str = s1 + s + s1;
        //fout << "nova: " << nova_str << endl;
        geraPal(nova_str, novoTam); 
     }
     
     
     
}


int main()
{
    fin >> a >> b;
    
    char str[15];
    string cena = " ";
    
    sprintf(str, "%d", b);
    maxS = strlen(str);
    
    geraPal("", 0);
    
    for (int i = 0; i <= 9; i++) {
        cena[0] = i + '0';
        geraPal(cena, 1);
    }
    
    sort(sol, sol+nSol);
    
    int ant = -1;
    
    //fout << "nSol: " << nSol << endl;
    
    for (int i = 0; i < nSol; i++) {
        if (ant != sol[i]) {
           fout << sol[i] << endl;
        }
        ant = sol[i];
    }
    
    
    fout.close();
    fin.close();
    return 0;
}
