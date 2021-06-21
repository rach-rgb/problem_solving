#include <iostream>
#include <vector>
using namespace std;

#define INF (987654321)

int V, M, N;
vector<vector<int>> graph;

void input() {
	cin >> V >> M >> N;

	graph.clear(); graph.resize(V+N);
	for (int i = 0; i < V + N; i++) {
		graph[i].resize(V + N, INF);
	}

	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		if (graph[a][b] > c) {
			graph[a][b] = c;
			graph[b][a] = c;
		}
	}

	for (int i = 0; i < V; i++) {
		graph[i][i] = 0;
	}
}

int minv(int x, int y) {
	if (x <= y) { return x; }
	else { return y; }
}

void precalc() {
	for (int k = 0; k < V; k++) {
		for (int s = 0; s < V; s++) {
			for (int t = 0; t < V; t++) {
				graph[s][t] = minv(graph[s][t], graph[s][k] + graph[k][t]);
			}
		}
	}
}

bool add_edge(int a, int b, int c) {
	bool useful = false;

	for (int s = 0; s < V; s++) {
		for (int t = 0; t < V; t++) {
			int prev = graph[s][t];

			graph[s][t] = minv(prev, minv(graph[s][a] + graph[b][t] + c, graph[s][b] + graph[a][t] + c));
			if (prev != graph[s][t]) { useful = true; }
		}
	}

	return useful;
}

int solve() {
	int result = 0;

	precalc();

	for (int i = 0; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		// check useful
		if (!add_edge(a, b, c)) { result++; }
	}

	return result;
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		input();
		cout << solve() << endl;
	}

	return 0;
}