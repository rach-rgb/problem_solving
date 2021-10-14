#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> query;
vector<vector<bool>> green(6, vector<bool>(4, false));
vector<vector<bool>> blue(6, vector<bool>(4, false));
int score;

void drop(vector<vector<bool>>& board, int loc, int len)
{
	int r;
	for (r = 1; r < 6; r++) {
		if ((board[r][loc] == true) || (board[r][loc + len - 1] == true)) {
			r--;
			break;
		}
	}

	if (r == 6) { r--; }

	board[r][loc] = true;
	board[r][loc + len - 1] = true;

	while (1) {
		bool change = false;

		int add = 0;

		for (int r = 2; r <= 5; r++) {
			bool erase = true;
			for (int c = 0; c < 4; c++) {
				if (!board[r][c]) { erase = false; break; }
			}

			if (erase) {
				int l = r;
				while (l > 0)
				{
					board[l] = board[l - 1];
					l--;
				}

				add++;
			}
		}

		if (add > 0)
		{
			for (int r = 0; r < add; r++) {
				for (int c = 0; c < 4; c++) {
					board[r][c] = false;
				}
			}

			score += add;
			change = true;
		}

		int l = 0;
		for (int c = 0; c < 4; c++) {
			if (board[0][c]) { l++; break; }
		}
		for (int c = 0; c < 4; c++) {
			if (board[1][c]) { l++; break; }
		}

		if (l > 0)
		{
			change = true;
			for (int r = 5 - l; r >= 0; r--) {
				board[r + l] = board[r];
			}
		}

		if (!change) { return; }
	}
}

int solve() {
	int ret = 0;
	score = 0;

	for (int i = 0; i < query.size(); i++) {
		int t = query[i][0], x = query[i][1], y = query[i][2];

		if (t == 1) {
			drop(green, y, 1);
			drop(blue, x, 1);
		}
		else if (t == 2) {
			drop(green, y, 2);
			drop(blue, x, 1);
			drop(blue, x, 1);
		}
		else if (t == 3) {
			drop(green, y, 1);
			drop(green, y, 1);
			drop(blue, x, 2);
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j]) { ret++; }
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (blue[i][j]) { ret++; }
		}
	}

	cout << score << "\n";

	return ret;
}

int main() {
	int N;

	cin >> N;
	query = vector<vector<int>>(N, vector<int>(3));

	for (int i = 0; i < N; i++) {
		int t, x, y;
		cin >> query[i][0] >> query[i][1] >> query[i][2];
	}

	cout << solve() << endl;

	return 0;
}
