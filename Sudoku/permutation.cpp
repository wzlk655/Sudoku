#include "permutation.h"

int permutation(int *x, int *values, int length, int& seed)
{
	if (length == 1)
	{
		x[0] = values[0];
		seed--;
		return seed;
	}
	int* n_values = new int[length - 1];
	for (int i = 0; i < length; ++i)
	{
		x[0] = values[i];
		for (int j = 0; j < length - 1; ++j)
		{
			n_values[j] = values[(i + j + 1) % length];
		}
		if (!permutation(x + 1, n_values, length - 1, seed))
		{
			delete[] n_values;
			return 0;
		}
	}
	delete[] n_values;
	return 1;
}