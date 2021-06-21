#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 1000
#define MAXINT 987654321

void input();
void solve();
void BFS(int start);

int N;
int adj[MAXN][MAXN];
int result;
int cresult;
bool visited[MAXN];
int dist[MAXN];
queue<int> q;

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
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> adj[i][j];
		}
	}
}

void solve()
{
	result = MAXINT;

	for (int i = 0; i < N; i++)
	{
		memset(visited, false, N);
		cresult = 0;
		BFS(i);

		result = (cresult < result) ? cresult : result;
	}
}

void BFS(int start)
{
	cresult = 0;
	visited[start] = true;
	dist[start] = 0;
	q.push(start);

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int i = 0; i < N; i++)
		{
			if ((adj[cur][i] == 1) && (!visited[i]))
			{
				q.push(i);
				visited[i] = true;
				dist[i] = dist[cur] + 1;
				cresult += dist[i]; // add up distance earlier
			}
		}

		if (cresult > result) { break; }
	}

	// make sure queue is empy
	while (!q.empty())
	{
		q.pop();
	}
}