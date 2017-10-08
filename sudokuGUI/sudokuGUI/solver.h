#pragma once
#include<algorithm>
#include<ctime>
using namespace std;
#define matrixLen 9
typedef pair<int, int> node;
class Solver {
public:
	Solver() {}
	const int seed[matrixLen][matrixLen] = {
		{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
		{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
		{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
		{ 2, 1, 4, 3, 6, 5, 8, 9, 7 },
		{ 3, 6, 5, 8, 9, 7, 2, 1, 4 },
		{ 8, 9, 7, 2, 1, 4, 3, 6, 5 },
		{ 5, 3, 1, 6, 4, 2, 9, 7, 8 },
		{ 6, 4, 2, 9, 7, 8, 5, 3, 1 },
		{ 9, 7, 8, 5, 3, 1, 6, 4, 2 }
	};
	int matrix[matrixLen][matrixLen];
	void LittleMatrixDig(int x, int y) {
		//ÍÚ2¸ö
		node a[100];
		int len = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				a[len++] = make_pair(x + i, y + j);
		random_shuffle(a, a + len);
		matrix[a[0].first][a[0].second] = 0;
		matrix[a[1].first][a[1].second] = 0;
	}
	int random(int o) {
		return rand() % o;
	}
	void buildMatrix(int res[matrixLen][matrixLen]) {
		srand(time(0));
		int digNum = random(31) + 30;
		int per[matrixLen + 1];
		for (int i = 1; i <= matrixLen; i++)
			per[i] = i;
		random_shuffle(per + 1, per + matrixLen + 1);
		for (int i = 0; i < matrixLen; i++)
			for (int j = 0; j < matrixLen; j++)
				matrix[i][j] = per[seed[i][j]];
		for (int i = 0; i < matrixLen; i += 3)
			for (int j = 0; j < matrixLen; j += 3)
				LittleMatrixDig(i, j);
		//2*9=18¸ö
		digNum -= 18;
		node nodes[100];
		int len = 0;
		for (int i = 0; i < matrixLen; i++)
			for (int j = 0; j < matrixLen; j++)
				if (matrix[i][j] != 0)
					nodes[len++] = make_pair(i, j);
		random_shuffle(nodes, nodes + len);
		for (int i = 0; i < digNum; i++)
			matrix[nodes[i].first][nodes[i].second] = 0;
		memcpy(res, matrix, sizeof(matrix));
	}
	void initVis(int vis[10]) {
		for (int i = 0; i < 10; i++)
			vis[i] = 0;
	}
	bool updateVis(int x, int y, int vis[10], int matrix[matrixLen][matrixLen]) {
		if (matrix[x][y] < 1 || matrix[x][y]>9 || vis[matrix[x][y]])
			return false;
		vis[matrix[x][y]] = 1;
		return true;
	}
	bool checkLittleMatrix(int x, int y, int vis[10], int matrix[matrixLen][matrixLen]) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				if (!updateVis(x + i, y + j, vis, matrix))
					return false;
			}
		return true;
	}
	bool checkMatrix(int matrix[matrixLen][matrixLen]) {
		int vis[10] = { 0 };
		for (int i = 0; i < matrixLen; i++) {
			initVis(vis);
			for (int j = 0; j < matrixLen; j++) {
				if (!updateVis(i, j, vis, matrix))
					return false;
			}
		}
		for (int i = 0; i < matrixLen; i++) {
			initVis(vis);
			for (int j = 0; j < matrixLen; j++) {
				if (!updateVis(i, j, vis, matrix))
					return false;
			}
		}
		for (int i = 0; i < matrixLen; i += 3)
			for (int j = 0; j < matrixLen; j += 3) {
				initVis(vis);
				if (!checkLittleMatrix(i, j, vis, matrix)) {
					return false;
				}
			}
		return true;
	}
};