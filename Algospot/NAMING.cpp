#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

#define MAXS 400000

void solve();

string s;
int f[MAXS]; // f[x] = y: longest suffix for [0:x] is length y
vector<int> result;

int main(void)
{
	ios::sync_with_stdio(false);

	string s1, s2;
	cin >> s1 >> s2;
	s = s1 + s2;
	solve();
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[result.size() - i - 1] << " ";
	}
	cout << endl;
	
	return 0;
}

void solve()
{
	int begin = 1, matched = 0;
	result.clear();

	memset(f, 0, sizeof(int) * s.size());

	// construct failure function
	while (begin + matched < s.size())
	{
		if (s[begin + matched] == s[matched])
		{
			matched++;
			f[begin + matched - 1] = matched;
		}
		else
		{
			if (matched == 0)
				++begin;
			else {
				begin = begin + matched - f[matched - 1];
				matched = f[matched - 1];
			}
		}
	}

	result.push_back(s.size());
	int k = f[s.size() - 1];
	while (k > 0)
	{
		result.push_back(k);
		k = f[k - 1];
	}
}