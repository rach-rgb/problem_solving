#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string N, M;
vector<int> pmatch;

void calculate() {
	pmatch = vector<int>(M.length(), 0);

	int begin = 1, matched = 0;
	while (begin + matched < M.length()) {
		if (M[begin + matched] == M[matched]) {
			matched++;
			pmatch[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin = begin + matched - pmatch[matched - 1];
				matched = pmatch[matched - 1];
			}
		}
	}
}

int solve() {
	int result = 0;

	calculate();

	int begin = 0, matched = 0;
	while (begin + matched < N.length()) {
		if (N[begin + matched] == M[matched]) {
			matched++;
			if (begin + matched == N.length()) {
				result = matched;
				break;
			}
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin = begin + matched - pmatch[matched - 1];
				matched = pmatch[matched - 1];
			}
		}
	}

	return 2 * N.size() - result;
}


int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		M = N; reverse(M.begin(), M.end());

		cout << solve() << endl;
	}

	return 0;
}
