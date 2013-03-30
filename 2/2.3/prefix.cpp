/*
ID: drakcap1
PROG: prefix
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

ofstream fout("prefix.out");
ifstream fin("prefix.in");

char primitivas[200][11];
int tamanhos[200];
int nPrim;
char S[200001];
int tam;
bool possivel[200001];


int
main()
{
      char temp[11];
      char buffer[200001];
      fin >> temp;
      
      while (strcmp(temp, ".") != 0) {
            tamanhos[nPrim] = strlen(temp);
            strcpy(primitivas[nPrim++], temp);
            fin >> temp;          
      }
      while (fin >> buffer) {
            //fout << "em while" << endl;
            strcpy(&S[tam], buffer);
            tam += strlen(buffer);
                  
      }
      
      int i;
      
      //fout << "in here" << endl;
      
      for (i = 0; i < tam; i++) {
          for (int j = 0; j < nPrim; j++) {
              if ((i == 0 || possivel[i]) && i + tamanhos[j] <= tam) {
                 if (strncmp(primitivas[j], &S[i], tamanhos[j]) == 0) {
                    possivel[i+tamanhos[j]] = true;                 
                 }     
              }
              
          }
          
      }
      
      int res = 0;
      
      for (int i = 0; i <= tam; i++) {
          if (possivel[i]) {
             res = i;
          }   
      }
      fout << res << endl;
      
      fout.close();
      fin.close();
      return 0;
}
