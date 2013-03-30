/*
ID: drakcap1
PROG: heritage
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

ofstream fout("heritage.out");
ifstream fin("heritage.in");

#define convert(x) (x - 'A')

struct No {
	int num;
	int l, r;
} nos[26];

int root;
char inorder[27];
char preorder[27];
int inputsize;

int
findroot(int minix, int maxix)
{
	for (int i = 0; i < inputsize; i++) {
		for (int j = minix; j <= maxix; j++) {
			if (preorder[i] == inorder[j]) {
				return convert(preorder[i]);
			}
		}
	}
	return -1;
}

void
go(int no, int minix, int maxix)
{
	int ix = -1;
	for (int i = minix; i <= maxix; i++) {
		if (convert(inorder[i]) == no) {
			ix = i;
			break;
		}
	}
	
	nos[no].l = findroot(minix, ix-1);
	if (nos[no].l != -1) {
		go(nos[no].l, minix, ix-1);
	}
	
	nos[no].r = findroot(ix+1, maxix);
	if (nos[no].r != -1) {
		go(nos[no].r, ix+1, maxix);
	}
}

void
visitpost(int no) {
	if (no == -1) return;
	visitpost(nos[no].l);
	visitpost(nos[no].r);
	fout << (char) (no + 'A');
}

int
main()
{

	for (int i = 0; i < 26; i++) {
		nos[i].l = nos[i].r = -1;
	}
	
	fin >> inorder >> preorder;
	
	root = convert(preorder[0]);
	inputsize = strlen(inorder);
	go(root, 0, inputsize-1);
	visitpost(root);
	fout << endl;
	
	fout.close();
	fin.close();
	return 0;
}
