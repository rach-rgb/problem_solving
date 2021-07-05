#include <iostream>
#include <vector>
using namespace std;

typedef struct _RN {
	int mn;
	int mx;
} RN;

int N, Q;
vector<int> h;
vector<pair<int, int>> q;
vector<RN> rangeTree; // range tree
#define INF (987654321)

int min(int x, int y) {
	if (x == INF) { return y; }
	if (y == INF) { return x; }
	return (x < y) ? x : y;
}

int max(int x, int y) {
	if (x == INF) { return y; }
	if (y == INF) { return x; }
	return (x > y) ? x : y;
}

void construct(int root, int left, int right) {
	if (left + 1 == right) {
		rangeTree[root].mn = h[left];
		rangeTree[root].mx = h[left];
		return;
	}

	// else
	int mid = (left + right) / 2;
	int lc = root * 2 + 1, rc = root * 2 + 2;
	construct(lc, left, mid);
	construct(rc, mid, right);

	rangeTree[root].mn = min(rangeTree[lc].mn, rangeTree[rc].mn);
	rangeTree[root].mx = max(rangeTree[lc].mx, rangeTree[rc].mx);
}

pair<int, int> search(int root, int left, int right, int lrange, int rrange) {
	// cout << root << " " << left << " " << right << " " << lrange << " " << rrange << endl;
	if ((right <= lrange) || (rrange <= left)) 
	{
		return pair<int, int>(INF, INF);
	}
	else if ((left <= lrange) && (rrange <= right)) 
	{
		return pair<int, int>(rangeTree[root].mn, rangeTree[root].mx);
	}
	else {
		int mrange = (lrange + rrange) / 2;
		pair<int, int> lp = search(root * 2 + 1, left, right, lrange, mrange);
		pair<int, int> rp = search(root * 2 + 2, left, right, mrange, rrange);

		int minh = min(lp.first, rp.first);
		int maxh = max(lp.second, rp.second);

		return pair<int, int>(minh, maxh);
	}
}

vector<int> solve() {
	vector<int> result(Q);

	rangeTree.clear(); rangeTree.resize(4 * N);
	construct(0, 0, N);

	/* for (int i = 0; i < 4 * N; i++) {
		cout << rangeTree[i].mn << " " << rangeTree[i].mx << endl;
	} */

	for (int i = 0; i < Q; i++) {
		pair<int, int> p = search(0, q[i].first, q[i].second + 1, 0, N);
		result[i] = p.second - p.first;
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		cin >> N >> Q;
		h.clear(); h.resize(N);
		for (int i = 0; i < N; i++) { cin >> h[i]; }
		q.clear(); q.resize(Q);
		for (int i = 0; i < Q; i++) { cin >> q[i].first >> q[i].second; }

		vector<int> result = solve();
		for (int i = 0; i < Q; i++) { cout << result[i] << endl; }
	}

	return 0;
}
