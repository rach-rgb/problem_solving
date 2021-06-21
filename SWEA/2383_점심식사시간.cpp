#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 10
#define MAXINT 987654321

void input();
void solve();
int stair1(int cur);
int stair2(int cur);

int N, K1, K2, P;
int time1[MAXN + 1]; // time for stair 1
int time2[MAXN + 1]; // time for stair 2
int result;
int t1[MAXN]; // people who use stair1
int t2[MAXN]; // people who use stair2
int t[MAXN]; // DP cache
int nt1 = 0, nt2 = 0; // # of people who use stair1, # of people who use stair2

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

	int v;
	int pX[MAXN];
	int pY[MAXN];
	int n = 0;
	int s1X, s1Y, s2X, s2Y;
	int s = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> v;

			if (v == 1)
			{
				pX[n] = i;
				pY[n] = j;
				n++;
			}
			else if (v >= 2)
			{
				if (s == 0)
				{
					K1 = v;
					s1X = i; s1Y = j;
					s++;
				}
				else if(s==1)
				{
					K2 = v;
					s2X = i; s2Y = j;
					s++;
				}
			}
		}
	}

	// calculate distance
	for (int i = 0; i < n; i++)
	{
		time1[i] = abs(pX[i] - s1X) + abs(pY[i] - s1Y);
		time2[i] = abs(pX[i] - s2X) + abs(pY[i] - s2Y);
	}

	P = n;
}

void solve()
{
	result = MAXINT;

	unsigned int mask; // people who use stair 1
	int cost1, cost2;
	for (mask = 0; mask < (1 << P); mask++)
	{
		cost1 = 0;
		cost2 = 0;
		nt1 = 0, nt2 = 0;

		int tmp = mask;
		for (int i = 0; i < P; i++)
		{
			if (tmp % 2 == 1) // use stair 1
			{
				t1[nt1] = time1[i];
				nt1++;
			}
			else // use stair 2
			{
				t2[nt2] = time2[i];
				nt2++;
			}
			tmp /= 2;
		}
		
		// for stair 1
		if (nt1 > 0)
		{
			sort(t1, t1 + nt1);

			// base value
			for (int i = 0; (i < 3) && (i < nt1); i++)
			{
				t[i] = t1[i] + 1 + K1;
			}

			if (nt1 <= 3) { cost1 = t[nt1 - 1]; }
			else {
				memset(t, -1, sizeof(int) * nt1);
				cost1 = stair1(nt1 - 1); // DP
			}

			if (result < cost1) { continue; }
		}

		// for stair 2
		if (nt2 > 0)
		{
			sort(t2, t2 + nt2);

			for (int i = 0; (i < 3) && (i < nt2); i++)
			{
				t[i] = t2[i] + 1 + K2;
			}

			if (nt2 <= 3) { cost2 = t[nt2 - 1]; }
			else { 
				memset(t, -1, sizeof(int) * nt2);
				cost2 = stair2(nt2 - 1); // DP
			}

			if (result < cost1) { continue; }
		}

		int cost = (cost1 > cost2) ? cost1 : cost2;
		result = (result < cost) ? result : cost;
	}

}

int stair1(int cur)
{
	int ret = t[cur];
	if (ret != -1) { return ret; }

	// else
	int prev = stair1(cur - 3);
	if (prev <= t1[cur]) { ret = t1[cur] + 1 + K1; } // doesn't have to wait cur-3
	else // need to wait cur-3
	{
		ret = prev + K1;
	}

	t[cur] = ret;

	return ret;
}

int stair2(int cur)
{
	int ret = t[cur];
	if (ret != -1) { return ret; }

	// else
	int prev = stair2(cur - 3);
	if (prev <= t2[cur]) { ret = t2[cur] + 1 + K2; } // doesn't have to wait cur-3
	else // need to wait cur-3
	{
		ret = prev + K2;
	}

	t[cur] = ret;

	return ret;
}