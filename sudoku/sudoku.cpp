//  sudoku
//  Created by ohazyi on 2017/10/1.
//  Copyright © 2017 ohazyi. All rights reserved.

#include "sudoku.h"

struct timeb tb;
bool debug = false, debug_time = true, u_flag = false;
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
	cout << "val=" << val << endl;
	return true;
}
void exit_invalid(string s) {
	cout << s << endl;
	exit(0);
}

int main(int argc, char *argv[]) {
	srand((int)time(0));

	Core s;
	/*if (argc != 3)
		exit_invalid("Too many or too few arguments!");*/
	if (strlen(argv[1]) != 2)
		exit_invalid("Invalid arguments!");
	s.out = fopen("sudoku.txt", "w");    // freopen("sudoku.txt", "w", stdout);
	s.debug = debug;
	if (debug_time) printTime("起始时间");
	if (strcmp(argv[1],"-c")==0) {
		val = 1;  // value = atoi(argv[2])
		if (!calc(argv[2]))
			exit_invalid("Invalid Command -c Number");
		if (val < 1 || val>1000000) 
			exit_invalid("Invalid -c number");

		s.init_gen(val, 1);
	}
	else if (strcmp(argv[1], "-s") == 0) {
		freopen(argv[2], "r", stdin);  // freopen("puzzlefile.txt", "r", stdin);
		
		s.init_sol();
	}
	else {
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
				exit_invalid("Invalid Command - argument");
			}
			if (arg_s == "-u") {//-u -n 10
				u_flag = true;
				continue;
			}
			if ((++i_arg) == argc) {//-n -u 10
				exit_invalid("Lack number");
			}
			
			if (arg_s == "-r") {
				flag_arg = false;
				rep (j, 0, (int)strlen(argv[i_arg]) - 1) {
					if (argv[i_arg][j] == '~') {
						flag_arg = true;
						pos_r = j;
						c[j] = '\0';
						break;
					}
					c[j] = argv[i_arg][j];
				}
				if (!flag_arg)
					exit_invalid("Invalid -r argument");

				if (!calc(c))
					exit_invalid("Invalid -r number1");
				r1 = val;
				memset(c, 0, sizeof(c));
				rep(j, pos_r + 1, (int)strlen(argv[i_arg]))
					c[j - pos_r - 1] = argv[i_arg][j];
				if (!calc(c))
					exit_invalid("Invalid -r number2");
				r2 = val;
				if (r1 < 20 || r2 < 20 || r1 > 55 || r2 > 55 || r1 > r2) 
					exit_invalid("-r number should be in [20, 55] and r1<=r2");
				mp[arg_s] = r1*100+r2;
				continue ;
			}
			if (calc(argv[i_arg])) {
				if (arg_s == "-n" && (val<1 || val>10000))
					exit_invalid("Invalid -n number");
				if (arg_s == "-m" && (val<1 || val>3))
					exit_invalid("Invalid -m number");
				if (arg_s == "-r" && (val<20 || val>55))
					exit_invalid("Invalid -r number");
				if (mp.count(arg_s) > 0)
					exit_invalid("Repeated parameter!");
				mp[arg_s] = val;
			}
			else {
				exit_invalid("Invalid Command Number");
			}

		}

		for (auto sss : cmd_type) {
			if (sss == "-u")
				continue;
			cout << sss << " : " << mp.count(sss) << "    ";
			if (mp.count(sss) > 0)
				cout << mp[sss];
			cout << endl;
		}

		if (mp.count("-m") > 0) {
			cout << u_flag << "u——flag" << endl;
			if (u_flag)
				exit_invalid("-u can not be with -m");
			if (mp.size() > 2)
				exit_invalid("Too many arguments!");
			if (mp.count("-n") == 0)
				exit_invalid("-m must be with -n");
			s.init_gen(10000, 0);//mp["-n"]*5
			s.generate(mp["-n"], mp["-m"], ans_new);
			rep(i, 1, mp["-n"]){
				s.out_file(ans_new[i]);
			}
		}else
		if (mp.count("-r") > 0) {  //
			if (mp.size() > 2)
				exit_invalid("Too many arguments!");
			if (mp.count("-n") == 0)
				exit_invalid("-m must be with -n");
			s.init_gen(10000, 0);
			s.generate(mp["-n"], r1, r2, u_flag, ans_new);
			rep(i, 1, mp["-n"]) {
				s.out_file(ans_new[i]);
			}
		}
	}
	if (debug_time) printTime("结束时间");
	return 0;
}
