/*
ID: drakcap1
PROG: nuggets
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

ofstream fout("nuggets.out");
ifstream fin("nuggets.in");

int MAX;
int N;
int nums[10];
bool* can;

//#define MAX 2000000000

int
main()
{

    fin >> N;
    
    for (int i = 0; i < N; i++) {
        fin >> nums[i];
        //can[nums[i]] = true;
        if (nums[i] == 1) {
            fout << 0 << endl;
            return 0;
        }
    }
    
    vector<int> naoDivisiveis;
    bool usa = true;
    
    for (int i = 0; i < N; i++) {
        usa = true;
        for (int j = 0; j < N; j++) {
            if (i != j && nums[i] % nums[j] == 0) {
                usa = false;
                break;
            }
        }
        if (usa) naoDivisiveis.push_back(nums[i]);
    }
    
    if (naoDivisiveis.size() == 1) {
        fout << 0 << endl;
        return 0;
    }
    
    int maior1 = max(naoDivisiveis[0], naoDivisiveis[1]), maior2 = min(naoDivisiveis[0], naoDivisiveis[1]);
    bool allPair = true;
    for (size_t i = 0; i < naoDivisiveis.size(); i++) {
        if (naoDivisiveis[i] % 2 != 0) {
            allPair = false;
        }
        //cout << maior1 << " " << maior2 << " " << naoDivisiveis[i] << endl;
        if (naoDivisiveis[i] > maior1) {
            swap(maior1, maior2);
            maior1 = naoDivisiveis[i];
        } else if (naoDivisiveis[i] > maior2) {
            maior2 = naoDivisiveis[i];
        }
        
    }
    
    if (allPair) {
        fout << 0 << endl;
        return 0;
    }
    //fout << maior1 << " " << maior2 << endl;
    MAX = maior1 * maior2;
    //fout << maior1 << " " << maior2 << endl;
    //fout << MAX << endl;
    can = new bool[MAX+10];
    memset(can, false, sizeof(can));
    can[0] = true;
    
    for (int i = 0; i < MAX; i++) {
        for (size_t j = 0; j < naoDivisiveis.size(); j++) {
            if (i-naoDivisiveis[j] >= 0 && can[i-naoDivisiveis[j]]) {
                can[i] = true;
            }
        }
    }

    for (int i = MAX-1; i >= 0; i--) {
        if (!can[i]) {
            fout << i << endl;
            break;
        }
    }

	fout.close();
	fin.close();
	return 0;
}
