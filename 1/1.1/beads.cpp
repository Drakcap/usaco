/*
ID: drakcap1
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;





int main()
{
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
    
    int N;
    string colar;
    unsigned max = 0;
    
    fin >> N >> colar;
    
    unsigned tam_i = colar.size();
    
    colar = colar + colar;
    //fout << colar << endl;
    
    bool azul;
    unsigned tam = 0;
    
    //procura a primeira cor
    while (colar[tam] == 'w') ++tam;
    
    azul = (colar[tam] == 'b' ? true : false);
    
    unsigned tam_meio = 0;
    unsigned tam_esq = tam;
    unsigned tam_dir = 0;
    unsigned i = tam;
    
    //procura primeira parte
    for ( ; i < colar.size(); i++) {
        
        if (azul) {
        
           if (colar[i] == 'b') {
              tam_esq++;
              tam_meio = 0;
           }
           else if (colar[i] == 'w') {
                ++tam_esq;
                ++tam_meio;
           }
           else
               break;
        }
        
        else {
             
           if (colar[i] == 'r') {
              tam_esq++;
              tam_meio = 0;
           }
           else if (colar[i] == 'w') {
                ++tam_esq;
                ++tam_meio;
           }
           else
               break;
        }             
             
    }
    
    if (tam_esq >= tam_i) {
       fout << tam_i << endl;
       return 0;
    }
    
    azul = !azul;
    
    tam_esq -= tam_meio;
    tam_dir = tam_meio;
    
    while (i < colar.size()) {
          
          if (colar[i] == 'w') {
             ++tam_meio;
             ++tam_dir;
          }
          else if (azul) {
          
               if (colar[i] == 'b') {
                  ++tam_dir;
                  tam_meio = 0;
               }
               
               else {
                    //fout << "esquerda: " << tam_esq << " direita: " << tam_dir << " meio: " << tam_meio << " i: " << i << endl;
                    if (tam_esq + tam_dir > max) {
                       max = tam_esq + tam_dir;
                    }
                    tam_esq = tam_dir - tam_meio;
                    tam_dir = 1 + tam_meio;
                    tam_meio = 0;
                    azul = !azul;                     
               }     
               
          }
          else {
               
               if (colar[i] == 'r') {
                  ++tam_dir;
                  tam_meio = 0;
               }
               
               else {
                    //fout << "esquerda: " << tam_esq << " direita: " << tam_dir << " meio: " << tam_meio << " i: " << i << endl;
                    if (tam_esq + tam_dir > max) {
                       max = tam_esq + tam_dir;
                    }
                    tam_esq = tam_dir - tam_meio;
                    tam_dir = 1 + tam_meio;
                    tam_meio = 0;    
                    azul = !azul; 
               }                
               
               
          }

          ++i;
          
    }
    

    
    
    //char procura = (azul ? 'b' : 'r');
    

    if (max >= tam_i) {
       fout << tam_i << endl;
 
    }
    else
    fout << max << endl;

    fout.close();
    fin.close();   
    return 0;
    
}
