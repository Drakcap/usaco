/*
ID: drakcap1
PROG: transform
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int N;

void rot_90 (int &x, int &y)
{
     double meio =  (double(N-1) / 2);
     
     double temp_x = x - meio;
     double temp_y = y - meio;
     
     x = int (temp_y + meio);
     y = int (- temp_x + meio);
     
}

void rot_180 (int &x, int &y)
{
     /*double meio =  (double(N-1) / 2);
     
     double temp_x = x - meio;
     double temp_y = y - meio;
     
     x = int (- temp_x + meio);
     y = int (temp_y + meio);*/
     rot_90(x,y);
     rot_90(x,y);
}

void rot_270 (int &x, int &y)
{
     double meio =  (double(N-1) / 2);
     
     double temp_x = x - meio;
     double temp_y = y - meio;
     
     x = int (-temp_y + meio);
     y = int (temp_x + meio);
}

void transf4 (int &y, int &x)
{
     
     double meio =  (double(N-1) / 2);
     
     double diff = meio - x;
     
     x = int (meio + diff);
     
     
}
     

int main()
{
    /*
    int x = 0;
    int y = 2;
    N = 3;
    rot_90(x,y);
    cout << x << " " << y << endl;
    cin.get();*/
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    fin >> N;
    
    string* padrao;
    string* transf;
    
    padrao = new string[N];
    transf = new string[N];
    
    for (int i = 0; i < N; i++) {
        fin >> padrao[i];
    }
    for (int i = 0; i < N; i++) {
        fin >> transf[i];
    }
    
    bool _1 = true;
    bool _2 = true;
    bool _3 = true;
    bool _4 = true;
    bool _5 = true;
    bool _5_1 = true;
    bool _5_2 = true;
    bool _5_3 = true;
    bool _6 = true;
    
    
    for (int i = 0; i < N; i++) {
        
        for (int j = 0; j < N; j++) {
        
            //1 ainda e' hipotese
            if (_1) {
                
                int x = i, y = j;
                rot_90(x, y);
                
                if (padrao[i][j] != transf[x][y]) {
                      _1 = false;
                }                 
            }
            
            if (_2) {
               
               int x = i, y = j;
               rot_180(x, y);
                
               if (padrao[i][j] != transf[x][y]) {
                      _2 = false;
               }
                    
                    
            }
            
            if (_3) {
                    
               int x = i, y = j;
               rot_270(x, y);
                
               if (padrao[i][j] != transf[x][y]) {
                      _3 = false;
               }                    
                    
            }
            
            if (_4) {
                   
               int x = i, y = j;
               transf4(x, y);
                
               if (padrao[i][j] != transf[x][y]) {
                       //fout << "falhou em: " << i << " " << j << " " << x << " " << y << endl;
                       //fout << padrao[i][j] << " " << transf[x][y] << endl;
                      _4 = false;
               }  
                   
            }
            
            if (_5) {
                    
                    int x = i, y = j;
                    
                    //espelho
                    transf4(x,y);
                    
                    if (_5_1) {
                       int temp_x = x, temp_y = y;
                       rot_90(temp_x,temp_y);
                       if (padrao[i][j] != transf[temp_x][temp_y]) {
                          _5_1 = false;
                       }                               
                              
                    }
                    
                    if (_5_2) {
                       int temp_x = x, temp_y = y;
                       rot_180(temp_x,temp_y);
                       if (padrao[i][j] != transf[temp_x][temp_y]) {
                          _5_2 = false;
                       }                               
                              
                    }
                    
                    if (_5_3) {
                       int temp_x = x, temp_y = y;
                       rot_270(temp_x,temp_y);
                       if (padrao[i][j] != transf[temp_x][temp_y]) {
                          _5_3 = false;
                       }                               
                              
                    }
                    
                    
                    
                    if (! (_5_1 || _5_2 || _5_3) ) {
                          _5 = false;
                    }        
            }
            
            if (_6) {
                    
                    if (padrao[i][j] != transf[i][j]) {
                       _6 = false;
                    }
                    
            }   
            
        }
    }
    
    if (_1) {
       fout << 1 << endl;
    }
    else if (_2) {
       fout << 2 << endl;
    }
    else if (_3) {
       fout << 3 << endl;
    }
    else if (_4) {
       fout << 4 << endl;
    }
    else if (_5) {
       fout << 5 << endl;
    }
    else if (_6) {
       fout << 6 << endl;
    }
    else {
         fout << 7 << endl;
    }
         
    
    
    fout.close();
    fin.close();    
    return 0;
}
