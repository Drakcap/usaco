/*
ID: drakcap1
PROG: packrec
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

ofstream fout("packrec.out");

struct Rectangulo {
       
       int largura;
       int comprimento;
       
       bool operator < (Rectangulo& r) const {
            return largura < r.largura;
       }

};

void cria_rect(int largura, int comprimento, Rectangulo &rect)
{          
       if (largura > comprimento) swap(largura,comprimento);      
       rect.largura = largura;
       rect.comprimento = comprimento;    
}

struct Solucao {
       
       int area;
       int largura;
       int comprimento;
       
       bool operator < (const Solucao &sol) const
       {
            return (largura < sol.largura);     
       }
};

void cria_sol (int l1, int l2, Solucao &sol)
{
     if (l1 > l2) swap(l1,l2);     
     
     sol.largura = l1;
     sol.comprimento = l2;
     sol.area = l1 * l2;
     
}

Rectangulo rect[4];
list<Solucao> sol;
int min_area = -1;

//true se a solucao for melhor ou igual
bool verifica_solucao (Solucao &s)
{
     
     if (s.largura > s.comprimento) swap(s.largura,s.comprimento); //poe-na correcta para depois fazer a ordenacao
     
     if (s.area < min_area || min_area == -1) {
        min_area = s.area;             
        sol.clear(); 
        sol.push_back(s);
        return true;         
     }
     else if (s.area == min_area) {
          sol.push_back(s);
          return true;
     }   
     return false;
}


void primeira(int ix, bool em_pe, Solucao &s)
{
     
     if (ix == 4) {
            s.area = s.comprimento * s.largura;
            verifica_solucao(s);
            return;
     }
     
     //o rectangulo esta de pe
     else if (em_pe == true)
     {
          Solucao antiga_solucao = s;
          
          if (rect[ix].comprimento > s.comprimento) {
             s.comprimento = rect[ix].comprimento;                         
          }
          s.largura += rect[ix].largura;
          
          primeira(ix, false, antiga_solucao); //testa com o rectangulo deitado
          primeira(ix+1,true, s); //continua com a solucao actual
     }
     
     //o rectangulo esta deitado
     else {
          
          if (rect[ix].largura > s.comprimento) {
             s.comprimento = rect[ix].largura;
          }       
          s.largura += rect[ix].comprimento;
          
          primeira(ix+1, true, s); //continua com a solucao actual
     }

     
}

void segunda(int baixo, int ix, bool em_pe, Solucao &s)
{
     
     if (ix == 4) {
            
            //soma dimensoes do rectangulo deitado
            s.largura = (s.largura > rect[baixo].comprimento ? s.largura : rect[baixo].comprimento);
            s.comprimento += rect[baixo].largura;
            
            s.area = s.comprimento * s.largura;
            verifica_solucao(s);
            //if (verifica_solucao(s)) fout << baixo << endl;
            return;            
     }
     
     if (ix == baixo) {
        segunda(baixo,ix+1,em_pe, s);       
     }
     
     //"igual" ao primeiro daqui para baixo
     
     //o rectangulo esta de pe
     else if (em_pe == true)
     {
          Solucao antiga_solucao = s;
          
          if (rect[ix].comprimento > s.comprimento) {
             s.comprimento = rect[ix].comprimento;                         
          }
          s.largura += rect[ix].largura;
          
          segunda(baixo, ix, false, antiga_solucao); //testa com o rectangulo deitado
          segunda(baixo, ix+1,true, s); //continua com a solucao actual
     }
     
     //o rectangulo esta deitado
     else {
          
          if (rect[ix].largura > s.comprimento) {
             s.comprimento = rect[ix].largura;
          }       
          s.largura += rect[ix].comprimento;
          
          segunda(baixo, ix+1, true, s); //continua com a solucao actual
     }     
     

      
}

void terceira(int baixo, int lado, int ix, bool em_pe, Solucao &s)
{
     
     if (ix == 4) {
        
        //com o rectangulo de baixo deitado
        Solucao s1 = s;
        s1.comprimento += rect[baixo].largura;
        s1.largura = (s1.largura > rect[baixo].comprimento ? s1.largura : rect[baixo].comprimento);
        
        //com o rectangulo de baixo de pe
        Solucao s2 = s;
        s2.comprimento += rect[baixo].comprimento;
        s2.largura = (s2.largura > rect[baixo].largura ? s2.largura : rect[baixo].largura);
        
        //com o rectangulo do lado em pe
        Solucao s3 = s1;
        Solucao s4 = s2;
        
        s3.largura += rect[lado].largura;
        s4.largura += rect[lado].largura;
        
        s3.comprimento = (s3.comprimento > rect[lado].comprimento ? s3.comprimento : rect[lado].comprimento);
        s4.comprimento = (s4.comprimento > rect[lado].comprimento ? s4.comprimento : rect[lado].comprimento);
        
        s3.area = s3.comprimento*s3.largura;
        s4.area = s4.comprimento*s4.largura;
        verifica_solucao(s3);
        verifica_solucao(s4);
        
        //com o rectangulo do lado deitado
        Solucao s5 = s1;
        Solucao s6 = s2;
        
        s5.largura += rect[lado].comprimento;
        s6.largura += rect[lado].comprimento;
        
        s5.comprimento = (s5.comprimento > rect[lado].largura ? s5.comprimento : rect[lado].largura);
        s6.comprimento = (s6.comprimento > rect[lado].largura ? s6.comprimento : rect[lado].largura);
        
        s5.area = s5.comprimento*s5.largura;
        s6.area = s6.comprimento*s6.largura;
        verifica_solucao(s5);
        verifica_solucao(s6); 
        
        return;    
            
     }
     
     if (ix == baixo || ix == lado) {
            terceira(baixo,lado,ix+1,true,s);
     }
     
     //"igual" ao primeiro daqui para baixo
     
     //o rectangulo esta de pe
     else if (em_pe == true)
     {
          Solucao antiga_solucao = s;
          
          if (rect[ix].comprimento > s.comprimento) {
             s.comprimento = rect[ix].comprimento;                         
          }
          s.largura += rect[ix].largura;
          
          terceira(baixo, lado, ix, false, antiga_solucao); //testa com o rectangulo deitado
          terceira(baixo, lado, ix+1,true, s); //continua com a solucao actual
     }
     
     //o rectangulo esta deitado
     else {
          
          if (rect[ix].largura > s.comprimento) {
             s.comprimento = rect[ix].largura;
          }       
          s.largura += rect[ix].comprimento;
          
          terceira(baixo, lado, ix+1, true, s); //continua com a solucao actual
     }      
}

void quarta_aux (int baixo, int cima, bool em_pe_cima, bool em_pe_baixo, Solucao s)
{
     
     int soma_largura = 0, soma_comprimento = 0;
     
     if (em_pe_cima) {
        soma_largura += rect[cima].largura;
        soma_comprimento += rect[cima].comprimento;
     }
     else {
          soma_largura += rect[cima].comprimento;
          soma_comprimento += rect[cima].largura;
     }
     
     if (em_pe_baixo) {
        soma_largura = (soma_largura > rect[baixo].largura ? soma_largura : rect[baixo].largura);                 
        soma_comprimento += rect[baixo].comprimento;              
     }
     else {
          soma_largura = (soma_largura > rect[baixo].comprimento ? soma_largura : rect[baixo].comprimento);     
          soma_comprimento += rect[baixo].largura;
     }
     
     s.largura += soma_largura;
     s.comprimento = (s.comprimento > soma_comprimento ? s.comprimento : soma_comprimento);
     
     s.area = s.comprimento * s.largura;
     verifica_solucao(s);
     
     
}


//quarta e quinta num mesmo
void quarta(int baixo, int cima, int ix, bool em_pe, Solucao &s)
{
     
     if (ix == 4) {
            
            //os dois em pe
            quarta_aux(baixo,cima,true,true,s);
            
            //os dois deitados
            quarta_aux(baixo,cima,false,false,s);
            
            //o de cima deitado, o de baixo em pe
            quarta_aux(baixo,cima,false,true,s);
            
            //o de cima em pe, o de baixo deitado
            quarta_aux(baixo,cima,true,false,s);
            
            return;
     }
     
     if (ix == baixo || ix == cima) {
            quarta(baixo,cima,ix+1,em_pe,s);
     }
     
     //"igual" ao primeiro daqui para baixo
     
     //o rectangulo esta de pe
     else if (em_pe == true)
     {
          Solucao antiga_solucao = s;
          
          if (rect[ix].comprimento > s.comprimento) {
             s.comprimento = rect[ix].comprimento;                         
          }
          s.largura += rect[ix].largura;
          
          quarta(baixo, cima, ix, false, antiga_solucao); //testa com o rectangulo deitado
          quarta(baixo, cima, ix+1,true, s); //continua com a solucao actual
     }
     
     //o rectangulo esta deitado
     else {
          
          if (rect[ix].largura > s.comprimento) {
             s.comprimento = rect[ix].largura;
          }       
          s.largura += rect[ix].comprimento;
          
          quarta(baixo, cima, ix+1, true, s); //continua com a solucao actual
     }
     
     
}

bool combinacoes[16][4] = { {0,0,0,0}, {0,0,0,1}, {0,0,1,0}, {0,0,1,1},
                            {0,1,0,0}, {0,1,0,1}, {0,1,1,0}, {0,1,1,1},
                            {1,0,0,0}, {1,0,0,1}, {1,0,1,0}, {1,0,1,1},
                            {1,1,0,0}, {1,1,0,1}, {1,1,1,0}, {1,1,1,1} };


void sexta()
{
     
     /*bool em_pe[4];
     em_pe[0] = false;
     em_pe[1] = false;
     em_pe[2] = false;
     em_pe[3] = false;*/
     
     for (int i = 0; i < 16; i++) {
         Solucao s;
         s.comprimento = 0;
         s.largura = 0;
         s.area = 0;
         
         int comprimento_esq, comprimento_dir,largura_esq,largura_dir;
         
         //empilha o rectangulo da posicao 0
         if (combinacoes[i][0]) {
            s.largura += rect[0].largura;
            largura_esq = rect[0].largura;
            comprimento_esq = rect[0].comprimento;             
         }
         else {
              s.largura += rect[0].comprimento;
              largura_esq = rect[0].comprimento;
              comprimento_esq = rect[0].largura;
         }
         
         //empilha o rectangulo da posicao 1
         if (combinacoes[i][1]) {
            s.largura += rect[1].largura;
            largura_dir = rect[1].largura;
            comprimento_dir = rect[1].comprimento;
         }
         else {
              s.largura += rect[1].comprimento;
              largura_dir = rect[1].comprimento;
              comprimento_dir = rect[1].largura;
         }
         
         //fout << s.largura << endl;
         //fout << s.comprimento << endl;
         //fout << comprimento_esq << endl;
         //fout << comprimento_dir << endl;
         //fout << largura_esq << endl;
         //fout << largura_dir << endl;

         int ocupado_dir = 0;
         int dimensao, outra, dimensao2, outra2;
         
         if (combinacoes[i][3]) {
            dimensao = rect[3].largura;
            outra = rect[3].comprimento;
         }
         else {
              dimensao = rect[3].comprimento;
              outra = rect[3].largura;
         }
         
         if (combinacoes[i][2]) {
            dimensao2 = rect[2].largura;
            outra2 = rect[2].comprimento;
         }
         else {
              dimensao2 = rect[2].comprimento;
              outra2 = rect[2].largura;
         }
         
         int comprimento_esq_ant = comprimento_esq;
         int comprimento_dir_ant = comprimento_dir;
         
         //fout << comprimento_esq << " " << comprimento_dir << endl;
         //fout << outra << " " << outra2 << endl << endl;
         
         comprimento_esq += outra;
         comprimento_dir += outra2;
         
         //int largura_esq_ant = largura_esq;   
         
         bool acima = false;      
         
         //empilha o rectangulo na posicao 3
            
        //se a largura nao ultrapassar a largura do que esta em baixo, tasse bem
        if (dimensao <= largura_esq) {
                       
           //comprimento_esq += outra;                    
        }
        else {
             
             //espaco de sobra no lado direito
             int sobra_dir = (largura_dir-dimensao2);
             int sobra_esq = (dimensao - largura_esq);
             
             if (comprimento_esq_ant >= comprimento_dir) { //o lado esquerdo é mais alto que o direito, bora ocupar do direito
                ocupado_dir += sobra_esq;
                acima = true;
                //fout << i << endl;
                //comprimento_esq += outra;                    
             }
             
             //e' mais baixo, mas mesmo assim arranja uma maneira fixe
             else if (sobra_dir > 0 && comprimento_esq_ant >= comprimento_dir_ant ) {
                  ocupado_dir += (sobra_dir > sobra_esq ? sobra_esq : sobra_dir);
                  largura_esq += (sobra_esq - ocupado_dir);
                  //fout << "aki " << i << endl;
                  //fout << dimensao << endl;
                  //fout << i << endl;
                  //fout << "sobra_esq: " << sobra_esq << endl;
                  //fout << "sobra_dir: " << sobra_dir << endl;
             }
             
             else { //lado esquerdo mais baixo, vai ter que ficar de fora
             //fout << "aqui:" << largura_esq << " " << dimensao << endl;  
                  largura_esq = dimensao;
                  //comprimento_esq += outra;
                    
             }

             
        }
        

        
        
        
        
         /*fout << comprimento_esq << endl;
         fout << comprimento_dir << endl;
         fout << largura_esq << endl;
         fout << largura_dir << endl;     */             

         //empila o rectangulo na posicao 2
         
         int ocupado_esq = 0;
         
         int sobra_esq = (largura_esq - dimensao);
         int sobra_dir = (dimensao2 - largura_dir);

         
         //se a largura nao ultrapassar a largura do que esta em baixo, tasse bem
         if (dimensao2 <= largura_dir) {
                      //comprimento_dir += outra;             
         }
         else {
               //lado direito mais alto que o esquerdo, tasse bem
              if (comprimento_dir_ant >= comprimento_esq) {
                 ocupado_esq += (dimensao2 - largura_dir);
                 //comprimento_dir += outra;
              }
              
              else if (sobra_esq > 0 && comprimento_dir_ant >= comprimento_esq_ant ) {
                   ocupado_esq += (sobra_esq > sobra_dir ? sobra_dir : sobra_esq);
                   largura_dir += (sobra_dir - ocupado_esq);                 
              }
              
              else {  //vai ficar uma parte de fora
                   //fout << "antes: " << dimensao << endl;
                   largura_dir = dimensao2;
                   //fout << "depois: " << largura_dir << endl;     
              }     
                 
         }
         
         /*
         fout << comprimento_esq << endl;
         fout << comprimento_dir << endl;
         fout << largura_esq << endl;
         fout << largura_dir << endl;      */   
         
         //ve qual dos lados e' mais alto
         s.largura = largura_dir + largura_esq;
         s.comprimento = (comprimento_dir > comprimento_esq ? comprimento_dir : comprimento_esq);
         
         if (acima && ocupado_dir > largura_dir) {
            s.largura += (ocupado_dir - largura_dir);          
         }
         
         if (ocupado_esq > largura_esq) {
            s.largura += (ocupado_esq - largura_esq);
         }
         
         s.area = s.largura * s.comprimento;
         
         /*if (s.largura * s.comprimento == 90) {
            for (int k = 0; k < 4; k++) {
                fout << rect[k].largura << " " << rect[k].comprimento << " " << combinacoes[i][k] << endl;
            }
            fout << largura_esq << " " << largura_dir << endl;
            fout << comprimento_esq << " " << comprimento_dir << endl;
            fout << ocupado_dir << endl;
            fout << ocupado_esq << endl;  
            fout << endl;             
         }*/
         
         verifica_solucao(s);
                    
     }
     
        
}

