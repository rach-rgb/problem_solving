#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN (100000)

void input();
void solve();
void DFS(int cur, const vector<int> ary[]);
int count();

int N, M, X;
vector<int> source[MAXN+1]; // source[X] := vector of Ys s.t. Y->X
vector<int> target[MAXN+1]; // target[X] := vector of Ys s.t. X->Y
int U, V;
bool visited[MAXN+1];

int main()
{
	input();
	solve();
	cout << U << " " << V << endl;

	return 0;
}

void input() {
	cin >> N >> M >> X;

	for (int i = 0; i < M; i++)
	{
		int s, t;
		cin >> s >> t;
		source[t].push_back(s);
		target[s].push_back(t);
	}
}

void solve() {
	// get lowest rank
	memset(visited, false, N+1);
	DFS(X, target);
	V = N - count() + 1;

	// get highest rank
	memset(visited, false, N+1);
	DFS(X, source);
	U = count();
}

void DFS(int cur, const vector<int> ary[]) {
	if (visited[cur]) { return;  } // alreay visited
	visited[cur] = true;

	for (int i = 0; i < ary[cur].size(); i++)
	{
		int next = ary[cur][i];
		DFS(next, ary);
	}
}

int count() {
	int c = 0;
	for (int i = 1; i <= N; i++)
	{
		if (visited[i]) { c++; }
	}

	return c;
}