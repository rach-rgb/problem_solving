/* 알고리즘 문제 해결 전략 1003p */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 987654321

int N, M;
int V;
vector<vector<int>> c; // capacity
vector<vector<int>> f; // flow

int source(int x) {
	return 2 * x;
}

int sink(int x) {
	return 2 * x + 1;
}

void input() {
	cin >> N >> M;

	V = 2 * N;
	c.clear(); c.resize(V);
	for (int i = 0; i < c.size(); i++) { c[i].resize(V, 0); }
	f.clear(); f.resize(V);
	for (int i = 0; i < f.size(); i++) { f[i].resize(V, 0); }

	for (int i = 1; i <= N - 2; i++) {
		cin >> c[source(i)][sink(i)];
	}

	c[source(0)][sink(0)] = INF;
	c[source(N - 1)][sink(N - 1)] = INF;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		c[sink(a)][source(b)] = INF;
		c[sink(b)][source(a)] = INF;
	}
}

vector<int> BFS(int s, int t) {
	vector<int> par(V, -1);
	vector<bool> visited(V, false);

	queue<int> q;
	q.push(s); par[s] = s;
	visited[s] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next = 0; next < V; next++) {
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
	ff(source(0), sink(N-1));

	int total = 0;
	for (int i = 0; i < V; i++) {
		total += f[0][i];
	}

	return total;
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
8 12
3 4 9 9 7 3
0 1
1 4
4 7
1 2
2 4
4 5
6 7
0 2
2 5
5 6
0 3
3 6
7 8
5 9 2 3 4
0 1
1 3
0 2
2 3
3 6
0 4
4 5
5 6

Answer:
10
5
*/
