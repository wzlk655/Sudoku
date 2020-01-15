#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			int nums[9];
			int values[9] = { 1,2,3,4,5,6,7,8,9 };
			int gt[9] = { 1,2,3,4,5,6,7,8,9 };
			int seed = 1;
			permutation(nums, values, 9, seed);
			Assert::IsTrue(
				(nums[0] == gt[0]) && (nums[1] == gt[1])
				&& (nums[2] == gt[2])
				&& (nums[3] == gt[3]) && (nums[4] == gt[4])
				&& (nums[5] == gt[5]) && (nums[6] == gt[6])
				&& (nums[7] == gt[7]) && (nums[8] == gt[8])
			);
		}
		TEST_METHOD(TestMethod2)
		{
			// TODO: 在此输入测试代码
			int nums[9];
			int values[9] = { 1,2,3,4,5,6,7,8,9 };
			int gt[9] = { 9,8,7,6,5,4,3,2,1 };
			int seed = 9*8*7*6*5*4*3*2;
			permutation(nums, values, 9, seed);
			Assert::IsTrue(
				(nums[0] == gt[0]) && (nums[1] == gt[1])
				&& (nums[2] == gt[2])
				&& (nums[3] == gt[3]) && (nums[4] == gt[4])
				&& (nums[5] == gt[5]) && (nums[6] == gt[6])
				&& (nums[7] == gt[7]) && (nums[8] == gt[8])
			);
		}
		TEST_METHOD(TestMethod3)
		{
			// TODO: 在此输入测试代码
			int nums[9];
			int values[9] = { 1,2,3,4,5,6,7,8,9 };
			int gt[9] = { 1,2,3,4,5,6,7,9,8 };
			int seed = 2;
			permutation(nums, values, 9, seed);
			Assert::IsTrue(
				(nums[0] == gt[0]) && (nums[1] == gt[1])
				&& (nums[2] == gt[2])
				&& (nums[3] == gt[3]) && (nums[4] == gt[4])
				&& (nums[5] == gt[5]) && (nums[6] == gt[6])
				&& (nums[7] == gt[7]) && (nums[8] == gt[8])
			);
		}
		TEST_METHOD(TestMethod4)
		{
			// TODO: 在此输入测试代码
			int nums[9];
			int values[9] = { 1,2,3,4,5,6,7,8,9 };
			int gt[9] = { 9,8,7,6,5,4,3,1,2 };
			int seed = 9*8*7*6*5*4*3*2-1;
			permutation(nums, values, 9, seed);
			Assert::IsTrue(
				(nums[0] == gt[0]) && (nums[1] == gt[1])
				&& (nums[2] == gt[2])
				&& (nums[3] == gt[3]) && (nums[4] == gt[4])
				&& (nums[5] == gt[5]) && (nums[6] == gt[6])
				&& (nums[7] == gt[7]) && (nums[8] == gt[8])
			);
		}
		TEST_METHOD(TestMethod5)
		{
			// TODO: 在此输入测试代码
			int nums[9];
			int values[9] = { 1,2,3,4,5,6,7,8,9 };
			int gt[9] = { 1,2,3,4,5,6,8,7,9 };
			int seed = 4;
			permutation(nums, values, 9, seed);
			Assert::IsTrue(
				(nums[0] == gt[0]) && (nums[1] == gt[1])
				&& (nums[2] == gt[2])
				&& (nums[3] == gt[3]) && (nums[4] == gt[4])
				&& (nums[5] == gt[5]) && (nums[6] == gt[6])
				&& (nums[7] == gt[7]) && (nums[8] == gt[8])
			);
		}
	};
}