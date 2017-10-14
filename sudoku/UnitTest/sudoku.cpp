#include "stdafx.h"
#include "sudoku.h"

int Core::solve_unique(int tmp[M]) {
	hasAnswer = 0;//false
	memcpy(x, tmp, sizeof(x));

	memset(a, 0, sizeof(a));
	rep(i, 0, 80) {
		if (x[i] > 0)
			modifyElement(i, x[i]);
	}
	dfs2(1, 0);
	return hasAnswer;
}

void Core::generate_single(int number, int from, int ran, int dow, int upd, bool unique, int result[][M]) {
	int first, fre, cnt_f = 0, id = 1, uni;
	while (cnt_f < number) {
		if (debug)
			cout << "----------------------" << endl;
		//srand((int)time(0));
		first = random(ran) + from;
		if (debug)
			cout << "空白个数：" << first << endl;

		fre = work3(first, id, 1.0*first / 81.0);
		if (fre >= dow && fre <= upd) {
			if (unique) {
				uni = solve_unique(game);
				if (uni > 1) {
					if (debug)
						cout << "********解不唯一********" << id << endl;
					//id++;
					continue;
				}
			}

			//cnt_f++;
			memcpy(result[cnt_f++], game, sizeof(game));
		}
		id++;
		if (debug)
			cout << "----------------------" << id << endl;
	}
	cout << "做到了第几个数独: " << id << " 产生数独数： " << cnt_f << endl;
}

void Core::generate(int number, int mode, int result[][M]) {
	try {
		if (number < 1 || number > 10000) {
			throw exception("-n number should be in [1,10000]");
		}
		if (mode < 1 || mode > 3) {
			throw exception("-m mode should be in 1 or 2 or 3");
		}
		init_gen(50000, 0);

		switch (mode) {
		case 1:
			generate_single(number, 40, 10, 0, 650, false, result);
			break;
		case 2:
			generate_single(number, 46, 15, 651, 999, false, result);
			break;
		case 3:
			generate_single(number, 56, 10, 1000, 9999, false, result);
			break;
		default:
			cout << "Invalid: -m mode number should be 1 or 2 or 3" << endl;
			return;
			//throw std::exception("Invalid Command - argument");
		}
	}
	catch (const exception& e)
	{
		hasException = true;
		puts(e.what());
	}
}

void Core::generate(int number, int lower, int upper, bool unique, int result[][M]) {
	try
	{
		if (number < 1 || number > 10000) {
			throw exception("-n number should be in [1,10000]");
		}
		if (lower < 20 || upper > 55) {
			throw exception("upper and lower should be in [20, 55]");
		}
		if (lower > upper)
		{
			throw exception("lower can not be bigger than upper");
		}
		init_gen(50000, 0);
		generate_single(number, lower, upper - lower + 1, 0, 9999, unique, result);

	}
	catch (const exception& e)
	{
		hasException = true;
		puts(e.what());
	}
}

