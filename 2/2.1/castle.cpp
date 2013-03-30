/*
ID: drakcap1
PROG: castle
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

#define MAX 2500
#define NORTE 0
#define ESTE 1
#define SUL 2
#define OESTE 3

ofstream fout("castle.out");
ifstream fin("castle.in");


struct No {
       int quarto;              //identificador do quarto
       //bool ligacoes[4];        //ligacoes normais     
       //bool lig_paredes[4];     //ligacoes com paredes
       int valor;
       bool visited;
};

No nos[50][50];
int quartos[MAX];  //tamanho de cada quarto
int nQuartos;
int maiorQuarto;
int maiorRemove;
int linhaMR;
int colunaMR;
int dirMR;
int M, N;


inline void
le_castelo()
{
      
      for (int i = 0; i < N; i++) {
          for (int j = 0; j < M; j++) {
              nos[i][j].visited = false;
              fin >> nos[i][j].valor;
          }
      }            
            
}

int
dfs(int linha, int coluna, int quarto)
{
        nos[linha][coluna].visited = true;
        nos[linha][coluna].quarto = quarto;
        
        int norte = 0, este = 0, sul = 0, oeste = 0;
        
        //para norte
        if (linha > 0 && !(nos[linha][coluna].valor & 2) && !nos[linha-1][coluna].visited) {
           //fout << linha << " " << coluna << " para norte" << endl;
           norte = dfs(linha-1, coluna, quarto);
        }
        
        //para este
        if (coluna < M-1 && !(nos[linha][coluna].valor & 4) && !nos[linha][coluna+1].visited) {
           //fout << linha << " " << coluna << " para este" << endl;
           este = dfs(linha, coluna+1, quarto);
        }
        
        //para sul
        if (linha < N-1 && !(nos[linha][coluna].valor & 8) && !nos[linha+1][coluna].visited) {
           //fout << linha << " " << coluna << " para sul" << endl;
           sul = dfs(linha+1, coluna, quarto);
        }
        
        //para oeste
        if (coluna > 0 && !(nos[linha][coluna].valor & 1) && !nos[linha][coluna-1].visited) {
           //fout << linha << " " << coluna << " para oeste" << endl;
           oeste = dfs(linha, coluna-1, quarto);
        }
        
        return norte + este + sul + oeste + 1;
}

void
remove_paredes(int linha, int coluna)
{
        int quarto = nos[linha][coluna].quarto;
        int tamQuarto = quartos[quarto];
        int novo_tam = tamQuarto;
        
        novo_tam = tamQuarto;
        
        //para norte
        if (linha > 0 && (nos[linha][coluna].valor & 2) && nos[linha-1][coluna].quarto != quarto) {
           novo_tam += quartos[nos[linha-1][coluna].quarto];
           
           if (novo_tam > maiorRemove || (novo_tam == maiorRemove && coluna < colunaMR)) {
               maiorRemove = novo_tam;
               linhaMR = linha;
               colunaMR = coluna;
               dirMR = NORTE;
           }
        }

        
        novo_tam = tamQuarto;
        
        //para este
        if (coluna < M-1 && (nos[linha][coluna].valor & 4)  && nos[linha][coluna+1].quarto != quarto) {
           novo_tam += quartos[nos[linha][coluna+1].quarto];
           
           if (novo_tam > maiorRemove || (novo_tam == maiorRemove && coluna < colunaMR)) {
               maiorRemove = novo_tam;
               linhaMR = linha;
               colunaMR = coluna;
               dirMR = ESTE;
           }
        }
        
        

                   
                   
                   
}


int
main()
{
      fin >> M >> N;
      
      le_castelo();
      
      //calculo dos quartos
      for (int i = 0; i < N; i++) {
          for (int j = 0; j < M; j++) {
              if (! nos[i][j].visited) {
                 quartos[nQuartos] = dfs(i, j, nQuartos);
                 if (quartos[nQuartos] > maiorQuarto) {
                    maiorQuarto = quartos[nQuartos];
                 }
                 ++nQuartos;
              }
          }
      }
      
      //remove paredes
      for (int i = N-1; i >= 0; i--) {
          for (int j = M-1; j >= 0; j--) {
              remove_paredes(i, j);        
          }
      }
      
      
      
      fout << nQuartos << endl;
      fout << maiorQuarto << endl;
      fout << maiorRemove << endl;
      fout << linhaMR + 1 << " " << colunaMR + 1 << " ";
      
      if (dirMR == NORTE) fout << "N" << endl;
      else if (dirMR == ESTE) fout << "E" << endl;
      else if (dirMR == OESTE) fout << "O" << endl;
      else fout << "S" << endl;
      
      fout.close();
      fin.close();
      return 0;
}
