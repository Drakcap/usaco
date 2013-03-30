/*
ID: drakcap1
PROG: milk3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <set>
using namespace std;

ofstream fout("milk3.out");
ifstream fin("milk3.in");

list<int> sol;

struct Estado
{
       int a, b, c;
       int cap_a, cap_b, cap_c;
       /*
       bool operator < (const Estado &e) const
       {
            //if (a < e.a) return true;
            //if (b < e.b) return true;
            //if (c < e.c) return true;
            
            return false;
       }*/
       
       //bool operator == (const Estado &e) const
       //{
       //     return (a == e.a && b == e.b && c == e.c);
       //}
};

//set<Estado> est_ants;
bool estados[8001];

//verte do balde 1 para o balde 2
void verter(int &balde1, int cap1, int &balde2, int cap2)
{
     
     int sobra2 = cap2 - balde2;
     int troca = (sobra2 < balde1 ? sobra2 : balde1);
     
     balde1 -= troca;
     balde2 += troca;
     
}

bool procura_estado(Estado e)
{
     return (estados[e.a * 400 + e.b * 20 + e.c]);     
}





int main()
{
    
    queue<Estado> q_estados;
    memset(estados, false, 8001);
    
    Estado inicial;
    inicial.a = 0;
    inicial.b = 0;
    
    fin >> inicial.cap_a >> inicial.cap_b >> inicial.cap_c;
    
    inicial.c = inicial.cap_c;
    
    q_estados.push(inicial);
    
    //est_ants.insert(inicial);
    
    while (! q_estados.empty()) {
    
          Estado e = q_estados.front();
          q_estados.pop();
          
          //set<Estado>::iterator it = est_ants.find(e);
          
          if (procura_estado(e)) {
            
             //for (int i = 0; i < 8000; i++) fout << estados[i] << endl;
            
             //fout << estados[e.a * 400 + e.b * 20 + e.c] << endl;
             //fout << e.a << " " << e.b << " " << e.c << endl;
             continue;
          }
          //est_ants.insert(e);
          estados[e.a * 400 + e.b * 20 + e.c] = true;
          
          //fout << "Estado:" << endl;
          //fout << e.a << endl << e.b << endl << e.c << endl << endl;
          
          //encontra solucao
          if (e.a == 0) {
                  //fout << "sol: " << e.c << endl;
                  sol.push_back(e.c);
          }
          
          //c para a
          Estado e1 = e;
          verter(e1.c, e1.cap_c, e1.a, e1.cap_a);
          q_estados.push(e1);
          
          //c para b
          Estado e2 = e;
          verter(e2.c, e2.cap_c, e2.b, e2.cap_b);
          q_estados.push(e2);
          
          //a para b
          Estado e3 = e;
          verter(e3.a, e3.cap_a, e3.b, e3.cap_b);
          q_estados.push(e3);
          
          //a para c
          Estado e4 = e;
          verter(e4.a, e4.cap_a, e4.c, e4.cap_c);
          q_estados.push(e4);
          
          //b para a
          e4 = e;
          verter(e4.b, e4.cap_b, e4.a, e4.cap_a);
          q_estados.push(e4); 
          
          //b para c
          e4 = e;
          verter(e4.b, e4.cap_b, e4.c, e4.cap_c);
          q_estados.push(e4);
              
          
    }
    
    sol.sort();
    list<int>::iterator it = sol.begin();
    bool first_run = true;
    
    for ( ; it != sol.end(); it++) {
        if (! first_run) {
              fout << " ";
        }
        else {
             first_run = false;
        }
        fout << *it;
         
    }
    fout << endl;
    
    
    
    
    fout.close();
    fin.close();
    return 0;   
    
}
