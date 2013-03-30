/*
ID: drakcap1
PROG: humble
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
using namespace std;

ofstream fout("humble.out");
ifstream fin("humble.in");

#define MAXK 100
#define MAXN 100000

int primes[MAXK];
int multHumble[MAXK];
int humbles[MAXN+1];
int N, K;


int
main()
{
      fin >> K >> N;
      
      for (int i = 0; i < K; i++) {
          fin >> primes[i];
          multHumble[i] = 0;
      }
      
      humbles[0] = 1;
      
      int ant = 1;
      int min_ = -1;
      int mult = 0;
      int ix = -1;
      
      for (int i = 0; i < N; i++) {
          min_ = -1;
          ix = -1;
          for (int j = 0; j < K; j++) {
              mult = humbles[multHumble[j]]*primes[j];
              
              if (mult == ant) {
                 ++multHumble[j];
                 mult = humbles[multHumble[j]]*primes[j];        
              }
              if (mult < min_ || min_ == -1) {
                   min_ = mult;
                   ix = j;   
              }           
          }
          ++multHumble[ix];
          
          //if (min_ < ant) {
          ////   fout << min_ << " " << ant << " " << ix << endl;         
          //}
          
          ant = min_;
          humbles[i+1] = min_;
          //fout << min_ << " " << ix << endl;
      }
      //for (int i = 0; i < N; i++) fout << humbles[i] << endl;
      fout << humbles[N] << endl;
      
      fout.close();
      fin.close();
      return 0;
}
