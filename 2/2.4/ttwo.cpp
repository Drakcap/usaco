/*
ID: drakcap1
PROG: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <set>
using namespace std;

ofstream fout("ttwo.out");
ifstream fin("ttwo.in");

#define N 0
#define E 1
#define S 2
#define O 3
#define VAZIO '.'
#define OBS '*'

struct Estado {
      bool dir[4][4];       
};

Estado estados[10][10][10][10];

int xJ, yJ, dirJ;
int xC, yC, dirC;
char grelha[10][10];
int tempo;

inline bool
colide(int x, int y)
{
       if (x < 0 || x > 9 || y < 0 || y > 9) {
             return true;
       }
       
       return (grelha[y][x] == '*');     
                    
}


void
actualiza_pos(int &x, int &y, int &dir)
{
      int x_ant = x;
      int y_ant = y;
                  
      if (dir == N) {
         --y;             
      }
      else if (dir == E) {
           ++x;        
      }
      else if (dir == S) {
           ++y;
      }
      else if (dir == O) {
           --x;     
      }
      
      if (colide(x, y)) {
          x = x_ant;
          y = y_ant;
          dir++;
          dir %= 4;           
      }            
                  
                              
}

int
main()
{
      for (int i = 0; i < 10; i++) {
          for (int j = 0; j < 10; j++) {
              for (int k = 0; k < 10; k++) {
                  for (int l = 0; l < 10; l++) {
                      for (int m = 0; m < 4; m++) {
                          for (int n = 0; n < 4; n++) {
                              estados[i][j][k][l].dir[m][n] = false;   
                          }    
                      }
                      
                  }    
              }
          }    
      }
      
      char temp[11];
      
      for (int i = 0; i < 10; i++) {
          fin >> temp;
          //fout << temp << endl;
          for (int j = 0; j < 10; j++) {
              grelha[i][j] = temp[j];
              //fout << grelha[i][j];
              
              if (grelha[i][j] == 'C') {
                 xC = j; yC = i;
                 grelha[i][j] = '.';                 
              }
              else if (grelha[i][j] == 'F') {
                   xJ = j; yJ = i;
                   grelha[i][j] = '.';  
              }    
          }
          //fout << endl;       
      }
      
      //fout << xJ << " " << yJ << " " << xC << " " << yC << endl;
      
      while (xJ != xC || yJ != yC) {
            if (estados[xJ][yJ][xC][yC].dir[dirJ][dirC]) {
               fout << 0 << endl;
               fout.close();
               fin.close();
               return 0;                             
            }
            estados[xJ][yJ][xC][yC].dir[dirJ][dirC] = true;
            
            actualiza_pos(xJ, yJ, dirJ);
            actualiza_pos(xC, yC, dirC);
            ++tempo;
            //fout << tempo << endl;
      }
      
      fout << tempo << endl;
      
      
      fout.close();
      fin.close();
      return 0;
}
