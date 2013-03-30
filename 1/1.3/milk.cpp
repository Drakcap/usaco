/*
ID: drakcap1
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

struct Farmer {
       
       int preco;
       int quantidade;
       
       bool operator < (const Farmer &f)
       {
            return (preco < f.preco);
       }
};

int main()
{
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    
    int milk, n_farmers;
    list<Farmer> farmers;
    
    fin >> milk >> n_farmers;
    
    for (int i = 0; i < n_farmers; i++) {
        Farmer f;
        fin >> f.preco;
        fin >> f.quantidade;
        farmers.push_back(f);     
    }
    
    farmers.sort();
    int preco = 0;
    
    list<Farmer>::iterator it = farmers.begin();
    
    while (milk > 0)
    {
          
          int quantidade = (it->quantidade > milk ? milk : it->quantidade);
          preco += quantidade * it->preco;
          milk -= quantidade;
          ++it;
          
    }
    
    fout << preco << endl;
        
    
    fout.close();
    fin.close();    
    return 0;
    
}
