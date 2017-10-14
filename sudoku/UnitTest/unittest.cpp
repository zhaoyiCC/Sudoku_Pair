#include "stdafx.h"
//#include "../sudoku.h"
#include "main.cpp"
#include <iostream>
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
#define rep(i,a,b) for (int i = (a); i <= (b); ++i)
int lll[10010][M];
int hhh = 0;
namespace UnitTest
{
	const int matrixLen = 9;
	const int maxn = 1000;
	const int maxnode = 5000;
	const int maxr = 1000;
	struct DLX {
		int n, sz;  // ¡– ˝£¨Ω⁄µ„◊‹ ˝
		int S[maxn];  // ∏˜¡–Ω⁄µ„ ˝(≤ª∞¸¿®–Èƒ‚Ω⁄µ„)
		int row[maxnode], col[maxnode];  // ∏˜Ω⁄µ„––¡–±‡∫≈
		int L[maxnode], R[maxnode], U[maxnode], D[maxnode];  //  Æ◊÷¡¥±Ì
		int ansd, ans[maxr];  // Ω‚
		void init(int n) {
			this->n = n;
			// –Èƒ‚Ω⁄µ„,0∫≈Œ™¡¥±ÌÕ∑
			for (int i = 0; i <= n; i++) {
				U[i] = i;
				D[i] = i;
				L[i] = i - 1;
				R[i] = i + 1;
			}
			R[n] = 0; L[0] = n;
			sz = n + 1;
			memset(S, 0, sizeof(S));
		}
		void addRow(int r, int columns[], int cnt) {
			// r ––∫≈,columns¥Ê∑≈’‚“ª––µƒƒƒ–©¡–Œ™1
			int first = sz;  // sz µ±«∞–¬Ω®Ω⁄µ„±Í∫≈
			for (int i = 0; i < cnt; i++) {
				int c = columns[i];
				L[sz] = sz - 1;
				R[sz] = sz + 1;
				D[sz] = c;
				U[sz] = U[c];
				D[U[c]] = sz;
				U[c] = sz;
				row[sz] = r;
				col[sz] = c;
				S[c]++;
				sz++;
			}
			R[sz - 1] = first;
			L[first] = sz - 1;
		}

