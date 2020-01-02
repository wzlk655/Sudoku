#include "Sudoku.h"

Sudoku::Sudoku(int _seed, int _id)
	:seed(_seed),id(_id)
{
	//初始化数独九宫格的各个单元
	blocks[0] = Block(_seed, _id);
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

Sudoku::Sudoku(const Sudoku & s)
	:seed(s.seed),id(s.id)
{
	for (int i = 0; i < 9; ++i)
	{
		blocks[i] = s.blocks[i];
	}
}

Sudoku Sudoku::operator=(const Sudoku & s)
{
	seed = s.seed;
	id = s.id;
	for (int i = 0; i < 9; ++i)
	{
		blocks[i] = s.blocks[i];
	}
	return Sudoku(s);
}

void Sudoku::toFile(FILE* f)
{
	for (int i = 0; i < 9; ++i)
	{
		int row = i / 3, line = i % 3;
		fprintf(f, "%d %d %d ", blocks[row*3].nums[line*3], blocks[row*3].nums[line*3 + 1], blocks[row*3].nums[line*3 + 2]);
		fprintf(f, "%d %d %d ", blocks[row*3 + 1].nums[line*3], blocks[row*3 + 1].nums[line*3 + 1], blocks[row*3 + 1].nums[line*3 + 2]);
		if(i<8)
			fprintf(f, "%d %d %d\n", blocks[row*3 + 2].nums[line*3], blocks[row*3 + 2].nums[line*3 + 1], blocks[row*3 + 2].nums[line*3 + 2]);
		else
			fprintf(f, "%d %d %d", blocks[row * 3 + 2].nums[line * 3], blocks[row * 3 + 2].nums[line * 3 + 1], blocks[row * 3 + 2].nums[line * 3 + 2]);
	}
}

void Sudoku::appendLine(FILE *f)
{
	fprintf(f, "\n\n");
}

Sudoku Sudoku::swapRows(int x, int i, int j)
{
	x %= 3;
	i %= 3;
	j %= 3;
	if (x == 0 && (i == 0 || j == 0))
		return *this;
	for (int m = x * 3; m < x * 3 + 3; ++m)
	{
		blocks[m].swapRows(i, j);
	}
	return *this;
}

Sudoku Sudoku::swapColumns(int y, int i, int j)
{
	y %= 3;
	i %= 3;
	j %= 3;
	if (y == 0 && (i == 0 || j == 0))
		return *this;
	for (int m=0; m < 3; ++m)
	{
		blocks[y + 3 * m].swapColumns(i, j);
	}
	return *this;
}

Sudoku Sudoku::changeState(int* seed)
{
	Sudoku new_sudoku(*this);
	
	//六种变换依次进行
	int seed0 = seed[0]%2;
	if (seed0)
		new_sudoku.swapRows(0, 1, 2);
	int seed3 = seed[3]%2;
	if (seed3)
		new_sudoku.swapColumns(0, 1, 2);

	//不能直接用seed[i]，因为会更改值
	int seed1 = seed[1] % 6 + 1;//6为3阶乘
	int x1[3] = { 0 }, y1[3] = { 0,1,2 };
	permutation(x1, y1, 3, seed1);
	for (int i = 0; i < 3; ++i)
	{
		int j = 0;
		for (; y1[j] != x1[i]; ++j);//查找原来序列中对应该位置的内容在哪里
		new_sudoku.swapRows(1, i, j);
		int tmp = y1[j];//交换y中数据，便于后续查找
		y1[j] = y1[i];
		y1[i] = tmp;
	}

	int seed2 = seed[2] % 6 + 1;//不能直接用seed[i]，因为会更改值
	int x2[3] = { 0 }, y2[3] = { 0,1,2 };
	permutation(x2, y2, 3, seed2);
	for (int i = 0; i < 3; ++i)
	{
		int j = 0;
		for (; y2[j] != x2[i]; ++j);//查找原来序列中对应该位置的内容在哪里
		new_sudoku.swapRows(2, i, j);
		int tmp = y2[j];//交换y中数据，便于后续查找
		y2[j] = y2[i];
		y2[i] = tmp;
	}

	int seed4 = seed[4] % 6 + 1;//不能直接用seed[i]，因为会更改值
	int x4[3] = { 0 }, y4[3] = { 0,1,2 };
	permutation(x4, y4, 3, seed4);
	for (int i = 0; i < 3; ++i)
	{
		int j = 0;
		for (; y4[j] != x4[i]; ++j);//查找原来序列中对应该位置的内容在哪里
		new_sudoku.swapColumns(1, i, j);
		int tmp = y4[j];//交换y中数据，便于后续查找
		y4[j] = y4[i];
		y4[i] = tmp;
	}

	int seed5 = seed[5] % 6 + 1;//不能直接用seed[i]，因为会更改值
	int x5[3] = { 0 }, y5[3] = { 0,1,2 };
	permutation(x5, y5, 3, seed5);
	for (int i = 0; i < 3; ++i)
	{
		int j = 0;
		for (; y5[j] != x5[i]; ++j);//查找原来序列中对应该位置的内容在哪里
		new_sudoku.swapColumns(2, i, j);
		int tmp = y5[j];//交换y中数据，便于后续查找
		y5[j] = y5[i];
		y5[i] = tmp;
	}
	return new_sudoku;
}