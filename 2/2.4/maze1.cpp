/*
ID: drakcap1
PROG: maze1
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
#include <iomanip>
#include <queue>
using namespace std;

ofstream fout("maze1.out");
FILE* fin = fopen("maze1.in", "r");
//ifstream fin("maze1.in");

#define N 0
#define E 1
#define S 2
#define O 3
#define INF 10000000

struct No {
       bool ligacoes[4];
       int distancia;
       bool visited;     
};

int dists1[100][38];
//int dists2[100][38];

struct Par {
       int x, y;     
};

int W, H;
int maxW, maxH;
No nos[100][38];
char linha[100];

int xE[2];
int yE[2];
int nE;

int res;

void
debug_saida(int num)
{
   fout << num << endl;          
   fout << nE << endl << endl;            
             
}

void
le_input()
{    
      //primeira linha
      fgets(linha,maxW+2, fin);
      //fout << linha << endl;
      
      //procura uma saida na primeira linha
      for (int i = 1; i < maxW; i+= 2) {
          if (linha[i] == ' ') {
            xE[nE] = i/2;
            yE[nE] = 0;
            ++nE;
            //debug_saida(1);              
          }    
      }
      
      //restantes linhas
      for (int i = 1; i <= maxH; i++) {
          fgets(linha,maxW+2, fin);
          //fout << linha << endl;     
                           
          //paredes na vertical
          if (i % 2 == 1) {
                //analisa primeira coluna
                if (linha[0] == ' ') {
                   xE[nE] = 0;
                   yE[nE] = i/2;
                   ++nE;
                   //debug_saida(2);                
                }
                //analisa restantes colunas
                for (int j = 2; j < maxW-1; j+= 2) {
                    if (linha[j] == ' ') {
                       nos[i/2][(j-1)/2].ligacoes[E] = true;
                       nos[i/2][j/2].ligacoes[O] = true;               
                    }
                }
                
                //analias ultima coluna
                if (linha[maxW-1] == ' ') {
                   xE[nE] = W-1;
                   yE[nE] = i/2;
                   ++nE;
                   //fout << W-1 << " " << i/2 << " " << xE[0] << " " << yE[0] << endl;
                   //debug_saida(3);              
                }      
          }
          //paredes na horizontal
          else {
               for (int j = 1; j < maxW-1; j+=2) {
                   if (linha[j] == ' ') {
                        nos[(i/2)-1][j/2].ligacoes[S] = true;
                        nos[i/2][j/2].ligacoes[N] = true;        
                   }    
               }
                       
                       
          }
      }
      
      
      
      
      //ultima linha
      if (H > 1) {
      
          fgets(linha,maxW+2, fin);
          //fout << xE[0] << " " << yE[0] << endl;
          //fout << linha << endl;
          
          //procura uma saida na ultima linha
          for (int i = 1; i < maxW; i++) {
              if (linha[i] == ' ') {
                xE[nE] = i/2;
                yE[nE] = H-1;
                ++nE;
                //debug_saida(4);              
              }    
          }
      }    
          
          
}

void
debug_ligacoes()
{
     for (int i = 0; i < H; i++) {
          for (int j = 0; j < W; j++) {
              fout << nos[i][j].ligacoes[0] << " " 
                   << nos[i][j].ligacoes[1] << " " 
                   << nos[i][j].ligacoes[2] << " "
                   << nos[i][j].ligacoes[3] << endl;
          }
      }
      fout << xE[0] << " " << yE[0] << " " << xE[1] << " " << yE[1] << endl;
      fout << nE << endl;
}

inline bool
dentro(int x, int y)
{
     return (x >= 0 && x < W && y >= 0 && y < H);           
}

void
melhor_caminho(int x, int y)
{
     for (int i = 0; i < H; i++) {
         for (int j = 0; j < W; j++) {
             if (i == y && j == x) {
                nos[i][j].distancia = 0;
                nos[i][j].visited = true;      
             }
             else {
                  nos[i][j].distancia = INF;
                  nos[i][j].visited = false;  
             }    
             
         }
     }
     queue<Par> fila;
     Par p, nP;
     p.x = x;
     p.y = y;
     //fout << x << " " << y << endl;
     int nova_dist;
     
     fila.push(p); 
     
     //fout << nos[1][4].ligacoes[N] << endl;
     
     while (! fila.empty()) { 
         nP = fila.front();
         fila.pop();
         //fout << fila.size() << endl;
         //fout << nP.y << " " << nP.x << endl;  
         nova_dist = nos[nP.y][nP.x].distancia + 1;
         //fout << nova_dist << endl;
         //if (nova_dist > res) res = nova_dist;
         
         //fout << nP.x << " " << nP.y << " " << nos[nP.y][nP.x].visited << endl;
         
         //Norte
         if (nos[nP.y][nP.x].ligacoes[N] && dentro(nP.x, nP.y-1) && !nos[nP.y-1][nP.x].visited) {
            p.x = nP.x;
            p.y = nP.y-1;
            nos[p.y][p.x].visited = true;
            nos[p.y][p.x].distancia = nova_dist;
            //fout << nP.x << " " << nP.y << endl;
            fila.push(p);                               
         }
         
         
         //Este
         if (nos[nP.y][nP.x].ligacoes[E] && dentro(nP.x+1, nP.y) && !nos[nP.y][nP.x+1].visited) {
            p.x = nP.x+1;
            p.y = nP.y;
            nos[p.y][p.x].visited = true;
            nos[p.y][p.x].distancia = nova_dist;
            //fout << x+1 << " " << y << endl;
            fila.push(p);                               
         }
         //fout << "here2" << endl;
         
         //Sul
         if (nos[nP.y][nP.x].ligacoes[S] && dentro(nP.x, nP.y+1) && !nos[nP.y+1][nP.x].visited) {
            p.x = nP.x;
            p.y = nP.y+1;
            nos[p.y][p.x].visited = true;
            nos[p.y][p.x].distancia = nova_dist;
            //fout << p.x << " " << p.y << endl;
            fila.push(p);                               
         }
         //fout << "here3" << endl;
         
         //Oeste
         if (nos[nP.y][nP.x].ligacoes[O] && dentro(nP.x-1, nP.y) && !nos[nP.y][nP.x-1].visited) {
            p.x = nP.x-1;
            p.y = nP.y;
            nos[p.y][p.x].visited = true;
            nos[p.y][p.x].distancia = nova_dist;
            //fout << "here" << endl;
            //fout << x-1 << " " << y << endl;
            fila.push(p);                               
         }
         //fout << "here4" << endl;  
           
     }               
                
                
}

int
main()
{
      fscanf(fin, "%d %d\n", &W, &H);
      maxW = 2*W+1;
      maxH = 2*H-1;
      
      for (int i = 0; i < H; i++) {
          for (int j = 0; j < W; j++) {
              for (int k = 0; k < 4; k++) {
                  nos[i][j].ligacoes[k] = false;    
              }
          }
      }
      //debug_ligacoes();
      le_input();
      
      //fout << nos[1][4].ligacoes[N] << endl;
      
      
      melhor_caminho(xE[0], yE[0]);
      
      for (int i = 0; i < H; i++) {
          for (int j = 0; j < W; j++) {
              dists1[i][j] = nos[i][j].distancia;
          }
      }
      
      melhor_caminho(xE[1], yE[1]);
      
      for (int i = 0; i < H; i++) {
          for (int j = 0; j < W; j++) {
              if (nos[i][j].distancia < dists1[i][j]) {
                 //fout << i << " " << j << endl;
                 dists1[i][j] = nos[i][j].distancia;
              }
          }
      }
      
      for (int i = 0; i < H; i++) {
          for (int j = 0; j < W; j++) {
              if (dists1[i][j] > res) {
                 res = dists1[i][j];
              }
          }
      }
      
      fout << res + 1 << endl;
      
      //fout << xE[0] << " " << yE[0] << " " << xE[1] << " " << yE[1] << endl;
      //fout << nE << endl;
      
      
      fout.close();
      fclose(fin);
      //fin.close();
      return 0;
}
