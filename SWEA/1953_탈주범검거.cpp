#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 50
#define MAXM 50
typedef struct _info {
	bool u;
	bool d;
	bool l;
	bool r;
	_info() : u(false), d(false), l(false), r(false) {}
} info;

typedef struct _coords {
	int x;
	int y;
	_coords(int ux, int uy) : x(ux), y(uy) {}
} coord;

void input();
void solve();
info nextPos(int x, int y);
bool inRange(int x, int y);
bool up(int x);
bool down(int x);
bool left(int x);
bool right(int x);

int N, M, R, C, L;
int board[MAXN][MAXM];
bool visited[MAXN][MAXM];
queue<coord> q;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
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
	cin >> N >> M >> R >> C >> L;

	int type;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> type;
			board[i][j] = type;
		}

		memset(visited+i, false, sizeof(bool) * M);
	}
}

void solve()
{
	result = 0;

	// use DFS
	q.push(coord(R, C));

	for (int i = 0; i < L; i++)
	{
		int qsize = q.size();
		for (int j = 0; j < qsize; j++)
		{
			coord cur = q.front();
			q.pop();
			visited[cur.x][cur.y] = true;

			info nextP = nextPos(cur.x, cur.y);
			bool next[4] = { nextP.u, nextP.d, nextP.l, nextP.r };

			for (int i = 0; i < 4; i++)
			{
				int nx = cur.x + dx[i];
				int ny = cur.y + dy[i];

				if ((!next[i])||(visited[nx][ny])) { continue; } // cannot proceed

				// else push to queue
				q.push(coord(nx, ny));
			}
		}
	}

	// clear queue
	while (!q.empty()) { q.pop(); }

	// get answer
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (visited[i][j]) { result++; }
		}
	}
}

// return list of possible next location
info nextPos(int x, int y)
{
	info ret;
	bool next[4] = { false, false, false, false }; // u d l r

	// check range
	for (int i = 0; i < 4; i++)
	{
		if (inRange(x + dx[i], y + dy[i])) { next[i] = true; }
	}

	// check pipe
	for (int i = 0; i < 4; i++)
	{
		if (!next[i]) { continue; } // not in range

		int curType = board[x][y];
		int nextType = board[x + dx[i]][y + dy[i]];

		if (i == 0) // up
		{
			next[i] = up(curType) && down(nextType);
		}
		else if (i == 1) // down
		{
			next[i] = down(curType) && up(nextType);
		}
		else if (i == 2) // left
		{
			next[i] = left(curType) && right(nextType);
		}
		else // i==3 right
		{
			next[i] = right(curType) && left(nextType);
		}
	}

	ret.u = next[0];
	ret.d = next[1];
	ret.l = next[2];
	ret.r = next[3];

	return ret;
}

// whether pipe connected to upper pipe
bool up(int x)
{
	if ((x==1) || (x==2) || (x==4) || (x==7))
	{
		return true;
	}
	return false;
}

// whether pipe connected to lower pipe
bool down(int x)
{
	if ((x == 1) || (x == 2) || (x == 5) || (x == 6))
	{
		return true;
	}
	return false;
}

// whether pipe connected to left pipe
bool left(int x)
{
	if ((x == 1) || (x == 3) || (x == 6) || (x == 7))
	{
		return true;
	}
	return false;
}

// whether pipe connected to right pipe
bool right(int x)
{
	if ((x == 1) || (x == 3) || (x == 4) || (x == 5))
	{
		return true;
	}
	return false;
}

bool inRange(int x, int y)
{
	if ((x >= 0) && (x < N))
	{
		if ((y >= 0) && (y < M))
		{
			return true;
		}
	}
	return false;
}