#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define MAXN (1000000)

void input();
void solve();
void solve2();
int getRandom(int min, int max);

int N, R, M;
int loc[MAXN+1]; // location of robots
int result;
int dist[2 * MAXN];

int main() {
	srand(5323);

	for(int i=0; i<100; i++)
	{
		input();
		if (result == -1) { continue; }
		solve();
		int val1 = result;
		solve2();
		int val2 = result;
		if (val1 != val2)
		{
			cout << N << " " << R << " " << M << endl;
			for (int i = 0; i < N; i++)
			{
				cout << loc[i] << " ";
			}
			cout << endl;
			cout << val1 << " " << val2 << endl;
		}
	}

	return 0;
}

void input()
{
	N = getRandom(1, 100);
	R = getRandom(1, 100);
	M = getRandom(N, 2 * R * N);
	
	for (int i = 0; i < N; i++) {
		loc[i] = getRandom(0, M - 1);
	}

	sort(loc, loc + N);

	for (int i = 0; i < N-1; i++) {
		if (loc[i] == loc[i + 1]) { result = -1; }
	}
}

void solve2()
{
	//if (M <= 2 * R) { result = 0; return; } // one robot is sufficient

	// calculate maximum distance
	int max = 0, dist;
	for (int i = 0; i < N-1; i++)
	{
		dist = loc[i + 1] - loc[i];
		max = (max > dist) ? max : dist;
	}
	dist = M - loc[N - 1] + loc[0];

	max = (max > dist) ? max : dist;

	if (max <= 2 * R) { result = 0; return; } // robots already cover all area

	// calculate maximum distance of optimal case
	int opt = 2 * R;

	// get result
	result = (max - opt + 1) / 2;
}

void solve()
{
	loc[N] = loc[0] + M;
	
	for (int i = 0; i < N; i++)
	{
		dist[i] = dist[i + N] = loc[i + 1] - loc[i] - 2 * R;
	}

	int sum = 0, mxsum = 0;
	for (int i = 0; i < 2 * N - 1; i++) {
		sum += dist[i];
		if (sum < 0) { sum = 0; }
		mxsum = mxsum > sum ? mxsum : sum;
	}

	result = (mxsum + 1) / 2;
}

int getRandom(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);

	return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}