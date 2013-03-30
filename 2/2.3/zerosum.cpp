/*
ID: drakcap1
PROG: zerosum
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

ofstream fout("zerosum.out");
ifstream fin("zerosum.in");

struct Solucao {
  int nums[9];
  int n_nums;
  char simbolos[9];
  int n_simbolos;
  
  string str;
       
  bool operator<(const Solucao &s) const
  {
       //return (strcmp(str, s.str) == -1);
       return str < s.str;     
       
  }
       
};

set<Solucao> sols;
int N;

bool debug;

bool
satisfaz(const Solucao &s)
{
   int acum = 0;
   
   acum += s.nums[0];
                 
   for (int i = 1; i < s.n_nums; i++) {
       if (s.simbolos[i-1] == '+') {               
          acum += s.nums[i];                  
       }
       else if (s.simbolos[i-1] == '-') {
            acum -= s.nums[i];
       }
       
   }
   //if (debug) fout << acum << endl;
   /*if (debug)
   {
       for (int i = 0; i < s.n_nums; i++) {
           fout << s.nums[i] << endl;    
       }          
             
   }*/
                 
   return (acum == 0);             
}

void
pesquisa(int num, int acum, int ix, Solucao s)
{    
          
     if (num > N) {
        //s.str[ix++] = '0' + num;
        //s.str += " "; 
        //s.str[ix] = 0; 
        s.nums[s.n_nums++] = acum;
           
        if (satisfaz(s)) {
           //prepara_sol(s);
           sols.insert(s);                 
        }
        return;             
     }
     
     s.str += "  ";
     
     //soma numero
     Solucao nova_sol1 = s;
     int ix1 = ix;
     nova_sol1.nums[nova_sol1.n_nums++] = acum;
     nova_sol1.simbolos[nova_sol1.n_simbolos++] = '+';
     nova_sol1.str[ix1++] = '+';
     nova_sol1.str[ix1++] = '0' + num;
     pesquisa(num+1, num, ix1, nova_sol1);
     
     //subtrai numero
     Solucao nova_sol2 = s;
     int ix2 = ix;
     nova_sol2.nums[nova_sol2.n_nums++] = acum;
     nova_sol2.simbolos[nova_sol2.n_simbolos++] = '-';
     nova_sol2.str[ix2++] = '-';
     nova_sol2.str[ix2++] = '0' + num;
     pesquisa(num+1, num, ix2, nova_sol2);
     
     //outro caso
     int ix3 = ix;
     s.str[ix3++] = ' ';
     s.str[ix3++] = '0' + num;               
     pesquisa(num+1, acum*10 + num, ix3, s);        
             
}

void
imprime_string(const char str[30])
{
       int ix = 0;
       
       while (str[ix] != 0) {
             fout << str[ix++];      
       }
       fout << endl;             
                    
}


int
main()
{
      fin >> N;
      
      Solucao s;
      
      s.str = " ";
      
      s.str[0] = '1';
      
      s.n_nums = 0;
      s.n_simbolos = 0;
      
      pesquisa(2, 1, 1, s);
      
      set<Solucao>::iterator it = sols.begin();
      //debug = true;
      
      for ( ; it != sols.end(); it++) {
          fout << it->str << endl;
          //imprime_string(it->str);
      }
      
      
      fout.close();
      fin.close();
      return 0;
}
