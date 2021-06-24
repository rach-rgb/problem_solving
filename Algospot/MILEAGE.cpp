/* 알고리즘 문제 해결 전략 1002p */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 987654321

int N, M;
int need = 0;
vector<vector<int>> c; // capacity
vector<vector<int>> f; // flow

int source(int x) {
	return x + 1;
}

int sink(int x) {
	return 1 + N + x;
}

void input() {
	cin >> N >> M;

	c.clear(); c.resize(N + M + 2);
	for (int i = 0; i < c.size(); i++) { c[i].resize(N + M + 2, 0); }
	f.clear(); f.resize(N + M + 2);
	for (int i = 0; i < f.size(); i++) { f[i].resize(N + M + 2, 0); }

	int rsource = 0, rsink = N + M + 1;

	for (int i = 0; i < N; i++) {
		cin >> c[rsource][source(i)];
	}

	need = 0;
	for (int i = 0; i < M; i++) {
		cin >> c[sink(i)][rsink];
		need += c[sink(i)][rsink];
	}

	for (int i = 0; i < N; i++) {
		int s;
		cin >> s;
		while (s--) {
			int t;
			cin >> t;
			c[source(i)][sink(t)] = INF;
		}
	}
}

vector<int> BFS(int s, int t) {
	vector<int> par(N + M + 2, -1);
	vector<bool> visited(N + M + 2, false);

	queue<int> q;
	q.push(s); par[s] = s;
	visited[s] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next = 0; next < N + M + 2; next++) {
			if ((!visited[next]) && c[cur][next] - f[cur][next] > 0) {
				par[next] = cur;
				visited[next] = true;

				if (next == t) { return par; }
				q.push(next);
			}
		}
	}

	return par;
}

void ff(int s, int t) {
	while (true) {
		vector<int> par = BFS(s, t);

		if (par[t] == -1) { break; } // no path

		int min = INF;
		int cur = t;
		while (cur != s) {
			int width = c[par[cur]][cur] - f[par[cur]][cur];

			min = (min < width) ? min : width;

			cur = par[cur];
		}

		cur = t;
		while (cur != s) {
			f[par[cur]][cur] += min;
			f[cur][par[cur]] -= min;

			cur = par[cur];
		}

	}
}

int solve() {
	ff(0, N + M + 1);

	int total = 0;
	for (int i = 0; i < N + M + 2; i++) {
		if (f[0][i] > 0) {
			total += f[0][i];
		}
	}

	return need - total;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		input();
		cout << solve() << endl;
	}

	return 0;
}

/*
ex)
2
2 2
10 5
9 7
2 0 1
1 1
3 3
10 5 6
10 10 4
3 0 1 2
1 0
2 1 2

Answer:
1
3
*/
