#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#define MAXN 500

void input();
void solve();

int N; // length of X, Y (assume two values are same)
string X, Y;
double result;
int dist[MAXN][MAXN]; // dist[i][j] := x[:i], y[:j]

int main()
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		printf("#%d %0.2f\n", i, result);
	}
	return 0;
}

void input()
{
	cin >> N;
	cin >> X >> Y;
}

void solve()
{
	result = 0;

	// init dist(0, *)
	bool flag = false;
	for (int j = 0; j < N; j++)
	{
		if (X[0] == Y[j]) { flag = true; }

		if (flag) { dist[0][j] = 1; }
		else { dist[0][j] = 0; }
	}

	// init dist(*, 0)
	flag = false;
	for (int i = 0; i < N; i++)
	{
		if (X[i] == Y[0]) { flag = true; }

		if (flag) { dist[i][0] = 1; }
		else { dist[i][0] = 0; }
	}

	// DP
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (X[i] == Y[j])
			{
				dist[i][j] = dist[i - 1][j - 1] + 1;
			}
			else
			{
				dist[i][j] = (dist[i - 1][j] > dist[i][j - 1]) ? dist[i - 1][j] : dist[i][j - 1];
			}
		}
	}
	result = dist[N - 1][N - 1];

	result = result * 100 / N;
}