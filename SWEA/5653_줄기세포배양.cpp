#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 50
#define MAXM 50
#define MAXK 300
typedef struct _cell {
	short x;
	short y;
	short e; // dead time
	short s; // start time
	_cell(short ux, short uy, short us, short ue) : x(ux), y(uy), e(ue), s(us) {}
} cell;

struct compare_start {
	bool operator()(cell x, cell y)
	{
		if (x.s > y.s) { return true; }
		else if (x.s < y.s) { return false;}
		else // x.s == y.s
		{
			return (x.e - x.s < y.e - y.s); // more power
		}
	}
};

struct compare_end {
	bool operator()(cell x, cell y)
	{
		return x.e > y.e;
	}
};

void input();
void solve();
bool inRange(int x, int y);

int N, M, K;
bool board[MAXK*2+MAXN][MAXK*2+MAXM];

priority_queue<cell, vector<cell>, compare_start> pq;
priority_queue<cell, vector<cell>, compare_end> wait_pq;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

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
	cin >> N >> M >> K;

	// reset board
	for (int i = 0; i < 2*MAXK+N; i++)
	{
		memset(board + i, false, sizeof(bool) * (2 * MAXK + M));
	}

	int p;
	for (int i = MAXK; i < MAXK + N; i++)
	{
		for (int j = MAXK; j < MAXK + M; j++)
		{
			cin >> p;

			if (p)
			{
				board[i][j] = true;
				cell c(i, j, p, 2*p);
				pq.push(c);
			}
		}
	}
}

void solve()
{
	result = 0;

	for (int t = 1; t < K; t++)
	{
		while (!pq.empty())
		{
			cell c = pq.top();
			if (c.s > t) { break; } // no more activated cell
			
			// else c.s = t (activated)
			int x = c.x;
			int y = c.y;
			int p = c.e - c.s;

			if (p > 1) { wait_pq.push(c); } // need to wait
			pq.pop();

			int nx, ny;
			for (int d = 0; d < 4; d++)
			{
				nx = x + dx[d];
				ny = y + dy[d];

				if (inRange(nx, ny) && (!board[nx][ny])) // not occupied
				{
					cell nc(nx, ny, t + 1 + p, t + 1 + 2 * p);
					pq.push(nc);
					board[nx][ny] = true;
				}
			}
		}

		while (!wait_pq.empty())
		{
			cell c = wait_pq.top();
			if (c.e > t + 1) { break; } // no cells to deactivate

			// else
			wait_pq.pop();
		}
	}

	result = pq.size() + wait_pq.size();


	// clear
	while (!pq.empty())
	{
		pq.pop();
	}

	while (!wait_pq.empty())
	{
		wait_pq.pop();
	}
}

bool inRange(int x, int y)
{
	if ((x >= 0) && (x < MAXK * 2 + N))
	{
		if ((y >= 0) && (y < MAXK * 2 + M))
		{
			return true;
		}
	}
	
	return false;
}