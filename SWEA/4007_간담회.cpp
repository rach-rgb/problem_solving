// 19개 중 0개, 제한시간 초과
#include <stdio.h>
#include <queue>
using namespace std;

#define MAXN 50000
#define MAXM 500000
#define MAXINT 987654321

struct compare
{
	bool operator()(pair<int, int> x, pair<int, int> y)
	{
		return x.second > y.second;
	}
};

void input();
void solve();
void dijkstra(int start);
void r_dijkstra(int start);

int N, M, X;
vector<pair<int, int>> edges[MAXN+1]; // edges[s]=(e, t) // (dest, cost)
vector<pair<int, int>> r_edges[MAXN + 1]; // edges[e]=(s, t)
priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq; // (index, distance)
int dist[MAXN+1];
int depart[MAXN+1];
bool visited[MAXN + 1];
int result;

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		input();
		solve();
		printf("#%d %d\n", i, result);
	}

	return 0;
}

void input()
{
	edges->clear();
	r_edges->clear();

	scanf("%d %d %d", &N, &M, &X);
	for (int i = 0; i < M; i++)
	{
		int s, e, t;
		scanf("%d %d %d", &s, &e, &t);
		edges[s].push_back(make_pair(e, t));
		r_edges[e].push_back(make_pair(s, t));
	}
}

void solve()
{
	result = 0;

	r_dijkstra(X);

	dijkstra(X);
	for (int i = 1; i <= N; i++)
	{
		if ((depart[i] == MAXINT) || (dist[i] == MAXINT)) { continue; }
		depart[i] += dist[i];
		result = (result > depart[i]) ? result : depart[i];
	}
}

void dijkstra(int start)
{
	// init pq
	for (int i = 1; i <= N; i++)
	{
		if (start == i) { dist[i] = 0; }
		else { dist[i] = MAXINT; }
		pq.push(make_pair(i, dist[i]));
	}

	//for (int i = 1; i <= N; i++) { visited[i] = false; }

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top();
		pq.pop();

		if (!visited[cur.first]) { continue; }
		visited[cur.first] = false;

		// else
		int cur_dist = cur.second;
		for (int i = 0; i < edges[cur.first].size(); i++)
		{
			pair<int, int> next = edges[cur.first][i];
			if (!visited[next.first]) { continue; }
			if (dist[next.first] > cur_dist + next.second) // need update
			{
				dist[next.first] = cur_dist + next.second;
				pq.push(make_pair(next.first, dist[next.first]));
			}
		}
	}

	while (!pq.empty()) { pq.pop(); }
}

void r_dijkstra(int start)
{
	// init pq
	for (int i = 1; i <= N; i++)
	{
		if (start == i) { depart[i] = 0; }
		else { depart[i] = MAXINT; }
		pq.push(make_pair(i, depart[i]));
	}

	//for (int i = 1; i <= N; i++) { visited[i] = false; }

	while (!pq.empty())
	{
		pair<int, int> cur = pq.top();
		pq.pop();

		if (visited[cur.first]) { continue; }
		visited[cur.first] = true;

		// else
		int cur_dist = cur.second;
		for (int i = 0; i < r_edges[cur.first].size(); i++)
		{
			pair<int, int> next = r_edges[cur.first][i];
			if (visited[next.first]) { continue; }
			if (depart[next.first] > cur_dist + next.second) // need update
			{
				depart[next.first] = cur_dist + next.second;
				pq.push(make_pair(next.first, depart[next.first]));
			}
		}
	}

	while (!pq.empty()) { pq.pop(); }
}