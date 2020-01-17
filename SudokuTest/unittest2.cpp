#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuTest
{
	TEST_CLASS(UnitTestBlock)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			Block block(1);
			int* nums = block.nums;
			int gt[9] = { 1,2,3,4,5,6,7,8,9 };
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
			Block block(1,3);
			int* nums = block.nums;
			int gt[9] = { 4,5,6,7,8,9,1,2,3 };
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
			Block block(1);
			int* nums = block.nums;
			block.swapRows(0, 1);
			int gt[9] = { 4,5,6,1,2,3,7,8,9 };
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
			Block block(1);
			int* nums = block.nums;
			block.swapColumns(0, 1);
			int gt[9] = { 2,1,3,5,4,6,8,7,9 };
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