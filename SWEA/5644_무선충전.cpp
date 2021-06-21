#include <iostream>
#include <cstdlib>
using namespace std;

#define MAXM 100
#define MAXA 8

typedef struct _info {
	short x;
	short y;
	short C; // range
	short P; // performance
} info;

typedef struct _coords {
	short x;
	short y;
} coords;

void input();
void solve();
void update(int pick, bool user);
bool inRange(coords user, info BC);
coords nextPos(coords user, short dir);

int M, A;
short path[2][MAXM]; // path[0]: A, path[1]: B
info infos[MAXA];
int result;

short a_high, a_low, b_high, b_low;

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
}

void input()
{
	cin >> M >> A;

	for (int i = 0; i < M; i++)
	{
		cin >> path[0][i];
	}
	for (int i = 0; i < M; i++)
	{
		cin >> path[1][i];
	}

	for (int i = 0; i < A; i++)
	{
		cin >> infos[i].x >> infos[i].y >> infos[i].C >> infos[i].P;
	}
}

void solve()
{
	result = 0;

	coords a = { 1, 1 };
	coords b = { 10, 10 };

	for (int i = 0; i <= M; i++)
	{
		a_high = -1, a_low = -1;
		b_high = -1, b_low = -1;

		for (int j = 0; j < A; j++)
		{
			if (inRange(a, infos[j])) { update(j, 0); }
			if (inRange(b, infos[j])) { update(j, 1); }
		}

		if ((a_high == -1) || (b_high == -1))
		{
			if (a_high != -1) { result += infos[a_high].P; }
			if (b_high != -1) { result += infos[b_high].P; }
		}
		else if (a_high == b_high)
		{
			short case1, case2, case3;
			case1 = infos[a_high].P; // two user share BC
			case2 = infos[a_high].P + infos[b_low].P;
			case3 = infos[a_low].P + infos[b_high].P;

			int temp = (case1 > case2) ? case1 : case2;
			temp = (temp > case3) ? temp : case3;

			result += temp;
		}
		else
		{
			result += infos[a_high].P;
			result += infos[b_high].P;
		}

		if (i == M) { break;  } // no next move

		a = nextPos(a, path[0][i]);
		b = nextPos(b, path[1][i]);
	}
}

void update(int pick, bool user)
{
	if (!user) // a
	{
		if (a_high == -1) { a_high = pick; }
		else if (infos[a_high].P < infos[pick].P) { a_low = a_high; a_high = pick; }
		else if (a_low == -1) { a_low = pick; }
		else if (infos[a_low].P < infos[pick].P) { a_low = pick; }
	}
	else // b
	{
		if (b_high == -1) { b_high = pick; }
		else if (infos[b_high].P < infos[pick].P) { b_low = b_high; b_high = pick; }
		else if (b_low == -1) { b_low = pick; }
		else if (infos[b_low].P < infos[pick].P) { b_low = pick; }
	}
}

bool inRange(coords user, info BC)
{
	short x = BC.x, y = BC.y;

	short dist = abs(x - user.x) + abs(y - user.y);

	return (dist <= BC.C);
}

coords nextPos(coords user, short dir)
{
	coords new_coords;
	new_coords.x = user.x;
	new_coords.y = user.y;

	if (dir == 0) { return user;  }
	else if (dir == 1) { new_coords.y--; }
	else if (dir == 2) { new_coords.x++; }
	else if (dir == 3) { new_coords.y++; }
	else { new_coords.x--; }

	return new_coords;
}