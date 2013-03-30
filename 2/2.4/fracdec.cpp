/*
ID: drakcap1
PROG: fracdec
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
using namespace std;

ofstream fout("fracdec.out");
ifstream fin("fracdec.in");

#define MAX 100001

int decimal[MAX];
int nDecimal;

bool restos[MAX];

int repetido;
bool rep;
int ixRep;

int nO;

int N, D;

int
main()
{
      fin >> N >> D;
      
      int resto;
      
      fout << N / D;
      
      char temp[10000];
      sprintf(temp, "%d", N/D);
      
      nO += strlen(temp);
      
      resto = N % D;
      
      fout << ".";
      
      ++nO;
      
      //int i = 0;
      
      if (resto == 0) fout << 0;
      
      while (resto != 0) {
            if (restos[resto]) {
               //fout << "resto: " <<  resto << endl;
               repetido = resto*10 / D;
               rep = true;
               break;                   
            }
            restos[resto] = true;
            resto *= 10;
            decimal[nDecimal++] = resto / D;
            
            resto = resto % D;
            
            //++i;      
      }
      
      for (int i = nDecimal-1; i >= 0; i--) if (decimal[i] == repetido) ixRep= i;
      
      
      for (int i = 0; i < nDecimal; i++) {
          if (i == ixRep && rep) {
             if (nO % 76 == 0) fout << endl;
             fout << "(";
             ++nO;
          }
          if (nO % 76 == 0) fout << endl;
          fout << decimal[i];
          ++nO;
      }
      if (nO % 76 == 0) fout << endl;
      if (rep) fout << ")";
      
      fout << endl;
      
      fout.close();
      fin.close();
      return 0;
      
}
