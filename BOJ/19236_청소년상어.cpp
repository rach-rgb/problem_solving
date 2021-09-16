#include <iostream>
#include <vector>
using namespace std;

#define MAXD 8
#define MAXF 16

const int dx[MAXD + 1] = { 99, -1, -1, 0, 1, 1, 1, 0, -1 };
const int dy[MAXD + 1] = { 99, 0, -1, -1, -1, 0, 1, 1, 1 };

bool inRange(int x, int y)
{
	return ((0 <= x) && (x < 4)) && ((0 <= y) && (y < 4));
}

int eatFish(vector<vector<int>> board, vector<vector<int>> fish, vector<int> shark)
{	
	// eat fish
	int f = board[shark[0]][shark[1]];
	shark[2] = fish[f][2];
	fish[f][0] = -1; // mark invalid
	board[shark[0]][shark[1]] = -1; // shark

	// move fish
	for (int i = 1; i <= MAXF; i++)
	{
		if (fish[i][0] == -1) { continue; } // invalid

		int initD = fish[i][2];
		int d = initD;
		for (int t = 0; t < 8; t++)
		{
			int x = fish[i][0], y = fish[i][1];
			int nx = x + dx[d], ny = y + dy[d];

			if (inRange(nx, ny) && (board[nx][ny] != -1)) {
				if (board[nx][ny] == 0) // empty
				{
					board[x][y] = 0;
				}
				else // other fish
				{
					board[x][y] = board[nx][ny];
					fish[board[nx][ny]][0] = x;
					fish[board[nx][ny]][1] = y;
				}
				board[nx][ny] = i;
				fish[i][0] = nx;
				fish[i][1] = ny;
				fish[i][2] = d;
				break;
			}

			d++;
			if (d == MAXD + 1) { d = 1; }
		}
	}

	// eat fish
	vector<vector<int>> nboard; vector<vector<int>> nfish; vector<int> nshark;

	int ret = 0;
	int x = shark[0], y = shark[1], d = shark[2];
	int nx = x + dx[d], ny = y + dy[d];
	while (inRange(nx, ny))
	{
		if (board[nx][ny] != 0)
		{
			nboard = board;
			nfish = fish;
			nshark = shark;

			nshark[0] = nx; nshark[1] = ny;
			nboard[x][y] = 0; // empty

			int res = eatFish(nboard, nfish, nshark);
			ret = (res > ret) ? res : ret;
		}

		nx += dx[d];
		ny += dy[d];
	}

	return f + ret;
}

int main() {
	vector<vector<int>> board(4, vector<int>(4));
	vector<vector<int>> fish(MAXF + 1, vector<int>(3));
	vector<int> shark(3);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) {
			int a, b;
			cin >> a >> b;

			board[i][j] = a;

			fish[a][0] = i;
			fish[a][1] = j;
			fish[a][2] = b;
		}
	}

	shark[0] = 0; shark[1] = 0;

	cout << eatFish(board, fish, shark) << endl;

	return 0;
}