bool Core::check(int a[M]) {//check if the sudoku(with 0) is valid
	rep(i, 0, 80) {
		if (a[i] < 0 || a[i] > 9)
			return false;
	}

	bool vis_col[N][N], vis_row[N][N], vis_magic[N][N];
	memset(vis_col, false, sizeof(vis_col));
	memset(vis_magic, false, sizeof(vis_magic));
	memset(vis_row, false, sizeof(vis_row));
	int x, y;
	rep(i, 0, 80) {
		if (a[i] == 0)
			continue;
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

bool Core::solve(int puzzle[M], int solution[M]) {

	if (!check(puzzle))
		return false;
	sol = solve_unique(puzzle);
	if (sol >= 1) {
		memcpy(solution, ans_first, sizeof(ans_first));
		return true;
	}
	return false;
}

bool Core::find(int x, int y, int z) {
	return (!vis_row[x][z] && !vis_col[y][z] && !vis_magic[belonging(x, y)][z]);
}

void Core::init_gen(int val, int type) {
	memset(vis_magic, false, sizeof(vis_magic));
	memset(vis_col, false, sizeof(vis_col));
	memset(vis_row, false, sizeof(vis_row));

	srand((int)time(0));
	int sta = random(9) + 1;
	cnt = 0;
	vis_row[0][sta] = vis_col[0][sta] = vis_magic[belonging(0, 0)][sta] = true;
	aaa[0] = sta + '0';

	/*cnt = 0;
	vis_row[0][1] = vis_col[0][1] = vis_magic[belonging(0, 0)][1] = true;
	aaa[0] = 1 + '0';*/

	//value = 1000000;
	value = val;
	hasAnswer = 0;
	dfs1(1, type);

	//generate(1, 20, 60, true, lll);

	//int ppp[M] = {
	//	0, 0, 0, 0, 0, 5, 9, 0, 9,
	//	3, 0, 5, 0, 0, 9, 0, 0, 6,
	//	7, 8, 0, 0, 2, 0, 0, 0, 0,
	//	1, 0, 0, 4, 0, 7, 6, 0, 0,
	//	4, 5, 0, 0, 0, 1, 0, 0, 7,
	//	8, 0, 0, 0, 0, 3, 0, 0, 0,
	//	0, 0, 1, 0, 7, 0, 5, 0, 4,
	//	0, 6, 4, 0, 0, 2, 8, 7, 3,
	//	5, 7, 8, 6, 3, 4, 9, 1, 2
	//};

	//int kkk[M];
	//bool zzyy = solve(ppp, kkk);
	//cout << "solve: " << zzyy << endl;
	////cout << "@@@@@@@@@@@@@@@@@" << endl;
	//rep(i, 1, 1) {
	//	rep(j, 0, 80) {
	//		//cout << lll[i][j] << " ";
	//		cout << kkk[j] << " ";
	//		if ((j + 1) % 9 == 0)
	//			cout << endl;
	//	}
	//	cout << endl;
	//}
}


void Core::init_sol() {
	while (scanf("%c", &ch) > 0) {
		if (ch < '0' || ch > '9')
			continue;
		x[tot++] = ch - '0';
		if (tot == 81) {
			rep(i, 0, 80)
				if (x[i] > 0)
					modifyElement(i, x[i]);

			dfs2(1, 1);
			tot = 0;
			hasAnswer = 0;//false
			memset(a, 0, sizeof(a));
		}
	}
}


void Core::trans(int a[81]) { //trans thee sudoku of a to the one which the first line is 1..9
	int X[10];
	int n = 9;
	for (int i = 0; i < n; i++)
		X[a[i]] = i + 1;
	for (int i = 0; i < n*n; i++)
		a[i] = X[a[i]];
}
bool Core::isEquivalent(int a[81], int b[81]) { // determine if a is equivalant with b
	int n = 9;
	int c[81], d[81];
	memcpy(c, a, sizeof(c));
	memcpy(d, b, sizeof(d));
	trans(c);
	trans(d);
	for (int i = 0; i < n*n; i++)
		if (c[i] != d[i])
			return false;
	return true;
}

bool Core::deleteElement(int pos, int r) { // add a restrict of pos which cannot be filled with r
	int i;
	if (a[pos][r] == 1)  // 代表之前已经不让填了
		return true;
	a[pos][r] = 1;
	if (++a[pos][0] == 9)  // 代表这个格子没有值可以填了
		return false;
	if (a[pos][0] == 8) {
		for (i = 1; i <= 9; ++i)
			if (a[pos][i] == 0)  // 找到是谁可以填
				break;
		if (!modifyElement(pos, i))
			return false;
	}
	return true;
}
bool Core::modifyElement(int pos, int r) { //change the element pos to r
	int p = pos / 9;  // 行号
	int q = pos % 9;  // 列号
	int h;
	x[pos] = r;
	rep(i, 1, 9)
		a[pos][i] = 1;
	a[pos][0] = 8;  // 代表只有一个元素可以填
	a[pos][r] = 0;  // 那就是r
	rep(j, 0, 8) {  // 增加同行的其它格子的限制
		h = Position(p, j);
		if (h != pos && !deleteElement(h, r))
			return false;
	}
	rep(i, 0, 8) {  // 增加同列的其它格子的限制
		h = Position(i, q);
		if (h != pos && !deleteElement(h, r))
			return false;
	}
	rep(i, 0, 2)  // 增加同九宫格的其它格子的限制
		rep(j, 0, 2) {
		h = (3 * (p / 3) + i) * 9 + (3 * (q / 3) + j);
		if (h != pos && !deleteElement(h, r))
			return false;
	}
	return true;
}
void Core::out_file(int *s) { //print the sudoku to file(sudoku.txt)

	char ans[300];
	int len = 0;
	rep(i, 0, 80) {
		if (s[i] >= 0 && s[i] <= 9)
			s[i] += '0';
		ans[len++] = s[i];
		ans[len++] = (((i + 1) % 9) == 0) ? '\n' : ' ';
		if (debug) {
			printf("%c ", s[i]);
			if ((i + 1) % 9 == 0)
				printf("\n");
		}
	}
	if (debug)
		printf("\n");

	ans[len++] = '\n';
	ans[len] = '\0';
	// ans[len] = '\0';  // fputs(ans, out); // fputs("\n", out);
	fwrite(ans, 1, strlen(ans), out);
	// ans[len] = '\0'; //fprintf(out, "%s\n", ans);
}
void Core::dfs2(int k, int type) { //
	int mx = -1, mxi;
	rep(i, 0, 80) {
		if (a[i][0]<8 && a[i][0]>mx) {
			mx = a[i][0];
			mxi = i;
		}
	}
	if (mx == -1) {
		rep(i, 0, 80) {
			if (x[i] <= 9)
				x[i] += '0';
		}
		if (hasAnswer == 0) {
			rep(i, 0, 80)
				ans_first[i] = x[i] - '0';
		}
		if (type == 1)
			out_file(x);

		hasAnswer++;//hasAnswer = true;
		return;
	}
	memcpy(a_backup[k], a, sizeof(a));
	rep(i, 1, 9) {
		if (a[mxi][i] == 0) {
			if (modifyElement(mxi, i))
				dfs2(k + 1, type);
			memcpy(a, a_backup[k], sizeof(a));
		}
		if (hasAnswer >= 2)
			return;
	}
}
void Core::dfs1(int k, int type) { // generate sudoku with dfs
	if (hasAnswer)
		return;
	int x, y, h;
	x = k / 9;
	y = k % 9;
	h = belonging(x, y);
	if (k > 80) {
		if (type == 1)
			out_file(aaa);
		ans_all_cnt++;

		memcpy(ans_all[ans_all_cnt], aaa, sizeof(aaa));//存储答案

		if (++cnt >= value) {
			hasAnswer = 1;//true
		}
		return;
	}
	rep(i, 1, 9) {
		if (find(x, y, i)) {
			aaa[k] = i + '0';
			vis_row[x][i] = vis_col[y][i] = vis_magic[h][i] = true;
			dfs1(k + 1, type);
			vis_row[x][i] = vis_col[y][i] = vis_magic[h][i] = false;
		}
	}
}

int Core::freedom(int a[M]) { //calcualte the freedom of sudoku
	int res = 0, x, y, h;
	rep(node, 0, 80) {
		if (a[node] != 0)
			continue;
		x = node / 9;
		y = node % 9;
		rep(q, 0, 8)
			if (q != y && a[x * 9 + q] == 0)
				res++;
		rep(p, 0, 8)
			if (p != x && a[p * 9 + y] == 0)
				res++;
		rep(i, 0, 2)  // 增加同九宫格的其它格子的限制
			rep(j, 0, 2) {
			h = (3 * (x / 3) + i) * 9 + (3 * (y / 3) + j);
			if (h != node && a[h] == 0)
				res++;
		}
	}
	return res;
}

double Core::getRandData(int min, int max) { // get a random double in [min, max]
											 //srand((int)time(0));
	double m1 = (double)(rand() % 101) / 101;                        // 计算 0，1之间的随机小数,得到的值域近似为(0,1)
	min++;                                                                             //将 区间变为(min+1,max),
	double m2 = (double)((rand() % (max - min + 1)) + min);    //计算 min+1,max 之间的随机整数，得到的值域为[min+1,max]
	m2 = m2 - 1;                                                                        //令值域为[min,max-1]
	return m1 + m2;                                                                //返回值域为(min,max),为所求随机浮点数
}

void Core::dfs3(int k, int tot) { // tranfer a complete sudoku to the one with 0
	if (k > 80)
		return;
	double t = getRandData(0, 1);
	if ((tot == num_0 || t >= p_exist) && (80 - k + 1 >= num_0 - tot + 1))
	{
		game[k] = ans_all[id][k];
		dfs3(k + 1, tot);
	}
	else {
		//square[belonging(k / 9, k % 9)]++;
		dfs3(k + 1, tot + 1);
	}
}

int Core::work3(int num_0_t, int id_t, double p_t) { //modify a complete sidoku with num_0 zeros, p is zero/81
													 //freopen("Ans.txt", "w", stdout);
	memset(isEmpty, true, sizeof(isEmpty));
	id = id_t;
	p_exist = p_t;
	num_0 = num_0_t;
	//while (true) {
	memset(game, 0, sizeof(game));
	//memset(square, 0, sizeof(square));
	dfs3(0, 0);
	//if (find()) {
	rep(i, 0, 80) {
		if (game[i]) {
			game[i] -= '0';
			isEmpty[i] = false;
		}
		if (debug)
			cout << game[i] << " ";
		//cout << (ans_all[id][i] - '0') << " ";
		if (((i + 1) % 9) == 0 && debug)
			cout << endl;
	}

	int fre = freedom(game);
	if (debug)
		cout << "自由度： " << fre << endl;
	//cout << "-----------" << endl;
	//cout << "___________" << endl;
	return fre;
}