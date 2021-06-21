#include <iostream>
using namespace std;

#define MAXN 20
typedef struct _info {
	int h;
	int count;
} info;

void input();
void solve();
bool build();

int N, X;
int board[MAXN][MAXN];

int heights[MAXN];

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
	cin >> N >> X;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}
}

void solve()
{
	result = 0;

	
	// horizontal
	// cout << "hor" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			heights[j] = board[i][j];
		}
		if (build()) { result++; }
	}

	// vertical
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			heights[j] = board[j][i];
		}
		if (build()) { result++; }
	}
}

bool build()
{
	info infos[MAXN];

	int in = 0;
	infos[0].h = heights[0];
	infos[0].count = 1;

	// collect informations
	for (int i = 1; i < N; i++)
	{
		if (infos[in].h == heights[i])
		{
			infos[in].count++;
		}
		else
		{
			in++;
			infos[in].h = heights[i];
			infos[in].count = 1;
		}
	}
	in++;

	if (in == 1) { return true; }
	
	for (int j = 1; j < in; j++)
	{
		if (infos[j - 1].h == infos[j].h - 1) // <
		{
			if (infos[j - 1].count < X)
			{
				return false;
			}
		}
		else if(infos[j - 1].h == infos[j].h + 1) // >
		{
			if (infos[j].count < X)
			{
				return false;
			}
			else
			{
				infos[j].count -= X;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}