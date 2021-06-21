#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 987654321

int V, E;
vector<vector<int>> adj;
vector<vector<int>> DP;
vector<pair<int, int>> ins;

void input() {
	cin >> V >> E;

	// initialize
	adj.resize(V);
	for (int i = 0; i < adj.size(); i++) { adj[i].resize(V, INF); }
	DP.resize(V);
	for (int i = 0; i < DP.size(); i++) { DP[i].resize(V, INF); }
	ins.resize(V);

	for (int i = 0; i < V; i++) {
		cin >> ins[i].first;
		ins[i].second = i;
	}
	sort(ins.begin(), ins.end());

	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;

		adj[a][b] = c;
		adj[b][a] = c;
		DP[a][b] = c;
		DP[b][a] = c;
	}

	for (int i = 0; i < V; i++) {
		adj[i][i] = 0;
		DP[i][i] = 0;
	}
}

int minv(int x, int y) {
	if (x < y) { return x; }
	else { return y; }
}

void solve() {
	for (int i = 0; i < V; i++) {
		int k = ins[i].second;

		for (int s = 0; s < V; s++) {
			for (int t = 0; t < V; t++) {
				adj[s][t] = minv(adj[s][t], adj[s][k] + adj[k][t]);
				DP[s][t] = minv(DP[s][t], adj[s][k] + adj[k][t] + ins[i].first);
			}
		}
	}
}

int main() {
	input();
	solve();

	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		cout << DP[a][b] << endl;
	}

	return 0;
}
