#include <iostream>
#include <cstring>
using namespace std;

#define MAXC 4000
#define MAXN 1000
typedef struct _info
{
	int x;
	int y;
	int d;
	int k;
} info;;

void input();
void solve();
bool inRange(int x, int y);

int N;
info infos[MAXN];

int board[MAXC + 1][MAXC + 1];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

int result;

int main()
{
	ios::sync_with_stdio(false);

	int T;
	cin >> T;

	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " " << result << endl;
	}

	return 0;
}

void input()
{
	cin >> N;

	// reset board
	for (int i = 0; i < MAXC + 1; i++)
	{
		memset(board + i, -1, sizeof(int) * (MAXC + 1));
	}

	int ux, uy, ud, uk;
	for (int i = 0; i < N; i++)
	{
		cin >> ux >> uy >> ud >> uk;

		infos[i].x = ux * 2 + 2000;
		infos[i].y = uy * 2 + 2000;
		infos[i].d = ud;
		infos[i].k = uk;
	}
}

void solve()
{
	result = 0;

	int count = N;
	for (int t = 0; t <= MAXC + 1; t++)
	{
		for (int i = 0; i < N; i++)
		{
			info in = infos[i];
			if (in.k == 0) { continue; }

			int* pval = &board[in.x][in.y];

			if (*pval == i)
			{
				*pval = -1;
			}
			else if (*pval != -1) // collision
			{
				result += in.k;
				infos[i].k = 0;
				count--;
				*pval = -1;
				continue;
			}

			int nx = in.x + dx[in.d];
			int ny = in.y + dy[in.d];

			if (!inRange(nx, ny))
			{
				infos[i].k = 0;
				continue;
			}

			// else
			int* val = &board[nx][ny];

			if (*val == -1)
			{
				*val = i;
				infos[i].x = nx;
				infos[i].y = ny;
			}
			else // collision
			{
				if ((*val) < N) { (*val) += N; }
				result += in.k;
				infos[i].k = 0;
				count--;
			}
		}

		if (count == 0) { break; }
	}
}

bool inRange(int x, int y)
{
	if ((x >= 0) && (x <= MAXC))
	{
		if ((y >= 0) && (y <= MAXC))
		{
			return true;
		}
	}
	return false;
}