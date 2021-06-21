#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define ALPH (26)
#define MAXN (1000)

int toInt(char c);
void input();
void solve();
void DFS(int x);

int N;
string words[MAXN];
bool adj[ALPH][ALPH]; // adj[x][y]: directed edge x->y
bool visited[ALPH];
bool success;
vector<int> answ;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
		if (success)
		{
			for (int j = 0; j < ALPH; j++)
			{
				cout << (char)(answ[j] + 'A');
			}
			cout << endl;
		}
		else { cout << "INVALID HYPOTHESIS" << endl; }
	}

	return 0;
}

void input()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> words[i];
	}

	for (int i = 0; i < ALPH; i++)
	{
		memset(adj+i, false, sizeof(bool)*ALPH);
	}

	memset(visited, false, sizeof(bool) * ALPH);
}
void solve()
{
	success = true;
	answ.clear();

	// construct graph
	for (int i = 1; i < N; i++)
	{
		int j = i - 1;
		int len = min(words[i].size(), words[j].size());
		bool diff = false;
		for (int k = 0; k < len; k++)
		{
			if (words[i][k] != words[j][k]) {
				int a = toInt(words[i][k]);
				int b = toInt(words[j][k]);
				adj[b][a] = true;
				diff = true;
				break;
			}
		}

		if ((!diff) & (words[i].size() < words[j].size())) { success = false; return; }
	}

	for (int i = 0; i < ALPH; i++)
	{
		if (!visited[i]) { DFS(i); }
	}

	reverse(answ.begin(), answ.end());

	// check cycle
	for (int i = 0; i < ALPH; i++)
	{
		for (int j = i + 1; j < ALPH; j++)
		{
			if (adj[answ[j]][answ[i]])
			{
				success = false;
				return;
			}
		}
	}
}

void DFS(int x)
{
	visited[x] = true;

	for (int i = 0; i < ALPH; i++)
	{
		if (adj[x][i]&&(!visited[i])) // outgoing edge
		{
			DFS(i);
		}
	}
	answ.push_back(x);
}

int toInt(char c)
{
	return c - 'a';
}