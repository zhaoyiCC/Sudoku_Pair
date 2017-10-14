//  sudoku
//  Created by ohazyi on 2017/10/1.
//  Copyright © 2017 ohazyi. All rights reserved.
#include "sudoku.h"

struct timeb tb;
bool debug = false, debug_time = false, u_flag = false;
bool mainException = false;
int val = 0, r1, r2, pos_r;
char c[110];
string getTime() {  // 得到当前时间的ms的时间
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}
void printTime(string str) {  // 得到当前时间
	cout << str << ": ";
	string time;
	time = getTime();
	cout << time;
	ftime(&tb);
	printf(".%03d\n", tb.millitm);
}

bool calc(char* s) {
	val = 0;
	for (int i = 0; s[i]; ++i) {
		if (s[i] < '0' || s[i] > '9')
			return false;
		val = val * 10 + s[i] - '0';
	}
	//cout << "val=" << val << endl;
	return true;
}
//void exit_invalid(string s) {
//	cout << s << endl;
//	exit(0);
//}

void help() {
	cout << "【Supported Commands】" << endl;
	cout << "    1. -c <N> : generate N sudokus, 1 <= N <= 1000000" << endl;
	cout << "    2. -s <path> : solve sudoku puzzles in path file" << endl;
	cout << "    3. -n <N> -m <M> (-u) : generate N sudokus which mode is M, M = 1,2,3 (-u means every soduku has a unique solution or not)" << endl;
	cout << "    4. -n <N> -r <N1>~<N2> (-u) : generate N sudokus and the number of empty grids is bewteen [N1, N2], 20 <= N1 <= N2 <= 55" << endl;
	cout << "    5. -help : show the help menu" << endl;
	cout << "【Contact】" << endl;
	cout << "    1. Email us: ohazyi(zhaoyi1031@gmail.com), yaoling(3791454124@qq.com)" << endl;
	cout << "" << endl;
}
int main(int argc, char *argv[]) {

	Core s;
	s.out = fopen("sudoku.txt", "w");    // freopen("sudoku.txt", "w", stdout);

	s.debug = debug;
	if (debug_time) printTime("起始时间");
	try
	{
		if (argc == 2 && strcmp(argv[1], "-help") == 0) {
			help();
			return 0;
		}

		if (argc < 3 || strlen(argv[1]) != 2) {
			throw std::exception("【Insufficient arguments】Try -help");
		}

		if (strcmp(argv[1], "-c") == 0) {
			if (argc > 3)
				throw std::exception("Excessive arguments of -c");
			val = 1;  // value = atoi(argv[2])
			if (!calc(argv[2]))
				throw std::exception("Use a number after -c");
			if (val < 1 || val>1000000)
				throw std::exception("-c number should be in [1,1000000]");

			s.init_gen(val, 1);
			cout << "-c  生成数独数：" << val << endl;
		}
		else if (strcmp(argv[1], "-s") == 0) {
			if (argc > 3)
				throw std::exception("Excessive arguments of -s");
			freopen(argv[2], "r", stdin);  // freopen("puzzlefile.txt", "r", stdin);

			s.init_sol();
			cout << "-s  解决了数独文件：";
			printf("%s\n", argv[2]);
		}
		else 
		{
			vector<string> cmd_type = { "-n", "-m", "-r", "-u" };
			string str(argv[1]);
			int type = -1;
			bool flag_arg;
			string arg_s, r_1, r_2;
			map<string, int> mp;
			for (int i_arg = 1; i_arg < argc; i_arg++) {

				flag_arg = false;
				for (auto sss : cmd_type) {
					if (sss == argv[i_arg]) {
						flag_arg = true;
						arg_s = sss;
						break;
					}
				}
				if (!flag_arg) {
					throw std::exception("Supported arguments: -c -s -n -m -r -u");
				}
				if (arg_s == "-u") {//-u -n 10
					u_flag = true;
					continue;
				}
				if ((++i_arg) == argc) {//-n -u 10
					throw std::exception("Lack number after -n/-m/-r");
				}

				if (arg_s == "-r") {
					flag_arg = false;
					rep(j, 0, (int)strlen(argv[i_arg]) - 1) {
						if (argv[i_arg][j] == '~') {
							flag_arg = true;
							pos_r = j;
							c[j] = '\0';
							break;
						}
						c[j] = argv[i_arg][j];
					}
					if (!flag_arg)
						throw std::exception("【-r Usage; -r r1~r2】");

					if (!calc(c))
						throw std::exception("Use r1~r2 after -r, r1 should be a int");
					r1 = val;
					memset(c, 0, sizeof(c));
					rep(j, pos_r + 1, (int)strlen(argv[i_arg]))
						c[j - pos_r - 1] = argv[i_arg][j];
					if (!calc(c))
						throw std::exception("Use r1~r2 after -r, r2 should be a int");
					r2 = val;
					if (r1 < 20 || r2 < 20 || r1 > 55 || r2 > 55 || r1 > r2)
						throw std::exception("-r number should be in [20, 55] and r1<=r2");
					mp[arg_s] = r1 * 100 + r2;
					continue;
				}
				if (calc(argv[i_arg])) {
					if (arg_s == "-n" && (val < 1 || val>10000))
						throw std::exception("-c number should be in [1,1000000]");
					if (arg_s == "-m" && (val < 1 || val>3))
						throw std::exception("-m number should be 1 or 2 or 3");
					if (arg_s == "-r" && (val < 20 || val>55))
						throw std::exception("lower and upper should be in [20, 55]");
					if (mp.count(arg_s) > 0)
						throw std::exception("Repeated parameter!");
					mp[arg_s] = val;
				}
				else {
					throw std::exception("Invalid Command Number");
				}
			}

			for (auto sss : cmd_type) {
				if (sss == "-u") {
					cout << "-u : Yes" << endl;
					continue;
				}
				cout << sss << " : " << ((mp.count(sss)==0)?"No":"Yes") << "    ";
				if (mp.count(sss) > 0) {
					if (sss == "-r")
						cout << r1 << "-" << r2;
					else
						cout << mp[sss];
				}
				cout << endl;
			}

			if (mp.count("-m") > 0) {
				if (u_flag)
					throw std::exception("-u can not be with -m");
				if (mp.size() > 2)
					throw std::exception("Too many arguments!");
				if (mp.count("-n") == 0)
					throw std::exception("-m must be with -n");
				//s.init_gen(10000, 0);//mp["-n"]*5
				s.generate(mp["-n"], mp["-m"], ans_new);
				rep(i, 0, mp["-n"]-1) {
					s.out_file(ans_new[i]);
				}
			}
			else
			if (mp.count("-r") > 0) {  //
				if (mp.size() > 2)
					throw std::exception("Too many arguments!");
				if (mp.count("-n") == 0)
					throw std::exception("-m must be with -n");

				s.generate(mp["-n"], r1, r2, u_flag, ans_new);
				rep(i, 0, mp["-n"]-1) {
					s.out_file(ans_new[i]);
				}
			}
			else 
			if (mp.count("-n") > 0 && mp.size() == 1)
			{
				throw std::exception("-n Must be with -m or -r");
			}
			else
				throw std::exception("【Other Invalid Command】Try -help");
		}
	}
	catch (const std::exception& e)
	{
		mainException = true;
		puts(e.what());
	}
	if (debug_time) printTime("结束时间");
	return 0;
}