		// À≥◊≈¡¥±ÌA,±È¿˙≥˝sÕ‚µƒ∆‰À¸‘™Àÿ
#define FOR(i, A, s) for (int i= A[s]; i != s; i=A[i])
		void remove(int c) {
			// “∆≥˝±Í∫≈Œ™cÀ˘‘⁄µƒ¡–
			L[R[c]] = L[c];
			R[L[c]] = R[c];
			FOR(i, D, c)
				FOR(j, R, i) {
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				--S[col[j]];
			}
		}
		void restore(int c) {
			// ª÷∏¥±Í∫≈cÀ˘‘⁄µƒ¡–
			FOR(i, U, c)
				FOR(j, L, i) {
				++S[col[j]];
				U[D[j]] = j;
				D[U[j]] = j;
			}
			L[R[c]] = c;
			R[L[c]] = c;
		}
		// dŒ™µ›πÈ…Ó∂»
		int dfs(int d, int cnt) {
			if (R[0] == 0) {
				// ±Ì æ¡–µƒ–Èƒ‚Ω⁄µ„∂º…æÕÍ¡À
				ansd = d;  // ’“µΩΩ‚
				return cnt + 1;  // º«¬ºΩ‚µƒ≥§∂»
			}
			// ’“S◊Ó–°µƒ¡–c
			int c = R[0];  // µ⁄“ª∏ˆŒ¥…æ≥˝¡–
			FOR(i, R, 0)
				if (S[i] < S[c])
					c = i;
			remove(c);  // …æ≥˝µ⁄c¡–
			FOR(i, D, c) {  // ”√Ω⁄µ„iÀ˘‘⁄––∏≤∏«µ⁄c¡–
				ans[d] = row[i];
				FOR(j, R, i)
					remove(col[j]);  // …æ≥˝Ω⁄µ„iÀ˘‘⁄––ƒ‹∏≤∏«µƒ∆‰À¸À˘”–¡–
				cnt = dfs(d + 1, cnt);
				if (cnt == 2)
					return cnt;
				FOR(j, L, i)
					restore(col[j]);  // ª÷∏¥Ω⁄µ„iÀ˘‘⁄––ƒ‹∏≤∏«µƒ∆‰À¸À˘”–¡–
			}
			restore(c);  // ª÷∏¥µ⁄c¡–
			return cnt;
		}
		int solve(int ansre[], int *anssize) {
			int re = dfs(0, 0);
			if (re == 0)
				return 0;
			for (int i = 0; i < ansd; i++)
				ansre[i] = ans[i];
			*anssize = ansd;
			return re == 1 ? 1 : -1;
		}
	};
	const int SLOT = 0;
	const int ROW = 1;
	const int COL = 2;
	const int SUB = 3;
	struct SolveS_DLX {
		DLX solver;
		int encode(int a, int b, int c) {
			return (a * matrixLen + b) * matrixLen + c + 1;
		}
		void decode(int code, int *a, int *b, int *c) {
			code--;
			*c = code%matrixLen;
			code /= matrixLen;
			*b = code %matrixLen;
			code /= matrixLen;
			*a = code;
		}
		int solve(int matrix[matrixLen][matrixLen]) {
			solver.init(matrixLen*matrixLen * 4);
			for (int r = 0; r < matrixLen; r++)
				for (int c = 0; c < matrixLen; c++)
					for (int v = 0; v < matrixLen; v++) {
						if (matrix[r][c] == 0 || matrix[r][c] == v + 1) {
							// vector<int> columns;
							int columns[10];
							int cnt = 0;
							// ¡–∫≈¥”1ø™ º
							columns[cnt++] = encode(SLOT, r, c);
							columns[cnt++] = encode(ROW, r, v);
							columns[cnt++] = encode(COL, c, v);
							columns[cnt++] = encode(SUB, r / 3 * 3 + c / 3, v);
							solver.addRow(encode(r, c, v), columns, cnt);
						}
					}
			int ans[1000];
			int ansSize = 0;
			int re = solver.solve(ans, &ansSize);
			if (re != 0) {
				for (int i = 0; i < ansSize; i++) {
					int r, c, v;
					decode(ans[i], &r, &c, &v);
					matrix[r][c] = v + 1;
				}
			}
			return re;
		}
	};
	int calcSudokuAnswer(int a[83]) {
		//∑µªÿ0¥˙±ÌŒﬁΩ‚ 1¥˙±ÌŒ®“ªΩ‚ -1¥˙±Ì∂‡∏ˆΩ‚
		SolveS_DLX solver;
		int matrix[matrixLen][matrixLen];
		for (int i = 0; i<matrixLen; i++)
			for (int j = 0; j<matrixLen; j++)
				matrix[i][j] = a[i*matrixLen + j];
		return solver.solve(matrix);
	}

