#include <iostream>
#include <vector>
using namespace std;

#define INV (987654321)

int N, M;

vector<vector<int>> disk;
vector<vector<int>> query;

int solve() {
	vector<int> top(N, 0);

	for (int t = 0; t < query.size(); t++) {
		int x = query[t][0], d = query[t][1], k = query[t][2];

		int y = x;
		vector<pair<int, int>> remove;

		// rotate
		while (y - 1 < N)
		{
			if (d == 0) { top[y - 1] -= k; }
			else if (d == 1) { top[y - 1] += k; }

			if (top[y - 1] < 0) { top[y - 1] += M; }
			else if (top[y - 1] >= M) { top[y - 1] -= M; }

			y += x;
		}

		// check
		for (int di = 0; di < N; di++) {
			for (int loc = 0; loc < M; loc++) {
				bool change = false;
				int& v = disk[di][(top[di] + loc) % M];

				// invalid
				if (v == INV) { continue; }

				// right
				int& r = disk[di][(top[di] + loc + 1) % M];
				if (r == v) {
					remove.push_back(pair<int, int>(di, (top[di] + loc + 1) % M));
					change = true;
				}

				// top
				if (di + 1 < N) {
					int& t = disk[di + 1][(top[di + 1] + loc) % M];
					if (t == v) {
						remove.push_back(pair<int, int>(di + 1, (top[di + 1] + loc) % M));
						change = true;
					}
				}

				// bottom
				if (di - 1 >= 0) {
					int& b = disk[di - 1][(top[di - 1] + loc) % M];
					if (b == v)
					{
						remove.push_back(pair<int, int>(di - 1, (top[di - 1] + loc) % M));
						change = true;
					}
				}

				if (change) {
					remove.push_back(pair<int, int>(di, (top[di] + loc) % M));
				}
			}
		}

		if (remove.empty()) {
			int sum = 0;
			int count = 0;
			for (int di = 0; di < N; di++) {
				for (int i = 0; i < M; i++) {
					if (disk[di][i] != INV) {
						sum += disk[di][i];
						count++;
					}
				}
			}

			float avg = (float)sum / (float)count;
			for (int di = 0; di < N; di++) {
				for (int i = 0; i < M; i++) {
					if (disk[di][i] != INV) {
						if (disk[di][i] > avg)
						{
							disk[di][i]--;
						}
						else if (disk[di][i] < avg)
						{
							disk[di][i]++;
						}
					}
				}
			}
		}
		else {
			for (int r = 0; r < remove.size(); r++) {
				disk[remove[r].first][remove[r].second] = INV;
			}
		}
	}

	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (disk[i][j] != INV)
			{
				ret += disk[i][j];
			}
		}
	}

	return ret;
}

int main(){
	ios::sync_with_stdio(false);

	int T;
	cin >> N >> M >> T;

	disk = vector<vector<int>>(N, vector<int>(M));
	query = vector<vector<int>>(T, vector<int>(3));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> disk[i][j];
		}
	}

	for (int i = 0; i < T; i++) {
		cin >> query[i][0] >> query[i][1] >> query[i][2];
	}

	cout << solve() << "\n";

	return 0;
}
