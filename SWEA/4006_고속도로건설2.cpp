// Kruskal Algorithm
#include <iostream>
#include <queue>
using namespace std;

#define MAXN 50000

typedef struct _edge {
	int a;
	int b;
	int cost;
	_edge(int ua, int ub, int uc) : a(ua), b(ub), cost(uc) {}
} edge;

struct compare {
	bool operator()(edge x, edge y)
	{
		return (x.cost > y.cost);
	}
};

void input();
void solve();
void make_set(int i);
void make_union(int i, int j);
int find_parent(int i);

int N, M;
priority_queue<edge, vector<edge>, compare> pq;
int parent[MAXN + 1];
int rankV[MAXN + 1];
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
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int s, e, c;
		cin >> s >> e >> c;
		edge ed(s, e, c);
		pq.push(ed);
	}
}

void solve()
{
	result = 0;
	int count = 1;

	for (int i = 1; i <= N; i++)
	{
		make_set(i);
	}

	while ((!pq.empty()) && (count <= N))
	{
		edge cur = pq.top();
		pq.pop();

		int x = cur.a;
		int y = cur.b;
		if (find_parent(x) != find_parent(y)) // use edge
		{
			result += cur.cost;
			make_union(x, y);
			count++;
		}
	}

	while (!pq.empty()) { pq.pop(); }
}

void make_set(int i)
{
	parent[i] = i;
	rankV[i] = 0;
}

void make_union(int i, int j)
{
	int pi = find_parent(i);
	int pj = find_parent(j);

	if (pi != pj) // merge
	{
		if (rankV[pi] > rankV[pj])
		{
			parent[pj] = pi;
		}
		else if (rankV[pi] < rankV[pj])
		{
			parent[pi] = pj;
		}
		else // same rank
		{
			parent[pj] = pi;
			rankV[pi]++;
		}
	}
}

int find_parent(int i)
{
	int p = parent[i];

	if (p != parent[p])
	{
		parent[i] = find_parent(p);
	}

	return parent[i];
}