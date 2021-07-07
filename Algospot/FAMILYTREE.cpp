#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, Q;
vector<vector<int>> tree;
vector<pair<int, int>> q;
vector<int> smap;
vector<int> r_smap;
vector<int> firstLoc;
vector<int> d;

struct RMT {
	int n;
	const int INF = 987654321;
	vector<int> rangeMin;
	
	RMT(const vector<int>& ary) {
		n = ary.size();
		rangeMin.resize(n * 4);
		init(1, ary, 0, n - 1);
	}

	int min(int x, int y) {
		if (x <= y) { return x; }
		else { return y; }
	}

	int init(int node, const vector<int>& ary, int nleft, int nright) {
		if (nleft == nright) {
			rangeMin[node] = ary[nleft];
			return rangeMin[node];
		}

		// else
		int nmid = (nleft + nright) / 2;
		rangeMin[node] 
		= min(init(node * 2, ary, nleft, nmid), init(node * 2 + 1, ary, nmid + 1, nright));

		return rangeMin[node];
	}

	int query(int node, int left, int right, int nleft, int nright) {

		if ((right < nleft) || (nright < left)) {
			return INF;
		}
		else if ((left <= nleft) && (nright <= right)) {
			return rangeMin[node];
		}

		// else
		int nmid = (nleft + nright) / 2;
		return min(query(node * 2, left, right, nleft, nmid), 
				   query(node * 2 + 1, left, right, nmid + 1, nright));
	}

	int query(int left, int right) {
		return query(1, left, right, 0, n - 1);
	}
};

void input() {
	cin >> N >> Q;

	tree = vector<vector<int>>(N);
	q = vector<pair<int, int>>(Q);
	smap = vector<int>(N, -1);
	r_smap = vector<int>(N);
	firstLoc = vector<int>(N);
	d = vector<int>(N);

	for (int i = 1; i < N; i++) {
		int p; cin >> p;
		tree[p].push_back(i);
	}

	for (int i = 0; i < Q; i++) {
		cin >> q[i].first >> q[i].second;
	}
}

void preorder(int node, vector<int>& path) {
	path.push_back(node);

	for (int i = 0; i < tree[node].size(); i++) {
		int child = tree[node][i];
		preorder(child, path);
		path.push_back(node);
	}
}

vector<int> serialize() {
	vector<int> path;

	preorder(0, path);

	int count = 0;
	for (int i = 0; i < path.size(); i++) {
		int cur = path[i];

		if (smap[cur] == -1) {
			smap[cur] = count;
			r_smap[count] = cur;
			firstLoc[cur] = i;
			count++;
		}

		path[i] = smap[cur];
	}

	return path;
}

void get_depth() {
	d[0] = 0;

	queue<int> q;
	q.push(0);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i = 0; i < tree[cur].size(); i++) {
			int next = tree[cur][i];

			d[next] = d[cur] + 1;
			q.push(next);
		}
	}
}

vector<int> solve() {
	get_depth();
	vector<int> array = serialize();
	vector<int> result(Q);

	struct RMT rmt(array);

	for (int i = 0; i < Q; i++) {
		int x = q[i].first, y = q[i].second;
		int lx = firstLoc[x], ly = firstLoc[y];
		if (lx > ly) { int tmp = lx; lx = ly; ly = tmp; }

		int ret = r_smap[rmt.query(lx, ly)];
		result[i] = d[x] + d[y] - d[ret] * 2;
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		input();

		vector<int> result = solve();
		for (int i = 0; i < Q; i++) {
			cout << result[i] << endl;
		}
	}

	return 0;
}
