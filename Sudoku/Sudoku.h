#pragma once
#include<string>
#include "Block.h"

class Sudoku
{
public:
	Sudoku(int _seed, int _id);
	Sudoku(const Sudoku &s);
	Sudoku operator=(const Sudoku &s);
	void toFile(FILE *f);
	static void appendLine(FILE *f);
	Sudoku swapRows(int x, int i, int j);
	Sudoku swapColumns(int y, int i, int j);
	Sudoku changeState(int* seed);
private:
	int seed;
	int id;
	Block blocks[9];
};