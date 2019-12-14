#include "Sudoku.h"

Sudoku::Sudoku(int _seed, int _id)
	:seed(_seed),id(_id)
{
	//初始化数独九宫格的各个单元
	blocks[0] = Block(_seed);
	blocks[1] = blocks[0];blocks[2] = blocks[0];
	blocks[3] = blocks[0];blocks[4] = blocks[0];blocks[5] = blocks[0];
	blocks[6] = blocks[0];blocks[7] = blocks[0];blocks[8] = blocks[0];

	blocks[3].swapRows(0, 1); blocks[3].swapRows(0, 2);
	blocks[5].swapRows(1, 2); blocks[5].swapRows(0, 2);
	
	blocks[1].swapColumns(0, 1); blocks[1].swapColumns(0, 2);
	blocks[7].swapColumns(1, 2); blocks[7].swapColumns(0, 2);

	blocks[0].swapRows(0, 1); blocks[0].swapRows(0, 2); blocks[0].swapColumns(0, 1); blocks[0].swapColumns(0, 2);
	blocks[2].swapRows(1, 2); blocks[2].swapRows(0, 2); blocks[2].swapColumns(0, 1); blocks[2].swapColumns(0, 2);

	blocks[8].swapRows(1, 2); blocks[8].swapRows(0, 2); blocks[8].swapColumns(1, 2); blocks[8].swapColumns(0, 2);
	blocks[6].swapRows(0, 1); blocks[6].swapRows(0, 2); blocks[6].swapColumns(1, 2); blocks[6].swapColumns(0, 2);
}

void Sudoku::toFile(std::string fname)
{
	FILE *f = fopen(fname.data(), "w");
	for (int i = 0; i < 9; ++i)
	{
		int row = i / 3, line = i % 3;
		fprintf(f, "%d %d %d ", blocks[row*3].nums[line*3], blocks[row*3].nums[line*3 + 1], blocks[row*3].nums[line*3 + 2]);
		fprintf(f, "%d %d %d ", blocks[row*3 + 1].nums[line*3], blocks[row*3 + 1].nums[line*3 + 1], blocks[row*3 + 1].nums[line*3 + 2]);
		fprintf(f, "%d %d %d\n", blocks[row*3 + 2].nums[line*3], blocks[row*3 + 2].nums[line*3 + 1], blocks[row*3 + 2].nums[line*3 + 2]);
	}
	fclose(f);
}