int main()
{

    ifstream fin ("packrec.in");
    
    for (int i = 0; i < 4; i++) {
        int l1, l2;
        fin >> l1 >> l2;
        cria_rect(l1,l2,rect[i]);   
    }
    
    //primeiro layout
    Solucao s;
    s.area = 0;
    s.largura = 0;
    s.comprimento = 0;
    primeira(0, true, s);
    
    //segundo layout
    for (int i = 0; i < 4; i++) {
        Solucao s2;
        s2.area = 0;
        s2.largura = 0;    
        s2.comprimento = 0;
        segunda(i,0,true,s2);
    }
    
    //terceiro layout
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                  Solucao s3;
                  s3.area = 0;
                  s3.largura = 0;
                  s3.comprimento = 0;
                  terceira(i,j,0,true, s3);
            }
        }
    }
    
    //quarto (e quinto...) layout
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                  Solucao s4;
                  s4.area = 0;
                  s4.largura = 0;
                  s4.comprimento = 0;
                  quarta(i,j,0,true,s4);
            }
        }
    }
    
    //sexto layout
    for (int i = 0; i < 12; i++) {
        sexta();
        next_permutation(rect,rect+4);    
    }
    
    
    sol.sort();
    
    list<Solucao>::iterator it = sol.begin();
    
    int larg_ant = -1, comp_ant = -1;
    fout << min_area << endl;
    for ( ; it != sol.end(); it++) {
        if (! (it->largura == larg_ant && it->comprimento == comp_ant)) {
           fout << it->largura << " " << it->comprimento;
           //fout << " " << it->largura * it->comprimento;
           fout << endl;
           larg_ant = it->largura; comp_ant = it->comprimento;
        }
    }


    fout.close();
    fin.close();    
    return 0;
    
}  
