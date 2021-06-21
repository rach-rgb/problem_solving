#include <iostream>
#include <vector>
using namespace std;

void input();
void solve();
vector<int> DFS(vector<int> pre, vector<int> in);

int N;
vector<int> pre;
vector<int> in;
vector<int> post;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		input();
		solve();
		for (int i = 0; i < N; i++)
		{
			cout << post[i] << " ";
		}
		cout << endl;
	}

	return 0;
}

void input()
{
	cin >> N;

	pre.clear(); pre.resize(N);
	in.clear(); in.resize(N);

	for (int i = 0; i < N; i++) { cin >> pre[i]; }
	for (int i = 0; i < N; i++) { cin >> in[i]; }
}

void solve()
{
	post = DFS(pre, in);
}

vector<int> DFS(vector<int> pre, vector<int> in)
{
	// base
	if (pre.size() == 0) { return pre; } // return empty vector
	else if (pre.size() == 1) { return pre; } // return itself


	// else
	int sizeL, sizeR;
	int root = pre[0], ridx;
	
	// find ridx
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == root) { ridx = i; break; }
	}

	sizeL = ridx;
	sizeR = in.size() - sizeL - 1;
	
	vector<int> preL(pre.begin() + 1, pre.begin() + 1 + sizeL);
	vector<int> preR(pre.begin() + 1 + sizeL, pre.end());
	vector<int> inL(in.begin(), in.begin() + sizeL);
	vector<int> inR(in.begin() + sizeL + 1, in.end());

	vector<int> postL = DFS(preL, inL);
	vector<int> postR = DFS(preR, inR);
	
	vector<int> result; result.reserve(postL.size() + postR.size() + 1);
	result.insert(result.end(), postL.begin(), postL.end());
	result.insert(result.end(), postR.begin(), postR.end());
	result.push_back(root);

	return result;
}