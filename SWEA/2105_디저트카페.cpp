#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 20
#define MAXD 100

void input();
void solve();
int leftLength(int x, int y);
int rightLength(int x, int y);
bool markAry(int val, bool* ary);
void findPaths(int x, int y);

int N;
int board[MAXN][MAXN];

bool visited[MAXD + 1];
bool visited_L[MAXD + 1]; // left point fixed
bool visited_R[MAXD + 1]; // right point fixed

int result;

int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " " << result << endl;
	}
}

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}
}

void solve()
{
	result = -1;

	for (int i = 0; i < N - 2; i++) // exclude last two rows
	{
		for (int j = 1; j < N - 1; j++) // exclude first & last column
		{
			memset(visited, false, sizeof(bool) * (MAXD+1));
			findPaths(i, j);
		}
	}
}

// mark ary[val] or return false it already occupied
bool markAry(int val, bool* ary)
{
	if (ary[val]) { return false; }
	else { ary[val] = true; return true; }
}

// find every path
void findPaths(int x, int y)
{
	int maxL = leftLength(x, y);
	int maxR = rightLength(x, y);

	if ((2 * maxL + 2 * maxR - 4) < result) { return; } // prune

	visited[board[x][y]] = true;

	int val, len;
	bool success;
	for (int left = 2; left <= maxL; left++)
	{
		int lx = x + left - 1;
		int ly = y - left + 1;
		val = board[lx][ly];

		if (!markAry(val, visited)) { break; } // cannot expand left

		memcpy(visited_L, visited, sizeof(bool) * (MAXD + 1));
		for (int right = 2; right <= maxR; right++)
		{
			int rx = x + right - 1;
			int ry = y + right - 1;
			val = board[rx][ry];

			if (!markAry(val, visited_L)) { break; }

			memcpy(visited_R, visited_L, sizeof(bool) * (MAXD + 1));
			success = true;
			int nx, ny;
			for (int i = 2; (i <= right) && (success); i++) // left bottom
			{
				nx = lx + i - 1; // nx - lx = i - 1
				ny = ly + i - 1; // ny - ly = i - 1

				if ((nx >= N) || (ny >= N)) { success = false; break; }

				val = board[nx][ny];

				if (!markAry(val, visited_R)) {
					success = false;
				}
			}
			for (int j = 2; (j < left) && (success); j++) // right bottom
			{
				nx = rx + j - 1; // nx - rx = j - 1
				ny = ry - j + 1; // ry - ny = j - 1

				if ((nx >= N) || (ny <= -1)) { success = false; break; }

				val = board[nx][ny];

				if (!markAry(val, visited_R)) {
					success = false;
				}
			}

			if (success) {
				len = 2 * left + 2 * right - 4;
				result = (result > len) ? result : len;
			}
		}
	}
}


// top -> left side
int leftLength(int x, int y)
{
	int ret = (y + 1 < N - x) ? y + 1 : N - x;
	return ret;
}

// top -> right side
int rightLength(int x, int y)
{
	int ret = (N - y < N - x) ? N - y : N - x;
	return ret;
}