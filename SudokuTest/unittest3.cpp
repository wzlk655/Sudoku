#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuTest
{
	TEST_CLASS(UnitTestSudoku)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			Sudoku sudoku(1,3);
			char filename[] = "test1.txt";
			FILE* f = fopen(filename, "w");
			sudoku.toFile(f);
			fclose(f);

			int prob[81];
			FILE* fp = fopen(filename, "r");
			for (int i = 0; i < 81; ++i)
				fscanf(fp, "%d", &prob[i]);
			Assert::IsTrue(
				(prob[0] == 3) && (prob[9] == 6) && (prob[18] == 9)
				&& (prob[1] == 1) && (prob[2] == 2)
			);
		}
		TEST_METHOD(TestMethod2)
		{
			// TODO: 在此输入测试代码
			Sudoku sudoku(1, 3);
			sudoku.swapRows(0, 1, 2);
			char filename[] = "test2.txt";
			FILE* f = fopen(filename, "w");
			sudoku.toFile(f);
			fclose(f);

			int prob[81];
			FILE* fp = fopen(filename, "r");
			for (int i = 0; i < 81; ++i)
				fscanf(fp, "%d", &prob[i]);
			Assert::IsTrue(
				(prob[0]==3)&&(prob[9]==9)&&(prob[18]==6)
			);
		}
		TEST_METHOD(TestMethod3)
		{
			// TODO: 在此输入测试代码
			Sudoku sudoku(1, 3);
			sudoku.swapColumns(0, 1, 2);
			char filename[] = "test3.txt";
			FILE* f = fopen(filename, "w");
			sudoku.toFile(f);
			fclose(f);

			int prob[81];
			FILE* fp = fopen(filename, "r");
			for (int i = 0; i < 81; ++i)
				fscanf(fp, "%d", &prob[i]);
			Assert::IsTrue(
				(prob[0] == 3) && (prob[1] == 2) && (prob[2] == 1)
			);
		}
		TEST_METHOD(TestMethod4)
		{
			// TODO: 在此输入测试代码
			Sudoku sudoku(1, 3);
			int seed[] = { 0,0,0,0,0,1 };
			sudoku=sudoku.changeState(seed);

			char filename[] = "test4.txt";
			FILE* f = fopen(filename, "w");
			sudoku.toFile(f);
			fclose(f);

			int prob[81];
			FILE* fp = fopen(filename, "r");
			for (int i = 0; i < 81; ++i)
				fscanf(fp, "%d", &prob[i]);
			Assert::IsTrue(
				(prob[0] == 3) && (prob[7] == 8) && (prob[8] == 7)
			);
		}
	};
}