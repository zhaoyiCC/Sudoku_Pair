#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include <stack>
#define CELL 81
#define GRIDSIZE 9

using namespace std;
class Core
{
public:
	Core();
	void generate(int number,int result[][CELL]);   //-c
	void generate(int number,int mode,int result[][CELL]); //-n -m
	void generate(int number, int lower, int upper, bool unique, int result[][CELL]); //-n -r -u
	bool solve(int puzzle[CELL], int solution[CELL]);
	
private:
	int m_grid[GRIDSIZE][GRIDSIZE];
	bool IsValid(int pos, bool isSolve);
	bool TraceBackSolve(int pos);
	int TraceBack(int pos, int number, int& count, int result[][CELL],bool isSolve);
	void CopySudoku(int result[CELL], int temp[GRIDSIZE][GRIDSIZE]);
	bool IsSingleSolution(int tot, int& ans);
};