	bool check(int a[M]) {//判断含0是不是一个数独
		rep(i, 0, 80) {
			if (a[i] >= '0')
				a[i] -= '0';
			if (a[i] < 0 || a[i] > 9)
				return false;
			/*cout << a[i] << " ";
			if ((i + 1) % 9 == 0)
				cout << endl;*/
		}
		cout << endl;
		bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];
		memset(vis_col, false, sizeof(vis_col));
		memset(vis_magic, false, sizeof(vis_magic));
		memset(vis_row, false, sizeof(vis_row));
		int x, y;
		rep(i, 0, 80) {
			if (a[i] == 0)
				continue ;
			x = i / 9;
			y = i % 9;
			if (vis_col[x][a[i]] || vis_row[y][a[i]] || vis_magic[belonging(x, y)][a[i]])
				return false;
			vis_col[x][a[i]] = true;
			vis_row[y][a[i]] = true;
			vis_magic[belonging(x, y)][a[i]] = true;
		}
		return true;
	}

	bool check2(int a[M], int b[M]) {
		rep(i, 0, 80) {
			if (b[i] > 0 && a[i] != b[i])
				return false;
		}
		return true;
	}

	bool check_r(int number,int start, int end, int a[][M]) {
		FILE *tmp;
		tmp = fopen("check_r.txt", "w");

		for (int i = 0; i < 10; ++i) {
			rep(j, 0, 80) {
				fprintf(tmp, "%d ", a[i][j]);
				if ((j + 1) % 9 == 0)
					fprintf(tmp, "\n");
			}

		}

		int tot;
		rep(i, 0, number-1) {
			
			tot = 0;
			rep(j, 0, 80) {
				/*if (a[i][j] >= '0')
					a[i][j] -= '0';*/
				tot += (a[i][j] == 0);
			}
			fprintf(tmp, "%d %d\n",i,tot);
			if (tot < start || tot > end)
				return false;
		}
		return true;
	}
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{//Test solve
			hhh++;
			Core s;
			int ppp[M] = {
				0, 0, 0, 0, 0, 5, 0, 0, 9,
				3, 0, 5, 0, 0, 9, 0, 0, 6,
				7, 8, 0, 0, 2, 0, 0, 0, 0,
				1, 0, 0, 4, 0, 7, 6, 0, 0,
				4, 5, 0, 0, 0, 1, 0, 0, 7,
				8, 0, 0, 0, 0, 3, 0, 0, 0,
				0, 0, 1, 0, 7, 0, 5, 0, 4,
				0, 6, 4, 0, 0, 2, 8, 7, 3,
				5, 7, 8, 6, 3, 4, 9, 1, 2
			};
			s.out = fopen("unit_out_1.txt", "w");
			int kkk[M];
			bool zzyy = s.solve(ppp, kkk);
			fprintf(s.out, "Answer is %d\n", s.sol);
			s.out_file(kkk);
			Assert::AreEqual(zzyy, true);
		}
		TEST_METHOD(TestMethod2)
		{//Test check
			Core s;
			int ppp[M] = {
				0, 0, 0, 0, 0, 5, 9, 0, 9,
				3, 0, 5, 0, 0, 9, 0, 0, 6,
				7, 8, 0, 0, 2, 0, 0, 0, 0,
				1, 0, 0, 4, 0, 7, 6, 0, 0,
				4, 5, 0, 0, 0, 1, 0, 0, 7,
				8, 0, 0, 0, 0, 3, 0, 0, 0,
				0, 0, 1, 0, 7, 0, 5, 0, 4,
				0, 6, 4, 0, 0, 2, 8, 7, 3,
				5, 7, 8, 6, 3, 4, 9, 1, 2
			};
			s.out = fopen("unit_out_2.txt", "w");
			fprintf(s.out, "Answer is %d\n", s.sol);
			int kkk[M];
			bool zzyy = s.solve(ppp, kkk);
			s.out_file(kkk);
			Assert::AreEqual(zzyy, false);
			fprintf(s.out, "hhh = %d\n", hhh);
		}
		TEST_METHOD(TestMethod3)
		{//check the function of generate -r
			int fff[1010][M];
			Core s;
			s.generate(1000, 20, 50, true, fff);
			s.out = fopen("unit_out_3.txt", "w");
			for (int i = 0; i < 1000; ++i) {
				rep(j, 0, 80) {
					fprintf(s.out, "%d ", fff[i][j]);
					if ((j + 1) % 9 == 0)
						fprintf(s.out, "\n");
				}
				fprintf(s.out, "\n");
			}
			bool zzyy = check_r(100, 20, 60, lll);
			//rep (i,0,80)//Must out_file later than check for it will add '0'
			//	s.out_file(lll[i]);
			Assert::AreEqual(zzyy, true);
		}
		TEST_METHOD(TestMethod4)
		{//check the function of generate -m
			Core s;
			s.generate(10000, 1, lll);
			s.out = fopen("unit_out_4.txt", "w");
			for (int i = 0; i < 10; ++i) {
				rep(j, 0, 80) {
					fprintf(s.out, "%d ", lll[i][j]);
					if ((j + 1) % 9 == 0)
						fprintf(s.out, "\n");
				}
			}
			bool zzyy = true;
			int fre;
			rep(i, 0, 9999) {
				fre = s.freedom(lll[i]);
				fprintf(s.out, "%d   %d\n", i, fre);
				if (fre > 650) {
					zzyy = false;
					break;
				}
			}
			//rep(i, 0, 9999)//Must out_file later than check for it will add '0'
				//s.out_file(lll[i]);
			Assert::AreEqual(zzyy, true);
			fprintf(s.out, "hhh = %d\n", hhh);
		}
		/*
		  Test -r r1~r2 and r1 < 20
		*/
		TEST_METHOD(TestMethod5)
		{
			Core s;
			s.generate(100, 10, 55, true, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		   Test -r r1~r2 and r2 > 55
		*/
		TEST_METHOD(TestMethod8)
		{
			Core s;
			s.generate(100, 30, 56, true, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		   Test -r r1~r2 and r1 > r2
		*/
		TEST_METHOD(TestMethod9)
		{
			Core s;
			s.generate(100, 50, 40, true, lll);
			Assert::AreEqual(s.hasException, true);
		}

		
		TEST_METHOD(TestMethod6)
		{//check -u
			Core s;
			s.generate(1000, 20, 50, true, lll);
			s.out = fopen("unit_out_6.txt", "w");
			for (int i = 0; i < 10; ++i) {
				rep(j, 0, 80) {
					fprintf(s.out, "%d ", lll[i][j]);
					if ((j + 1) % 9 == 0)
						fprintf(s.out, "\n");
				}
			}
			bool zzyy = true;
			rep(i, 0, 999) {
				s.out_file(lll[i]);
;				if (!check(lll[i])) {
					zzyy = false;
					break;
				}
				if (calcSudokuAnswer(lll[i]) != 1) {
					zzyy = false;
					break;
				}
			}
			Assert::AreEqual(zzyy, true);
		}
		TEST_METHOD(TestMethod7)
		{//test solve_unique
			Core s;
			int ppp[M] = {
				6, 1, 0, 3, 0, 0, 0, 0, 9,
				0, 4, 0, 7, 0, 0, 0, 2, 0,
				0, 8, 9, 1, 2, 0, 0, 0, 0,
				0, 2, 3, 0, 0, 7, 0, 9, 0,
				4, 5, 6, 0, 9, 1, 2, 3, 7,
				0, 0, 7, 0, 0, 3, 0, 5, 0,
				0, 0, 0, 0, 0, 8, 0, 6, 0,
				5, 6, 0, 0, 0, 0, 0, 0, 3,
				9, 0, 0, 6, 3, 0, 0, 0, 0
			};
			int uni = s.solve_unique(ppp);
			
			s.out = fopen("unit_out_7.txt", "w");
			fprintf(s.out, "%d\n", uni);
			Assert::AreEqual((uni>1), true);
		}
		/*
		Test -n(with -r)
		*/
		TEST_METHOD(TestMethod10)
		{
			Core s;
			s.generate(0, 30, 50, true, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		Test -n(with -r)
		*/
		TEST_METHOD(TestMethod11)
		{
			Core s;
			s.generate(10001, 30, 50, true, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		Test -n(with -m)
		*/
		TEST_METHOD(TestMethod12)
		{
			Core s;
			s.generate(10001, 3, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		Test -n(with -m)
		*/
		TEST_METHOD(TestMethod13)
		{
			Core s;
			s.generate(-1, 2, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		Test -m
		*/
		TEST_METHOD(TestMethod14)
		{
			Core s;
			s.generate(101, 4, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		Test -m
		*/
		TEST_METHOD(TestMethod15)
		{
			Core s;
			s.generate(10001, 0, lll);
			Assert::AreEqual(s.hasException, true);
		}
		/*
		Test -c
		*/
		TEST_METHOD(TestMethod16)
		{
			Core s;
			s.out = fopen("sudoku_16.txt", "w");

			s.init_gen(1, 1);
			bool zy = true;
			rep(i, 1, 1) {
				s.out_file(ans_all[i]);
				if (!check(ans_all[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual((!s.hasException&&zy), true);
		}
		/*
		Test -c
		*/
		TEST_METHOD(TestMethod17)
		{
			Core s;
			s.out = fopen("sudoku_17.txt", "w");

			s.init_gen(10, 1);
			bool zy = true;
			rep(i, 1, 10) {
				s.out_file(ans_all[i]);
				if (!check(ans_all[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual((!s.hasException&&zy), true);
		}
		/*
		Test -c
		*/
		TEST_METHOD(TestMethod18)
		{
			Core s;
			s.out = fopen("sudoku_18.txt", "w");

			s.init_gen(100, 1);
			bool zy = true;
			rep(i, 1, 100) {
				s.out_file(ans_all[i]);
				if (!check(ans_all[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual((!s.hasException&&zy), true);
		}
		/*
		Test -c
		*/
		TEST_METHOD(TestMethod19)
		{
			Core s;
			s.out = fopen("sudoku_19.txt", "w");

			s.init_gen(1000, 1);
			bool zy = true;
			rep(i, 1, 1000) {
				s.out_file(ans_all[i]);
				if (!check(ans_all[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual((!s.hasException&&zy), true);
		}
		/*
		Test -c
		*/
		TEST_METHOD(TestMethod20)
		{
			Core s;
			s.out = fopen("sudoku_20.txt", "w");

			s.init_gen(1, 10000);
			bool zy = true;
			rep(i, 1, 1) {
				s.out_file(ans_all[i]);
				if (!check(ans_all[i])) {
					zy = false;
					break;
				}
			}
			Assert::AreEqual((!s.hasException&&zy), true);
		}
		/*
		Test -n 100 -m 1
		*/
		TEST_METHOD(TestMethod21)
		{
			char *command[10] = { "sudoku.exe", "-n", "100", "-m", "1" };
			main (5, (char**)command);
			Assert::AreEqual(mainException, false);
			mainException = false;
		}
		/*
		Test -n 100 -m 4
		*/
		TEST_METHOD(TestMethod22)
		{
			char *command[] = { "sudoku.exe", "-n", "100", "-m", "4" };
			main (5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		/*
		Test -m 2
		*/
		TEST_METHOD(TestMethod23)
		{
			char *command[] = { "sudoku.exe", "-m", "2" };
			main(5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		/*
		Test -n 100 -n 100 -m 2
		*/
		TEST_METHOD(TestMethod24)
		{
			char *command[] = { "sudoku.exe","-n", "100", "-n", "100", "-m", "2" };
			main(5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		/*
		Test -g 100
		*/
		TEST_METHOD(TestMethod25)
		{
			char *command[] = { "sudoku.exe","-g","100" };
			main(5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		/*
		Test -c
		*/
		TEST_METHOD(TestMethod26)
		{
			char *command[] = { "sudoku.exe","-c" };
			main(5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		/*
		Test -c  1000000000
		*/
		TEST_METHOD(TestMethod27)
		{
			char *command[] = { "sudoku.exe","-c","1000000000" };
			main(5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		/*
		Test -n 100 - u
		*/
		TEST_METHOD(TestMethod28)
		{
			char *command[] = { "sudoku.exe","-n 100 - u"};
			main(5, (char**)command);
			Assert::AreEqual(mainException, true);
			mainException = false;
		}
		
	};
}