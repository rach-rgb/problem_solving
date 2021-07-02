#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string N, M;
vector<int> pmatch;

void calculate() {
	pmatch.resize(N.length());

	int begin = 1, matched = 0;
	while (begin + matched < N.length()) {
		if (N[begin + matched] == M[matched]) {
			matched++;
			pmatch[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) { begin++; }
			else
			{
				begin = begin + matched - pmatch[matched - 1];
				matched = pmatch[matched - 1];
			}
		}
	}
}

vector<int> solve() {
	vector<int> result;

	calculate(); // precalculate partial match

	int matched = N.length();
	while (matched > 0) {
		result.push_back(matched);
		matched = pmatch[matched - 1];
	}

	reverse(result.begin(), result.end());

	return result;
}

int main() {
	string s1, s2;
	cin >> s1 >> s2;
	N = s1 + s2;
	M = s1 + s2;

	vector<int> result = solve();
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;

	return 0;
}
