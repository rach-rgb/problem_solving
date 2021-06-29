/* 알고리즘 문제 해결 전략 1022p */
#include <iostream>
#include <vector>
using namespace std;

int N, M, K;

vector<vector<bool>> c;
vector<int> match;
vector<bool> visited;
int V, source, sink;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0 ,-1 };

bool inRange(int x, int y) {
	if ((x < 0) || (x >= N)) { return false; }
	else if ((y < 0) || (y >= M)) { return false; }
	else { return true; }
}

int node(int x, int y) {
	return 1 + M * x + y;
}

bool odd(int x, int y) {
	if (x % 2 == 0) { return (y % 2 == 0); }
	else { return (y % 2 == 1); }
}

void input()
{
	cin >> N >> M;
	V = N * M + 2;
	source = 0, sink = V - 1;
	c = vector<vector<bool>>(V, vector<bool>(V, false));
	match = vector<int>(V, -1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int n = node(i, j);
			if (odd(i, j)) { // source to odd
				c[source][n] = true;
			}
			else { // even to sink
				c[n][sink] = true;
			}
		}
	}

	cin >> K;
	for (int i = 0; i < K; i++) {
		int x, y;
		cin >> x >> y;
		int n = node(x, y);
		if (odd(x, y)) { // source to odd
			c[source][n] = false;
		}
		else { // even to sink
			c[n][sink] = false;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int n = node(i, j);
			if (odd(i, j)) { // odd to even
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (inRange(nx, ny)) {
						int nn = node(nx, ny);
						c[n][nn] = true;
					}
				}
			}
		}
	}
}

bool DFS(int a) {
	if (visited[a]) { return false; }

	visited[a] = true;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (!odd(x, y))
			{
				int n = node(x, y);
				if (c[a][n] && c[n][sink]) {
					if ((match[n] == -1) || (DFS(match[n]))) {
						match[n] = a;
						match[a] = n;
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool solve() {
	int size = 0;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < M; y++) {
			if (odd(x, y))
			{
				int n = node(x, y);
				if(c[source][n]) {
					visited = vector<bool>(V, false);
					if (DFS(n)) {
						size++;
					}
				}
			}
		}
	}

	if (size * 2 == N * M - K) { return true; }
	else { return false; }
}

int main() {
	int T; cin >> T;
	while (T--) {
		input();
		if (solve()) {
			cout << "True" << endl;
		}
		else { cout << "False" << endl; }
	}

	return 0;
}

/*
2
4 6
4
0 0
0 5
2 2
3 0
4 6
8
0 0
0 2
0 3
0 5
2 2
3 0
3 1
3 2

// T F
*/
