#include <iostream>
#include <cstring>
using namespace std;

#define MAXM 10
#define MAXN 12
#define INF 987654321

void input();
void solve();
int DP(int taken, int semester);
int bitCount(int target);

int N, K, M, L;
int pre[MAXN];
int lectures[MAXM];

int cache[MAXM][(1 << MAXN)];
int result;

int main()
{
	ios::sync_with_stdio(false);

	int C;
	cin >> C;
	for (int i = 0; i < C; i++)
	{
		input();
		solve();
		if (result == INF)
		{
			cout << "IMPOSSIBLE" << endl;
		}
		else
		{
			cout << result << endl;
		}
	}

	return 0;
}

void input()
{
	cin >> N >> K >> M >> L;

	int n, x;
	for (int i = 0; i < N; i++)
	{
		cin >> n;
		pre[i] = 0;
		for (int j = 0; j < n; j++)
		{
			cin >> x;
			pre[i] |= (1 << x);
		}
	}

	for (int i = 0; i < M; i++)
	{
		cin >> n;
		lectures[i] = 0;
		for (int j = 0; j < n; j++)
		{
			cin >> x;
			lectures[i] |= (1 << x);
		}
	}
}

void solve()
{
	// initialize as -1
	for (int i = 0; i < M; i++)
	{
		memset(cache + i, -1, sizeof(int) * (1 << N));
	}

	result = DP(0, 0);
}

int DP(int taken, int semester)
{
	if (bitCount(taken) >= K) { return 0; } // success
	if (semester >= M) { return INF; } // fail

	int& ret = cache[semester][taken];
	if (ret != -1) { return ret; }

	// else
	ret = INF;

	int candidate = lectures[semester] & (~taken);
	int tmp = candidate;
	for (int i = 0; i < N; i++)
	{
		// opened & prerequisites
		if (tmp % 2)
		{
			if ((pre[i] & taken) != pre[i])
			{
				candidate -= (1 << i);
			}
		}
		tmp /= 2;
	}

	// for all subset
	for (int sub = candidate; sub > 0; sub = (sub - 1) & candidate)
	{
		if (bitCount(sub) <= L)
		{
			int val = DP(taken | sub, semester + 1) + 1;
			ret = (ret < val) ? ret : val;
		}
	}

	// skip
	int val = DP(taken, semester + 1);
	ret = (ret < val) ? ret : val;

	return ret;
}

int bitCount(int target)
{
	if (target == 0) { return 0; }

	// else
	return (target % 2) + bitCount(target / 2);
}
