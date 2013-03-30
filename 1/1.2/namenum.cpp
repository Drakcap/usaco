/*
ID: drakcap1
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


char nums[25] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9'};



int main()
{
    
    ifstream fin("namenum.in");
    ifstream dic("dict.txt");
    ofstream fout("namenum.out");
    
    string linha, palavra;
    bool ha_palavra = false;
    
    fin >> linha;

    
    while (dic >> palavra) {
    
          if (palavra.size() != linha.size()) {                 
            continue;
          }
           
           bool palavra_serve = true;
            
           for (unsigned i = 0; i < palavra.size(); i++) {
               if (nums[palavra[i]-'A'] != linha[i]) {
                  palavra_serve = false;
                  break;
               }
               
           }
           
           if (palavra_serve) {
              ha_palavra = true;
              fout << palavra << endl;
           }
          
    }
    

    if (! ha_palavra) {
          fout << "NONE" << endl;
    }
    


    
    dic.close();
    fout.close();
    fin.close();    
    return 0;
}
