#pragma once
#include<string>

class SudokuSolver
{
public:
	SudokuSolver(int sudoku[]);
	int solve(std::string method = "backtrack");
	void print();
	void toFile(FILE *f);
	static void appendLine(FILE *f);
private:
	int _backtrackSolve(int holder);
	bool _isLegal(int pos);
	static int _find_next_empty(int *map, int size);
	int sudoku[81];
};