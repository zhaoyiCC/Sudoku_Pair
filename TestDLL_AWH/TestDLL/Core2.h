#pragma once
#include "set"
#include "string"
#ifndef ENDPRODUCER_H_
#define ENDPRODUCER_H_
#define MAX_NUM_ROWSUB 72
#define SUDOKU_SIZE 81
#define NUM_ROW 9
#define Type123 1
#define Type456 4
#define Type789 7
#define Check true
#define NotCheck false
#define CREATEMAX 1000000
#define GANGNMAX 10000
#define MODEMAX 3
#define LOWER 20
#define UPPER 55
#define EASY 1
#define MEDIUM 2
#define HARD 3

using namespace std;



//struct __declspec(dllexport)  MyOrderException : public exception
struct MyOrderException : public exception
{
	const char * msg() const throw ()
	{
		return "Error : No Such Order\n\
    Correct Usage:\n\
        -c [number]                         (1<=number<=1,000,000)\n\
        -s [puzzle_file_path]               (absolute or relative)\n\
        -n [number]                         (1<=number<=10,000)\n\
        -n [number] -m [mode]               (1<=number<=10,000) (1<=mode<=3)\n\
        -n [number] -u                      (1<=number<=10,000)\n\
        -n [number] -r [lower]~[upper]      (1<=number<=10,000) (20<=lower<=upper<=55)\n\
        -n [number] -r [lower]~[upper] -u   (1<=number<=10,000) (20<=lower<=upper<=55)\n\
    Parameter order is arbitrary.";
	}
};

//struct __declspec(dllexport)  MyFileException : public exception
struct MyFileException : public exception
{
	const char * msg() const throw ()
	{
		return "Error : File Not Found\n\
        -s [puzzle_file_path]               (absolute or relative)\n\
        File must exist!";
	}
};

//struct __declspec(dllexport)  MySudokuException : public exception
struct MySudokuException : public exception
{
	const char * msg() const throw ()
	{
		return "Error : Unsupported Sudoku\n\
        File content must be legal!";
	}
};

//struct __declspec(dllexport)  MyParameterException : public exception
struct MyParameterException : public exception
{
	const char * msg() const throw ()
	{
        return "Error : No Such Order\n\
    Correct Usage:\n\
        -c [number]                         (1<=number<=1,000,000)\n\
        -s [puzzle_file_path]               (absolute or relative)\n\
        -n [number]                         (1<=number<=10,000)\n\
        -n [number] -m [mode]               (1<=number<=10,000) (1<=mode<=3)\n\
        -n [number] -u                      (1<=number<=10,000)\n\
        -n [number] -r [lower]~[upper]      (1<=number<=10,000) (20<=lower<=upper<=55)\n\
        -n [number] -r [lower]~[upper] -u   (1<=number<=10,000) (20<=lower<=upper<=55)\n\
    Parameter order is arbitrary.";
	}
};

//struct __declspec(dllexport) MyFormatException : public exception
struct MyFormatException : public exception
{
	const char * msg() const throw ()
	{
        return "Error : No Such Order\n\
    Correct Usage:\n\
        -c [number]                         (1<=number<=1,000,000)\n\
        -s [puzzle_file_path]               (absolute or relative)\n\
        -n [number]                         (1<=number<=10,000)\n\
        -n [number] -m [mode]               (1<=number<=10,000) (1<=mode<=3)\n\
        -n [number] -u                      (1<=number<=10,000)\n\
        -n [number] -r [lower]~[upper]      (1<=number<=10,000) (20<=lower<=upper<=55)\n\
        -n [number] -r [lower]~[upper] -u   (1<=number<=10,000) (20<=lower<=upper<=55)\n\
    Parameter order is arbitrary.";
	}
};

//class __declspec(dllexport) Core
class Core
{
private:
	int _ancestorMartix[SUDOKU_SIZE] =
	{ 9,4,1,2,8,3,6,7,5,
		3,7,2,5,6,1,8,9,4,
		8,5,6,7,4,9,1,2,3,
		2,6,4,1,5,7,3,8,9,
		1,9,5,8,3,4,7,6,2,
		7,8,3,6,9,2,5,4,1,
		5,2,7,9,1,8,4,3,6,
		4,1,9,3,7,6,2,5,8,
		6,3,8,4,2,5,9,1,7
	};
	int solveCnt = 0;
	
	set<string> _startSet;

public:
	Core();
	~Core();
	void RowSwap(int* srcMartix, int Type, int* rank);

	void create(int number, int result[][SUDOKU_SIZE]);
	bool DuplicateCheck(int* a, int aim, int count);
	void Swap(int* a, int* b);

	//generate(3 params)
	void generate(int number, int mode, int result[][SUDOKU_SIZE]);
	void generate(int number, int lower, int upper, bool unique, int result[][SUDOKU_SIZE]);
	bool isUnique(int puzzle[SUDOKU_SIZE]);
	int numTransfor(int num);  
	int RemoveCandidates(int index, int puzzle[], int flag[]);
	bool Fill(int index, int puzzle[], int flag[], int tt);
	bool solve(int puzzle[], int solution[]);
	int str2num(char *s, int max);

	// io
	void print(int number, int result[][SUDOKU_SIZE]);
	void read(int argc, char* argv[]);
	int readFile(char *path, int puzzleSet[][SUDOKU_SIZE]);
};

#endif