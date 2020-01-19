#include "permutation.h"

int permutation(int *x, int *values, int length, int& seed)
{
	/*
	x�����ɵ����д�ŵ�����
	values�����е�����Ԫ��
	length��x��values�е�Ԫ�ظ���
	seed�����е����ӣ���ΧΪ1-(length!)���;��������һһ��Ӧ
	*/
	if (length == 1) //1����������ֱ��������
	{
		x[0] = values[0];
		seed--;  //�ҵ�һ������
		return seed;  //���seed==0����ʾ�ҵ�seed��Ӧ�����У�������ֹ
	}
	int* n_values = new int[length - 1];
	for (int i = 0; i < length; ++i)  //�����ڵ�һ��λ������values��ĳ��ֵ
	{
		x[0] = values[i];
		for (int j = 0; j < length - 1; ++j)  //�µ�values���ų���ֵ
		{
			n_values[j] = values[(i + j + 1) % length];
		}
		if (!permutation(x + 1, n_values, length - 1, seed))  //��֮ǰ�����϶�֮���������������
		{
			delete[] n_values;
			return 0;  //��ʾ�Ѿ��ҵ�seed��Ӧ�������ˣ�������ֹ
		}
	}
	delete[] n_values;
	return 1;  //������û�н���
}