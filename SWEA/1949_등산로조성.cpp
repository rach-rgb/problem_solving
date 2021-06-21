#include <iostream>
#include <vector>
using namespace std;

#define MAXN 8
#define MAXH 5

void input();
void solve();
bool inRange(int x, int y);
void DFS(int x, int y, bool use, int len, int curH, vector<bool> visited);

int N, K;
int H; // # of highest hill
short board[MAXN][MAXN];
int hx[MAXH]; // coords of highes hill
int hy[MAXH];
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
	cin >> N >> K;

	H = 0;
	int h;
	int maxH = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> h;
			board[i][j] = h;

			if (h > maxH)
			{
				H = 1;
				maxH = h;
				hx[0] = i;
				hy[0] = j;
			}
			else if (h == maxH)
			{
				hx[H] = i;
				hy[H] = j;
				H++;
			}

		}
	}
}

void solve()
{
	result = 0;
	vector<bool> visited(N*N, false);

	int top = board[hx[0]][hy[0]];

	for (int i = 0; i < H; i++)
	{
		vector<bool> nvisit = visited;
		nvisit[N * hx[i] + hy[i]] = true;
		DFS(hx[i], hy[i], false, 1, top, nvisit);
	}
}

void DFS(int x, int y, bool use, int len, int curH, vector<bool> visited)
{
	// for adj hills
	for (int i = 0; i < 4; i++)
	{
		int nX = x + dx[i];
		int nY = y + dy[i];

		if ((!inRange(nX, nY))||(visited[nX * N + nY])) { continue; }

		// else
		int nH = board[nX][nY];
		if (nH < curH)
		{
			vector<bool> nVisited = visited;
			nVisited[N * nX + nY] = true;
			DFS(nX, nY, use, len + 1, nH, nVisited);
		}
		else if ((!use) && (nH - K < curH))
		{
			vector<bool> nVisited = visited;
			nVisited[N * nX + nY] = true;
			DFS(nX, nY, true, len + 1, curH-1, nVisited);
		}
	}

	if (len > result) { result = len; }
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