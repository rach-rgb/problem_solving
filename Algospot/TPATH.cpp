#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<pair<int, pair<int, int>>> edges;
vector<int> par;
vector<int> h;

void input() {
	cin >> N >> M;

	// allocation
	par.clear(); par.resize(N);
	h.clear(); h.resize(N);
	edges.clear(); edges.resize(M);

	for (int i = 0; i < M; i++) {
		cin >> edges[i].second.first >> edges[i].second.second;
		cin >> edges[i].first;
	}

	sort(edges.begin(), edges.end());
}

int get_par(int x) {
	if (par[x] == x) { return x; }
	else {
		par[x] = get_par(par[x]);
		return par[x];
	}
}

void merge(int x, int y) {
	int px = get_par(x);
	int py = get_par(y);

	if (h[px] < h[py]) {
		par[px] = py;
	}
	else {
		par[py] = px;
		if (h[px] == h[py]) { h[px]++; }
	}
}

void initialize() {
	for (int i = 0; i < par.size(); i++) { par[i] = i; }
	for (int i = 0; i < h.size(); i++) { h[i] = 0; }
}

int solve() {
	int result = 987654321;

	for (int low = 0; low < edges.size(); low++) {
		if ((low > 0) && (edges[low].first == edges[low - 1].first)) {
			continue;
		}

		initialize();
		for (int i = low; i < edges.size(); i++) {
			int x = edges[i].second.first;
			int y = edges[i].second.second;
			int weight = edges[i].first;

			// early terminate
			if (weight - edges[low].first >= result) { break; }

			if (get_par(x) != get_par(y)) {
				merge(get_par(x), get_par(y));

				// check whether (s, t) is connected
				if (get_par(0) == get_par(N-1)) {
					int diff = weight - edges[low].first;

					result = (result < diff) ? result : diff;
					break;
				}
			}
		}
	}
	
	return result;
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
