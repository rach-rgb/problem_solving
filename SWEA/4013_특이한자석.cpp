#include <iostream>
using namespace std;

#define MAXK 20

void input();
void solve();
int left(int num);
int right(int num);
int answer();

int K;
int mag[5][8]; // magnetic information mag[1] ~ mag[4]
int rnum[MAXK];
int rdir[MAXK];

int top[5]; // magnetic tops

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
	cin >> K;

	
	for (int i = 1; i <= 4; i++)
	{
		top[i] = 0;
		for (int j = 0; j < 8; j++) {
			cin >> mag[i][j];
		}
	}

	for (int i = 0; i < K; i++)
	{
		cin >> rnum[i] >> rdir[i];
	}
}

void solve()
{
	result = 0;

	for (int i = 0; i < K; i++)
	{
		int mag = rnum[i];
		int dir = rdir[i];
		int rval = right(mag);
		int lval = left(mag);

		top[mag] -= dir;
		if (top[mag] == -1) { top[mag] = 7; }
		else if (top[mag] == 8) { top[mag] = 0; }

		int l = mag - 1;
		int ld = dir;
		while (l >= 1)
		{
			if (right(l) != lval) // rotate
			{
				lval = left(l);

				ld *= -1;
				top[l] -= ld;
				if (top[l] == -1) { top[l] = 7; }
				else if (top[l] == 8) { top[l] = 0; }

				l--;
			}
			else
			{
				break;
			}
		}

		int r = mag + 1;
		int rd = dir;
		while (r <= 4)
		{
			if (left(r) != rval) // rotate
			{
				rval = right(r);

				rd *= -1;
				top[r] -= rd;
				if (top[r] == -1) { top[r] = 7; }
				else if (top[r] == 8) { top[r] = 0; }

				r++;
			}
			else
			{
				break;
			}
		}
	}

	result = answer();
}

// give left side type of mag[num]
int left(int num)
{
	int idx = top[num] - 2;

	if (idx >= 0) { return mag[num][idx]; }
	else { return mag[num][idx + 8]; }
}

// give right side type
int right(int num)
{
	int idx = top[num] + 2;

	if (idx < 8) { return mag[num][idx]; }
	else { return mag[num][idx - 8]; }
}

int answer()
{
	int ret = 0;

	if (mag[1][top[1]] == 1) { ret += 1; }
	if (mag[2][top[2]] == 1) { ret += 2; }
	if (mag[3][top[3]] == 1) { ret += 4; }
	if (mag[4][top[4]] == 1) { ret += 8; }

	return ret;
}