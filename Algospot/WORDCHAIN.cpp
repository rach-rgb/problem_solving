#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN (100)
#define ALP (26)

int N;
int adj[ALP][ALP]; // adj[i][j] := # of edges between i and j
vector<string> graph[ALP][ALP]; // graph[i][j] := vector of string s s.t. s[0] = i and s[-1] = j
int indegree[ALP];
int outdegree[ALP];

void input()
{
	cin >> N;

	// initialize
	for (int i = 0; i < ALP; i++)
	{
		for (int j = 0; j < ALP; j++)
		{
			graph[i][j].clear();
		}
	}

	for (int i = 0; i < ALP; i++)
	{
		for (int j = 0; j < ALP; j++) { adj[i][j] = 0; }
	}

	for (int i = 0; i < ALP; i++) { indegree[i] = 0; }
	for (int i = 0; i < ALP; i++) { outdegree[i] = 0; }

	for (int i = 0; i < N; i++)
	{
		string str;
		cin >> str;
		int s = str[0] - 'a', e = str[str.size() - 1] - 'a';

		adj[s][e]++;
		graph[s][e].push_back(str);
		indegree[e]++;
		outdegree[s]++;
	}
}

bool exist()
{
	int plus1 = 0, minus1 = 0;

	for(int i = 0; i < ALP; i++)
	{ 
		int diff = outdegree[i] - indegree[i];

		if (diff == 1) { plus1++; }
		else if (diff == -1) { minus1++; }
		else if ((diff > 1) || (diff < -1)) { return false; }
	}

	return ((plus1 == 1) && (minus1 == 1)) || ((plus1 == 0) && (minus1 == 0));
}

void getEulerCircuit(int x, vector<int>& circuit) {
	for (int i = 0; i < ALP; i++)
	{
		if (adj[x][i] > 0)
		{
			adj[x][i]--;
			getEulerCircuit(i, circuit);
		}
	}

	circuit.push_back(x);
}

vector<int> getEuler() {
	vector<int> circuit;

	// trail
	for (int i = 0; i < ALP; i++)
	{
		if (outdegree[i] == indegree[i] + 1)
		{
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}

	// circuit
	for (int i = 0; i < ALP; i++)
	{
		if (outdegree[i] > 0)
		{
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
}

void solve()
{
	if (!exist()) { cout << "IMPOSSIBLE" << endl; return; }

	vector<int> circuit = getEuler();
	if(circuit.size()-1 != N){ cout << "IMPOSSIBLE" << endl; return; }

	reverse(circuit.begin(), circuit.end());

	for (int i = 1; i < circuit.size(); i++)
	{
		int s = circuit[i - 1], e = circuit[i];
		string str = graph[s][e].back();
		graph[s][e].pop_back();
		cout << str << " ";
	}
	cout << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
	}

	return 0;
}