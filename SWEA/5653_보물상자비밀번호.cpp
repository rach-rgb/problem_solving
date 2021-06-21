#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 28
#define val(p) ((p<0)? numbers[N+p] : numbers[p])

void input();
void solve();

short N, K;
char numbers[MAXN];

string values[MAXN];

unsigned long long result;

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
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> numbers[i];
	}
}

void solve()
{
	result = 0;

	int len = N / 4;
	for (int i = 0; i > (-1) * len; i--)
	{
		values[(-4) * i] = "";
		values[(-4) * i + 1] = "";
		values[(-4) * i + 2] = "";
		values[(-4) * i + 3] = "";

		// first
		for (int j = 0; j < len; j++)
		{
			values[(-4) * i].push_back(val(i + j));
		}

		// second
		for (int j = 0; j < len; j++)
		{
			values[(-4) * i + 1].push_back(val(i + j + len));
		}
		// first
		for (int j = 0; j < len; j++)
		{
			values[(-4) * i + 2].push_back(val(i + j + len * 2));
		}
		// first
		for (int j = 0; j < len; j++)
		{
			values[(-4) * i + 3].push_back(val(i + j + len * 3));
		}
	}

	sort(values, values + N, greater<string>());

	string select;
	int count = 1;
	int i = 0;
	for (i = 1; (i < N) && (count < K); i++)
	{
		if (values[i - 1] != values[i]) { count++; }
	}

	select = values[i-1];

	// convert
	int sz = select.size();
	for (int i = 0; i < sz; i++)
	{
		int v;
		char c = select[i];
		if (c - 'A' >= 0) { v = c - 'A' + 10; }
		else { v = c - '0'; }

		result += ((unsigned long long)v) * pow(16, sz - i - 1);
	}
}