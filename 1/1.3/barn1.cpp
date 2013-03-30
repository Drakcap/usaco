/*
ID: drakcap1
PROG: barn1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");
    
    int n_placas, n_estabulos, n_vacas;
    
    fin >> n_placas >> n_estabulos >> n_vacas;

    list<int> espacos_sem_vacas;
    vector<int> vacas;
    
    for (int i = 0; i < n_vacas; i++) {
        int temp;
        fin >> temp;
        vacas.push_back(temp);
    }
    sort(vacas.begin(), vacas.end());
    
    int n_anterior = vacas[0];
    int n_inicial = n_anterior;
    
    for (int i = 1; i < n_vacas; i++) {
        int temp;
        temp = vacas[i];
        
        int dif = temp - n_anterior -1;
        
        if (dif >= 1) {
                espacos_sem_vacas.push_back(dif);
        }
        n_anterior = temp;    
    }
    
    espacos_sem_vacas.sort();
    
    list<int>::reverse_iterator it = espacos_sem_vacas.rbegin();
    --n_placas;
    int resposta = n_anterior - n_inicial + 1;
    
    while (n_placas > 0 && it != espacos_sem_vacas.rend()) {
          
          resposta -=*it;
          //fout << *it << endl;
          
          --n_placas;
          ++it;      
    }
    
    fout << resposta << endl;
    
    fout.close();
    fin.close();    
    return 0;
    
}    
