/*
ID: drakcap1
PROG: sort3
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

ofstream fout("sort3.out");
ifstream fin("sort3.in");

#define MAX 1000

int nums[MAX];
int N;
int n1, n2, n3;
int _1em2, _1em3, _2em1, _2em3, _3em1, _3em2;
int trocas;

void
calcula_trocas()
{
     int max_troca;
     
     //troca 1s com 2s
     max_troca = (_1em2 < _2em1 ? _1em2 : _2em1);
     trocas += max_troca;
     _1em2 -= max_troca;
     _2em1 -= max_troca;
     
     //troca 1s com 3s
     max_troca = (_1em3 < _3em1 ? _1em3 : _3em1);
     trocas += max_troca;
     _1em3 -= max_troca;
     _3em1 -= max_troca;
     
     //troca 2s com 3s                
     max_troca = (_2em3 < _3em2 ? _2em3 : _3em2);
     trocas += max_troca;
     _2em3 -= max_troca;
     _2em1 -= max_troca; 
     
     int resto = _1em2 + _1em3 + _2em1 + _2em3 + _3em1 + _3em2;
     
     resto /= 3;
     
     trocas += resto*2;         
                
}

int
main()
{
      fin >> N;
      
      for (int i = 0; i < N; i++) {
          fin >> nums[i];
          
          if (nums[i] == 1) {
            ++n1;
          }    
          else if (nums[i] == 2) {
               ++n2;
          }
          else if (nums[i] == 3) {
               ++n3;
          }
      }
      //lugar dos 1s
      for (int i = 0; i < n1; i++) {
          if (nums[i] == 2) {
             ++_2em1;
          }
          else if (nums[i] == 3) {
               ++_3em1;
          }      
      }
      int sup = n1+n2;
      
      //lugar dos 2s
      for (int i = n1; i < n1+n2; i++) {
          if (nums[i] == 1) {
             ++_1em2;
          }
          else if (nums[i] == 3) {
               ++_3em2;
          }      
      }
      sup += n3;
      
      //lugar dos 3s
      for (int i = n1+n2; i < sup; i++) {
          if (nums[i] == 1) {
             ++_1em3;
          }
          else if (nums[i] == 2) {
               ++_2em3;
          }      
      }
      
      //fout << _1em2 << " " << _1em3 << " " << _2em1 << " " << _2em3 << " " << _3em1 << " " << _3em2 << endl;
      
      calcula_trocas();
      
      fout << trocas << endl;
      
      fout.close();
      fin.close();
      return 0;
}
