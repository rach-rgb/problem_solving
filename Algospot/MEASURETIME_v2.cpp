#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> seq;

struct FT {
	const int MAXA = 999999;
	vector<int> ary;

	FT() {
		ary = vector<int>(MAXA + 2, 0);
	}

	long long sum(int i) {
		long long ret = 0;
		i++;

		while (i > 0) {
			ret += ary[i];
			i &= (i - 1);
		}

		return ret;
	}

	// add x to array[i]
	void add(int i, int x) {
		i++;
		while (i < ary.size()) {
			ary[i] += x;
			i += (i & -i);
		}
	}
};

long long solve() {
	long long ret = 0;

	struct FT tree;
	for (int i = 0; i < N; i++) {
		ret += tree.sum(tree.MAXA) - tree.sum(seq[i]);
		tree.add(seq[i], 1);
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		seq = vector<int>(N);
		for (int i = 0; i < N; i++) { cin >> seq[i]; }
		cout << solve() << endl;
	}

	return 0;
}
