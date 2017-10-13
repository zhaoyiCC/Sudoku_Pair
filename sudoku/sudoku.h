#include "headers.h"


#define random(x) (rand()%x)

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
inline int belonging(int x, int y) { return x / 3 * 3 + y / 3 + 1; }
inline int Position(int x, int y) { return 9 * x + y; }
using namespace std;
const int N = 11;
const int M = 83;

static int ans_all_cnt = 0, ans_all[1000010][M], ans_new[50010][M];

/*

在个人项目上增量修改，实现void generate(int number, int mode, int[][] result)接口，对于输入的数独游戏的需求数量和难度等级，通过result返回生成的数独游戏的集合。
对这一generate接口进行测试，把单元测试代码Push到Github上(注意避免把单元测试的结果Push到Github上)。
实现void generate(int number, int lower, int upper, bool unique, int[][] result)接口，生成number个空白数下界为lower，上界为upper的数独游戏，并且如果unique为真，则生成的数独游戏的解必须唯一，计算的结果存储在result中。
对这一generate接口进行测试，把单元测试代码Push到Github上(注意避免把单元测试的结果Push到Github上)。
实现bool solve(int[] puzzle, int[] solution)接口，对于输入的数独题目puzzle（数独矩阵按行展开为一维数组），返回一个bool值表示是否有解。如果有解，则将一个可行解存储在solution中（同样表示为数独矩阵的一维数组展开）。
对solve接口进行测试，把单元测试代码Push到Github上(注意避免把单元测试的结果Push到Github上)。
设计其他部分的接口，按照设计好的接口在个人项目基础上增量修改，同样把单元测试代码Push到Github上。
在完成这一阶段的任务之后，使用git tag step1标记第一阶段已经完成，并在Push到Github上时使用--tags参数把tag也推送到Github，例如git push origin --tags。

*/


class Core { //__declspec(dllexport)
public:
	int sol = 0, tot, x[M], a[M][N], a_backup[M][M][N], aaa[M];
	bool debug;
	int hasAnswer = 0;
	FILE *out;

	int value, cnt, n, m, len = 0;  // value代表要输出的矩阵的个数
	char ch;
	bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];

	int num_0, id, game[M];
	bool isEmpty[M];
	double p_exist;
	bool hasException = false;

	bool find(int x, int y, int z); //判断数独[x][y]的位置能否填z
	void init_gen(int val, int type); //处理-c
	void init_sol(); //处理-s
	void trans(int a[81]); //把当前数独进行数字转换，转换成第一行为1..9的数独
	bool isEquivalent(int a[81], int b[81]); //判断数独a与数独b是不是等效
	bool deleteElement(int pos, int r); //求解数独中的操作_增加一个数独元素的限制
	bool modifyElement(int pos, int r); //求解数独中的操作_填充一个数独元素
	void out_file(int *s); //输出数独s到文件(sudoku.txt)中
	void dfs1(int k, int type); //生成数独的回溯1
	void dfs2(int k, int type); //求解数独的回溯2
	int freedom(int a[M]); //求解数独a的自由度
	double getRandData(int min, int max); //生成一个(min,max)的浮点数
	void dfs3(int k, int tot); //从填满元素的数独中挖空的回溯3
	int work3(int num_0_t, int id_t, double p_t); //生成确定0个数的数独，原型是第id号满数独

	void generate(int number, int mode, int result[][M]); //对于输入的数独游戏的需求数量和难度等级，通过result返回生成的数独游戏的集合
	void generate(int number, int lower, int upper, bool unique, int result[][M]); //生成number个空白数下界为lower，上界为upper的数独游戏，并且如果unique为真，则生成的数独游戏的解必须唯一，计算的结果存储在result中
	bool check(int a[M]); //检查含0的数独a是不是合法的
	bool solve(int puzzle[M], int solution[M]); //对于输入的数独题目puzzle（数独矩阵按行展开为一维数组），返回一个bool值表示是否有解。如果有解，则将一个可行解存储在solution中（同样表示为数独矩阵的一维数组展开）

	void generate_single(int number, int from, int ran, int dow, int upd, bool unique, int result[][M]); //生成numer个数独，0的个数在[ran, ran+from-1]中，自由度在[dow, upd]中，unique代表要不要生成唯一解
	int solve_unique(int tmp[M]); //求解一个单一的数独tmp并求出解的个数, 结果放在ans_first

	int ans_first[M];
};

