#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuTest
{
	TEST_CLASS(UnitTestSudokuSolver)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			char filename[] = "testsolver.txt";

			int prob[81];
			FILE* fp = fopen(filename, "r");
			for (int i = 0; i < 81; ++i)
				fscanf(fp, "%d", &prob[i]);
			SudokuSolver solver(prob);
			Assert::IsNotNull(&solver);
		}
		TEST_METHOD(TestMethod2)
		{
			// TODO: 在此输入测试代码
			char filename[] = "testsolver.txt";

			int prob[81];
			FILE* fp = fopen(filename, "r");
			for (int i = 0; i < 81; ++i)
				fscanf(fp, "%d", &prob[i]);
			SudokuSolver solver(prob);
			Assert::IsTrue(solver.solve());
		}
	};
}