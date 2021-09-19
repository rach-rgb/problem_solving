#include <iostream>
#include <vector>
using namespace std;

const int INF(987654321);

int N, M;
vector<pair<int, int>> store;
vector<pair<int, int>> home;

int distance(int s, int h) {
	int dx = store[s].first - home[h].first;
	int dy = store[s].second - home[h].second;

	dx = (dx > 0) ? dx : -dx;
	dy = (dy > 0) ? dy : -dy;

	return dx + dy;
}

// return minimum sum of distances
int solve(vector<int> dist, int idx, int count) {
	// edge case
	if (count == M)
	{
		int ret = 0;
		for (int i = 0; i < dist.size(); i++) { ret += dist[i]; }
		return ret;
	}
	if (idx == store.size())
	{
		return INF;
	}

	vector<int> ndist = dist;

	// exclude store[idx]
	int res1 = solve(ndist, idx + 1, count);

	// include store[idx]
	ndist = dist;
	for (int i = 0; i < dist.size(); i++) {
		int val = distance(idx, i);
		ndist[i] = (ndist[i] < val) ? ndist[i] : val;
	}

	int res2 = solve(ndist, idx + 1, count + 1);

	return (res1 < res2) ? res1 : res2;
}

int main() {
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int x;
			cin >> x;

			if (x == 1) {
				home.push_back(pair<int, int>(i, j));
			}
			else if (x == 2) {
				store.push_back(pair<int, int>(i, j));
			}
		}
	}

	vector<int> distance(home.size(), INF);
	cout << solve(distance, 0, 0) << endl;

	return 0;
}
