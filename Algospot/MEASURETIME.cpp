#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> ary;

int mergeSort(vector<int>& ary) {
	if (ary.size() < 2) { return 0; }

	// else
	int mid = ary.size() / 2;

	vector<int> x(ary.begin(), ary.begin() + mid);
	vector<int> y(ary.begin() + mid, ary.end());

	int inv1 = mergeSort(x);
	int inv2 = mergeSort(y);
	int inv3 = 0;

	int i = 0, j = 0, k = 0;
	while ((i<x.size())&&(j<y.size())) {
		if (x[i] <= y[j]) {
			ary[k] = x[i];
			i++;
		}
		else {
			ary[k] = y[j];
			j++;
			inv3 += x.size() - i;
		}
		k++;
	}

	while (i < x.size()) {
		ary[k] = x[i];
		k++; i++;
	}

	while (j < y.size()) {
		ary[k] = y[j];
		k++; j++;
	}

	return inv1 + inv2 + inv3;
}

int solve() {
	return mergeSort(ary);
}

int main() {
	ios::sync_with_stdio(false);

	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		ary = vector<int>(N);
		for (int i = 0; i < N; i++) { cin >> ary[i]; }
		cout << solve() << endl;
	}

	return 0;
}
