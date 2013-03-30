/*
ID: drakcap1
PROG: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <set>
using namespace std;

ofstream fout("numtri.out");
ifstream fin("numtri.in");

struct No {
       int valor;
       int soma_maxima; //soma maxima herdada (sem contar com valor)
       int linha;     
       
};

int nlinhas;
int n_nos;
int soma_maxima;
No* nos;
int pos_max;

void le_input()
{
     int num_no = 1;
     for (int linha = 1; linha <= nlinhas; linha++) {
         
         for (int i = 0; i < linha; i++) {
             fin >> nos[num_no].valor;
             nos[num_no].soma_maxima = 0; 
             nos[num_no].linha = linha;
             ++num_no;
         }  
     }   
}

void calcula_somas()
{
     int novo_valor;
     int filho1, filho2;
     
     for (int i = 1; i <= n_nos; i++) {
         if (nos[i].linha == nlinhas) {
            //fout << i << endl;
            break;
         }
         
         novo_valor = nos[i].soma_maxima + nos[i].valor;
         filho1 = nos[i].linha + i;
         filho2 = filho1 + 1;
         
         //filho 1
         if (novo_valor > nos[filho1].soma_maxima) {
            nos[filho1].soma_maxima = novo_valor;
         }
         
         //filho2
         if (novo_valor > nos[filho2].soma_maxima) {
            nos[filho2].soma_maxima = novo_valor;
         }  
         
     }     
         
}

void
verifica_max()
{
    int pos = ((nlinhas-1)*nlinhas)/2 + 1;
    int soma;
    
    for (int i = 0; i < nlinhas; i++, pos++) {
        soma = nos[pos].valor + nos[pos].soma_maxima;
        
        if (soma > soma_maxima) {
           soma_maxima = soma;
           pos_max = pos;
        }  
    }
              
              
}


int main()
{
    
    fin >> nlinhas;
    n_nos = (nlinhas*(nlinhas+1))/2;
    
    nos = new No[n_nos+1];
    
    le_input();
    
    /*for (int i = 1; i <= n_nos; i++) {
        fout << i << " " << nos[i].valor << " " << nos[i].linha << endl;    
    }*/
    
    calcula_somas();
    
    verifica_max();
    
    //fout << pos_max << endl;
    fout << soma_maxima << endl;
    
    
    delete[] nos;
    
    fout.close();
    fin.close();
    return 0;
}
