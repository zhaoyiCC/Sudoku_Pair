#include "Core.h"
#include "Exception.h"
#include "stdafx.h"
#include "iostream"
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
int a[10][81] = { 0 };
int main() {
	//srand((int)time(0));
	Core c;
	/*int ppp[M] = {
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
	int a[81];
	{
		rep(j, 0, 80) {
		cout << a[j] << " ";
		if ((j + 1) % 9 == 0)
			puts("");
	}
	}
	c.solve(ppp, a);*/

	try {
		c.generate(1, 20, 5000, false, a);
	}
	catch (NumberOutOfBoundException& e){
		cout << e.m_msg << endl;
	}

	int ppp[81] = {
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
	int a[81];
	bool zy=c.solve(ppp, a);
	{
	rep(j, 0, 80) {
	cout << a[j] << " ";
	if ((j + 1) % 9 == 0)
	puts("");
	}
	}
	cout << zy << endl;


	return 0;

	/*for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 81; ++j) {
			cout << a[i][j] << " ";
			if ((j + 1) % 9 == 0)
							cout << endl;
		}
		cout << endl;
	}*/
	//int hhh = c.find(1, 1, 1);
	//int a[11][M];
	//c.generate(1, 25, 25, true, a);
	//printf("%d\n", c.debug);
	////c.init_gen(1, 0);
	//rep(i, 0, 0) {
	//	cout << "-----------------------" << endl;
	//	rep(j, 0, 80) {
	//		cout << a[i][j] << " ";
	//		if ((j + 1) % 9 == 0)
	//			cout << endl;
	//	}
	//	//cout << "-----------------------" << endl;
	//}
	///*find(int x, int y, int z) {
	//	return (!vis_row[x][z] && !vis_col[y][z] && !vis_magic[belonging(x, y)][z]);
	//}*/
	//printf("%d\n", c.vis_row[1][1]);
	//printf("%d\n", c.vis_col[1][1]);
	//printf("%d\n", belonging(1,1));
	//printf("%d\n", c.vis_magic[1][1]);
	//printf("%d\n", h);
	return 0;
}