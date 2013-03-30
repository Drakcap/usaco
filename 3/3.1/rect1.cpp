/*
ID: drakcap1
PROG: rect1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <stdlib.h>
#include <set>
#include <cmath>
#include <iomanip>
#include <queue>
using namespace std;

ofstream fout("rect1.out");
ifstream fin("rect1.in");

#define MAXCOLOR 2501
#define MAXN 1000

struct Rectangulo {
       int xi, xf;
       int yi, yf;     
       int cor;
	   int ix;
};

Rectangulo rects[MAXN];
int cores[MAXCOLOR];
int areaVisivel;
int A, B, N;

int calcVisivel(Rectangulo rect, int z);

int
caso2(Rectangulo &rect, Rectangulo &compara, int z)
{
    Rectangulo r1, r2, r3, r4;
	r1.ix = r2.ix = r3.ix = r4.ix = rect.ix;
	//fout << "caso2" << " " << rect.ix << " " << compara.ix << endl;
    
    r1.xi = rect.xi;
    r1.xf = compara.xi-1;
    r1.yi = rect.yi;
    r1.yf = rect.yf;
	
	r3.xi = compara.xf+1;
    r3.xf = rect.xf;
    r3.yi = rect.yi;
    r3.yf = rect.yf;

	r2.xi = compara.xi;
	r2.xf = compara.xf;
	r2.yi = compara.yf+1;
	r2.yf = rect.yf;
	
	r4.xi = compara.xi;
	r4.xf = compara.xf;
	r4.yi = rect.yi;
	r4.yf = compara.yi-1;
	
	return calcVisivel(r1, z) + calcVisivel(r2, z) + calcVisivel(r3, z) + calcVisivel(r4, z);
}

int
caso3(Rectangulo &rect, Rectangulo &compara, int z)
{
	Rectangulo r1, r2, r3, r4;
	r1.ix = r2.ix = r3.ix = r4.ix = rect.ix;
	//fout << "caso3" << " " << rect.ix << " " << compara.ix << endl;
	
	int res = 0;
	
	//rectangulo de cima
	if (compara.yf < rect.yf) {
		r1.yi = compara.yf+1;
		r1.yf = rect.yf;
		r1.xi = (compara.xi < rect.xi ? rect.xi : compara.xi);
		r1.xf = (compara.xf > rect.xf ? rect.xf : compara.xf);
		res += calcVisivel(r1, z);
	}
	
	//rectangulo de baixo
	if (compara.yi > rect.yi) {
		r2.yi = rect.yi;
		r2.yf = compara.yi-1;
		r2.xi = (compara.xi < rect.xi ? rect.xi : compara.xi);
		r2.xf = (compara.xf > rect.xf ? rect.xf : compara.xf);
		res += calcVisivel(r2, z);
	}
	
	//rectangulo da esquerda
	if (compara.xi > rect.xi) {
		r3.xi = rect.xi;
		r3.xf = compara.xi-1;
		r3.yi = rect.yi;
		r3.yf = rect.yf;
		res += calcVisivel(r3, z);
	}
	
	//rectangulo da direita
	if (compara.xf < rect.xf) {
		r4.xi = compara.xf+1;
		r4.xf = rect.xf;
		r4.yi = rect.yi;
		r4.yf = rect.yf;
		res += calcVisivel(r4, z);
	}

	return res;

}

int
calcVisivel(Rectangulo rect, int z)
{
    int area = (rect.xf - rect.xi + 1) * (rect.yf - rect.yi + 1);
	//fout << "calcVisivel: " << rect.xi << " " << rect.xf << " " << rect.yi << " " << rect.yf << endl;
    //fout << area << endl;
    
    for (int i = z+1; i < N; i++) {
        //caso 1
        if (rects[i].xi <= rect.xi && rects[i].xf >= rect.xf
            && rects[i].yi <= rect.yi && rects[i].yf >= rect.yf) {
			//fout << "caso1" << " " << rect.ix << " " << i << endl;
            return 0;                   
        }
        //caso 2
        if (rects[i].xi >= rect.xi && rects[i].xf <= rect.xf
			&& rects[i].yi >= rect.yi && rects[i].yf <= rect.yf) {
            return caso2(rect, rects[i], i);
        }
		//caso 3
		if (rects[i].xi <= rect.xf && rects[i].xf >= rect.xi &&
			rects[i].yi <= rect.yf && rects[i].yf >= rect.yi) {
			return caso3(rect, rects[i], i);
		}
	}
		
		return area;
}

int
main()
{
      fin >> A >> B >> N;
      
      for (int i = 0; i < N; i++) {
        fin >> rects[i].xi >> rects[i].yi >> rects[i].xf >> rects[i].yf >> rects[i].cor;
        --rects[i].xf;
        --rects[i].yf;
		rects[i].ix = i;
      }
      
      int res;
	  int areas[MAXN];
      
      for (int i = 0; i < N; i++) {
          res = calcVisivel(rects[i], i);
          areaVisivel += res;
		  areas[i] = res;
          cores[rects[i].cor] += res;    
      }
      cores[1] += A*B - areaVisivel;
	  
	  /*fout << "areas: " << endl;
	  for (int i = 0; i < N; i++) {
		fout << i << " " << areas[i] << endl;
	  }*/
      
	  //fout << "solucao: " << endl;
      for (int i = 1; i < MAXCOLOR; i++) {
          if (cores[i] > 0)
             fout << i << " " << cores[i] << endl;    
      }
      
      fout.close();
      fin.close();
      return 0;
}

