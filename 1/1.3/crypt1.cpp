/*
ID: drakcap1
PROG: crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
using namespace std;

int n;
int nums[10];
int nums_ord[9];
int resposta = 0;

ofstream fout ("crypt1.out");

/*
string to_string (int num)
{
       string s = "";
       unsigned i = 0;
       
       while (num > 0) {
             s = " " + s;
             s[i] = num % 10;
             num = num / 10;
             ++i;
       }
             
       return s;
       
}*/

bool serve_num (int num1, int n_digits)
{
     int n_dig = 0;
     
     while (num1 > 0)
     {
           int mod = num1 % 10;
           
           if (nums[mod] == false) {
              return false;
           }
           
           num1 = num1 / 10;
           ++n_dig;
           
           if (n_dig > n_digits) {
              return false;
           }
     }
     
     return true;
}
     
     

bool serve (int num1, int num2)
{
     
     /*
     if (! serve(num1) ) {
           return false;
     }*/
     
     if (! serve_num(num2, 2) ) {
           return false;
     }
     
     int mult = num1 * num2;
     
     if (! serve_num(mult, 4) ) {
           return false;
     }
     
     int dig_1 = num2 % 10;
     int dig_2 = num2 / 10;
     
     int mult1 = dig_1 * num1;
     
     if (! serve_num(mult1, 3) ) {
           return false;
     }
     
     int mult2 = dig_2 * num1;
     
     if (! serve_num(mult2, 3) ) {
           return false;
     }
     
     return true;
     
     
}

void calc_solucoes (int num1)
{
     
     for (int i = 0; i < n; i++) {
         int temp = nums_ord[i];
         for (int j = 0; j < n; j++) {
             int temp2 = temp;
             temp2 += nums_ord[j] * 10;
             if ( serve(num1, temp2) ) {
                  //fout << num1 << " " << temp2 << endl;
                  ++resposta;
             }
         }
     }
     
}

void calc_solucoes ()
{
     
     for (int i = 0; i < n; i++) {
         int temp = nums_ord[i];
         for (int j = 0; j < n; j++) {
             int temp2 = temp;
             temp2 += nums_ord[j] * 10;
             for (int k = 0; k < n; k++) {
                 int temp3 = temp2;
                 temp3 += nums_ord[k] * 100;
                 if (serve_num(temp3, 3)) {
                    calc_solucoes(temp3);
                 }
             }
             
         }
         
     }
     
}


int compare(const void *a,const void *b) {
    int c,d;
    c=*(int*)a;
    d=*(int*)b;
    return c-d;
}

int main()
{
    ifstream fin ("crypt1.in");
    
    fin >> n;
    
    for (int i = 0; i < 10; i++) {
        nums[i] = false;    
    }
    
    for (int i = 0; i < n; i++) {
        fin >> nums_ord[i];
        nums[nums_ord[i]] = true;   
    }
    
    //qsort(nums_ord, n, sizeof(int), compare);
    
    calc_solucoes();
    
    fout << resposta << endl;
     
    
    fout.close();
    fin.close();    
    return 0;    
    
}
