#include <iostream>
#include <cstring>
using namespace std;

#define MAXV 10000

void input();
void solve();
int sibling(int cur);
void DFS(int cur, int target);

int V, E; // V start from 1
int X, Y; // two vertex
int result_parent;
int result;
int parent[MAXV + 1]; //parent[x] = y => edge y->x
int children[MAXV + 1][2]; //children[x] = [y, z] =>edge x->y, x->z
int size;
bool isFind;

int main()
{
	int T;
	cin >> T;

	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		cout << "#" << i << " " << result_parent << " " << result << endl;
	}

	return 0;
}

void input()
{
	cin >> V >> E;
	cin >> X >> Y;

	// children[x] = [y, 0] => edge x->y
	memset(children[0], 0, sizeof(int) * (V + 1));
	memset(children[1], 0, sizeof(int) * (V + 1));

	for (int i = 0; i < E; i++)
	{
		int par, chil;
		cin >> par >> chil;

		// store info
		parent[chil] = par;
		if (children[par][0] == 0) { children[par][0] = chil; }
		else { children[par][1] = chil; }
	}
}

void solve()
{
	int size_X, size_Y;
	result = 0;

	int cur = X;
	int sib;

	isFind = false;

	do
	{
		sib = sibling(cur);

		if (cur == 1) { break; } // root
		else if (sib == 0) { cur = parent[cur]; continue; } // no sibling

		// not root, has sibling
		cur = parent[cur];
		size = 0; isFind = false;
		DFS(sib, Y);
	} while (!isFind);

	if (cur == 1) // root
	{
		result_parent = 1;
		result = V;
	}
	else // not root & find is true
	{
		size_Y = size;
		size = 0;
		DFS(sibling(sib), 0);
		size_X = size;

		result_parent = cur;
		result = size_X + size_Y + 1;
	}
}

// return true if target is found
// increment size for each visit
void DFS(int cur, int target)
{
	size++;
	if (cur == target) { isFind = true; }

	// else
	int child1 = children[cur][0];
	int child2 = children[cur][1];

	if (child1 != 0) { DFS(child1, target); }
	if (child2 != 0) { DFS(child2, target); }

	return;
}

// return sibling
int sibling(int cur)
{
	if (cur == 1) { return 0; } // root
	else
	{
		int par = parent[cur];

		if (cur == children[par][1]) { return children[par][0]; }
		else { return children[par][1]; }
	}
}