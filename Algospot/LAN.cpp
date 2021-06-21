#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

#define MAXN (500)
#define INF (87654321)

int N, M;
vector<vector<double>> edges;
vector<int> xcoords;
vector<int> ycoords;
priority_queue<pair<double, pair<int, int>>> pq;
vector<int> par;
vector<int> h;
int add;

double dist(int a, int b) {
	double ret = 0;
	ret = pow(xcoords[a] - xcoords[b], 2) + pow(ycoords[a] - ycoords[b], 2);
	ret = sqrt(ret);

	return ret;
}

void input() {
	cin >> N >> M;

	// initialize
	par.resize(N, -1);
	for (int i = 0; i < par.size(); i++) { par[i] = i; }
	h.resize(N, 0);
	while (!pq.empty()) { pq.pop(); }
	edges.resize(N);
	for (int i = 0; i < edges.size(); i++) { edges[i].clear(); edges[i].resize(N, INF); }
	xcoords.resize(N);
	ycoords.resize(N);

	for (int i = 0; i < N; i++) {
		cin >> xcoords[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> ycoords[i];
	}

	add = 0;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		
		if (a > b) { int tmp = b; b = a; a = tmp; }
		if (edges[a][b] == 0) { continue; }
		edges[a][b] = 0;
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (edges[i][j] != 0) { edges[i][j] = dist(i, j); }
			pair<double, pair<int, int>> p;
			p.first = -edges[i][j];
			p.second.first = i;
			p.second.second = j;
			pq.push(p);

		}
	}
}

int get_par(int x) {
	if (par[x] == x) { return x; }
	else {
		par[x] = get_par(par[x]);
		return par[x];
	}
}

void merge(int x, int y) {
	if (h[x] < h[y]) {
		par[x] = y;
	}
	else {
		par[y] = x;
		if (h[x] == h[y]) {
			h[x]++;
		}
	}
}

double solve() {
	double ret = 0;

	while (add < N - 1) {
		pair<double, pair<int, int>> p = pq.top();
		pq.pop();
		double w = -p.first;
		int a = p.second.first, b = p.second.second;

		// cout << p.first << " " << p.second.first << " " << p.second.second << endl;

		if (get_par(a) != get_par(b)) {
			merge(get_par(a), get_par(b));
			ret += w;
			add++;
		}
	}

	return ret;
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		input();
		cout.fixed;
		cout.precision(11);
		cout << solve() << endl;
	}

	return 0;
}
