#pragma once
#include<string>
#include "Block.h"

class Sudoku
{
public:
	Sudoku(int _seed, int _id);
	void toFile(std::string fname="sudoku.txt");
private:
	int seed;
	int id;
	Block blocks[9];
};