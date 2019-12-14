#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include "permutation.h"
#include "Sudoku.h"
using namespace std;

void handleCreate(int);

int main(int argc, char* argv[])
{
	Sudoku sudoku(1, 1);
	sudoku.toFile();

	int x[9] = {0};
	int y[] = { 1,2,3,4,5,6,7,8,9 };

	int seed = 1;
	for(int i=1;i<100;++i,seed=i)
		permutation(x, y, 9, seed);
	seed =x[0];

	//判断参数是否合法
	if (argc != 3)
	{
		printf("参数不合法！\n");
	}

	if (argv[1][1] == 'c')
	{
		int num;
		string s_num(argv[2]);
		stringstream ss_num(s_num);
		ss_num >> num;
		handleCreate(num);
	}
}

void handleCreate(int amount)
{
	return;
}
