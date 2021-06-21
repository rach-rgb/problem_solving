#include <iostream>
#include <queue>
using namespace std;

#define MAXN 1000

typedef struct _edge
{
	int src;
	int dest;
	long long dist;
} edge;

struct compare
{
	bool operator()(edge x, edge y)
	{
		return (x.dist > y.dist);
	}
};

void input();
void solve();
long long cost(int i, int j);
void store_edges();
void merge(int x, int y);
int find_parent(int i);
void make_set(int i);

int N;
double E; // tax rate
int X[MAXN]; // x coordinates
int Y[MAXN]; // y coordinates
int parent[MAXN];
int rankV[MAXN];
long long result;
priority_queue<edge, vector<edge>, compare> pq;

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
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> X[i];
	}
	for (int i = 0; i < N; i++)
	{
		cin >> Y[i];
	}
	cin >> E;
}

void solve()
{
	result = 0;

	store_edges();

	for (int i = 0; i < N; i++)
	{
		make_set(i);
	}

	while (!pq.empty())
	{
		edge e = pq.top();
		pq.pop();

		int x = e.src;
		int y = e.dest;
		long long len = e.dist;

		int px = find_parent(x);
		int py = find_parent(y);

		if (px != py)
		{
			merge(px, py);
			result += len;
		}
	}

	// tax rate
	result = result * E + 0.5;
}

// store all edges to pq
void store_edges()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			edge e;
			e.src = i;
			e.dest = j;
			e.dist = cost(i, j);
			if (e.dist < 0) { cout << e.dist << endl; cout << X[i] << " " << X[j] << " " << Y[i] << " " << Y[j] << endl; }
			pq.push(e);
		}
	}
}

// distance between Vi and Vj
long long cost(int i, int j)
{
	long long dx = X[i] - X[j];
	long long dy = Y[i] - Y[j];
	return dx * dx + dy * dy;
}

// make set with one element i
void make_set(int i)
{
	rankV[i] = 0;
	parent[i] = i; // itself
}

// find parent of i with path compression
int find_parent(int i)
{
	if (parent[i] != i) { parent[i] = find_parent(parent[i]); }

	return parent[i];
}

// make union with x and y
void merge(int x, int y)
{
	int parX = find_parent(x);
	int parY = find_parent(y);

	if (parX == parY) { return; } // already merged

	if (rankV[parX] > rankV[parY])
	{
		parent[parY] = parX;
	}
	else if (rankV[parX] < rankV[parY])
	{
		parent[parX] = parY;
	}
	else // same rank
	{
		parent[parY] = parX;
		rankV[parX]++;
	}
}


