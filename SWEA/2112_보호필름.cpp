#include <iostream>
#include <cstring>
using namespace std;

#define MAXD 13
#define MAXW 20

typedef struct _info
{
	bool type = false; // A=false, B=true
	bool pass = false;
	short count = 0;
} info;

void input();
void solve();
bool isSatisfied(info* v);
void DFS(info* infos, short layer, short t);
bool needPrune(int t);

int D, W, K;
bool films[MAXD][MAXW];
int result;
int tmp;

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
	cin >> D >> W >> K;

	for (int i = 0; i < D; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> films[i][j];
		}
	}
}

void solve()
{
	result = K;

	if (K == 1) { result = 0; return; } // already satisfied

	info v[MAXW];
	DFS(v, -1, 0);
}

void DFS(info* infos, short layer, short t)
{
	needPrune(t);

	// test pass
	if (isSatisfied(infos)) { result = t; return; }

	// end of layer & fail test
	if (layer == D - 1) { return; }

	// can't pass even if every remaining layer is changed
	if (((D - layer) < K - t) && (tmp < t)) { return; }

	// else
	short nLayer = layer + 1;

	// case 1: no change
	info v1[MAXW];
	memcpy(v1, infos, sizeof(info) * W);
	for (int i = 0; i < W; i++)
	{
		if (films[nLayer][i] == v1[i].type) { v1[i].count++; }
		else { v1[i].type = !(v1[i].type); v1[i].count = 1; }
	}
	DFS(v1, nLayer, t);
	if (needPrune(t)) { return; }

	// case2 : change with 0
	info v2[MAXW];
	memcpy(v2, infos, sizeof(info) * W);
	for (int i = 0; i < W; i++)
	{
		if (v2[i].type == 0) { v2[i].count++; }
		else { v2[i].type = 0; v2[i].count = 1; }
	}
	DFS(v2, nLayer, t + 1);
	if (needPrune(t)) { return; }

	// case3 : change with 1
	info v3[MAXW];
	memcpy(v3, infos, sizeof(info) * W);
	for (int i = 0; i < W; i++)
	{
		if (v3[i].type == 1) { v3[i].count++; }
		else { v3[i].type = 1; v3[i].count = 1; }
	}
	DFS(v3, nLayer, t + 1);
}

// check if every vector is satisfied
bool isSatisfied(info* v)
{
	bool isPass = true;
	tmp = K;

	for (int i = 0; i < W; i++)
	{
		if (!v[i].pass)
		{
			if (v[i].count < K) {
				tmp = (tmp < v[i].count) ? tmp : v[i].count;
				isPass = false;
			}
			else { v[i].pass = true; }
		}
	}

	return isPass;
}

// compare with result
bool needPrune(int t)
{
	if (t >= result) { return true; } // already exceeds min value
	if (result == 1) { return true; } // no need to check further
	return false;
}