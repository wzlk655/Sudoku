#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<sstream>
#include "permutation.h"
#include "Sudoku.h"
#include "SudokuSolver.h"
using namespace std;

const int SEED_MAX = 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;//���ڹ̶�һλ������Ϊ8!
const int ID = 3;

void handleCreate(string);
void handleSolve(string);
void paramError();

int main(int argc, char* argv[])
{
	//handleCreate(string("1000"));
	//�жϲ����Ƿ�Ϸ�
	if (argc != 3)
	{
		printf("�������Ϸ���\n");
	}

	if (string(argv[1]) == "-c")
	{
		handleCreate(string(argv[2]));
	}
	else if (string(argv[1]) == "-s")
	{
		handleSolve(string(argv[2]));
	}
	else
	{
		paramError();
	}
}

void handleCreate(string amount)
{
	int num;
	stringstream ss_num(amount);
	FILE* f = fopen("sudoku.txt", "w");
	if (ss_num >> num)
	{
		//TODO:�����Ӹ��±�Ϊ���򣬱�������������һ��
		int seed = rand() % SEED_MAX + 1;
		while (true)
		{
			Sudoku sudoku(seed, ID);
			int seeds[6] = { 0 };
			bool flag = false;
			for (seeds[0] = 0; seeds[0] < 2; ++seeds[0])
			{
				for (seeds[1] = 0; seeds[1] < 6; ++seeds[1])
				{
					for (seeds[2] = 0; seeds[2] < 6; ++seeds[2])
					{
						for (seeds[3] = 0; seeds[3] < 2; ++seeds[3])
						{
							for (seeds[4] = 0; seeds[4] < 6; ++seeds[4])
							{
								for (seeds[5] = 0; seeds[5] < 6; ++seeds[5])
								{
									Sudoku n_sudoku(sudoku.changeState(seeds));
									if (!(--num))//����ָ������
									{
										n_sudoku.toFile(f);
										flag = true;
										break;
									}
									else
									{
										n_sudoku.toFile(f);
										n_sudoku.appendLine(f);
									}
									if (flag)
										break;
								}
								if (flag)
									break;
							}
							if (flag)
								break;
						}
						if (flag)
							break;
					}
					if (flag)
						break;
				}
				if (flag)
					break;
			}
			if (flag)
				break;
		}
	}
	else//���벻������
		paramError();
	fclose(f);
	return;
}

void handleSolve(string filename)
{
	FILE *fp;
	int prob[81];
	if (fp = fopen(filename.data(), "r"))
	{
		for (int i = 0; i < 81; ++i)
			fscanf(fp, "%d", &prob[i]);
		SudokuSolver solver(prob);
		solver.solve();
		solver.print();
	}
	else
	{

	}
	return;
}

void paramError()
{
	//�������벻�Ϸ�
	printf("���벻�Ϸ�����ʹ�� \"suodoku.exe -c ����\" �� \"sudoku.exe -s �ļ���\" ��ʽ���롣\n");
	exit(0);
}

void typeErrorNum()
{
	printf("����-c�����Ƿ�Ϊ���֡�\n");
}

void fileNotFound()
{
	printf("����-s�����ļ��Ƿ���ڡ�\n");
}