/*
ID: drakcap1
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

struct Farmer {

       long long int inicio;
       long long int fim; 
       
       bool operator<(const Farmer &f) {
            return inicio < f.inicio;     
       }      
       
};

long long int ult_tempo = 0;
long long int novo_tempo = 0;    
list<Farmer> farmers;
list<long long int> fins;
int farmers_no_activo = 0;
long long int max_cont = 0;
long long int max_idle = 0;
long long int cont = 0;
long long int idle = 0;
bool fim = false;



//devolve true se a proxima accao for um farmer entrar em accao
//devolve false se a proxima accao for um farmer sair de accao ou ja nao houver mais accoes
bool ve_tempo()
{
     
     if (farmers.size() == 0 && fins.size() == 0) {
        fim = true;
        return false;
     }
     
     if (farmers.size() == 0) {
        novo_tempo = *fins.begin();
        fins.pop_front();
        return false;
     }
     
     list<Farmer>::iterator it = farmers.begin();
     
     if (fins.size() == 0 || it->inicio <= *fins.begin()) {
        novo_tempo = it->inicio;
        fins.push_back(it->fim);
        fins.sort();
        farmers.pop_front();
        return true;
     }
     else {
          novo_tempo = *fins.begin();
          fins.pop_front();
          return false;       
     }
        
}

int main()
{
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
    
    
    int N;
    
    fin >> N;
    

    
    for (int i = 0; i < N; i++) {
        Farmer f;    
        fin >> f.inicio;
        fin >> f.fim;
        farmers.push_back(f);
    }
    
    farmers.sort();
    
    bool first_run = true;
    
    while (true)
    {
          bool ocorr = ve_tempo();
          
          if (! first_run) {
              if (farmers_no_activo == 0) {
                 idle += novo_tempo - ult_tempo;
                 if (cont > max_cont) max_cont = cont;
                 cont = 0;
              }
              else {
                   cont += novo_tempo - ult_tempo;
                   if (idle > max_idle) max_idle = idle;
                   idle = 0;    
              }
          }
          
          if (! ocorr && fim) break;
          
          else if (ocorr) {
               ++farmers_no_activo;
          }
          
          else {
               --farmers_no_activo;     
          }
          
          ult_tempo = novo_tempo;
          first_run = false;
          
    }
    
    fout << max_cont << " " << max_idle << endl;
    
    
    fout.close();
    fin.close();   
    return 0;
    
}
