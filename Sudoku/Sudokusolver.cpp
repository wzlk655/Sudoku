#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(int sudoku[])
{
	for (int i = 0; i < 81; ++i)
		this->sudoku[i] = sudoku[i];
}

int SudokuSolver::solve(std::string method)
{
	if (method == "backtrack")
	{
		int st = _find_next_empty(sudoku, 81);
		return _backtrackSolve(st);
	}
}

void SudokuSolver::print()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
			printf("%d ", sudoku[i * 9 + j]);
		printf("\n");
	}
}

int SudokuSolver::_backtrackSolve(int holder)
{
	if (holder == -1)//所有空格都填上了
		return 1;
	for (int i = 1; i <= 9; ++i)
	{
		sudoku[holder] = i;
		if (this->_isLegal(holder))
		{
			int n_holder = _find_next_empty(sudoku, 81);
			if (_backtrackSolve(n_holder))//找到解了
				return 1;
			//否则，该值无解，尝试下一个数字
		}
		//否则，该值不合法，尝试下一个解
	}
	sudoku[holder] = 0;//还原现场
	return 0;
}

int SudokuSolver::_find_next_empty(int *map, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (!map[i])
			return i;
	}
	return -1;
}

bool SudokuSolver::_isLegal(int pos)
{
	int x = pos / 9, y = pos % 9;
	int result = 0, tmp;
	for (int i = 0; i < 9; ++i)
	{
		if (sudoku[x * 9 + i])
			tmp = result & (1 << sudoku[x * 9 + i]);
		else
			tmp = 0;
		if (tmp)
			return false;
		else
			result = result | (1 << sudoku[x * 9 + i]);
	}

	result = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (sudoku[i * 9 + x])
			tmp = result & (1 << sudoku[i * 9 + x]);
		else
			tmp = 0;
		if (tmp)
			return false;
		else
			result = result | (1 << sudoku[i * 9 + x]);
	}
	
	result = 0;
	x /= 3, y /= 3;//block序号
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (sudoku[9*(x * 3 + i)+y * 3 + j])
				tmp = result & (1<<sudoku[9 * (x * 3 + i) + y * 3 + j]);
			else
				tmp = 0;
			if (tmp)
				return false;
			else 
				result = result | (1<<sudoku[9 * (x * 3 + i) + y * 3 + j]);
		}
	}

	return true;
}