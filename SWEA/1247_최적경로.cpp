#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define MAXN 10
#define MAXINT 987654321

void input();
void solve();
bool mycmp(pair<int, int> x, pair<int, int> y);
int dist(pair<int, int> x, pair<int, int> y);

int N;
pair<int, int> office;
pair<int, int> home;
pair<int, int> customers[MAXN];
int mim;
int result;

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

	cin >> office.first >> office.second >> home.first >> home.second;

	for (int i = 0; i < N; i++)
	{
		cin >> customers[i].first >> customers[i].second;
	}

	sort(customers, customers + N, mycmp);
}

bool mycmp(pair<int, int> x, pair<int, int> y)
{
	if (x.first < y.first) { return true; }
	else if (x.first == y.first) { return (x.second < y.second); }
	else return false;
}

void solve()
{
	mim = MAXINT;

	do
	{
		int cur = dist(office, customers[0]) + dist(home, customers[N - 1]);

		for (int i = 1; i < N; i++)
		{
			cur += dist(customers[i - 1], customers[i]);
			if (cur > mim) { break; }
		}

		mim = (cur < mim) ? cur : mim;
	} while (next_permutation(customers, customers + N, mycmp));

	result = mim;
}

int dist(pair<int, int> x, pair<int, int> y)
{
	return abs(x.first - y.first) + abs(x.second - y.second);
}