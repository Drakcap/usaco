/*
ID: drakcap1
PROG: calfflac
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string texto;
string texto_original;
int tam_texto;
int tam_max_pal = 0; //tamanho do maior palindromo

int ix_esq_max_pal; //inicio do max_pal
int ix_dir_max_pal; //fim do max_pal
//string max_pal;

//variaveis usadas para tratamento de cada indice
int tam_esq;
int tam_dir;
int tam_meio; 

ofstream fout ("calfflac.out");


bool is_letra (char c)
{
     
     if (c >= 'a' && c <= 'z') {
           return true;
     }
     
     if (c >= 'A' && c <= 'Z') {
           return true;
     }
     
     return false;
     
}

void minusculas ()
{
     
     for (int i = 0; i < tam_texto; i++) {
         texto[i] = tolower(texto[i]);
     }
     
}

void processa_indice (int ix)
{
     
     tam_esq = tam_dir = 0;
     tam_meio = 1;
     
     int ix_esq = ix-1;
     int ix_dir = ix+1;
     
     int max_dir = tam_texto-1;
     
     bool letra = is_letra(texto[ix_esq]);
     
     //calcula tamanho do meio para a esquerda
     while ( (! letra || texto[ix_esq] == texto[ix]) && ix_esq >= 0) {
           
           if (letra) {
              ++tam_meio;
           }
           --ix_esq;
           
           if (ix_esq >= 0)
           letra = is_letra(texto[ix_esq]);      
     }
     ++ix_esq;
     
     if (! letra ) {
           ++ix_esq;
     }
     
     letra = is_letra(texto[ix_dir]);
     
     //calcula tamanho do meio para a direita
     while ( (! letra || texto[ix_dir] == texto[ix]) && ix_dir <= max_dir) {
           if (letra) {
              ++tam_meio;
           }
           ++ix_dir;
           
           if (ix_dir <= max_dir)
           letra = is_letra(texto[ix_dir]);
     }
     --ix_dir;
     
     if (! letra ) {
           --ix_dir;
     }
     
     
     //guardar os valores do meio
     int ix_dir_ant = ix_dir;
     int ix_esq_ant = ix_esq;
     
     //fout << ix_dir << " " << ix_esq << endl;
     
     
     //expande palindromo a partir do meio
     while (ix_esq > 0 && ix_dir < max_dir)
     {
           ix_dir_ant = ix_dir;
           ix_esq_ant = ix_esq;
           --ix_esq;
           ++ix_dir;
           
           //procura primeira letra para a esquerda do meio
           while (! is_letra(texto[ix_esq]) && ix_esq >= 0) {
                 //fout << "aki" << endl;
                 --ix_esq;
           }
           
           if (ix_esq < 0) { //nao encontrou nenhuma letra
              ix_esq = ix_esq_ant;
              break;
           }
           
           
           while (! is_letra(texto[ix_dir]) && ix_dir <= max_dir) {
                 ++ix_dir;
                 //fout << "aki" << endl;
           }
           
           //nao encontrou nenhuma letra
           if (ix_dir > max_dir ) {
                 ix_esq = ix_esq_ant;
                 ix_dir = ix_dir_ant;
                 break;
           }
           
           if (texto[ix_esq] == texto[ix_dir]) {
              ++tam_esq;
              ++tam_dir;
           }
           
           else {
                ix_esq = ix_esq_ant;
                ix_dir = ix_dir_ant;
                break;
           } 
           
     }
     
     
     
     int tamanho = tam_meio + tam_esq + tam_dir;
     //fout << tam_meio << endl;
     
     if (tamanho > tam_max_pal) {
        ix_esq_max_pal = ix_esq;
        ix_dir_max_pal = ix_dir;
        tam_max_pal = tamanho;             
     }
     
     
     
}

int main()
{

    ifstream fin ("calfflac.in");
    

    string temp;
    
    getline(fin, temp);
    texto = temp;
    
    while (getline(fin, temp)) {
          texto = texto + "\n" + temp;
    }
    tam_texto = texto.size();
    string texto_original = texto;
    minusculas();
    //fout << texto << endl;
    
    tam_texto = texto.size();
    
    for (int i = 0; i < tam_texto; i++) {
        if (is_letra(texto[i])) {
           processa_indice(i);
        }    
    }
    
    fout << tam_max_pal << endl;
    int tam = ix_dir_max_pal - ix_esq_max_pal + 1;
    //fout << ix_dir_max_pal << " " << ix_esq_max_pal << endl;
    fout << texto_original.substr(ix_esq_max_pal, tam) << endl;
    
    fout.close();
    fin.close();    
    return 0;
    
}   
