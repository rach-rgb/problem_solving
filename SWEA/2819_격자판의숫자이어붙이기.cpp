#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define SIZEB 4
#define MAXN 10000000

void input();
void solve();
void count(int step, int x, int y, int* ary);
void mark(int* ary);
bool inRange(int x, int y);

short board[SIZEB][SIZEB];
bool check[MAXN];
int result;
int dx[4] = { -1, +1, 0, 0 };
int dy[4] = { 0, 0, -1, +1 };

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
		cout << result << endl;
	}
}

void input()
{
	for (int i = 0; i < SIZEB; i++)
	{
		for (int j = 0; j < SIZEB; j++)
		{
			cin >> board[i][j];
		}
	}

	memset(check, false, MAXN);
}

void solve()
{
	result = 0;

	int ary[7];
	for (int i = 0; i < SIZEB; i++)
	{
		for (int j = 0; j < SIZEB; j++)
		{
			count(6, i, j, ary);
		}
	}

	for (int i = 0; i < MAXN; i++)
	{
		if (check[i]) { result++; }
	}
}

void count(int step, int x, int y, int* ary)
{
	if (!inRange(x, y)) { return; }
	else if (step < 0) { mark(ary); return; }

	// else
	ary[step] = board[x][y];
	for (int i = 0; i < 4; i++)
	{
		count(step-1, x + dx[i], y + dy[i], ary);
	}
}

bool inRange(int x, int y)
{
	return (0 <= x) && (x < 4) && (0 <= y) && (y < 4);
}

void mark(int* ary)
{
	int val = 0;

	for (int i = 0; i < 7; i++)
	{
		val += ary[i] * pow(10, i);
	}

	check[val] = true;
}