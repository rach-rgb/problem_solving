#include <iostream>
#include <cstring>
using namespace std;

#define MAXD 13
#define MAXW 20
typedef struct _hist
{
	bool val;
	bool pass = false;
	int count = 0;
} hist;

void input();
void solve();
void DFS(int d, int k, hist* h);
bool satisfied(hist* h);

int D, W, K;
bool board[MAXD][MAXW]; // A = false, B = true
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
	cin >> D >> W >> K;

	for (int i = 0; i < D; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> board[i][j];
		}
	}
}

void solve()
{
	result = K;

	if (K == 1) { result = 0; return; }

	hist h[MAXW];
	DFS(-1, 0, h);
}

// read by layer d, use chance k times
void DFS(int d, int k, hist* h)
{
	if (k >= result) { return; } // exceed min value
	if (satisfied(h)) {
		result = (result < k) ? result : k;
		return;
	}
	if (d >= D - 1) { return; }

	// else
	// don't change
	hist v1[MAXW];
	memcpy(v1, h, sizeof(hist) * W);
	for (int i = 0; i < W; i++)
	{
		if (v1[i].pass) { continue; }

		bool val = board[d + 1][i];

		if (v1[i].count == 0) // for layer 0
		{
			v1[i].count = 1;
			v1[i].val = val;
		}
		else if (v1[i].val == val)
		{
			v1[i].count++;
		}
		else
		{
			v1[i].count = 1;
			v1[i].val = val;
		}
	}
	DFS(d + 1, k, v1);
	if (result == k) { return; }

	// change to A
	hist v2[MAXW];
	memcpy(v2, h, sizeof(hist) * (W));
	for (int i = 0; i < W; i++)
	{
		if (v2[i].pass) { continue; }

		if (v2[i].count == 0) // for layer 0
		{
			v2[i].count = 1;
			v2[i].val = false;
		}
		else if (v2[i].val == false)
		{
			v2[i].count++;
		}
		else // v2[i].val == true
		{
			v2[i].count = 1;
			v2[i].val = false;
		}
	}
	DFS(d + 1, k + 1, v2);
	if (result == k+1) { return; }

	// change to B
	hist v3[MAXW];
	memcpy(v3, h, sizeof(hist) * (W));
	for (int i = 0; i < W; i++)
	{
		if (v3[i].pass) { continue; }

		if (v3[i].count == 0) // for layer 0
		{
			v3[i].count = 1;
			v3[i].val = true;
		}
		else if (v3[i].val == true)
		{
			v3[i].count++;
		}
		else // v3[i].val == false
		{
			v3[i].count = 1;
			v3[i].val = true;
		}
	}
	DFS(d + 1, k + 1, v3);
}

bool satisfied(hist* h)
{
	bool ret = true;
	;
	for (int i = 0; i < W; i++)
	{
		if (h[i].pass) { continue; }
		else
		{
			if (h[i].count >= K) { h[i].pass = true; }
			else { ret = false; }
		}
	}

	return ret;
}