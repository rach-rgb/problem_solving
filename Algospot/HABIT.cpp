#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int K;
string S;
int N;

typedef struct _mycmp {
	const vector<int>& g;
	int t;

	_mycmp(const vector<int>& ug, int ut) : g(ug), t(ut) { };

	bool operator()(int a, int b) {
		if (g[a] != g[b]) { return g[a] < g[b]; }
		else {
			return g[a + t] < g[b + t];
		}
	}

} mycmp;

// construct suffix array
vector<int> construct() {
	vector<int> group(N + 1);
	for (int i = 0; i < N; i++) { group[i] = S[i]; }
	group[N] = -1;

	vector<int> result(N);
	for (int i = 0; i < N; i++) { result[i] = i; }

	int t = 1;
	while (t < N) {
		mycmp cmp(group, t);
		sort(result.begin(), result.end(), cmp);

		t = t * 2;
		if (t >= N) { break; }

		vector<int> ngroup(N + 1);
		ngroup[result[0]] = 0; // first
		for (int i = 1; i < N; i++) {
			if (cmp(result[i-1],result[i])) {
				ngroup[result[i]] = ngroup[result[i - 1]] + 1;
			}
			else {
				ngroup[result[i]] = ngroup[result[i - 1]];
			}
		}
		ngroup[S.length()] = -1;

		group = ngroup;
	}

	/* Debug
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	} cout << endl;  */

	return result;
}

int solve() {
	int result = 0;

	N = S.length();
	vector<int> sary = construct();

	for (int i = 0; i + K - 1 < N; i++) {
		int len = 0, j = i + K - 1;
		while ((sary[i] + len < N) && (sary[j] + len < N)) {
			if (S[sary[i] + len] == S[sary[j] + len]) {
				len++;
			}
			else {
				break;
			}
		}

		result = (result > len) ? result : len;
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		cin >> K >> S;
		cout << solve() << endl;
	}

	return 0;
}
