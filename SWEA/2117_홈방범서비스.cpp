#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define MAXN 20
#define MAXM 10

void input();
void solve();
int getDist(int x, int y);

int N, M;
int H;
int hX[MAXN * MAXN];
int hY[MAXN * MAXN];
int dist[MAXN * 2 + 1];
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
	cin >> N >> M;

	int v;
	H = 0;
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> v;
			if (v == 1)
			{
				hX[H] = i;
				hY[H] = j;
				H++;
			}
		}
	}
}

void solve()
{
	result = 0;
	if (H == 1) { result = M - 1; return; }

	int maxR;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			maxR = getDist(i, j);
			int m = 0;
			for (int k = 1; k <= maxR + 1; k++)
			{
				m += dist[k - 1];
				int cost = M * m - (2 * k * k) + (2 * k) - 1;

				if (cost >= 0)
				{
					result = (result > m) ? result : m;
				}
			}
		}
	}
}

int getDist(int x, int y)
{
	memset(dist, 0, sizeof(int) * (2 * N + 1));

	int val;
	int maxV = 0;
	for (int i = 0; i < H; i++)
	{
		val = abs(x - hX[i]) + abs(y - hY[i]);
		dist[val]++;
		maxV = (maxV > val) ? maxV : val;
	}

	return maxV;
}