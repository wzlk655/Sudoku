#include<iostream>
#include<cstdio>
#include<string>
#include<sstream>
#include "permutation.h"
#include "Sudoku.h"
#include "SudokuSolver.h"
using namespace std;

void handleCreate(int);
void handleSolve(string);

int main(int argc, char* argv[])
{
	handleSolve("problem.txt");
	return 0;
	Sudoku sudoku(1, 3);
	sudoku.toFile(); sudoku.appendLine();

	sudoku.swapColumns(0, 1, 2).toFile();
	sudoku.appendLine();
	sudoku.swapRows(2, 1, 2).toFile();

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
	else if (argv[1][1] == 's')
	{
		string s_file(argv[2]);
		handleSolve(s_file);
	}
}

void handleCreate(int amount)
{
	return;
}

void handleSolve(string filename)
{
	FILE *fp;
	int prob[81];
	if (fp = fopen(filename.data(), "r"))
	{
		for (int i = 0; i < 81; ++i)
			fscanf(fp, "%d", &prob[i]);
		SudokuSolver solver(prob);
		solver.solve();
		solver.print();
	}
	return;
}
