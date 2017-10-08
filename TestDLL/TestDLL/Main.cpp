#include <stdio.h>
#include "sudoku.h"
int main() {
	Core c;
	int a[11][M];
	c.generate(10, 55, 55, true, a);
	printf("%d\n", c.debug);
	//c.init_gen(1, 0);
	rep(i, 1, 10) {
		cout << "-----------------------" << endl;
		rep(j, 0, 80) {
			cout << a[i][j] << " ";
			if ((j + 1) % 9 == 0)
				cout << endl;
		}
		//cout << "-----------------------" << endl;
	}
	printf("%d\n",c.find(1, 1, 1));
}