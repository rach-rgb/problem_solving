#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXH = 20;
const int MAXW = 20;
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

int H, W;
char board[MAXH][MAXW];
int id[MAXH][MAXW];
int asize, bsize;
vector<vector<bool>> graph;
vector<int> amatch;
vector<int> bmatch;
vector<bool> visited;
vector<bool> aselect;
vector<bool> bselect;

bool inRange(int x, int y) {
	return ((x >= 0) && (x < H) && (y >= 0) && (y < W));
}

void buildGraph() {
	asize = 0, bsize = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == '.') {
				if ((i + j) % 2 == 0) {
					id[i][j] = asize++;
				}
				else {
					id[i][j] = bsize++;
				}
			}
		}
	}

	graph = vector<vector<bool>>(asize, vector<bool>(bsize, false));

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((board[i][j] == '.') && ((i + j) % 2 == 0)) {
				for (int d = 0; d < 4; d++) {
					int ni = i + dx[d], nj = j + dy[d];
					if ((inRange(ni, nj) && (board[ni][nj] == '.'))) {
						graph[id[i][j]][id[ni][nj]] = true;
					}
				}
			}
		}
	}
}

bool match(int a) {
	if (visited[a]) { return false; }

	visited[a] = true;
	for (int b = 0; b < bsize; b++) {
		if (graph[a][b]) {
			if ((bmatch[b] == -1) || (match(bmatch[b]))) {
				amatch[a] = b;
				bmatch[b] = a;
				return true;
			}
		}
	}
	return false;
}

int bipartiteMatch() {
	int ret = 0;

	amatch = vector<int>(asize, -1);
	bmatch = vector<int>(bsize, -1);

	for (int i = 0; i < asize; i++) {
		visited = vector<bool>(asize, false);
		if (match(i)) { ret++; }
	}

	return ret;
}

void maxIndependentSet(int msize) {
	// select A&M and B-M
	aselect = vector<bool>(asize, true);
	bselect = vector<bool>(bsize, false);

	for (int j = 0; j < bsize; j++) {
		if (bmatch[j] == -1) { bselect[j] = true; }
	}

	// check all pairs
	while (1) {
		bool changed = false;

		for (int i = 0; i < asize; i++) {
			for (int j = 0; j < bsize; j++) {
				if (aselect[i] && bselect[j] && graph[i][j]) {
					aselect[i] = false;
					bselect[aselect[i]] = true;
					changed = true;
				}
			}
		}

		if (!changed) { break; }
	}
}

int main() {
	int T; cin >> T;
	while (T--) {
		cin >> H >> W;
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				cin >> board[i][j];
			}
		}

		buildGraph();
		int msize = bipartiteMatch();
		
		maxIndependentSet(msize);
		
		cout << asize + bsize - msize << endl;

		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				if (board[i][j] == '.') {
					if ((i + j) % 2 == 0) {
						if (aselect[id[i][j]]) { cout << '^'; }
						else { cout << '.'; }
					}
					else {
						if (bselect[id[i][j]]) { cout << '^'; }
						else { cout << '.'; }
					}
				}
				else { cout << board[i][j]; }
			}
			cout << endl;
		}
	}
}
