/*
ID: drakcap1
PROG: dualpal
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

bool is_palindrome (string num)
{
     int inicio = 0;
     int fim = num.size()-1;
     
     while (inicio < fim) {
           if (num[inicio] != num[fim]) {
              return false;
           }
           
           inicio++;
           fim--;
     }
     
     return true;
     
}

string to_base(int num, int base)
{
       
       string s = "";
       unsigned i = 0;
       
       while (num > 0) {
             int mod = num % base;
             s = " " + s;
             
             s[i] = ('0' + mod);        
             
             num = num / base;
             
       }
       
       return s;
         
}


int main()
{

    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");
    
    int N, S;
    
    fin >> N >> S;
    
    ++S;
    
    while (N > 0) {
          
          int count = 0;
          
          for (unsigned i = 2; i <= 10; i++) {
              
              string s = to_base(S, i);
              //fout << s << endl;
              
              if (is_palindrome(s)) ++count;
              
              if (count == 2) {
                 fout << S << endl;
                 N--;
                 break;
              }
          }
          
          //fout << endl;
          
          ++S;
    }
    
    
    fout.close();
    fin.close();    
    return 0;
    
}    
