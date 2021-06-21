#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 10

void input();
void solve();
void resetAdj();
int findLongPath(int c, int dist);

int N, K, M;
bool adj[MAXN + 1][MAXN + 1];
int result[MAXN + 1];
bool visited[MAXN + 1];
int longPath;
int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " ";
		for (int j = 1; j <= N; j++)
		{
			cout << result[j] << " ";
		}
		cout << longPath << endl;
	}
	return 0;
}

void input()
{
	int src, dst;

	cin >> N >> K;
	resetAdj();
	for (int i = 0; i < K; i++)
	{
		cin >> M;
		cin >> src;
		for (int j = 1; j < M; j++)
		{
			cin >> dst;
			adj[src][dst] = true;
			src = dst;
		}
	}
}

void resetAdj()
{
	for (int i = 1; i <= N; i++)
	{
		memset(adj + i, false, N + 1);
	}
}

void solve()
{
	int p;
	longPath = 0;

	for (int i = 1; i <= N; i++)
	{
		result[i] = 0;
		for (int j = 1; j <= N; j++)
		{
			if (adj[i][j]) { result[i]++; }
		}
	}

	for (int i = 1; i <= N; i++)
	{
		memset(visited, false, N + 1);
		visited[i] = true;
		p = findLongPath(i, 1);
		longPath = (p > longPath) ? p : longPath;
	}
}

int findLongPath(int c, int dist)
{
	int ret = dist;

	for (int i = 1; i <= N; i++)
	{
		int newDist = -1;
		if (adj[c][i] && (!visited[i])) // if there's path
		{
			visited[i] = true;
			newDist = findLongPath(i, dist + 1);
			visited[i] = false;
		}
		ret = (ret > newDist) ? ret : newDist;
	}

	return ret;
}