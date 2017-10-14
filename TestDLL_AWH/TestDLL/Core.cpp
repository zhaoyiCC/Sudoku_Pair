#include "stdafx.h"
#include "Core.h"
#include "stdlib.h"
#include "time.h"
#include "algorithm"
#include "iostream"
#include "fstream"
#include "set"
using namespace std;
int result[CREATEMAX][SUDOKU_SIZE] = { 0 };
int puzzleSet[CREATEMAX][SUDOKU_SIZE] = { 0 };
Core::Core()
{
}
Core::~Core()
{
	;
}
void Core::Swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
bool Core::DuplicateCheck(int* a, int aim, int count)
{
	int i = 0;
	for (i = 0; i < count; i++)
	{
		if (a[i] == aim)
			return true;
	}
	return false;
}
void Core::RowSwap(int* srcMartix, int Type, int* rank)
{
	int ranktemp[3] = { 0 };
	for (int i = 0; i < 3; i++) {
		ranktemp[i] = rank[i];
	}
	while (ranktemp[0] != Type || ranktemp[1] != Type + 1 || ranktemp[2] != Type + 2)
	{
		if (ranktemp[0] != Type) {
			if (ranktemp[1] == Type)
			{
				int top = (ranktemp[0] - 1)*NUM_ROW;
				int end = (ranktemp[1] - 1)*NUM_ROW;
				for (int i = 0; i < NUM_ROW; i++) {
					Swap(&srcMartix[top + i], &srcMartix[end + i]);
				}
				int temp = ranktemp[0];
				ranktemp[0] = ranktemp[1];
				ranktemp[1] = temp;
				continue;
			}
			else if (ranktemp[2] == Type)
			{
				int top = (ranktemp[0] - 1)*NUM_ROW;
				int end = (ranktemp[2] - 1)*NUM_ROW;
				for (int i = 0; i < NUM_ROW; i++) {
					Swap(&srcMartix[top + i], &srcMartix[end + i]);
				}
				int temp = ranktemp[0];
				ranktemp[0] = ranktemp[2];
				ranktemp[2] = temp;
				continue;
			}
		}
		if (ranktemp[1] != Type + 1) {
			if (ranktemp[0] == Type + 1)
			{
				int top = (ranktemp[0] - 1)*NUM_ROW;
				int end = (ranktemp[1] - 1)*NUM_ROW;
				for (int i = 0; i < NUM_ROW; i++) {
					Swap(&srcMartix[top + i], &srcMartix[end + i]);
				}
				int temp = ranktemp[0];
				ranktemp[0] = ranktemp[1];
				ranktemp[1] = temp;
				continue;
			}
			else if (ranktemp[2] == Type + 1)
			{
				int top = (ranktemp[1] - 1)*NUM_ROW;
				int end = (ranktemp[2] - 1)*NUM_ROW;
				for (int i = 0; i < NUM_ROW; i++) {
					Swap(&srcMartix[top + i], &srcMartix[end + i]);
				}
				int temp = ranktemp[1];
				ranktemp[1] = ranktemp[2];
				ranktemp[2] = temp;
				continue;
			}
		}
		if (ranktemp[2] != Type + 2) {
			if (ranktemp[0] == Type + 2)
			{
				int top = (ranktemp[0] - 1)*NUM_ROW;
				int end = (ranktemp[2] - 1)*NUM_ROW;
				for (int i = 0; i < NUM_ROW; i++) {
					Swap(&srcMartix[top + i], &srcMartix[end + i]);
				}
				int temp = ranktemp[0];
				ranktemp[0] = ranktemp[2];
				ranktemp[2] = temp;
				continue;
			}
			else if (ranktemp[1] == Type + 2)
			{
				int top = (ranktemp[2] - 1)*NUM_ROW;
				int end = (ranktemp[1] - 1)*NUM_ROW;
				for (int i = 0; i < NUM_ROW; i++) {
					Swap(&srcMartix[top + i], &srcMartix[end + i]);
				}
				int temp = ranktemp[1];
				ranktemp[1] = ranktemp[2];
				ranktemp[2] = temp;
				continue;
			}
		}
	}
}
void Core::create(int number, int result[][SUDOKU_SIZE])
{
	int rank1[6][3] = {
		{ 1,2,3 },{ 1,3,2 },{ 2,1,3 },{ 2,3,1 },
		{ 3,1,2 },{ 3,2,1 }
	};
	int rank2[6][3] = {
		{ 4,5,6 },{ 4,6,5 },{ 5,4,6 },{ 5,6,4 },
		{ 6,4,5 },{ 6,5,4 }
	};
	int rank3[6][3] = {
		{ 7,8,9 },{ 7,9,8 },{ 8,7,9 },{ 8,9,7 },
		{ 9,7,8 },{ 9,8,7 }
	};
	int martixCount = 0;
	srand((unsigned)time(NULL));
	while (true)
	{
		//solve Random Puzzle
		int puzzleStart[81] = { 0 };
		int OriMartixCopy[81] = { 0 };
		int OriMarRowCopy[81] = { 0 };
		char startSet[10];
		string sSet;
		int position[10] = { 0, 12, 24, 28, 40, 52, 56, 68, 80 };
		int a[10] = { 0 };
		int t = 0;
		for (int i = 0; i < 10; i++)
		{
			while (true)
			{
				t = rand() % 9 + 1;
				if (a[t] < 2)
				{
					a[t]++;
					break;
				}
			}
			puzzleStart[position[i]] = t;
			startSet[i] = t + '0';
		}
		sSet = startSet;
		int setSize = _startSet.size();
		_startSet.insert(sSet);
		if (setSize == sSet.size())
		{
			continue;
		}
		if (!solve(puzzleStart, OriMartixCopy))
		{
			printf("no solution");
			continue;
		}
		//row transfor
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					memcpy(OriMarRowCopy, OriMartixCopy, sizeof(int) * 81);
					RowSwap(OriMarRowCopy, Type123, rank1[i]);
					RowSwap(OriMarRowCopy, Type456, rank2[j]);
					RowSwap(OriMarRowCopy, Type789, rank3[k]);
					memcpy(result[martixCount], OriMarRowCopy, sizeof(int) * SUDOKU_SIZE);
					martixCount++;
					if (martixCount == number)
					{
						return;
					}
				}
			}
		}
	}
}
void Core::generate(int number, int mode, int result[][SUDOKU_SIZE])
{
	create(number, result);
	int blankNum = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < number; i++)
	{
		blankNum = rand() % 12 + 8 + mode * 12;
		//$todo: study set random
		for (int j = 0; j < blankNum; j++)
		{
			int t = rand() % 81;
			while (result[i][t] == 0)
			{
				t = rand() % 81;
			}
			result[i][t] = 0;
		}
	}
}
int Core::numTransfor(int a)
{
	int temp = 1;
	for (int k = 1; k < a; k++)
	{
		temp <<= 1;
	}
	return temp;
}
int Core::RemoveCandidates(int index, int puzzle[], int flag[])
{
	if (flag[index] == 1)
	{
		return puzzle[index];
	}
	int row = index / 9;
	int col = index % 9;
	int m = row / 3;
	int n = col / 3;
	int i1;
	int j1;
	int pointCopy = puzzle[index];
	//Palace candidates removal
	for (i1 = m * 3; i1 < m * 3 + 3; i1++)
	{
		for (j1 = n * 3; j1 < n * 3 + 3; j1++)
		{
			if (flag[i1 * 9 + j1] == 1)
			{
				pointCopy = pointCopy & (~numTransfor(puzzle[i1 * 9 + j1]));
			}
		}
	}
	//row and col candidates removal
	int i;
	for (i = 0; i < 9; i++)
	{
		if (flag[row * 9 + i] == 1)
		{
			pointCopy = pointCopy & (~numTransfor(puzzle[row * 9 + i]));
		}
		if (flag[i * 9 + col] == 1)
		{
			pointCopy = pointCopy & (~numTransfor(puzzle[i * 9 + col]));
		}
		else
			;
	}
	return pointCopy;
}
bool Core::Fill(int index, int puzzle[], int flag[], int solveMode)
{
	if (index >= 81)
	{
		solveCnt++;
		if (solveCnt == solveMode)
			return true;
		else
			return false;
	}
	int shiftvalue = RemoveCandidates(index, puzzle, flag);
	if (shiftvalue == 0)
	{
		return false;
	}
	int pointCopy = puzzle[index];
	if (flag[index] == 0)
	{
		for (int i = 1; shiftvalue > 0; i++)
		{
			if (shiftvalue % 2 != 0)
			{
				puzzle[index] = i;
				flag[index] = 1;
				if (Fill(index + 1, puzzle, flag, solveMode))
				{
					return true;
				}
			}
			shiftvalue = shiftvalue >> 1;
		}
	}
	else
	{
		return Fill(index + 1, puzzle, flag, solveMode);
	}
	puzzle[index] = pointCopy;
	flag[index] = 0;
	return false;
}
bool Core::isUnique(int puzzle[SUDOKU_SIZE])
{
	int t[81] = { 0 };
	memcpy(t, puzzle, (sizeof(int)) * 81);
	int flag[SUDOKU_SIZE] = { 0 };
	for (int i = 0; i<SUDOKU_SIZE; i++)
	{
		if (t[i] == 0)
		{
			t[i] = 0x1ff;
			flag[i] = 0;
		}
		else
		{
			flag[i] = 1;
		}
	}
	solveCnt = 0;
	if (Fill(0, t, flag, 2))
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Core::generate(int number, int lower, int upper, bool unique, int result[][SUDOKU_SIZE])
{
	create(number, result);
	int blankNum = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < number; i++)
	{
		int temp[SUDOKU_SIZE] = { 0 };
		memcpy(temp, result[i], sizeof(int) * SUDOKU_SIZE);
		blankNum = rand() % (upper - lower + 1) + lower;
		//$todo: study set random
		for (int j = 0; j < blankNum; j++)
		{
			int t = rand() % SUDOKU_SIZE;
			while (result[i][t] == 0)
			{
				t = rand() % SUDOKU_SIZE;
			}
			result[i][t] = 0;
		}
		if (unique)
		{
			if (isUnique(result[i]))
			{
				continue;
			}
			else
			{
				memcpy(result[i], temp, sizeof(int) * SUDOKU_SIZE);
				i--;
				continue;
			}
		}
	}
}
bool Core::solve(int puzzle[], int solution[])
{
	int flag[SUDOKU_SIZE] = { 0 };
	for (int i = 0; i<81; i++)
	{
		if (puzzle[i] == 0)
		{
			continue;
		}
		else
		{
			for (int j = i / 9 * 9; j < 9; j++)
			{
				if (puzzle[i] == puzzle[j] && i != j)
				{
					return false;
				}
			}
			for (int j = i % 9; j < 81; j += 9)
			{
				if (puzzle[i] == puzzle[j] && i != j)
				{
					return false;
				}
			}
			for (int j = i / 9 / 3 * 3; j < 3; j++)
			{
				for (int k = i % 9 / 3 * 3; k < 3; k++)
				{
					if (puzzle[i] == puzzle[j * 9 + k] && i != j * 9 + k)
					{
						return false;
					}
				}
			}
		}
	}
	for (int i = 0; i < SUDOKU_SIZE; i++)
	{
		if (puzzle[i] == 0)
		{
			puzzle[i] = 0x1ff;
			flag[i] = 0;
		}
		else
		{
			flag[i] = 1;
		}
	}
	memcpy(solution, puzzle, sizeof(int) * SUDOKU_SIZE);
	solveCnt = 0;
	return Fill(0, solution, flag, 1);
}
int Core::str2num(char *s, int max)
{
	if (strlen(s) == 0)
	{
		return -1;
	}
	int t = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i]<'0' || s[i]>'9')
		{
			return -1;
		}
		t = t * 10 + s[i] - '0';
		if (t > max)
		{
			return -1;
		}
	}
	return t;
}
void Core::print(int number, int result[][SUDOKU_SIZE])
{
	FILE* outfile;
	errno_t err1;
	if ((err1 = fopen_s(&outfile, "sudoku.txt", "w")) != 0)
	{
		printf("Unable to open sudoku.txt\n");
		exit(1);
	}
	for (int i = 0; i < number; i++) {
		//$todo: to solve the leak of the memory
		int m = 0;
		char temp[325];
		for (int j = 0; j < SUDOKU_SIZE; j++, m += 2)
		{
			temp[m] = result[i][j] + '0';
			if ((j + 1) % 9 == 0)
			{
				temp[m + 1] = '\n';
				continue;
			}
			temp[m + 1] = ' ';
		}
		temp[m] = '\n';
		temp[m + 1] = '\0';
		std::fputs(temp, outfile);
	}
	std::fclose(outfile);
}
int Core::readFile(char *path, int puzzleSet[][SUDOKU_SIZE])
{
	FILE *inFile;
	errno_t err;
	if ((err = fopen_s(&inFile, path, "r")) != 0)
	{
		throw MyFileException();
	}
	int sudokuNum = 0;
	int num = 0;
	int x = 0;
	while ((fscanf(inFile, "%d", &x)) != EOF)
	{
		if (x < 0 || x > 9)
		{
			throw MySudokuException();
		}
		puzzleSet[sudokuNum][num++] = x;
		if (num >= 81)
		{
			num = 0;
			sudokuNum++;
		}
	}
	if (num != 0 || sudokuNum == 0)
	{
		throw MySudokuException();
	}
	fclose(inFile);
	return sudokuNum;
}
void Core::read(int argc, char* argv[])
{
	if (argc == 3)
	{
		//-c x
		if (strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'c')
		{
			int t = str2num(argv[2], CREATEMAX);
			if (t <= 0)
			{
				throw MyParameterException();
			}
			memset(result, 0, CREATEMAX * (sizeof(int)));
			create(t, result);
			print(t, result);
		}
		//-s filepath
		else if (strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 's')
		{
			int sudokuNum = readFile(argv[2], puzzleSet);
			memset(result, 0, CREATEMAX * (sizeof(int)));
			for (int i = 0; i < sudokuNum; i++)
			{
				if (!solve(puzzleSet[i], result[i]))
				{
					throw MySudokuException();
				}
			}
			print(sudokuNum, result);
		}
		//-n x
		else if (strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n')
		{
			int t = str2num(argv[2], GANGNMAX);
			if (t <= 0)
			{
				throw MyParameterException();
			}
			memset(result, 0, CREATEMAX * (sizeof(int)));
			generate(t, EASY, result);
			print(t, result);
		}
		else
		{
			throw MyOrderException();
		}
	}
	//-n x -u
	else if (argc == 4 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'u'
		)
	{
		int t = str2num(argv[2], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, LOWER, UPPER, true, result);
		print(t, result);
	}
	//-u -n x
	else if (argc == 4 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'u' &&
		strlen(argv[2]) == 2 && argv[2][0] == '-' && argv[2][1] == 'n'
		)
	{
		int t = str2num(argv[3], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, LOWER, UPPER, true, result);
		print(t, result);
	}
	//-n x -m mode
	else if (argc == 5 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'm'
		)
	{
		int t = str2num(argv[2], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int mode = str2num(argv[4], MODEMAX);
		if (mode <= 0 || mode >= 4)
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, mode, result);
		print(t, result);
	}
	//-m mode -n x
	else if (argc == 5 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'm' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'n'
		)
	{
		int t = str2num(argv[4], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int mode = str2num(argv[2], MODEMAX);
		if (mode <= 0 || mode >= 4)
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, mode, result);
		print(t, result);
	}
	//-n x -r lower~upper
	else if (argc == 5 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'r'
		)
	{
		int t = str2num(argv[2], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[4]) == 5 && argv[4][2] == '~' &&
			'0' <= argv[4][0] && argv[4][0] <= '9' &&
			'0' <= argv[4][1] && argv[4][1] <= '9' &&
			'0' <= argv[4][3] && argv[4][3] <= '9' &&
			'0' <= argv[4][4] && argv[4][4] <= '9'
			)
		{
			lower = (argv[4][0] - '0') * 10 + (argv[4][1] - '0');
			upper = (argv[4][3] - '0') * 10 + (argv[4][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, false, result);
		print(t, result);
	}
	//-r lower~upper -n x
	else if (argc == 5 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'r' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'n'
		)
	{
		int t = str2num(argv[4], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[2]) == 5 && argv[2][2] == '~' &&
			'0' <= argv[2][0] && argv[2][0] <= '9' &&
			'0' <= argv[2][1] && argv[2][1] <= '9' &&
			'0' <= argv[2][3] && argv[2][3] <= '9' &&
			'0' <= argv[2][4] && argv[2][4] <= '9'
			)
		{
			lower = (argv[2][0] - '0') * 10 + (argv[2][1] - '0');
			upper = (argv[2][3] - '0') * 10 + (argv[2][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, false, result);
		print(t, result);
	}
	//-n x -r lower~upper -u
	else if (argc == 6 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'r' &&
		strlen(argv[5]) == 2 && argv[5][0] == '-' && argv[5][1] == 'u'
		)
	{
		int t = str2num(argv[2], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[4]) == 5 && argv[4][2] == '~' &&
			'0' <= argv[4][0] && argv[4][0] <= '9' &&
			'0' <= argv[4][1] && argv[4][1] <= '9' &&
			'0' <= argv[4][3] && argv[4][3] <= '9' &&
			'0' <= argv[4][4] && argv[4][4] <= '9'
			)
		{
			lower = (argv[4][0] - '0') * 10 + (argv[4][1] - '0');
			upper = (argv[4][3] - '0') * 10 + (argv[4][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, true, result);
		print(t, result);
	}
	//-n x -u -r lower~upper
	else if (argc == 6 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'u' &&
		strlen(argv[4]) == 2 && argv[4][0] == '-' && argv[4][1] == 'r'
		)
	{
		int t = str2num(argv[2], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[5]) == 5 && argv[5][2] == '~' &&
			'0' <= argv[5][0] && argv[5][0] <= '9' &&
			'0' <= argv[5][1] && argv[5][1] <= '9' &&
			'0' <= argv[5][3] && argv[5][3] <= '9' &&
			'0' <= argv[5][4] && argv[5][4] <= '9'
			)
		{
			lower = (argv[5][0] - '0') * 10 + (argv[5][1] - '0');
			upper = (argv[5][3] - '0') * 10 + (argv[5][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, true, result);
		print(t, result);
	}
	//-r lower~upper -n x -u
	else if (argc == 6 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'r' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'n' &&
		strlen(argv[5]) == 2 && argv[5][0] == '-' && argv[5][1] == 'u'
		)
	{
		int t = str2num(argv[4], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[2]) == 5 && argv[2][2] == '~' &&
			'0' <= argv[2][0] && argv[2][0] <= '9' &&
			'0' <= argv[2][1] && argv[2][1] <= '9' &&
			'0' <= argv[2][3] && argv[2][3] <= '9' &&
			'0' <= argv[2][4] && argv[2][4] <= '9'
			)
		{
			lower = (argv[2][0] - '0') * 10 + (argv[2][1] - '0');
			upper = (argv[2][3] - '0') * 10 + (argv[2][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, true, result);
		print(t, result);
	}
	//-r lower~upper -u -n x
	else if (argc == 6 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'r' &&
		strlen(argv[3]) == 2 && argv[3][0] == '-' && argv[3][1] == 'u' &&
		strlen(argv[4]) == 2 && argv[4][0] == '-' && argv[4][1] == 'n'
		)
	{
		int t = str2num(argv[5], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[2]) == 5 && argv[2][2] == '~' &&
			'0' <= argv[2][0] && argv[2][0] <= '9' &&
			'0' <= argv[2][1] && argv[2][1] <= '9' &&
			'0' <= argv[2][3] && argv[2][3] <= '9' &&
			'0' <= argv[2][4] && argv[2][4] <= '9'
			)
		{
			lower = (argv[2][0] - '0') * 10 + (argv[2][1] - '0');
			upper = (argv[2][3] - '0') * 10 + (argv[2][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, true, result);
		print(t, result);
	}
	//-u -n x -r lower~upper
	else if (argc == 6 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'u' &&
		strlen(argv[2]) == 2 && argv[2][0] == '-' && argv[2][1] == 'n' &&
		strlen(argv[4]) == 2 && argv[4][0] == '-' && argv[4][1] == 'r'
		)
	{
		int t = str2num(argv[3], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[5]) == 5 && argv[5][2] == '~' &&
			'0' <= argv[5][0] && argv[5][0] <= '9' &&
			'0' <= argv[5][1] && argv[5][1] <= '9' &&
			'0' <= argv[5][3] && argv[5][3] <= '9' &&
			'0' <= argv[5][4] && argv[5][4] <= '9'
			)
		{
			lower = (argv[5][0] - '0') * 10 + (argv[5][1] - '0');
			upper = (argv[5][3] - '0') * 10 + (argv[5][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, true, result);
		print(t, result);
	}
	//-u -r lower~upper -n x
	else if (argc == 6 &&
		strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'u' &&
		strlen(argv[2]) == 2 && argv[2][0] == '-' && argv[2][1] == 'r' &&
		strlen(argv[4]) == 2 && argv[4][0] == '-' && argv[4][1] == 'n'
		)
	{
		int t = str2num(argv[5], GANGNMAX);
		if (t <= 0)
		{
			throw MyParameterException();
		}
		int lower = 0;
		int upper = 0;
		if (strlen(argv[3]) == 5 && argv[3][2] == '~' &&
			'0' <= argv[3][0] && argv[3][0] <= '9' &&
			'0' <= argv[3][1] && argv[3][1] <= '9' &&
			'0' <= argv[3][3] && argv[3][3] <= '9' &&
			'0' <= argv[3][4] && argv[3][4] <= '9'
			)
		{
			lower = (argv[3][0] - '0') * 10 + (argv[3][1] - '0');
			upper = (argv[3][3] - '0') * 10 + (argv[3][4] - '0');
			if (lower > upper || lower < LOWER || upper > UPPER)
			{
				throw MyParameterException();
			}
		}
		else
		{
			throw MyParameterException();
		}
		memset(result, 0, CREATEMAX * (sizeof(int)));
		generate(t, lower, upper, true, result);
		print(t, result);
	}
	else
	{
		throw MyOrderException();
	}
}