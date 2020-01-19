#include "permutation.h"

int permutation(int *x, int *values, int length, int& seed)
{
	/*
	x：生成的排列存放的数组
	values：排列的所有元素
	length：x，values中的元素个数
	seed：排列的种子，范围为1-(length!)，和具体的排列一一对应
	*/
	if (length == 1) //1个数的排列直接是自身
	{
		x[0] = values[0];
		seed--;  //找到一个排列
		return seed;  //如果seed==0，表示找到seed对应的排列，搜索终止
	}
	int* n_values = new int[length - 1];
	for (int i = 0; i < length; ++i)  //尝试在第一个位置填上values的某个值
	{
		x[0] = values[i];
		for (int j = 0; j < length - 1; ++j)  //新的values中排除该值
		{
			n_values[j] = values[(i + j + 1) % length];
		}
		if (!permutation(x + 1, n_values, length - 1, seed))  //在之前基础上对之后的数再生成排列
		{
			delete[] n_values;
			return 0;  //表示已经找到seed对应的排列了，搜索终止
		}
	}
	delete[] n_values;
	return 1;  //搜索还没有结束
}