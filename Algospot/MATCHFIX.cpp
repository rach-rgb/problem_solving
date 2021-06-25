#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define INF 987654321

int N, M;
int V;
int source = 0, sink;
int opps;
vector<vector<int>> c;
vector<vector<int>> f;
vector<int> scores;

int result;

int player(int x) {
	return 1 + M + x;
}

int match(int x) {
	return 1 + x;
}

void input() {
	cin >> N >> M;

	// initialize
	V = N + M + 2;
	sink = V - 1;
	for (int i = 0; i < c.size(); i++) { c[i].clear(); } c.clear();
	c.resize(V); for (int i = 0; i < c.size(); i++) { c[i].resize(V, 0); }
	for (int i = 0; i < f.size(); i++) { f[i].clear(); } f.clear();
	f.resize(V); for (int i = 0; i < f.size(); i++) { f[i].resize(V, 0); }

	scores.clear(); scores.resize(N);
	for (int i = 0; i < N; i++) { cin >> scores[i]; }

	// source to match
	for (int i = 0; i < M; i++) {
		c[source][match(i)] = 1;
	}

	opps = 0;
	// match to player
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;

		c[match(i)][player(a)] = 1;
		c[match(i)][player(b)] = 1;

		if ((a == 0) || (b == 0)) { opps++; }
	}

	// player to sink
	int high = -1, cnt = 0;
	for (int i = 0; i < scores.size(); i++) {
		if (high < scores[i]) {
			high = scores[i];
			cnt = 1;
		}
		else if (high == scores[i]) { cnt++; }
	}

	// case 1 : player 0 solo win
	if ((high==scores[0])&&(cnt==1)) {
		result = high;

		for (int i = 1; i < N; i++) {
			c[player(i)][sink] = result - 1 - scores[i];
		}
	}
	// case 2 : player 0 not win / joint win
	else {
		result = high + 1;
		if (scores[0] + opps < result) { result = -1; }
		else {
			c[player(0)][sink] = result - scores[0];
			for (int i = 1; i < N; i++) {
				c[player(i)][sink] = result - 1 - scores[i];
			}
		}
	}
}

vector<int> BFS(int s, int t) {
	vector<int> par(V, -1);
	vector<bool> visited(V, false);

	queue<int> q;
	q.push(s); visited[s] = true; par[s] = -1;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next = 0; next < V; next++) {
			int left = c[cur][next] - f[cur][next];
			if ((!visited[next]) && (left > 0)) {
				visited[next] = true;
				par[next] = cur;

				if (next == t) { return par; } // early terminate
				q.push(next);
			}
		}
	}

	return par;
}

void solve() {
	if (result == -1) { return;	}

	int total = 0;
	while (true) {
		vector<int> par = BFS(source, sink);

		if (par[sink] == -1) { // no path
			if (total == M) { break; }

			// increase player - sink capacity
			result++;
			if (scores[0] + opps < result) {
				result = -1;
				return;
			}
			else {
				for (int i = 0; i < N; i++) {
					c[player(i)][sink]++;
				}
			}
		}
		else {

			int cur = sink;
			int min = INF;
			while (par[cur] != -1) {
				int left = c[par[cur]][cur] - f[par[cur]][cur];
				min = (min < left) ? min : left;
				cur = par[cur];
			}

			cur = sink;
			total += min;
			while (par[cur] != -1) {
				f[par[cur]][cur] += min;
				f[cur][par[cur]] -= min;
				
				cur = par[cur];
			}

		}
	}

	return;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		input();
		solve();
		cout << result << endl;
	}

	return 0;
}
