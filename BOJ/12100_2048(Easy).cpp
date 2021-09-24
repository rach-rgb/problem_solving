#include <iostream>
#include <vector>
using namespace std;

int N;

void printBoard(const vector<vector<int>>& board)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		} cout << endl;
	 }
}

int row(int i, int j, int d)
{
	if (d == 0) { return i; }
	else if (d == 1) { return N - j - 1; }
	else if (d == 2) { return i;  }
	else if (d == 3) { return j; }
}

int col(int i, int j, int d) {
	if (d == 0) { return j; }
	else if (d == 1) { return i; }
	else if (d == 2) { return N - j - 1; }
	else if (d == 3) { return i; }
}

void arrange(vector<int>& blocks)
{
	vector<int> nblocks;

	if (blocks.size() < 2) { return; }
	// else

	for (int i = 1; i < blocks.size(); i++) {
		if (blocks[i - 1] == blocks[i]) {
			blocks[i - 1] = blocks[i] * 2;
			blocks[i] = 0;
		}
	}

	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i] != 0) { nblocks.push_back(blocks[i]); }
	}

	blocks = nblocks;

	return;
}

int solve(vector<vector<int>> board, int count)
{
	int ret = -1;

	// base
	if(count == 0){ 
		ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ret = (ret > board[i][j]) ? ret : board[i][j];
			}
		}

		return ret;
	}

	// else
	for (int d = 0; d < 4; d++) {
		vector<vector<int>> nboard(N, vector<int>(N, 0));
		for (int i = 0; i < N; i++) {
			vector<int> v;
			for (int j = 0; j < N; j++) {
				if (board[row(i, j, d)][col(i, j, d)] != 0) { v.push_back(board[row(i, j, d)][col(i, j, d)]); }
			}
			arrange(v);
			for (int k = 0; k < v.size(); k++) {
				nboard[row(i, k, d)][col(i, k, d)] = v[k];
			}
		}
		//printBoard(nboard);

		int result = solve(nboard, count - 1);
		ret = (ret > result) ? ret : result;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);

	cin >> N;
	vector<vector<int>> board(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}

	cout << solve(board, 5) << endl;

}
