#include <iostream>
#include <vector>
using namespace std;

#define INF 987654321

typedef struct __cam {
	int x;
	int y;
	int type;
} cam;

int N, M;
vector<cam> cams;

const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { 1, -1, 0, 0 };
vector<vector<vector<bool>>> dTypes = {
	{}, // 0
	{
		{true, false, false, false},
		{false, true, false, false},
		{false, false, true, false},
		{false, false, false, true},
	},
	{
		{true, true, false, false},
		{false, false, true, true},
	},
	{
		{true, false, true, false},
		{true, false, false, true},
		{false, true, true, false},
		{false, true, false, true},
	},
	{
		{false, true, true, true},
		{true, false, true, true},
		{true, true, false, true},
		{true, true, true, false},
	},
	{
		{true, true, true, true}
	},
};

bool inRange(int x, int y) {
	return ((0 <= x) && (x < N)) && ((0 <= y) && (y < M));
}

int solve(vector<vector<int>> board, int count)
{
	int ret = INF;

	// base
	if (count == cams.size())
	{
		ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (board[i][j] == 0) { ret++; }
			}
		}
		return ret;
	}

	// else
	vector<vector<bool>> dType = dTypes[cams[count].type];
	for (int i = 0; i < dType.size(); i++) {
		vector<bool> dirs = dType[i];
		vector<vector<int>> nboard(board);

		for (int d = 0; d < 4; d++)
		{
			if (dirs[d])
			{
				int x = cams[count].x + dx[d];
				int y = cams[count].y + dy[d];

				while (1) {
					if ((!inRange(x, y)) || (nboard[x][y] == 6))
					{
						break;
					}
					else if (nboard[x][y] == 0)
					{
						nboard[x][y] = 7;
					}

					x += dx[d];
					y += dy[d];
				}
			}
		}

		int result = solve(nboard, count + 1);
		ret = (ret < result) ? ret : result;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);

	cin >> N >> M;
	vector<vector<int>> board(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];

			int t = board[i][j];
			if ((1 <= t) && (t <= 5))
			{
				cam c;
				c.x = i; c.y = j; c.type = t;

				cams.push_back(c);
			}
		}
	}

	cout << solve(board, 0) << endl;

	return 0;
}
