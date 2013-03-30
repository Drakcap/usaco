/*
ID: drakcap1
PROG: palsquare
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
             
             if (mod < 10) {
                s[i] = ('0' + mod);        
             }
             else {
                  s[i] = ('A' + (mod - 10));
             }
             
             num = num / base;
             
       }
       
       return s;
       
       
       
}

int main()
{

    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
    
    int base;
    
    fin >> base;
    
    for (unsigned i = 1; i <= 300; i++) {
        int square = i*i;
        string s = to_base(square, base);
        if (is_palindrome(s)) {
           fout << to_base(i,base) << " " << s << endl;
        }
        
    }
    
    
        
    
    fout.close();
    fin.close();    
    return 0;
    
}
