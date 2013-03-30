/*
ID: drakcap1
PROG: concom
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

ofstream fout("concom.out");
ifstream fin("concom.in");

#define MAXCOMPANHIAS 101

struct Ligacao {
       int dest;
       int valor;     
       
};

struct No {      
      bool possui[101];
      bool chefe[101];
      
      list<int> lPossui;
      list<int> lChefe;
      
      //<companhia, valor>
      map<int, int> valores;
       
};

No nos[MAXCOMPANHIAS];
int n;

void
acrescenta_posse1(int chefe, int sub)
{
   nos[chefe].possui[sub] = true;
   nos[chefe].lPossui.push_back(sub);
      
   nos[sub].chefe[chefe] = true;
   nos[sub].lChefe.push_back(chefe);                                   
}

void
acrescenta_posse(int chefe, int sub)
{
      if (chefe == sub) return;               
                     
      if (nos[chefe].possui[sub]) {
           return;
      }
      acrescenta_posse1(chefe, sub);

      list<int>::iterator it = nos[sub].lPossui.begin();
      
      for ( ; it != nos[sub].lPossui.end(); it++) {
          acrescenta_posse1(chefe, *it);     
      }
      
      map<int, int>::iterator it2 = nos[sub].valores.begin();
      
      for ( ; it2 != nos[sub].valores.end(); it2++) {
          if (it2->second < 50 && !nos[chefe].possui[it2->first] && it2->first != chefe)
             nos[chefe].valores[it2->first] += it2->second;    
      }
      
      it = nos[chefe].lChefe.begin();
      
      for ( ; it !=  nos[chefe].lChefe.end(); it++) {
          acrescenta_posse(*it, sub);
      }                
                     
                     
}



int
main()
{
      fin >> n;
      
      for (int i = 1; i < MAXCOMPANHIAS; i++) {
          for (int j = 1; j < MAXCOMPANHIAS; j++) { 
              nos[i].possui[j] = false;
              nos[i].chefe[j] = false;
          }
             
      }
      int c1, c2, valor;
      //Ligacao l;
      
      for (int i = 0; i < n; i++) {
          fin >> c1 >> c2 >> valor;
          
          if (c1 == c2) continue;
          
          //if (valor > 50) {
          //   acrescenta_posse(c1, c2);        
          //}
          //else {
             nos[c1].valores[c2] = valor; 
          //}
      }
      
      bool continua = true;
      map<int, int>::iterator it, it_ant;;
      
      while (continua)
      {

           continua = false; 
           for (int i = 1; i < MAXCOMPANHIAS; i++) {
                 //fout << i << endl;
                 it = nos[i].valores.begin();
                 
                 //if (i == 34) fout << "tamanho: " << nos[i].valores.size() << endl;
                // int count = 0;
                 /*while (it != nos[i].valores.end())
                 {
                     if (it->second > 50) {
                          nos[i].valores.erase(it->first);         
                          acrescenta_posse(i, it->first);
                          continua = true;
                     }     
                       
                 }*/
                 
                 for ( ; it != nos[i].valores.end(); it++) {
                     //if (i == 34) fout << "valor: " << it->second << " " << it->first << endl;
                     if (it->second > 50) {
                          nos[i].valores[it->first] = 0;         
                          acrescenta_posse(i, it->first);
                          continua = true;
                     }    
                 } 
               
           }      
            
            
      }
      
      for (int i = 1; i < MAXCOMPANHIAS; i++) {
          for (int j = 1; j < MAXCOMPANHIAS; j++) {
              if (nos[i].possui[j] && i != j) {
                 fout << i << " " << j << endl;
              }   
          }
      }
      
      
      fout.close();
      fin.close();
      return 0;
}
