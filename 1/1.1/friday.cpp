/*
ID: drakcap1
PROG: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

#define N_DIAS 7
#define N_MESES 12

int freq_dias[N_DIAS];

int sextas[N_MESES];
int dias_meses[N_MESES] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

bool leap_year (const int year)
{
     
     if (year % 4 != 0) {
        return false;
     }
     
     if (year % 100 == 0) {
        return (year % 400 == 0);
     }
     
     return true;
     
}

inline void prox_dia (int &dia_act, int num_dias)
{
     dia_act = (dia_act + num_dias) % N_DIAS;     
}

int main()
{
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
    
    for (int i = 0; i < N_DIAS; i++) {
        freq_dias[i] = 0;
    }
    
    
    int N;
    
    fin >> N;
    
    //sexta de 1900 calha num sabado
    sextas[0] = 6;
    int dia = 6;
    freq_dias[dia]++;
    
    for (unsigned i = 1; i < N_MESES; i++) {
        prox_dia(dia, dias_meses[i-1]);
        sextas[i] = dia;
        freq_dias[dia]++;
    }
    
    unsigned max = N + 1900;
    
    for (unsigned i = 1901; i < max; i++) {
        
        dia = sextas[N_MESES-1];
        
        for (unsigned j = 0; j < N_MESES; j++) {
            int mes_a_somar = (j == 0 ? 11 : j-1);
            int dias_a_somar;
            
            if (j == 2) {
               dias_a_somar = (leap_year(i) ? 29 : 28);
            }
            else {
                 dias_a_somar = dias_meses[mes_a_somar];
            }
            
            prox_dia(dia, dias_a_somar);
            sextas[j] = dia;
            freq_dias[dia]++;
        }
        
    }
    
    fout << freq_dias[6];
    
    for (unsigned i = 0; i < N_DIAS-1; i++) {
        fout << " " << freq_dias[i];
    }
    
    fout << endl;
    
    
    fout.close();
    fin.close();
    
    return 0;
}
