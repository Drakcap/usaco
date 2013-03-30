/*
ID: drakcap1
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

typedef map<string, int> mapa;

string p[10];

int main()
{
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");
    
    int n;
    
    //while (fin >> n) {
            
            fin >> n;

          mapa pessoas;
    
          for (int i = 0; i < n; i++) {
              string temp;
              fin >> temp;
              pessoas.insert(make_pair(temp, 0));
              p[i] = temp;
          }
                
          string person;
          
          while (fin >> person) {
                
                int money, n_people;
                fin >> money >> n_people;
          
                if (money == 0 && n_people == 0) {
                   continue;
                }
                
                mapa::iterator it = pessoas.find(person);
                
                it->second += (money % n_people) - money;
                int division = money / n_people;

                
                for (int i = 0; i < n_people; i++) {
                    string temp;
                    fin >> temp;
                    mapa::iterator itr = pessoas.find(temp);
                    itr->second += division;  
                }    
              
          }
          
          for (int i = 0; i < n; i++) {
              fout << p[i] << " " << pessoas.find(p[i])->second << endl;
          }
          
   // }
    
    fout.close();
    fin.close();
    
    return 0;
}
