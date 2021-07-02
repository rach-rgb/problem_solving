#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int K;
string N, M;
vector<string> dials;
vector<int> pmatch;
deque<char> d;

void calculate() {
	pmatch = vector<int>(M.length(), 0);

	int begin = 1, match = 0;
	while (begin + match < M.length()) {
		if (M[begin + match] == M[match]) {
			match++;
			pmatch[begin + match - 1] = match;
		}
		else {
			if (match == 0) {
				begin++;
			} else {
				begin = begin + match - pmatch[match - 1];
				match = pmatch[match - 1];
			}
		}
	}
}

// return begin
int KMP() {
	int begin = 0, match = 0;
	
	while (begin + match < N.length()) {
		if (N[begin + match] == M[match]) {
			match++;
			if (match == M.length()) { return begin; }
		}
		else {
			if (match == 0) {
				begin++;
			}
			else {
				begin = begin + match - pmatch[match - 1];
				match = pmatch[match - 1];
			}
		}
	}

	return begin;
}

string build_N(const string x, int dir) {
	if (dir == 0) {
		string rx = x;
		reverse(rx.begin(), rx.end());

		return rx + rx;
	}
	else {
		return x + x;
	}
}

string build_M(const string x, int dir) {
	if (dir == 0) {
		string rx = x;
		reverse(rx.begin(), rx.end());

		return rx;
	}
	else {
		return x;
	}
}

int solve() {
	int result = 0;

	for (int i = 1; i < K + 1; i++) {
		int dir = (i % 2 == 0); // 0: counter clockwise, 1: clockwise

		N = build_N(dials[i - 1], dir);
		M = build_M(dials[i], dir);

		calculate();
		result += KMP();
	}

	return result;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> K;
		dials.resize(K + 1);
		for (int i = 0; i < K + 1; i++) { cin >> dials[i]; }

		cout << solve() << endl;
	}

	return 0;
}
