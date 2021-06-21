#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXM 100
#define MAXB 8

typedef struct _BC {
	int X = 0;
	int Y = 0;
	int C = 0;
	int P = 0;
	_BC(int ux, int uy, int uc, int up) : X(ux), Y(uy), C(uc), P(up) {}
	_BC() : X(0), Y(0), C(0), P(0) {}
} BC;

typedef struct _info
{
	int i1, i2;
	int P1, P2;
	_info(int ui1, int ui2, int uP1, int uP2) : i1(ui1), i2(ui2), P1(uP1), P2(uP2) {}
	_info() : i1(0), i2(0), P1(0), P2(0) {}
} info;

void input();
void solve();
bool compare(BC x, BC y);
info maxBC(int x, int y);
int dist(int x1, int y1, int x2, int y2);

int M, A;
BC charges[MAXB];
int moveA[MAXM];
int moveB[MAXM];

int dx[5] = { 0, 0, +1, 0, -1 };
int dy[5] = { 0, -1, 0, +1, 0 };
info possInfo;

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
	cin >> M >> A;

	// A
	for (int i = 0; i < M; i++)
	{
		cin >> moveA[i];
	}

	// B
	for (int i = 0; i < M; i++)
	{
		cin >> moveB[i];
	}
	
	int ux, uy, uc, up;
	for (int i = 0; i < A; i++)
	{
		cin >> ux >> uy >> uc >> up;
		charges[i] = BC(ux, uy, uc, up);
	}

	sort(charges, charges + A, compare);
}

bool compare(BC x, BC y)
{
	if (x.P > y.P) { return true; }
	else { return false; }
}

void solve()
{
	result = 0;

	int t = 0;
	int x1 = 1, x2 = 10, y1 = 1, y2 = 10;
	do {
		info aInfo = maxBC(x1, y1);
		info bInfo = maxBC(x2, y2);

		if (aInfo.i1 == bInfo.i1) // duplicate
		{
			int val1 = aInfo.P1;
			int val2 = aInfo.P1 + bInfo.P2;
			int val3 = aInfo.P2 + bInfo.P1;

			int val = (val1 > val2) ? val1 : val2;
			val = (val > val3) ? val : val3;

			result += val;
		}
		else
		{
			result += aInfo.P1;
			result += bInfo.P1;
		}

		if (t >= M) { break; }

		x1 = x1 + dx[moveA[t]];
		y1 = y1 + dy[moveA[t]];
		x2 = x2 + dx[moveB[t]];
		y2 = y2 + dy[moveB[t]];
		t++;

	} while (t <= M);
}

int dist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

info maxBC(int x, int y)
{
	int i1 = -1, i2 = -1;

	for (int i = 0; i < A; i++)
	{
		BC b = charges[i];
		if (dist(x, y, b.X, b.Y) <= b.C)
		{
			if (i1 == -1) { i1 = i; continue; }
			else if (i2 == -1) { i2 = i; break; }
		}
	}

	if (i1 == -1)
	{
		possInfo = info(-1, -1, 0, 0);
	}
	else if (i2 == -1)
	{
		possInfo = info(i1, -1, charges[i1].P, 0);
	}
	else
	{
		possInfo = info(i1, i2, charges[i1].P, charges[i2].P);
	}

	return possInfo;
}