#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 100

typedef struct _wall {
	short x;
	short y;
	short r;
	vector<int> adjs; // adjs[0] = parent
} wall;

struct mycmp {
	bool operator()(wall w1, wall w2)
	{
		return (w1.r > w2.r);
	}
};

void input();
void solve();
void construct();
int DFS(int cur, int x);
bool isInside(int i, int j);
int getHeight(int x);

int N;
wall walls[MAXN];
int height[MAXN];
int result;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
		cout << result << endl;
	}

	return 0;
}

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> walls[i].x >> walls[i].y >> walls[i].r;
		walls[i].adjs.clear();
	}
	sort(walls, walls + N, mycmp()); // sort by radius
}

void solve()
{
	result = 0;

	construct(); // construct tree
	memset(height, -1, sizeof(int) * N);

	for (int i = 0; i < N; i++)
	{
		if (walls[i].adjs.size() == 1) { continue; }

		// else
		int v1 = -1, v2 = -1;
		int v;

		for (int j = 1; j < walls[i].adjs.size(); j++)
		{
			int c = walls[i].adjs[j], h = getHeight(c);

			if (h > v1) { v2 = v1; v1 = h; }
			else if (h > v2) { v2 = h; }
		}

		if ((v1 != -1) && (v2 == -1))
		{
			v = v1 + 1;
		}
		else if((v1!=-1)&&(v2!=-1))
		{
			v = v1 + v2 + 2;
		}
		else
		{
			v = 0;
		}

		result = (result > v) ? result : v;
	}

}

// construct tree
void construct()
{
	walls[0].adjs.push_back(-1); // dummy

	for (int i = 1; i < N; i++)
	{
		// visit nodes by postorder
		int loc = DFS(0, i);

		walls[loc].adjs.push_back(i);
		walls[i].adjs.push_back(loc);
	}
}

// cur: index of current node, x: new node to insert
int DFS(int cur, int x)
{
	// visit child nodes
	for (int i = 1; i < walls[cur].adjs.size(); i++)
	{
		int c = walls[cur].adjs[i];

		int ret = DFS(c, x);
		if (ret != -1) { return ret; } // find location
	}

	// check current node
	if (isInside(cur, x)) // walls[cur] contains walls[x]
	{
		return cur;
	}
	else // walls[cur] doesn't contain walls[x]
	{
		return -1;
	}
}

// check whether walls[i] includes walls[j]
bool isInside(int i, int j)
{
	if (walls[i].r <= walls[j].r){ return false; }

	int dist = pow(walls[i].x - walls[j].x, 2) + pow(walls[i].y - walls[j].y, 2);

	if (dist < pow(walls[i].r - walls[j].r, 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int getHeight(int x)
{
	int& ret = height[x];
	if (ret != -1) { return ret; }

	// else
	if (walls[x].adjs.size() == 1) // no child
	{
		ret = 0;
	}
	else
	{
		for (int i = 1; i < walls[x].adjs.size(); i++)
		{
			int c = walls[x].adjs[i], h = getHeight(c);

			ret = (ret > h + 1) ? ret : h + 1;
		}
	}

	return ret;
}