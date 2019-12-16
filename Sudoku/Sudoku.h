#pragma once
#include<string>
#include "Block.h"

class Sudoku
{
public:
	Sudoku(int _seed, int _id);
	void toFile(std::string fname="sudoku.txt");
	static void appendLine(std::string fname = "sudoku.txt");
	Sudoku swapRows(int x, int i, int j);
	Sudoku swapColumns(int y, int i, int j);
private:
	int seed;
	int id;
	Block blocks[9];
};