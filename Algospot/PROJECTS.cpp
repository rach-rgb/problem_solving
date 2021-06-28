#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INF 987654321

int N, M;
vector<vector<int>> c;
vector<vector<int>> f;

int V, source, sink;

int business(int x) {
	return 1 + x;
}

int resource(int x) {
	return 1 + N + x;
}

// construct graph
void input()
{
	cin >> N >> M;

	V = N + M + 2;
	source = 0; sink = V - 1;
	for (int i = 0; i < c.size(); i++) { c[i].clear(); } c.clear();
	c.resize(V); for (int i = 0; i < c.size(); i++) { c[i].resize(V, 0); }
	for (int i = 0; i < f.size(); i++) { f[i].clear(); } f.clear();
	f.resize(V); for (int i = 0; i < f.size(); i++) { f[i].resize(V, 0); }

	for (int i = 0; i < N; i++) { cin >> c[source][business(i)]; }
	for (int i = 0; i < M; i++) { cin >> c[resource(i)][sink]; }

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int need;
			cin >> need;
			if (need == 1) {
				c[business(i)][resource(j)] = INF;
			}
		}
	}
}

vector<int> BFS(int s, int t) {
	vector<int> par(V, -1);
	vector<bool> visited(V, false);

	queue<int> q;
	q.push(s); visited[s] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next = 0; next < V; next++) {
			if (!visited[next] && (c[cur][next] - f[cur][next] > 0)) {
				par[next] = cur;
				q.push(next);
				visited[next] = true;
				if (next == t) {
					return par;
				}
			}
		}
	}

	return par;
}

int solve() {

	// get min cut
	while (1) {
		vector<int> par = BFS(source, sink);

		if (par[sink] == -1) { // no path
			break;
		}

		// else
		int cur = sink;
		int min = INF;
		while (par[cur] != -1) {
			int cap = c[par[cur]][cur] - f[par[cur]][cur];
			min = (min < cap) ? min : cap;
			cur = par[cur];
		}

		cur = sink;
		while (par[cur] != -1) {
			f[par[cur]][cur] += min;
			f[cur][par[cur]] -= min;
			cur = par[cur];
		}
	}

	int mflow = 0, total = 0;
	for (int i = 0; i < N; i++) {
		mflow += f[source][business(i)];
		total += c[source][business(i)];
	}

	return total - mflow;
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
2
2 2
10 10
5 10
1 0
1 1
5 5
260 60 140 350 500
250 100 150 300 100
1 0 0 0 0
1 1 1 0 0
0 0 1 1 0
0 0 0 1 0
0 0 0 1 1

Answ:
5
460
*/
