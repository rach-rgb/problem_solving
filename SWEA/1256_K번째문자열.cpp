#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define MAXK 400

void solve();

string input;
string output;
int K;
string substrs[MAXK * MAXK];

int main(void)
{
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		cin >> K >> input;
		solve();
		cout << "#" << i << " " << output << endl;
	}
}

void solve()
{
	int N = input.length();

	int n = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			string sub = input.substr(i, j - i + 1);
			substrs[n] = sub;
			n++;
		}
	}
	if (K > n) { output = "none"; return; }

	sort(substrs, substrs + n);

	if (K == 1) {
		output = substrs[0]; return;
	}

	int cur = 1, i = 1;
	for (i; (i < n) && (cur < K); i++)
	{
		if (substrs[i - 1] != substrs[i])
		{
			cur++;
		}
	}

	if (cur >= K) { output = substrs[i-1]; }
	else { output = "none"; }
}