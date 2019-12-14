#include "Block.h"

int Block::values[9] = { 1,2,3,4,5,6,7,8,9 };

Block::Block(int _seed):seed(_seed)
{
	permutation(nums, values, 9, seed);
}

Block::Block(Block & block)
{
	seed = block.seed;
	for (int i = 0; i < 9; ++i)
	{
		nums[i] = block.nums[i];
	}
}

void Block::swapColumns(int i, int j)
{
	i = i % 3;
	j = j % 3;
	int tmp;
	for (int t = 0; t < 3; ++t)
	{
		tmp = nums[3 * t + i];
		nums[3 * t + i] = nums[3 * t + j];
		nums[3 * t + j] = tmp;
	}
}

void Block::swapRows(int i, int j)
{
	i = i % 3;
	j = j % 3;
	int tmp;
	for (int t = 0; t < 3; ++t)
	{
		tmp = nums[3 * i + t];
		nums[3 * i + t] = nums[3 * j + t];
		nums[3 * j + t] = tmp;
	}
}