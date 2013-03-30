/*
ID: drakcap1
PROG: inflate
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

ofstream fout("inflate.out");
ifstream fin("inflate.in");

#define MAXN 10000
#define MAXM 10000

struct Item {
    int points;
    int size;   
};

int best[MAXM+1];
Item items[MAXN];
int M, N;


int
main()
{
      fin >> M >> N;
      
      best[0] = 0;
      
      for (int i = 0; i < N; i++) {
          fin >> items[i].points;
          fin >> items[i].size;       
      }
      
      int maxL;
      
      for (int i = 0; i < N; i++) {
          //fout << i << endl;
          maxL = M - items[i].size;
          
          if (items[i].points > best[items[i].size])
             best[items[i].size] = items[i].points;
          
          for (int j = 1; j <= maxL; j++) {
              if (best[j+items[i].size] < best[j]+items[i].points) {
                 best[j+items[i].size] = best[j]+items[i].points;             
              }       
          }
      }
      
      for (int i = M; i >= 0; i--) {
          if (best[i] != 0) {
             fout << best[i] << endl;
             break;
          }
      }
      
      
      fout.close();
      fin.close();
      return 0;
}
