#pragma once
#include "permutation.h"

class Block
{
public:
	Block(int _seed=1);
	Block(int _seed, int _id);
	Block(const Block& block);
	Block operator=(const Block &block);
	void swapColumns(int i, int j);
	void swapRows(int i, int j);
	static int values[9];
	int seed;
	int nums[9];
};