#include <iostream>
#include <vector>
using namespace std;

struct RPQ {
	int n;
	int INF = 30000, NINF = -1;
	vector<pair<int, int>> rangePair;

	RPQ(const vector<int>& array) {
		n = array.size();
		rangePair.resize(4 * n);
		init(array, 0, n - 1, 1);
	}

	pair<int, int> merge(const pair<int, int>& a, const pair<int, int>& b) {
		pair<int, int> result;

		if (a.first <= b.first) { result.first = a.first; }
		else { result.first = b.first; }
		if (a.second >= b.second) { result.second = a.second; }
		else { result.second = b.second; }

		return result;
	}

	pair<int, int> init(const vector<int>& array, int left, int right, int node) {
		if (left == right) {
			rangePair[node].first = array[left];
			rangePair[node].second = array[left];
			return pair<int, int>(array[left], array[right]);
		}

		int mid = (left + right) / 2;
		pair<int, int> p1 = init(array, left, mid, node * 2);
		pair<int, int> p2 = init(array, mid + 1, right, node * 2 + 1);

		rangePair[node] = merge(p1, p2);

		return rangePair[node];
	}

	pair<int, int> query(int left, int right, int node, int nleft, int nright) {
		// cout << left << " " << right << " " << node << " " << nleft << " " << nright << endl;

		if ((right < nleft) || (nright < left)) {
			return pair<int, int>(INF, NINF);
		}
		else if ((left <= nleft) && (nright <= right)) {
			return rangePair[node];
		}

		int mid = (nleft + nright) / 2;
		pair<int, int> p1 = query(left, right, node * 2, nleft, mid);
		pair<int, int> p2 = query(left, right, node * 2 + 1, mid + 1, nright);

		return merge(p1, p2);
	}

	pair<int, int> query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};

int N, Q;
vector<int> h;
vector<pair<int, int>> q;


vector<int> solve() {
	vector<int> result(Q);

	struct RPQ tree(h);

	/* for (int i = 0; i < 4 * N; i++) {
		cout << tree.rangePair[i].first << " " << tree.rangePair[i].second << endl;
	} */

	for (int i = 0; i < Q; i++) {
		pair<int, int> p = tree.query(q[i].first, q[i].second);
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
