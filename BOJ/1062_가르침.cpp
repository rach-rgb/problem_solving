#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXK (26)
#define MAXN (50)

int N, K;
bool known[MAXK];
string words[MAXN];


int solve(int i, int k) {
	int ret = 0, result;

	if ((i == MAXK) || (k == 0)) {
		for (int j = 0; j < N; j++) {
			bool fail = false;
			for (int x = 0; x < words[j].size(); x++) {
				if (!known[words[j][x] - 'a']) { fail = true; break; }
			}
			if (!fail) { ret++; }
		}
		return ret;
	}

	for (int j = i; j < MAXK; j++) {
		if (!known[j])
		{
			known[j] = true;
			result = solve(j + 1, k - 1);
			ret = (ret > result) ? ret : result;
			known[j] = false;
		}
	}

	return ret;
}

int main() {
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> words[i];
		words[i] = words[i].substr(4, words[i].size() - 8);
	}

	if (K < 5) { cout << 0 << endl; return 0; }
	else if (K >= 26) { cout << N << endl; return 0; }
	else {
		K -= 5;
		memset(known, false, sizeof(false) * MAXK);
		known['a' - 'a'] = true;
		known['n' - 'a'] = true;
		known['t' - 'a'] = true;
		known['i' - 'a'] = true;
		known['c' - 'a'] = true;
	}

	cout << solve(1, K) << endl; // 'a' is known
}
