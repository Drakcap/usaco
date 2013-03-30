/*
ID: drakcap1
PROG: contact
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <stdlib.h>
#include <set>
#include <cmath>
#include <iomanip>
#include <queue>
#include <cmath>
using namespace std;

ofstream fout("contact.out");
ifstream fin("contact.in");

struct Sol {
       string str;
       int nOcorr;
       
       bool operator<(const Sol &s) const
       {
            if (s.nOcorr == nOcorr) {
               if ( str.size() == s.str.size()) {
                    return str < s.str;
               }
               return str.size() < s.str.size();             
            }
            
            return nOcorr > s.nOcorr;     
       }   
       
};

set<Sol> sols;
int nSol;

Sol ocorr[13][4096];

int A, B, N;
string str, temp ="";

int
to_int(string &str)
{
    int mult = 1;
    int res = 0, tam = str.size();
    
    for (int i = 0; i < tam; i++) {
        res  += ((str[i] - '0') * mult);
        mult *= 2;  
    }                 
    
    return res;
}

int
main()
{
      fin >> A >> B >> N;
      
      while (fin >> temp) {
            str += temp;
      }
      
      int tamStr = str.size();
      string temp;
      
      for (int i = A; i <= B; i++) {
          for (int j = 0; j < 4096; j++) {
              ocorr[i][j].nOcorr = 0;
          }    
      }
      int coiso;
      
      for (int tam = A; tam <= B; tam++) {
          for (int i = 0; i < tamStr; i++) {
              if (tam + i <= tamStr) {
                  temp = str.substr(i, tam);
                  coiso = to_int(temp);
                  ++ocorr[tam][coiso].nOcorr;
                  ocorr[tam][coiso].str = temp; 
              }   
          }
      }
      
      
      int ant = -1;
      bool first_run = true;
      Sol s;
      
      for (int i = A; i <= B; i++) {
          for (int j = 0; j < 4096; j++) {
              if (ocorr[i][j].nOcorr > 0) {
                 //fout << ocorr[i][j].nOcorr << " " << ocorr[i][j].str << endl;
                 sols.insert(ocorr[i][j]);                  
              }    
          }    
      }
      set<Sol>::iterator it = sols.begin();
      int c = 0;
      //fout << nSol << " " << N << " " << (sols.size()) << endl;
      
      //imprime solucoes
      while (nSol <= N && it != sols.end()) {
            //fout << "here" << endl;
            if (it->nOcorr == ant) {
               if (c == 6) {fout << endl << it->str; c = 0;}
               
               else fout << " " << it->str;
               ++c;        
            }
            else {
                 c = 1;
                 if (nSol == N) break;
                 
                 if (! first_run) {
                    fout << endl;      
                 }
                 first_run = false;
                 fout << it->nOcorr << endl;
                 fout << it->str;
                 nSol++;
            }
            ant = it->nOcorr;
            it++;
            
      }
      fout << endl;
      
      
      fout.close();
      fin.close();
      return 0;
}
