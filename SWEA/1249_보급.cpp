#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 100
#define MAXINT 987654321

typedef struct _vertex {
	int x;
	int y;
	int dist;
} vertex;

struct compare {
	bool operator()(vertex x, vertex y)
	{
		if (x.dist > y.dist) { return true; }
		else { return false; }
	}
};

void input();
void solve();
bool inRange(int x, int y);
bool isGoal(int x, int y);
void clearPQ();

int N;
int board[MAXN][MAXN];
int cost[MAXN][MAXN];
priority_queue< vertex, vector<vertex>, compare > pq;
int result;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

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
	return 0;
}

void input()
{
	char in;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		memset(cost[i], -1, sizeof(int) * N);
		for (int j = 0; j < N; j++)
		{
			cin >> in;
			board[i][j] = in - '0';
			vertex v;
			v.x = i; v.y = j;
			v.dist = MAXINT;
			pq.push(v);
		}
	}

	vertex v;
	v.x = 0; v.y = 0;
	v.dist = 0;
	pq.push(v);
	cost[0][0] = 0;
}

void solve()
{
	result = MAXINT;

	while (!pq.empty())
	{
		vertex cur = pq.top(); // get nearest vertex
		pq.pop();

		int x = cur.x;
		int y = cur.y;
		int dist = cur.dist;
		if (isGoal(x, y)) { break; }

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inRange(nx, ny))
			{
				int ndist = cost[nx][ny];
				int cmp = cost[x][y] + board[nx][ny];

				if ((ndist == -1) || (ndist > cmp))
				{
					cost[nx][ny] = cmp; // update distance
					vertex next;
					next.x = nx;
					next.y = ny;
					next.dist = cmp;
					pq.push(next);
				}
			}
		}
	}
	result = cost[N - 1][N - 1];

	clearPQ();
}

bool isGoal(int x, int y)
{
	return ((x == N - 1) && (y == N - 1));
}

bool inRange(int x, int y)
{
	if ((x >= 0) && (x < N))
	{
		if ((y >= 0) && (y < N))
		{
			return true;
		}
	}
	return false;
}

void clearPQ()
{
	while (!pq.empty()) { pq.pop(); }
}