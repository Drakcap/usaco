/*
ID: drakcap1
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{

    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
	
	string cometa, grupo;
	
	while (fin >> cometa >> grupo) {
	
		int soma_cometa = 1;
		
		for (unsigned i = 0; i < cometa.size(); i++) {
			soma_cometa *= cometa[i] - 'A' + 1;
		}
		
		int cometa = soma_cometa % 47;
		int soma_grupo = 1;
		
		for (unsigned i = 0; i < grupo.size(); i++) {
			soma_grupo *= grupo[i] - 'A' + 1;
		}
		
		int grupo = soma_grupo % 47;
		
		fout << (grupo == cometa ? "GO" : "STAY") << endl;
		
	
	}


	return 0;
}
