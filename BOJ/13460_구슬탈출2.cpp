#include <iostream>
#include <vector>
using namespace std;

int N, M;

const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { -1, 0, 1, 0 };

bool inRange(int x, int y) {
	return ((0 <= x) && (x < N)) && ((0 <= y) && (y < M));
}

// return true to move red ball first
bool whichBall(const vector<int>& pos, int d)
{
	if (d == 0) { return pos[1] <= pos[3]; }
	else if (d == 1) { return pos[0] >= pos[2]; }
	else if (d == 2) { return pos[1] >= pos[3]; }
	else if (d == 3) { return pos[0] <= pos[2]; }
}

bool success(const vector<int>& pos) {
	return (pos[0] == -1) && (pos[1] == -1) && (pos[2] != -1) && (pos[3] != -1);
}

bool fail(const vector<int>& pos) {
	return (pos[2] == -1) && (pos[3] == -1);
}


bool hasMoved(const vector<int>& pos, const vector<int>& npos)
{
	return (pos[0] != npos[0]) || (pos[1] != npos[1]) || (pos[2] != npos[2]) || (pos[3] != npos[3]);
}

void moveBall(vector<vector<char>>& board, int& x, int& y, int d, bool type) {
	int nx = x + dx[d], ny = y + dy[d];

	while (1) {
		if ((!inRange(nx, ny)) || ((board[nx][ny] != '.') && (board[nx][ny] != 'O')))
		{
			nx -= dx[d];
			ny -= dy[d];
			break;
		}
		else if (board[nx][ny] == 'O') // goal
		{
			board[x][y] = '.';
			x = -1; y = -1;
			return;
		}
		else
		{
			nx += dx[d];
			ny += dy[d];
		}
	}

	board[x][y] = '.';
	board[nx][ny] = (type) ? 'R' : 'B';
	x = nx;
	y = ny;

	return;
}

// return min if it is solvable in count moves
int solve(vector<vector<char>> board, int count, vector<int> pos) {
	int ret = -1;

	if (count < 1) { return -1; }

	// else
	for (int d = 0; d < 4; d++) {
		vector<vector<char>> nboard = board;
		vector<int> npos = pos;
		if (whichBall(npos, d))
		{
			moveBall(nboard, npos[0], npos[1], d, true);
			moveBall(nboard, npos[2], npos[3], d, false);
		}
		else
		{
			moveBall(nboard, npos[2], npos[3], d, false);
			moveBall(nboard, npos[0], npos[1], d, true);
		}

		if (success(npos)) { return 10 - count + 1; }
		else if ((!fail(npos)) && hasMoved(pos, npos)) // moved, but not success
		{
			int result = solve(nboard, count - 1, npos);
			if (result != -1) {
				if (ret == -1) { ret = result; }
				else { ret = (ret < result) ? ret : result; }
			}
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);

	cin >> N >> M;
	vector<vector<char>> board(N, vector<char>(M));
	vector<int> pos(4);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];

			if (board[i][j] == 'R') { pos[0] = i; pos[1] = j; }
			else if (board[i][j] == 'B') { pos[2] = i; pos[3] = j; }
		}
	}

	cout << solve(board, 10, pos) << endl;

	return 0;
}
